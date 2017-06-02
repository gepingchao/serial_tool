#ifndef CMD_H
#define CMD_H

#include <QObject>

class cmd : public QObject
{
    Q_OBJECT
public:
    explicit cmd(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CMD_H
