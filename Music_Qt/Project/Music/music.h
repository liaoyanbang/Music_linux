#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QTcpSocket>
#include <qDebug>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QThread>


namespace Ui {
class Music;
}

class Music : public QWidget
{
    Q_OBJECT

public:
    explicit Music(QWidget *parent = 0);
    ~Music();
    void setaddrport(QString Addr,int Port);
    void bind_operation(void);
    void send_cmd(QString cmd);
    void closeEvent(QCloseEvent *event);
    void Init_file_Socket(void);
    void send_file_info(void);
    void send_data(void);

signals:

private slots:
    void onReadReady();
    void onConnected();
    void onDisconnected();

    void onReadReady_file();
    void onConnected_file();
    void onDisconnected_file();
    void onError(QAbstractSocket::SocketError socketError);

    void setLineEditValue(int value);

    void on_linkk_clicked();

    void on_next_pushButton_clicked();

    void on_nextpushButton_clicked();

    void on_Star_pushButton_clicked();

    void on_stoppushButton_clicked();

    void on_lastpushButton_clicked();

    void on_Last_Pushbotton_clicked();

    void on_Link_clicked();

    void on_Bind_clicked();

    void on_Back_clicked();

    void on_ModePush_clicked();

    void timeout_slot();

    void on_voice_up_clicked();

    void on_voice_dowm_clicked();

    void on_transportMusicFile_clicked();

    void on_hide_clicked();

    void on_selectfile_clicked();
    
    void on_start_clicked();

private:
    Ui::Music *ui;
    QString addr;
    int port;
    int file_port;
    QTimer timer;
    QTimer send_timer;
    // 状态
    bool tcp_flag = 0;
    bool bind_flag = 0;
    bool start_flag = 0;
    bool suspend_flag = 0;
    bool file_flag = 0;
    bool stop_flag = 0;
    bool cansend = 0;
    int mode = 0;

    QTcpSocket tcpSocket;
    QTcpSocket file_Socket;

    QString File_Name;
    qint64 File_Size;
    qint64 Send_Size;
    QFile file;

};


#endif // MUSIC_H
