#include "serial_tool.h"
#include "ui_serial_tool.h"
extern crc8 mycrc;
//extern Ui::serial_tool *ui;
#include "protocol.h"

extern unsigned char cur_reg;
void serial_tool::show_reg_value(QByteArray data)
{
    unsigned int recv_value = 0;
    unsigned char loopx = data.at(12);
    unsigned char step = 0;

    QByteArray tmp;
    tmp.resize(loopx);

    while(loopx --)
    {
        recv_value |= (unsigned char)data.at(13+step);
        if(loopx){recv_value = (recv_value<<8)&0XFFFFFFFF;}

        tmp[step] = data.at(13+step);
        step ++;
    }
    QString show_value = myHelper::ByteArrayToHexStr(tmp);

    switch(data.at(11))
    {
        case 0:
         ui->SYSCON_VALUE->setText(show_value);
         decode_syscon(recv_value);
        break;

    case 1:
     ui->EMUCON_VALUE->setText(show_value);
    break;

    case 2:
     ui->HFconst_VALUE->setText(show_value);
    break;

    case 3:
     ui->Pstart_VALUE->setText(show_value);
    break;

    case 5:
     ui->PAGain_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:A"){ui->adjust_p_gain_value_2->setText(show_value);}

    break;

    case 6:
     ui->PBGain_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:B"){ui->adjust_p_gain_value_2->setText(show_value);}
    break;

    case 7:
     ui->PhaseA_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:A"){ui->adjust_phase_value_2->setText(show_value);}
    break;

    case 8:
     ui->PhaseB_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:B"){ui->adjust_phase_value_2->setText(show_value);}
    break;

    case 0x0a:
     ui->PAOS_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:A"){ui->adjust_p_offset_value_2->setText(show_value);}
    break;

    case 0x0b:
     ui->PBOS_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:B"){ui->adjust_p_offset_value_2->setText(show_value);}
    break;

    case 0x0e:
     ui->RmsIAOS_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:A"){ui->adjust_p_rmsi_value_2->setText(show_value);}
    break;

    case 0x0f:
     ui->RmsIBOS_VALUE->setText(show_value);
     if(ui->cur_adjust_channel->text()=="当前校准通道:B"){ui->adjust_p_rmsi_value_2->setText(show_value);}
    break;

    case 0x10:
     ui->IBGain_VALUE->setText(show_value);
    break;

    case 0x11:
     ui->PSGain_VALUE->setText(show_value);
     ui->adjust_psgain_value_2->setText(show_value);
    break;

    case 0x12:
     ui->PSOS_VALUE->setText(show_value);
     ui->adjust_psos_value_2->setText(show_value);
    break;

    case 0x18:
     ui->SELCON_VALUE->setText(show_value);
    break;

    case 0x1e:
     ui->PFCnt_P_VALUE->setText(show_value);
    break;

    case 0x1f:
     ui->PFCnt_N_VALUE->setText(show_value);
    break;

    case 0x20:
     ui->PFCnt_VALUE->setText(show_value);
    break;

    case 0x22:
     ui->RmsIA_VALUE->setText(show_value);
    break;

    case 0x23:
     ui->RmsIB_VALUE->setText(show_value);
    break;

    case 0x24:
     ui->RmsU_VALUE->setText(show_value);
    break;

    case 0x25:
     ui->Ufreq_VALUE->setText(show_value);
    break;

    case 0x26:
     ui->POWERA_VALUE->setText(show_value);
    break;

    case 0x27:
     ui->POWERB_VALUE->setText(show_value);
    break;

    case 0x29:
     ui->E_P_VALUE->setText(show_value);
    break;

    case 0x2a:
     ui->E_P2_VALUE->setText(show_value);
    break;

    case 0x2d:
     ui->EMUStat_VALUE->setText(show_value);
     decode_emusatus(recv_value);
    break;

    case 0x2e:
     ui->PowerFa_VALUE->setText(show_value);
    break;

    case 0x30:
     ui->PowerS_VALUE->setText(show_value);
    break;

    case 0x34:
     ui->EP_P_VALUE->setText(show_value);
    break;

    case 0x35:
     ui->EP_N_VALUE->setText(show_value);
    break;

    case 0x38:
     ui->InstanIA_VALUE->setText(show_value);
    break;

    case 0x39:
     ui->InstanIB_VALUE->setText(show_value);
    break;

    case 0x3a:
     ui->InstanU_VALUE->setText(show_value);
    break;

    case 0x40:
     ui->IE_VALUE->setText(show_value);
    break;

    case 0x41:
     ui->IF_VALUE->setText(show_value);
    break;

    case 0x42:
     ui->RIF_VALUE->setText(show_value);
    break;

    case 0x43:
     ui->SysStat_VALUE->setText(show_value);
    break;

    case 0x44:
     ui->Rdata_VALUE->setText(show_value);
    break;

    case 0x45:
     ui->Wdata_VALUE->setText(show_value);
    break;

    case 0x7f:
     ui->DeviceID_VALUE->setText(show_value);
    break;


    }
}

void serial_tool::show_channel_status(QByteArray data)
{
    unsigned char status = data.at(11);
    if(status & 0X01)
    {
        ui->channel_a_status->setText("状态：开");
    }
    if(0 == (status & 0X01))
    {
        ui->channel_a_status->setText("状态：关");
    }

    if(status & 0X10)
    {
        ui->channel_b_status->setText("状态：开");
    }
    if(0 == (status & 0X10))
    {
        ui->channel_b_status->setText("状态：关");
    }
}

void serial_tool::decode_syscon(unsigned int syscon_value)
{
    if(syscon_value&0X40)
    {
        ui->adc_b_status->setText("状态：打开");
    }else{        
        ui->adc_b_status->setText("状态：关闭");
    }
}

void serial_tool::decode_emusatus(unsigned int emusatus_value)
{
    if(emusatus_value&0X200000)
    {
        ui->cur_adjust_channel->setText("当前校准通道:B");
        ui->label_PGAIN->setText("PBGain:");
        ui->label_POFFSET->setText("PBOS:");
        ui->label_PHAUSE->setText("HauseB:");
        ui->label_RMSI->setText("RmsIBOS:");
    }else{
        ui->cur_adjust_channel->setText("当前校准通道:A");
        ui->label_PGAIN->setText("PAGain:");
        ui->label_POFFSET->setText("PAOS:");
        ui->label_PHAUSE->setText("HauseA:");
        ui->label_RMSI->setText("RmsIAOS:");
    }
}




void serial_tool::deal_recv_data(QByteArray data)
{
    if(data.isEmpty())
    {
        return;
    }
    if((data.size()<30))
    {
        return;
    }
    if((data.at(8) == -123)&&(data.at(9) == 10))
    {
        switch(data.at(10))
        {
        case 2:
            show_reg_value(data);
            if(0x7f == data.at(11))
            {
                cur_reg = 0;
            }
            else
            {
                cur_reg = data.at(11)+1;
            }
            get_cse7790_reg_value(data.at(11)+1);
            break;

        case 3:
            show_reg_value(data);
            break;
        case 16:
            show_channel_status(data);
            break;
        }
    }
}


//msc指令规定长度
QByteArray serial_tool::creat_tcm300_msg(unsigned char master_command, unsigned char salve_command, unsigned char *data)
{
    unsigned char* tmp = data;
    QByteArray res;
    res.resize(33);
    res[0] = 0X55;
    res[1] = 0x00;
    res[2] = 0x14;
    res[3] = 0x06;
    res[4] = 0x01;
    mycrc.SetCRC8Sub((res.data()+1),4);
    res[6] = 0XD2;
    res[7] = 0X68;
    res[8] = master_command;
    res[9] = salve_command;
    res[10] = *(tmp++);
    res[11] = *(tmp++);
    res[12] = *(tmp++);
    res[13] = *(tmp++);
    res[14] = *(tmp++);
    res[15] = *(tmp++);
    res[16] = *(tmp++);
    res[17] = *(tmp++);
    res[18] = *(tmp++);
    res[19] = *(tmp++);
    res[20] = *(tmp++);
    res[21] = 0X88;
    res[22] = 0X88;
    res[23] = 0X88;
    res[24] = 0X88;
    res[25] = 0X00;
    res[26] = 0X03;
    res[27] = 0XFF;
    res[28] = 0XFF;
    res[29] = 0XFF;
    res[30] = 0XFF;
    res[31] = 0XFF;
    mycrc.SetCRC8Sub((res.data()+6),26);
    return res;
    //res[3] =
}

void serial_tool::tcm300_send_msg(const QByteArray msg)
{
    unsigned char data[11] = {1,2,3,4,5,6,7,8,9,0,1};
    myCom->write(creat_tcm300_msg(0x80,0x78,data));
}

void serial_tool::test_tcm300()
{
    unsigned char data[11] = {1,2,3,4,5,6,7,8,9,0,1};
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::enable_adc_b(bool value)
{
    unsigned char data[11] = {0};
    if(value)
    {
        data[0] = 0XC3;
    }else{
        data[0] = 0XC4;
    }
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}
void serial_tool::choose_channel_a(void)
{
    unsigned char data[11] = {0};
    data[0] = 0XC5;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::choose_channel_b(void)
{
    unsigned char data[11] = {0};
    data[0] = 0XC6;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::reset_device(void)
{
    unsigned char data[11] = {0};
    data[0] = 0XC7;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::get_cse7790_reg_value(unsigned char address)
{
    unsigned char data[11] = {0};
    data[0] = 0XA2;
    data[1] = address;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::get_one_cse7790_reg_value(unsigned char address)
{
    unsigned char data[11] = {0};
    data[0] = 0XA3;
    data[1] = address;
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}

void serial_tool::set_one_cse7790_reg_value(unsigned char address, QByteArray value)
{
    unsigned char loopx = value.size();
    unsigned char step = 3;
    unsigned char data[11] = {0};
    data[0] = 0XA4;
    data[1] = address;
    while(loopx--)
    {
        data[2+step] = value.at(loopx);
        step--;
    }
    QByteArray msg = creat_tcm300_msg(0x80,0x78,data);
    myCom->write(msg);
}


