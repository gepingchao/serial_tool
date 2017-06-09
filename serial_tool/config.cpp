#include "serial_tool.h"
#include "ui_serial_tool.h"

void serial_tool::get_cmd_info(QString cmd_name)
{
    char buf[2048] = {0};
    QString data;
    QString cmd_list;
    QString cmd_info;

    if(!G_config_file->isOpen())
    {
        G_config_file->open(QIODevice::ReadOnly|QIODevice::Text);
    }
    G_config_file->seek(0);
    while(1)
    {
        G_config_file->readLine(buf,sizeof(buf));
        data = QString(buf);
        if(data == "end")
            {
                break;
            }
        cmd_list = data.split(":")[0];
        if(cmd_name == cmd_list)
            {
            cmd_info = data.split(":")[1];
            cmd_info = cmd_info.split('\n')[0];
            ui->cmd_info->setText(cmd_info);
            break;
            }
     }
}

void serial_tool::load_config()
{
    G_config_file->close();
    char buf[2048] = {0};
    QString data;
    QString cmd_list;
    G_config_file->open(QIODevice::ReadOnly|QIODevice::Text);
    while(1)
    {
        if(!G_config_file->isOpen()){G_config_file->open(QIODevice::ReadOnly|QIODevice::Text);continue;}
        G_config_file->readLine(buf,sizeof(buf));
        data = QString(buf);
        if(data == "end")
            {
                G_config_file->close();
                break;
            }
        cmd_list = data.split(":")[0];
        ui->cmd_list->addItem(cmd_list);
        ui->cmd_info->setText(data.split(":")[1]);
    }
    ui->cmd_list->setCurrentIndex(ui->cmd_list->count()-1);



    if(G_config_file->exists())
    {
        myHelper::ShowMessageBoxInfo("已载入配置文件");
    }else{
        myHelper::ShowMessageBoxInfo("未找到配置文件");
    }
}
