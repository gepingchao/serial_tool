#include "serial_tool.h"
#include "ui_serial_tool.h"

serial_tool::serial_tool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serial_tool)
{
    ui->setupUi(this);
    this->tool_init();
}

serial_tool::~serial_tool()
{
    delete ui;
}
crc8 mycrc;
unsigned char cur_reg = 0;
void serial_tool::tool_init()
{
    myHelper::SetsysCode();
    my_timer = new QTimer(this);
    G_config_file = new QFile(this);
    myReadTimer = new QTimer(this);
    myWriteTimer = new QTimer(this);
    callTimer = new QTimer(this);
    mycmd = new cmd(this);

    QStringList baudList;
    QStringList comList;
    QStringList parityList;
    QStringList stopBitsList;
    QStringList DataBitList;

    comList<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"
          <<"COM7"<<"COM8"<<"COM9"<<"COM10"<<"COM11"<<"COM12"
         <<"COM13"<<"COM14"<<"COM15"<<"COM16"<<"COM17"<<"COM18";

    baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
           <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
          <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
         <<"76800"<<"115200"<<"128000"<<"256000";

    stopBitsList<<"1"<<"1.5"<<"2";
    DataBitList<<"5"<<"6"<<"7"<<"8";
    parityList<<"none"<<"odd"<<"even";

    ui->comList->addItems(comList);
    ui->comList->setCurrentIndex(2);

    ui->baudList->addItems(baudList);
    ui->baudList->setCurrentIndex(17);

    ui->parity->addItems(parityList);
    ui->parity->setCurrentIndex(0);

    ui->stop->addItems(stopBitsList);
    ui->stop->setCurrentIndex(0);

    ui->data_list->addItems(DataBitList);
    ui->data_list->setCurrentIndex(3);

    myReadTimer = new QTimer(this);
    myReadTimer->setInterval(10);
    connect(myReadTimer,SIGNAL(timeout()),this,SLOT(ReadMyCom()));

    connect(callTimer,SIGNAL(timeout()),this,SLOT(calltimer_callback()));

    G_config_file->setFileName("./config/config.txt");
    //load_config();

    QRegExp double_rx100("100|([0-9]{0,2}[\.][0-9]{1,3})");
    //QRegExp double_rx10000("10000|([0-9]{0,4}[\.][0-9]{1,3})");
    //QRegExp double_rx10("10|([0-9]{0,1}[\.][0-9]{1,3})");
    ui->adjust_p_gain_value->setValidator(new QRegExpValidator(double_rx100, ui->adjust_p_gain_value));
    ui->adjust_p_offset_value->setValidator(new QRegExpValidator(double_rx100, ui->adjust_p_offset_value));
    ui->adjust_phase_value->setValidator(new QRegExpValidator(double_rx100, ui->adjust_phase_value));

}


















void serial_tool::send_cmd()
{
    QByteArray outData;
    int size;
    QString str = ui->cmd_info->text();
    if(str ==""){ui->cmd_info->setFocus();return;}
    if(!myCom->isOpen()){return;}
    if(ui->hex_send->isChecked())
    {
        outData = myHelper::HexStrToByteArray(str);
        size = outData.size();
    }
    else
    {
        outData = str.toAscii();
        size = outData.size();
    }
    myCom->write(outData);
    ui->recv_buf->append(QString("C>  %1     time:%2").arg(str).arg(QTime::currentTime().toString("HH:mm:ss")));
}

void serial_tool::WriteMyCom()
{
    QByteArray outData;
    int size;
    QString str = ui->send_buf->text();
    if(str ==""){ui->send_buf->setFocus();return;}
    if(!myCom->isOpen()){return;}
    if(ui->hex_send->isChecked())
    {
        outData = myHelper::HexStrToByteArray(str);
        size = outData.size();
    }
    else
    {
        outData = str.toAscii();
        size = outData.size();
    }
    myCom->write(outData);
    ui->recv_buf->append(QString(">>  %1     time:%2").arg(str).arg(QTime::currentTime().toString("HH:mm:ss")));
}

void serial_tool::ReadMyCom()
{
    QString tmpdata;
    //ui->recv_buf->append(QString("time:%1").arg(QTime::currentTime().toString("HH:mm:ss")));
    if(myCom->bytesAvailable()<=0){return;}
    myHelper::Sleep(30);
    QByteArray buffer = myCom->readAll();

    deal_recv_data(buffer);

    if(ui->hex_recv->isChecked())
    {
        tmpdata = myHelper::ByteArrayToHexStr(buffer);
    }
    else
    {
        tmpdata = QString(buffer);
    }
    ui->recv_buf->append(QString("<<  %1     time:%2").arg(tmpdata).arg(QTime::currentTime().toString("HH:mm:ss")));
}



void serial_tool::on_Button_open_clicked()
{
    if(ui->Button_open->text() == "OPEN")
    {
        QString portName = ui->comList->currentText();
        myCom = new QextSerialPort(portName);
        if(myCom->open(QIODevice::ReadWrite))
            {
            //清空缓冲区
            myCom->flush();
            //设置波特率
            myCom->setBaudRate((BaudRateType)ui->baudList->currentText().toInt());
            //设置数据位
            myCom->setDataBits((DataBitsType)ui->data_list->currentText().toInt());
            //设置校验位
            myCom->setParity((ParityType)ui->parity->currentIndex());
            //设置停止位
            myCom->setStopBits((StopBitsType)ui->stop->currentIndex());
            myCom->setFlowControl(FLOW_OFF);
            myCom->setTimeout(3);

            //this->ChangeEnable(true);
            ui->Button_open->setText("CLOSE");
           // ui->labIsOpen->setText("串口状态：打开");
            this->myReadTimer->start();
            }
    }
    else
    {
        myCom->close();
        this->myReadTimer->stop();
        ui->Button_open->setText("OPEN");
        ui->recv_buf->setText("");
    }
}

void serial_tool::on_clear_clicked()
{

    ui->recv_buf->setText("");
}

void serial_tool::on_sendButton_clicked()
{
    //test_tcm300();
    this->WriteMyCom();
}

void serial_tool::on_pushButton_clicked()
{
    this->load_config();
}

void serial_tool::on_send_cmd_clicked()
{
    this->send_cmd();
}

void serial_tool::on_cmd_list_currentIndexChanged(const QString &arg1)
{
    this->get_cmd_info(arg1);
}

void serial_tool::on_GET_SYSCON_clicked()
{
    get_one_cse7790_reg_value(0);
}

void serial_tool::on_GET_EMUCON_clicked()
{
    get_one_cse7790_reg_value(1);
}

void serial_tool::on_GET_DeviceID_clicked()
{
    get_one_cse7790_reg_value(0X7F);
}


void serial_tool::calltimer_callback()
{
    static unsigned loopx;
    get_cse7790_reg_value(loopx);
    if(0x46 == loopx)
    {
        loopx = 0;
        callTimer->stop();
        get_cse7790_reg_value(0x7f);
    }
    else
    {
        loopx ++;
    }
}
void serial_tool::on_get_all_value_clicked()
{
    get_cse7790_reg_value(cur_reg);
}

void serial_tool::on_GET_PAGain_clicked()
{
    get_one_cse7790_reg_value(5);
}
void serial_tool::on_GET_PAOS_clicked()
{
    get_one_cse7790_reg_value(0x0a);
}
void serial_tool::on_GET_RmsIAOS_clicked()
{
    get_one_cse7790_reg_value(0x0e);
}



void serial_tool::on_GET_SELCON_clicked()
{
    get_one_cse7790_reg_value(0x18);
}

void serial_tool::on_GET_PFCnt_P_clicked()
{
    get_one_cse7790_reg_value(0x1e);
}

void serial_tool::on_GET_SYSCON_26_clicked()
{
    get_one_cse7790_reg_value(0x22);
}

void serial_tool::on_GET_E_P_clicked()
{
    get_one_cse7790_reg_value(0x29);
}

void serial_tool::on_GET_EMUStat_clicked()
{
    get_one_cse7790_reg_value(0x2d);
}

void serial_tool::on_GET_PowerS_clicked()
{
    get_one_cse7790_reg_value(0x30);
}

void serial_tool::on_GET_IBGain_clicked()
{
    get_one_cse7790_reg_value(0x10);
}

void serial_tool::on_clear_data_clicked()
{
    cur_reg =0;
    QString show_value = "";
    ui->SYSCON_VALUE->setText(show_value);
    ui->EMUCON_VALUE->setText(show_value);
    ui->HFconst_VALUE->setText(show_value);
    ui->Pstart_VALUE->setText(show_value);
    ui->PAGain_VALUE->setText(show_value);
    ui->PBGain_VALUE->setText(show_value);
    ui->PhaseA_VALUE->setText(show_value);
    ui->PhaseB_VALUE->setText(show_value);
    ui->PAOS_VALUE->setText(show_value);
    ui->PBOS_VALUE->setText(show_value);
    ui->RmsIAOS_VALUE->setText(show_value);
    ui->RmsIBOS_VALUE->setText(show_value);
    ui->IBGain_VALUE->setText(show_value);
    ui->PSGain_VALUE->setText(show_value);
    ui->PSOS_VALUE->setText(show_value);
    ui->SELCON_VALUE->setText(show_value);
    ui->PFCnt_P_VALUE->setText(show_value);
    ui->PFCnt_N_VALUE->setText(show_value);
    ui->PFCnt_VALUE->setText(show_value);
    ui->RmsIA_VALUE->setText(show_value);
    ui->RmsIB_VALUE->setText(show_value);
    ui->RmsU_VALUE->setText(show_value);
    ui->Ufreq_VALUE->setText(show_value);
    ui->POWERA_VALUE->setText(show_value);
    ui->POWERB_VALUE->setText(show_value);
    ui->E_P_VALUE->setText(show_value);
    ui->E_P2_VALUE->setText(show_value);
    ui->EMUStat_VALUE->setText(show_value);
    ui->PowerFa_VALUE->setText(show_value);
    ui->PowerS_VALUE->setText(show_value);
    ui->EP_P_VALUE->setText(show_value);
    ui->EP_N_VALUE->setText(show_value);
    ui->InstanIA_VALUE->setText(show_value);
    ui->InstanIB_VALUE->setText(show_value);
    ui->InstanU_VALUE->setText(show_value);
    ui->IE_VALUE->setText(show_value);
    ui->IF_VALUE->setText(show_value);
    ui->RIF_VALUE->setText(show_value);
    ui->SysStat_VALUE->setText(show_value);
    ui->Rdata_VALUE->setText(show_value);
    ui->Wdata_VALUE->setText(show_value);
    ui->DeviceID_VALUE->setText(show_value);
}

void serial_tool::on_rest_device_clicked()
{
    reset_device();
}

void serial_tool::on_GET_HFconst_clicked()
{
    get_one_cse7790_reg_value(0x2);
}

void serial_tool::on_GET_Pstart_clicked()
{
    get_one_cse7790_reg_value(0x3);
}

void serial_tool::on_GET_PBGain_clicked()
{
    get_one_cse7790_reg_value(0x6);
}

void serial_tool::on_GET_PhaseA_clicked()
{
    get_one_cse7790_reg_value(0x7);
}

void serial_tool::on_GET_PhaseB_clicked()
{
    get_one_cse7790_reg_value(0x8);
}

void serial_tool::on_GET_PBOS_clicked()
{
    get_one_cse7790_reg_value(0xB);
}

void serial_tool::on_GET_RmsIBOS_clicked()
{
    get_one_cse7790_reg_value(0xF);
}

void serial_tool::on_GET_PSGain_clicked()
{
    get_one_cse7790_reg_value(0x11);
}

void serial_tool::on_GET_PSOS_clicked()
{
    get_one_cse7790_reg_value(0x12);
}

void serial_tool::on_GET_PFCnt_N_clicked()
{
    get_one_cse7790_reg_value(0x1F);
}

void serial_tool::on_GET_PFCnt_clicked()
{
    get_one_cse7790_reg_value(0x20);
}

void serial_tool::on_GET_RmsIB_clicked()
{
    get_one_cse7790_reg_value(0x23);
}

void serial_tool::on_GET_RmsU_clicked()
{
    get_one_cse7790_reg_value(0x24);
}

void serial_tool::on_GET_Ufreq_clicked()
{
    get_one_cse7790_reg_value(0x25);
}

void serial_tool::on_GET_POWERA_clicked()
{
    get_one_cse7790_reg_value(0x26);
}

void serial_tool::on_GET_POWERB_clicked()
{
    get_one_cse7790_reg_value(0x27);
}

void serial_tool::on_GET_E_P2_clicked()
{
    get_one_cse7790_reg_value(0x2A);
}

void serial_tool::on_GET_PowerFa_clicked()
{
    get_one_cse7790_reg_value(0x2E);
}

void serial_tool::on_GET_EP_P_clicked()
{
    get_one_cse7790_reg_value(0x34);
}

void serial_tool::on_GET_EP_N_clicked()
{
    get_one_cse7790_reg_value(0x35);
}

void serial_tool::on_GET_InstanIA_clicked()
{
    get_one_cse7790_reg_value(0x38);
}

void serial_tool::on_GET_InstanIB_clicked()
{
    get_one_cse7790_reg_value(0x39);
}

void serial_tool::on_GET_InstanU_clicked()
{
    get_one_cse7790_reg_value(0x3A);
}

void serial_tool::on_GET_IE_clicked()
{
    get_one_cse7790_reg_value(0x40);
}

void serial_tool::on_GET_IF_clicked()
{
    get_one_cse7790_reg_value(0x41);
}

void serial_tool::on_GET_RIF_clicked()
{
    get_one_cse7790_reg_value(0x42);
}

void serial_tool::on_GET_SysStat_clicked()
{
    get_one_cse7790_reg_value(0x43);
}

void serial_tool::on_GET_Rdata_clicked()
{
    get_one_cse7790_reg_value(0x44);
}

void serial_tool::on_GET_Wdata_clicked()
{
    get_one_cse7790_reg_value(0x45);
}

void serial_tool::on_open_close_serial_clicked()
{
    on_Button_open_clicked();
    ui->open_close_serial->setText(ui->Button_open->text());
}

void serial_tool::on_pushButton_2_clicked()
{
    ui->adjust_p_gain_value_2->setText("");
    ui->adjust_p_gain_value->setText("");
    ui->adjust_p_offset_value_2->setText("");
    ui->adjust_p_offset_value->setText("");
    ui->adjust_phase_value_2->setText("");
    ui->adjust_phase_value->setText("");
    ui->adjust_p_rmsi_value_2->setText("");
    ui->adjust_psgain_value_2->setText("");
    ui->adjust_psos_value_2->setText("");
    if(ui->cur_adjust_channel->text() == "当前校准通道:A")
    {
        //enable_adc_b(true);
        choose_channel_b();
    }else{
        //enable_adc_b(false);
        choose_channel_a();
    }
}

void serial_tool::on_adjust_p_gain_clicked()
{
    float err;
    unsigned char int_value;
    unsigned short dec_value;
    unsigned char data[11] = {0};
    err = (ui->adjust_p_gain_value->text()).toFloat();
    if(err)
    {
        int_value = (unsigned char)err;
        dec_value = ((unsigned short)(err*1000))%1000;
        if(ui->cur_adjust_channel->text() == "当前校准通道:A")
        {
            data[0]=0XB0;
        }else{
            data[0]=0XB6;
        }
        data[1] = int_value;
        data[2] = (dec_value>>8)&0XFF;
        data[3] = (dec_value>>0)&0XFF;
        if(ui->flag_adjust_p_gain_value->isChecked())
        {
            data[1]|=0X80;
        }


        QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
        myCom->write(msg);
    }else{
        return;
    }
}

void serial_tool::on_adjust_p_offset_clicked()
{
    float err;
    unsigned char int_value;
    unsigned short dec_value;
    unsigned char data[11] = {0};
    err = (ui->adjust_p_offset_value->text()).toFloat();
    if(err)
    {
        int_value = (unsigned char)err;
        dec_value = ((unsigned short)(err*1000))%1000;
        if(ui->cur_adjust_channel->text() == "当前校准通道:A")
        {
            data[0]=0XB1;
        }else{
            data[0]=0XB7;
        }
        data[1] = int_value;
        data[2] = (dec_value>>8)&0XFF;
        data[3] = (dec_value>>0)&0XFF;
        if(ui->flag_adjust_p_offset_value->isChecked())
        {
            data[1]|=0X80;
        }

        QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
        myCom->write(msg);
    }else{
        return;
    }
}

void serial_tool::on_adjust_phase_clicked()
{
    float err;
    unsigned char int_value;
    unsigned short dec_value;
    unsigned char data[11] = {0};
    err = (ui->adjust_phase_value->text()).toFloat();
    if(err)
    {
        int_value = (unsigned char)err;
        dec_value = ((unsigned short)(err*1000))%1000;
        if(ui->cur_adjust_channel->text() == "当前校准通道:A")
        {
            data[0]=0XB2;
        }else{
            data[0]=0XB8;
        }
        data[1] = int_value;
        data[2] = (dec_value>>8)&0XFF;
        data[3] = (dec_value>>0)&0XFF;
        if(ui->flag_adjust_phase_value->isChecked())
        {
            data[1]|=0X80;
        }

        QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
        myCom->write(msg);
    }else{
        return;
    }
}

void serial_tool::on_SET_HFconst_clicked()
{
    QByteArray value;
    value = myHelper::HexStrToByteArray(ui->HFconst_VALUE->text());
    set_one_cse7790_reg_value(2,value);
}

void serial_tool::on_adjust_p_rmsi_clicked()
{
    unsigned char data[11] = {0};
    if(ui->cur_adjust_channel->text() == "当前校准通道:A")
    {
        data[0]=0XB3;
    }else{
        data[0]=0XB9;
    }

    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::on_adjust_psgain_clicked()
{
    unsigned char data[11] = {0};
    data[0]=0XBC;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::on_adjust_psos_clicked()
{
    unsigned char data[11] = {0};
    data[0]=0XBD;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::on_channel_a_switch_clicked()
{
    unsigned char data[11] = {0};
    data[0]=0XC0;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::on_channel_b_switch_clicked()
{
    unsigned char data[11] = {0};
    data[0]=0XC1;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::on_enable_adc_b_switch_clicked()
{
    if(ui->adc_b_status->text() == "状态：关闭")
    {
        enable_adc_b(true);
    }else{
        enable_adc_b(false);
    }
}
