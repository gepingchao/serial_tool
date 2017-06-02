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

void serial_tool::tool_init()
{
    myHelper::SetsysCode();
    my_timer = new QTimer(this);
    G_config_file = new QFile(this);
    myReadTimer = new QTimer(this);
    myWriteTimer = new QTimer(this);
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

    G_config_file->setFileName("./config/config.txt");
    //load_config();
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
    ui->recv_buf->append(QString("time:%2 C>>%1 ").arg(str).arg(QTime::currentTime().toString("HH:mm:ss")));
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
    ui->recv_buf->append(QString(">>>%1 time:%2 ").arg(str).arg(QTime::currentTime().toString("HH:mm:ss")));
}

void serial_tool::ReadMyCom()
{
    QString tmpdata;
    //ui->recv_buf->append(QString("time:%1").arg(QTime::currentTime().toString("HH:mm:ss")));
    if(myCom->bytesAvailable()<=0){return;}
    myHelper::Sleep(30);
    QByteArray buffer = myCom->readAll();
    if(ui->hex_recv->isChecked())
    {
        tmpdata = myHelper::ByteArrayToHexStr(buffer);
    }
    else
    {
        tmpdata = QString(buffer);
    }
    ui->recv_buf->append(QString("<<<%1 time:%2").arg(tmpdata).arg(QTime::currentTime().toString("HH:mm:ss")));
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
