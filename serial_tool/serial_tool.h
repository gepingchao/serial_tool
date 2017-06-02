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

private:
    void tool_init();
    void load_config();
    void get_cmd_info(QString cmd_name);
private:
    QTimer *my_timer;
    QFile *G_config_file;
    QextSerialPort *myCom;
    QTimer *myReadTimer;
    QTimer *myWriteTimer;
    cmd *mycmd;


private:
    Ui::serial_tool *ui;
};

#endif // SERIAL_TOOL_H
