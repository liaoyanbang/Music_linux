#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>
#include <qDebug>
#include <QString>
#include <QFile>
#include "music.h"
#include <QThread>
class SendFile : public QThread
{
public:
    void run(QString path);
signals:
    // 通知主线程发送文件进度百分比
    void curPercent(int num);
private:
    QTcpSocket file_tcp;
};


#endif // SENDFILE_H
