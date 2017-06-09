#ifndef SERIAL_TOOL_H
#define SERIAL_TOOL_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include "qextserialport.h"
#include <QFile>
#include "cmd.h"
#include "myhelper.h"
#include <QLatin1String>
#include "crc.h"
#include <QThread>
#include <QRegExp>
#include <QRegExpValidator>

namespace Ui {
class serial_tool;
}

class serial_tool : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit serial_tool(QWidget *parent = 0);
    ~serial_tool();
private slots:

    void on_Button_open_clicked();

    void send_cmd();
    void WriteMyCom();
    void ReadMyCom();

    void on_clear_clicked();

    void on_sendButton_clicked();

    void on_pushButton_clicked();

    void on_send_cmd_clicked();

    void on_cmd_list_currentIndexChanged(const QString &arg1);

    void on_GET_SYSCON_clicked();

    void on_GET_EMUCON_clicked();

    void on_GET_DeviceID_clicked();

    void on_get_all_value_clicked();


    void calltimer_callback();
    void on_GET_PAGain_clicked();

    void on_GET_RmsIAOS_clicked();

    void on_GET_PAOS_clicked();

    void on_GET_SELCON_clicked();

    void on_GET_PFCnt_P_clicked();

    void on_GET_SYSCON_26_clicked();

    void on_GET_E_P_clicked();

    void on_GET_EMUStat_clicked();

    void on_GET_PowerS_clicked();

    void on_GET_IBGain_clicked();

    void on_clear_data_clicked();

    void on_rest_device_clicked();

    void on_GET_HFconst_clicked();

    void on_GET_Pstart_clicked();

    void on_GET_PBGain_clicked();

    void on_GET_PhaseA_clicked();

    void on_GET_PhaseB_clicked();

    void on_GET_PBOS_clicked();

    void on_GET_RmsIBOS_clicked();

    void on_GET_PSGain_clicked();

    void on_GET_PSOS_clicked();

    void on_GET_PFCnt_N_clicked();

    void on_GET_PFCnt_clicked();

    void on_GET_RmsIB_clicked();

    void on_GET_RmsU_clicked();

    void on_GET_Ufreq_clicked();

    void on_GET_POWERA_clicked();

    void on_GET_POWERB_clicked();

    void on_GET_E_P2_clicked();

    void on_GET_PowerFa_clicked();

    void on_GET_EP_P_clicked();

    void on_GET_EP_N_clicked();

    void on_GET_InstanIA_clicked();

    void on_GET_InstanIB_clicked();

    void on_GET_InstanU_clicked();

    void on_GET_IE_clicked();

    void on_GET_IF_clicked();

    void on_GET_RIF_clicked();

    void on_GET_SysStat_clicked();

    void on_GET_Rdata_clicked();

    void on_GET_Wdata_clicked();

    void on_open_close_serial_clicked();

    void on_pushButton_2_clicked();

    void on_adjust_p_gain_clicked();

    void on_adjust_p_offset_clicked();

    void on_adjust_phase_clicked();

    void on_SET_HFconst_clicked();

    void on_adjust_p_rmsi_clicked();

    void on_adjust_psgain_clicked();

    void on_adjust_psos_clicked();

    void on_channel_a_switch_clicked();

    void on_channel_b_switch_clicked();

    void on_enable_adc_b_switch_clicked();

private:
    void tool_init();
    void load_config();
    void get_cmd_info(QString cmd_name);

    void deal_recv_data(QByteArray data);
    void show_reg_value(QByteArray data);
    void show_channel_status(QByteArray data);

    void decode_syscon(unsigned int syscon_value);
    void decode_emusatus(unsigned int emusatus_value);


    QByteArray creat_tcm300_msg(unsigned char master_command,unsigned char salve_command,unsigned char* data);
    void test_tcm300();
    void tcm300_send_msg(const QByteArray msg);

    void get_cse7790_reg_value(unsigned char address);
    void get_one_cse7790_reg_value(unsigned char address);
    void set_one_cse7790_reg_value(unsigned char address,QByteArray value);


    void enable_adc_b(bool value);
    void choose_channel_a(void);
    void choose_channel_b(void);
    void reset_device(void);
private:
    QTimer *my_timer;
    QFile *G_config_file;
    QextSerialPort *myCom;
    QTimer *myReadTimer;
    QTimer *myWriteTimer;

    QTimer *callTimer;

    cmd *mycmd;


private:
    Ui::serial_tool *ui;
};

#endif // SERIAL_TOOL_H
