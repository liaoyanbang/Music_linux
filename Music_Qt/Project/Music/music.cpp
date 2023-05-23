#include "music.h"
#include "ui_music.h"


Music::Music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Music)
{
    this->bind_flag = 0;
    this->tcp_flag = 0;
    this->start_flag = 0;
    this->suspend_flag = 0;
    this->stop_flag = 0;

    this->addr = "192.168.123.62";
    this->file_port = 8080;

    ui->setupUi(this);
    ui->link->hide();
    ui->transfile->hide();
    ui->Voice_Slider->setMinimum(0);// 设置滑动条的最小值
    ui->Voice_Slider->setMaximum(100);// 设置滑动条的最大值
    ui->Voice_Slider->setValue(50); // 设置滑动条初始值

    ui->progressfile->setRange(0,100);
    ui->progressfile->setValue(0);


    // 当发送sendFile信号，让worker的sendFile函数处理（子线程）

    connect(ui->Voice_Slider, SIGNAL(valueChanged(int)), this, SLOT(setLineEditValue(int)));

    connect(&tcpSocket,SIGNAL(readyRead()),this,SLOT(onReadReady()));
    connect(&tcpSocket,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(&tcpSocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(&tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError(QAbstractSocket::SocketError)));
    /*connect(&tcpSocket, &QTcpSocket::error, this, [=](){
        qDebug() << tcpSocket.error();
        qDebug() << tcpSocket.errorString();
    });*/

    connect(&file_Socket,SIGNAL(readyRead()),this,SLOT(onReadReady_file()));
    connect(&file_Socket,SIGNAL(connected()),this,SLOT(onConnected_file()));
    connect(&file_Socket,SIGNAL(disconnected()),this,SLOT(onDisconnected_file()));
    connect(&file_Socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError(QAbstractSocket::SocketError)));

    connect(&timer, &QTimer::timeout, this, &Music::timeout_slot);
    connect(&send_timer,&QTimer::timeout,this,[=]{
        send_timer.stop();
        send_data();
    });



}

Music::~Music()
{
    delete ui;
}

void Music::setLineEditValue(int value)
{
    int voice_int = this->ui->Voice_Slider->value();
    QString voice_string = QString("%1").arg(voice_int);
//    QJsonObject obj;
//    obj.insert("cmd", "app_voice_set");
//    obj.insert("voice",voice_string);

//    //QJsonOBject转换成QBYteArray
//    QByteArray ba = QJsonDocument(obj).toJson();
//    this->tcpSocket.write(ba);
}
void Music::timeout_slot()
{
    send_cmd("app_music");
    this->timer.stop();
}

void Music::setaddrport(QString Addr, int Port)
{
    this->addr = Addr;
    this->port = Port;

    qDebug()<<Addr<<this->addr<<endl;
    qDebug()<<Port<<this->port<<endl;
}


void Music::onReadReady()
{
    QString cmd;
    QJsonObject json_object;
    QByteArray data = this->tcpSocket.readAll();
    qDebug()<<"readReady";
    qDebug()<<"read"<<data;

    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(data, &json_error);

    if (json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "parse json error " << json_error.error << endl;
        return ;
    }

    if( json_doc.isObject() )
    {
        json_object = json_doc.object();
        if(json_object.contains("cmd"))
        {
            //QJsonValue Qdata= json_object["cmd"];
            QString QStringdata= json_object["cmd"].toString();
            if( 0 == QStringdata.toInt() )   // 返回成功
            {
                cmd = QStringdata;
            }
        }
    }
    qDebug()<<"cmd:"<<cmd<<endl;
    if("reply_bind"==cmd && this->bind_flag==0)
    {
         QString result = json_object["result"].toString();
         if ("yes"==result)                 //已经绑定
         {
                 qDebug() << "已经绑定";
                 bind_flag = 1;
                 this->ui->link->hide();
                 //启动定时器，3秒后发送获取所有音乐的请求
                 this->timer.start(6000);
         }
         else if ("no"==result)
         {
                  qDebug() << "未绑定";
                  bind_flag = 0;
                  //绑定
                  bind_operation();
          }
    }
    else if(this->bind_flag==1)
    {
        if(cmd=="app_reply")
        {
            QString result = json_object["result"].toString();
            if (result == "start_success")  //开始播放成功
            {
                  ui->Star_pushButton->setText("||");
                  ui->stoppushButton->setText("开始播放");
                  this->start_flag = 1;
            }
            else if (result == "suspend_success")   //暂停成功
            {
                  ui->Star_pushButton->setText("|>");
                  ui->stoppushButton->setText("继续播放");
                  this->suspend_flag = 1;
            }
            else if (result == "continue_success")
            {
                  ui->Star_pushButton->setText("||");
                  ui->stoppushButton->setText("暂停播放");
                  this->suspend_flag = 0;
            }
            else if (result == "off_line")
            {
                  QMessageBox::warning(this, "操作提示", "音箱下线");
            }
        }
        else if (cmd == "app_reply_status")        //播放器状态的回复
        {

            //播放状态、歌曲名、音量
             QString status = json_object["status"].toString();
             if(status=="start")
             {
                 start_flag = 1;
                 stop_flag = 0;
                 suspend_flag = 0;
             }
             else if(status=="suspend")
             {
                 suspend_flag = 1;
             }
             else if(status == "stop")
             {
                 stop_flag = 1;
                 start_flag = 0;
                 suspend_flag = 0;
             }
             QString music_name = json_object["music"].toString();
             ui->cur_music->setText(music_name);

             int lavel = json_object["voice"].toInt();
             ui->Voice_Slider->setValue(lavel);
        }
        else if(cmd == "app_reply_music")//所有音乐的回复 get music
        {
            qDebug()<<"get some music:"<<endl;
            if( json_object.contains("music") )
            {
                 QJsonValue arrays_value = json_object.take("music");
                 if (arrays_value.isArray()) // 判断他是不是json数组
                 {
                     //QTextCodec *codec = QTextCodec::codecForName("UTF-8");   // 使用UTF-8格式
                     QString desStr = "";
                     QJsonArray MusicArray = arrays_value.toArray();
                     for(int i =0;i<MusicArray.size();i++)
                     {
                         QJsonValue MusicArrayValue = MusicArray.at(i);
                         if (MusicArrayValue.isObject())
                         {
                             QJsonObject json_object_2 = MusicArrayValue.toObject();
                             if(json_object_2.contains("name"))
                             {
                                  desStr.append(json_object_2["name"].toString());
                                  desStr.append("\n");
                             }
                         }
                     }
                     qDebug()<<desStr<<endl;
                     this->ui->music_list->setText(desStr);
                 }
            }
        }
           /* QJsonArray arr = obj.value("music").toArray();  //转换成json数组
            QString result;
            for (int i = 0; i < arr.count(); i++)
            {
                qDebug()<<arr.at(i).toString()<<endl;//没有
                result.append(arr.at(i).toString());
                result.append('\n');
            }
            qDebug()<<result<<endl;
            this->ui->music_list->setText(result);*/

    }
}

void Music::bind_operation()
{
    QString app_id = "100";
    QString dev_id = "001";
    \

    QJsonObject obj;
    obj.insert("cmd", "bind");
    obj.insert("appid", app_id);
    obj.insert("deviceid", dev_id);

    //QJsonOBject转换成QBYteArray
    QByteArray ba = QJsonDocument(obj).toJson();
    this->tcpSocket.write(ba);
}

void Music::onConnected()
{
    qDebug()<<"connected";
    ui->linkk->setText("断开");
    //ui->link->hide();
    tcp_flag = 1;
}

void Music::onDisconnected()
{
    ui->linkk->setText("连接");
    qDebug()<<"disconnected";
    tcp_flag = 0;
}

void Music::onReadReady_file()
{
    qint64 Code;
    QJsonObject json_object;
    double_t process;
    QByteArray data = this->file_Socket.readLine();
    qDebug()<<"readReady";
    qDebug()<<"read"<<data;

    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(data, &json_error);
    if (json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "parse json error " << json_error.error << endl;
        return ;
    }

    if( json_doc.isObject() )
    {
        json_object = json_doc.object();
        if(json_object.contains("Code"))
        {
            //QJsonValue Qdata= json_object["cmd"];
            qint64 Qintdata= json_object["Code"].toInt();
            Code = Qintdata;
            if(json_object.contains("Data"))
            {
                 process = json_object["Data"].toDouble();
            }
        }
    }
    qDebug()<<"Code:"<<Code<<endl;

    if(Code==111) // exist
    {
        //cansend = 0;
        QMessageBox * mBox = new QMessageBox(this);
        mBox->setWindowTitle(QString("文件已存在"));
        mBox->setText(QString("是否进行覆盖？"));
        mBox->setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
        mBox->setButtonText(QMessageBox::StandardButton::Ok, QString("确定"));
        mBox->setButtonText(QMessageBox::StandardButton::Cancel, QString("取消"));
        mBox->exec();
        QMessageBox::StandardButton ret = mBox->standardButton(mBox->clickedButton());
        switch (ret)
        {
        case QMessageBox::NoButton:
            qDebug() << QString("没有选择").toStdString().c_str();
            break;
        case QMessageBox::Ok:
            qDebug() << QString("确定").toStdString().c_str();
            this->file_Socket.write("yes\n");
            break;
        case QMessageBox::Cancel:
            qDebug() << QString("取消").toStdString().c_str();
            this->file_Socket.write("no\n");
            break;
        default:
            break;
        }
        if (mBox != nullptr)
        {
            delete mBox;
            mBox = nullptr;
        }


    }
    else if(Code==200) // ok
    {
        cansend = 1;
    }
    else if(Code==500)
    {
        qDebug()<<"服务器寄了"<<endl;
    }
    else if(Code==403)
    {

    }
    else if(Code==201)
    {
        //qDebug()<< process;
        ui->progressfile->setValue(process);
        if(process>=100)
        {
            ui->file_path->setText("文件传输完毕！");
            ui->selectfile->setEnabled(true);
        }

    }



}

void Music::onConnected_file()
{
    qDebug()<<"文件连接成功"<<endl;
    file_flag = 1;
}

void Music::onDisconnected_file()
{
    qDebug()<<"文件连接断开"<<endl;
    file_flag = 0;
}

void Music::onError(QAbstractSocket::SocketError socketError)
{
    qDebug()<<"error"<<socketError;
}

void Music::on_linkk_clicked()
{
    if(tcp_flag==0)
    {
        ui->link->show();
    }
    else
    {
        tcpSocket.disconnectFromHost();
    }

}
void Music::on_next_pushButton_clicked()
{
    if(start_flag==1&&suspend_flag==0)
    {
        send_cmd("app_next");
        qDebug()<<"next"<<endl;
    }


}
void Music::on_Star_pushButton_clicked()
{
    if(start_flag==0)
        send_cmd("app_start");
    else if(start_flag==1&&suspend_flag==1)
        send_cmd("app_continue");
    else if(start_flag==1&&suspend_flag==0)
        send_cmd("app_suspend");

}

void Music::on_stoppushButton_clicked()
{
    if(start_flag==0)
        send_cmd("app_start");
    else if(start_flag==1&&suspend_flag==1)
        send_cmd("app_continue");
    else if(start_flag==1&&suspend_flag==0)
        send_cmd("app_suspend");
}

void Music::on_lastpushButton_clicked()
{
    if(start_flag==1&&suspend_flag==0)
    {
        send_cmd("app_last");
        qDebug()<<"last"<<endl;
    }
}

void Music::on_Last_Pushbotton_clicked()
{
    if(start_flag==1&&suspend_flag==0)
    {
        send_cmd("app_last");
        qDebug()<<"last"<<endl;
    }
}


void Music::send_cmd(QString cmd)
{
    QJsonObject obj;
    obj.insert("cmd", cmd);

    QByteArray mes = QJsonDocument(obj).toJson();
    this->tcpSocket.write(mes);
}

void Music::on_nextpushButton_clicked()
{
    if(start_flag==1&&suspend_flag==0)
    {
        send_cmd("app_next");
        qDebug()<<"next"<<endl;
    }

}

void Music::on_Link_clicked()
{
    this->setaddrport(ui->my_addr->text(),ui->my_port->text().toInt());
    tcpSocket.connectToHost(this->addr,this->port);
}

void Music::on_Bind_clicked()
{
    QString app_id = "100";
    QJsonObject obj;
    obj.insert("cmd", "search_bind");
    obj.insert("appid", app_id);
    //向服务器发送数据，查询是否已经绑定
    QByteArray mes = QJsonDocument(obj).toJson();
    this->tcpSocket.write(mes);
}

void Music::on_Back_clicked()
{
    ui->link->hide();
}

void Music::on_ModePush_clicked()
{
    mode++;
    if(mode>2) mode = 0;
    switch (mode) {
    case 0:
    {
        qDebug()<<"0"<<endl;
        send_cmd("app_random");
        this->ui->ModePush->setText("随机播放");
        break;
    }
    case 1:
    {
        qDebug()<<"1"<<endl;
        send_cmd("app_circle");
        this->ui->ModePush->setText("单曲循环");
        break;
    }
    case 2:
    {
        qDebug()<<"2"<<endl;
        send_cmd("app_sequence");
        this->ui->ModePush->setText("顺序播放");
        break;
    }
    default:
        break;
    }
}
void Music::closeEvent(QCloseEvent *event)
{
    send_cmd("app_off_line");
    event->accept();
}

void Music::Init_file_Socket()
{
    if(tcp_flag==0 && bind_flag ==0 && file_flag==0)
    {
        this->file_Socket.abort();
        this->file_Socket.connectToHost(this->addr,this->file_port);
    }
    else if(file_flag==1)
    {
        qDebug()<<"继续传输"<<endl;
    }
    else
    {
        QMessageBox::warning(this,"错误提示","请先进行连接绑定！");
    }
}

void Music::send_file_info()
{
    //先发送文件信息
    QJsonObject obj;
    obj.insert("cmd", "sendfile");
    obj.insert("name", this->File_Name);

    QString str = QString::number(this->File_Size);


    obj.insert("size", this->File_Size);
    QByteArray mes = QJsonDocument(obj).toJson();
    int m = mes.count();
    for(int i=0;i<m;i++)
    {
        if(mes[i] =='\n')
        {
            mes[i] = ' ';
        }
    }
    mes.append("\n");
    qDebug()<<mes;
    qint64 len = this->file_Socket.write(mes);

    if(len>0)//发送文件信息成功
    {
        qDebug()<<"发送文件信息成功"<<endl;
    }
    else
    {
        qDebug()<<"文件信息发送失败"<<endl;
    }
}

void Music::on_voice_up_clicked()
{
    send_cmd("app_voice_up");
}

void Music::on_voice_dowm_clicked()
{
    send_cmd("app_vo_dowm");
}


void Music::on_transportMusicFile_clicked()
{
    ui->transfile->show();
}

void Music::on_hide_clicked()
{
    ui->transfile->hide();
}

void Music::on_selectfile_clicked()
{
    QString filePath =QFileDialog::getOpenFileName(this,"打开文件","/");
    if(filePath.isEmpty()==false)
    {
        QFileInfo info(filePath);

        this->File_Name = info.fileName();
        this->File_Size = info.size();
        qDebug()<<this->File_Name<<this->File_Size<<endl;
        this->Send_Size = 0;

        Init_file_Socket();

        ui->file_path->setText(filePath);

        send_file_info();
        file.setFileName(ui->file_path->text());
        bool isok = file.open(QIODevice::ReadOnly);
        if(isok == false)
        {
            qDebug()<<"文件打开失败"<<endl;
        }


    }
    else
    {
        ui->start->setEnabled(false);
        qDebug()<<"文件路径选择失败";
        this->file_Socket.disconnectFromHost();
        this->file_flag = 0;
        this->file_Socket.close();
    }
    
}

void Music::on_start_clicked()
{
    if(file_flag ==1 && cansend == 1)
    {
        ui->selectfile->setEnabled(false);
        send_timer.start(20);
    }
    else
    {
        qDebug()<<"文件连接失败";
    }

}

void Music::send_data()
{
    qint64 len = 0;
    QByteArray mess;
    QJsonObject obj;
    QByteArray mes;
    int memery_count = 0;
    do
    {
        mess = file.read(1024);//获取文件分片
        memery_count++;
        obj.insert("size", mess.count());//获取文件分片大小
        mes = QJsonDocument(obj).toJson();
        int m = mes.count();
        for(int i=0;i<m;i++)
        {
            if(mes[i] =='\n')
            {
                mes[i] = ' ';
            }
        }
        mes.append("\n");
        qDebug()<<mes;
        this->file_Socket.write(mes);
        //先发送块大小  后发送内容
        //qDebug()<<mess;
        len = this->file_Socket.write(mess);
        Send_Size+=len;

    }while(len>0);
    qDebug()<<"分片数目："<<memery_count<<endl;
}

