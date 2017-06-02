/********************************************************************************
** Form generated from reading UI file 'serial_tool.ui'
**
** Created: Fri Jun 2 15:30:27 2017
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIAL_TOOL_H
#define UI_SERIAL_TOOL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serial_tool
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QComboBox *comList;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QComboBox *baudList;
    QHBoxLayout *horizontalLayout_9;
    QLabel *data_2;
    QComboBox *data_list;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QComboBox *stop;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QComboBox *parity;
    QCheckBox *hex_recv;
    QCheckBox *hex_send;
    QPushButton *Button_open;
    QSpacerItem *verticalSpacer_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *recv_buf;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *clear;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *send_buf;
    QPushButton *sendButton;
    QHBoxLayout *horizontalLayout;
    QComboBox *cmd_list;
    QLineEdit *cmd_info;
    QPushButton *send_cmd;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *serial_tool)
    {
        if (serial_tool->objectName().isEmpty())
            serial_tool->setObjectName(QString::fromUtf8("serial_tool"));
        serial_tool->resize(900, 600);
        serial_tool->setMinimumSize(QSize(900, 600));
        centralWidget = new QWidget(serial_tool);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 128, 432));
        verticalLayout_6 = new QVBoxLayout(layoutWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        comList = new QComboBox(layoutWidget);
        comList->setObjectName(QString::fromUtf8("comList"));
        comList->setEnabled(true);
        comList->setMinimumSize(QSize(80, 20));
        comList->setMaximumSize(QSize(80, 20));

        horizontalLayout_6->addWidget(comList);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_8->addWidget(label_6);

        baudList = new QComboBox(layoutWidget);
        baudList->setObjectName(QString::fromUtf8("baudList"));
        baudList->setMinimumSize(QSize(80, 20));
        baudList->setMaximumSize(QSize(80, 20));

        horizontalLayout_8->addWidget(baudList);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        data_2 = new QLabel(layoutWidget);
        data_2->setObjectName(QString::fromUtf8("data_2"));

        horizontalLayout_9->addWidget(data_2);

        data_list = new QComboBox(layoutWidget);
        data_list->setObjectName(QString::fromUtf8("data_list"));
        data_list->setMinimumSize(QSize(80, 20));
        data_list->setMaximumSize(QSize(80, 20));

        horizontalLayout_9->addWidget(data_list);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_10->addWidget(label_7);

        stop = new QComboBox(layoutWidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setMinimumSize(QSize(80, 20));
        stop->setMaximumSize(QSize(80, 20));

        horizontalLayout_10->addWidget(stop);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_11->addWidget(label_8);

        parity = new QComboBox(layoutWidget);
        parity->setObjectName(QString::fromUtf8("parity"));
        parity->setMinimumSize(QSize(80, 20));
        parity->setMaximumSize(QSize(80, 20));

        horizontalLayout_11->addWidget(parity);


        verticalLayout_7->addLayout(horizontalLayout_11);


        verticalLayout_6->addLayout(verticalLayout_7);

        hex_recv = new QCheckBox(layoutWidget);
        hex_recv->setObjectName(QString::fromUtf8("hex_recv"));
        hex_recv->setChecked(true);

        verticalLayout_6->addWidget(hex_recv);

        hex_send = new QCheckBox(layoutWidget);
        hex_send->setObjectName(QString::fromUtf8("hex_send"));
        hex_send->setChecked(true);

        verticalLayout_6->addWidget(hex_send);

        Button_open = new QPushButton(layoutWidget);
        Button_open->setObjectName(QString::fromUtf8("Button_open"));
        Button_open->setMinimumSize(QSize(100, 30));
        Button_open->setMaximumSize(QSize(140, 30));

        verticalLayout_6->addWidget(Button_open);

        verticalSpacer_2 = new QSpacerItem(20, 208, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(180, 13, 711, 411));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        recv_buf = new QTextEdit(layoutWidget1);
        recv_buf->setObjectName(QString::fromUtf8("recv_buf"));
        recv_buf->setMinimumSize(QSize(350, 250));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        recv_buf->setFont(font);
        recv_buf->setAutoFillBackground(true);
        recv_buf->setReadOnly(true);

        verticalLayout_2->addWidget(recv_buf);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(80, 30));
        pushButton->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton);

        clear = new QPushButton(layoutWidget1);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setMinimumSize(QSize(80, 30));
        clear->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(clear);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        send_buf = new QLineEdit(layoutWidget1);
        send_buf->setObjectName(QString::fromUtf8("send_buf"));
        send_buf->setMinimumSize(QSize(300, 30));
        send_buf->setMaximumSize(QSize(300000, 30));

        horizontalLayout_2->addWidget(send_buf);

        sendButton = new QPushButton(layoutWidget1);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setMinimumSize(QSize(75, 30));
        sendButton->setMaximumSize(QSize(75, 40));

        horizontalLayout_2->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmd_list = new QComboBox(layoutWidget1);
        cmd_list->setObjectName(QString::fromUtf8("cmd_list"));
        cmd_list->setMinimumSize(QSize(120, 30));

        horizontalLayout->addWidget(cmd_list);

        cmd_info = new QLineEdit(layoutWidget1);
        cmd_info->setObjectName(QString::fromUtf8("cmd_info"));
        cmd_info->setEnabled(false);
        cmd_info->setMinimumSize(QSize(300, 30));
        cmd_info->setMaximumSize(QSize(300000, 30));

        horizontalLayout->addWidget(cmd_info);

        send_cmd = new QPushButton(layoutWidget1);
        send_cmd->setObjectName(QString::fromUtf8("send_cmd"));
        send_cmd->setMinimumSize(QSize(75, 25));
        send_cmd->setMaximumSize(QSize(75, 40));

        horizontalLayout->addWidget(send_cmd);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        serial_tool->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(serial_tool);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 23));
        serial_tool->setMenuBar(menuBar);
        mainToolBar = new QToolBar(serial_tool);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        serial_tool->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(serial_tool);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        serial_tool->setStatusBar(statusBar);

        retranslateUi(serial_tool);

        QMetaObject::connectSlotsByName(serial_tool);
    } // setupUi

    void retranslateUi(QMainWindow *serial_tool)
    {
        serial_tool->setWindowTitle(QApplication::translate("serial_tool", "serial_tool", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("serial_tool", "\344\270\262\345\217\243", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("serial_tool", "\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        data_2->setText(QApplication::translate("serial_tool", "\346\225\260\346\215\256\344\275\215", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("serial_tool", "\345\201\234\346\255\242\344\275\215", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("serial_tool", "\346\240\241\351\252\214\344\275\215", 0, QApplication::UnicodeUTF8));
        hex_recv->setText(QApplication::translate("serial_tool", "\345\215\201\345\205\255\350\277\233\345\210\266\346\216\245\346\224\266", 0, QApplication::UnicodeUTF8));
        hex_send->setText(QApplication::translate("serial_tool", "\345\215\201\345\205\255\350\277\233\345\210\266\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        Button_open->setText(QApplication::translate("serial_tool", "OPEN", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("serial_tool", "\345\210\267\346\226\260\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        clear->setText(QApplication::translate("serial_tool", "\346\270\205\351\231\244\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("serial_tool", "send", 0, QApplication::UnicodeUTF8));
        send_cmd->setText(QApplication::translate("serial_tool", "ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serial_tool: public Ui_serial_tool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIAL_TOOL_H
