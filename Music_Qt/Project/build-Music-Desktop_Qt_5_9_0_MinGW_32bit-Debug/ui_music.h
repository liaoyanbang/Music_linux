/********************************************************************************
** Form generated from reading UI file 'music.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSIC_H
#define UI_MUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Music
{
public:
    QFrame *frame;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QPushButton *linkk;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QTextBrowser *music_list;
    QScrollBar *verticalScrollBar;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *voice_up;
    QSpacerItem *verticalSpacer_3;
    QPushButton *voice_dowm;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_2;
    QSlider *Voice_Slider;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *transportMusicFile;
    QHBoxLayout *horizontalLayout_3;
    QLabel *mode_lable;
    QPushButton *ModePush;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *cur_music;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *lastpushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *stoppushButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *nextpushButton;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout;
    QPushButton *Last_Pushbotton;
    QSpacerItem *horizontalSpacer;
    QPushButton *Star_pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *next_pushButton;
    QToolBox *link;
    QWidget *linkPage1_2;
    QLineEdit *my_addr;
    QLineEdit *my_port;
    QLabel *addr;
    QLabel *port;
    QPushButton *Link;
    QLabel *label;
    QPushButton *Back;
    QPushButton *Bind;
    QToolBox *transfile;
    QWidget *transportfile;
    QPushButton *selectfile;
    QProgressBar *progressfile;
    QPushButton *stop;
    QPushButton *quit;
    QPushButton *start;
    QPushButton *hide;
    QLineEdit *file_path;

    void setupUi(QWidget *Music)
    {
        if (Music->objectName().isEmpty())
            Music->setObjectName(QStringLiteral("Music"));
        Music->resize(998, 598);
        Music->setAutoFillBackground(true);
        frame = new QFrame(Music);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-40, -40, 1031, 611));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_3 = new QWidget(frame);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(100, 130, 731, 481));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_5 = new QLabel(verticalLayoutWidget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font;
        font.setPointSize(12);
        label_5->setFont(font);

        gridLayout_3->addWidget(label_5, 0, 2, 1, 1);

        linkk = new QPushButton(verticalLayoutWidget_3);
        linkk->setObjectName(QStringLiteral("linkk"));
        QFont font1;
        font1.setPointSize(14);
        linkk->setFont(font1);

        gridLayout_3->addWidget(linkk, 0, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(verticalLayoutWidget_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        verticalLayout_2->addWidget(label_4);

        music_list = new QTextBrowser(verticalLayoutWidget_3);
        music_list->setObjectName(QStringLiteral("music_list"));
        QFont font2;
        font2.setPointSize(11);
        music_list->setFont(font2);

        verticalLayout_2->addWidget(music_list);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalScrollBar = new QScrollBar(verticalLayoutWidget_3);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout_6->addWidget(verticalScrollBar);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        voice_up = new QPushButton(verticalLayoutWidget_3);
        voice_up->setObjectName(QStringLiteral("voice_up"));
        voice_up->setFont(font2);

        verticalLayout->addWidget(voice_up);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        voice_dowm = new QPushButton(verticalLayoutWidget_3);
        voice_dowm->setObjectName(QStringLiteral("voice_dowm"));
        voice_dowm->setFont(font2);

        verticalLayout->addWidget(voice_dowm);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        Voice_Slider = new QSlider(verticalLayoutWidget_3);
        Voice_Slider->setObjectName(QStringLiteral("Voice_Slider"));
        Voice_Slider->setOrientation(Qt::Vertical);

        horizontalLayout_4->addWidget(Voice_Slider);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        transportMusicFile = new QPushButton(verticalLayoutWidget_3);
        transportMusicFile->setObjectName(QStringLiteral("transportMusicFile"));
        transportMusicFile->setFont(font2);

        horizontalLayout_4->addWidget(transportMusicFile);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        mode_lable = new QLabel(verticalLayoutWidget_3);
        mode_lable->setObjectName(QStringLiteral("mode_lable"));
        mode_lable->setFont(font);

        horizontalLayout_3->addWidget(mode_lable);

        ModePush = new QPushButton(verticalLayoutWidget_3);
        ModePush->setObjectName(QStringLiteral("ModePush"));
        ModePush->setFont(font);

        horizontalLayout_3->addWidget(ModePush);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 6, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);

        horizontalLayout_5->addWidget(label_3);

        cur_music = new QLabel(verticalLayoutWidget_3);
        cur_music->setObjectName(QStringLiteral("cur_music"));
        QFont font3;
        font3.setPointSize(13);
        cur_music->setFont(font3);

        horizontalLayout_5->addWidget(cur_music);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 1, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lastpushButton = new QPushButton(verticalLayoutWidget_3);
        lastpushButton->setObjectName(QStringLiteral("lastpushButton"));
        lastpushButton->setFont(font2);

        horizontalLayout_2->addWidget(lastpushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        stoppushButton = new QPushButton(verticalLayoutWidget_3);
        stoppushButton->setObjectName(QStringLiteral("stoppushButton"));
        stoppushButton->setFont(font2);

        horizontalLayout_2->addWidget(stoppushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        nextpushButton = new QPushButton(verticalLayoutWidget_3);
        nextpushButton->setObjectName(QStringLiteral("nextpushButton"));
        nextpushButton->setFont(font2);

        horizontalLayout_2->addWidget(nextpushButton);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_8, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Last_Pushbotton = new QPushButton(verticalLayoutWidget_3);
        Last_Pushbotton->setObjectName(QStringLiteral("Last_Pushbotton"));
        Last_Pushbotton->setFont(font2);

        horizontalLayout->addWidget(Last_Pushbotton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Star_pushButton = new QPushButton(verticalLayoutWidget_3);
        Star_pushButton->setObjectName(QStringLiteral("Star_pushButton"));
        Star_pushButton->setFont(font2);

        horizontalLayout->addWidget(Star_pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        next_pushButton = new QPushButton(verticalLayoutWidget_3);
        next_pushButton->setObjectName(QStringLiteral("next_pushButton"));
        next_pushButton->setFont(font2);

        horizontalLayout->addWidget(next_pushButton);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout_6);

        link = new QToolBox(frame);
        link->setObjectName(QStringLiteral("link"));
        link->setGeometry(QRect(100, 100, 401, 341));
        linkPage1_2 = new QWidget();
        linkPage1_2->setObjectName(QStringLiteral("linkPage1_2"));
        linkPage1_2->setGeometry(QRect(0, 0, 401, 311));
        my_addr = new QLineEdit(linkPage1_2);
        my_addr->setObjectName(QStringLiteral("my_addr"));
        my_addr->setGeometry(QRect(130, 70, 161, 31));
        my_port = new QLineEdit(linkPage1_2);
        my_port->setObjectName(QStringLiteral("my_port"));
        my_port->setGeometry(QRect(130, 140, 161, 31));
        addr = new QLabel(linkPage1_2);
        addr->setObjectName(QStringLiteral("addr"));
        addr->setGeometry(QRect(80, 80, 51, 21));
        QFont font4;
        font4.setPointSize(10);
        addr->setFont(font4);
        port = new QLabel(linkPage1_2);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(80, 140, 51, 21));
        port->setFont(font2);
        Link = new QPushButton(linkPage1_2);
        Link->setObjectName(QStringLiteral("Link"));
        Link->setGeometry(QRect(30, 210, 81, 41));
        label = new QLabel(linkPage1_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 21, 201, 20));
        label->setFont(font2);
        Back = new QPushButton(linkPage1_2);
        Back->setObjectName(QStringLiteral("Back"));
        Back->setGeometry(QRect(260, 210, 81, 41));
        Bind = new QPushButton(linkPage1_2);
        Bind->setObjectName(QStringLiteral("Bind"));
        Bind->setGeometry(QRect(150, 210, 71, 41));
        link->addItem(linkPage1_2, QStringLiteral(""));
        transfile = new QToolBox(frame);
        transfile->setObjectName(QStringLiteral("transfile"));
        transfile->setGeometry(QRect(500, 100, 351, 321));
        transportfile = new QWidget();
        transportfile->setObjectName(QStringLiteral("transportfile"));
        transportfile->setGeometry(QRect(0, 0, 351, 291));
        selectfile = new QPushButton(transportfile);
        selectfile->setObjectName(QStringLiteral("selectfile"));
        selectfile->setGeometry(QRect(60, 20, 131, 41));
        selectfile->setFont(font2);
        progressfile = new QProgressBar(transportfile);
        progressfile->setObjectName(QStringLiteral("progressfile"));
        progressfile->setGeometry(QRect(20, 190, 321, 31));
        progressfile->setFont(font);
        progressfile->setValue(24);
        stop = new QPushButton(transportfile);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(60, 250, 93, 28));
        stop->setFont(font3);
        quit = new QPushButton(transportfile);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setGeometry(QRect(210, 250, 93, 28));
        quit->setFont(font3);
        start = new QPushButton(transportfile);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(20, 150, 131, 31));
        start->setFont(font3);
        hide = new QPushButton(transportfile);
        hide->setObjectName(QStringLiteral("hide"));
        hide->setGeometry(QRect(300, 0, 51, 31));
        hide->setFont(font2);
        file_path = new QLineEdit(transportfile);
        file_path->setObjectName(QStringLiteral("file_path"));
        file_path->setGeometry(QRect(10, 80, 331, 51));
        file_path->setFont(font2);
        transfile->addItem(transportfile, QStringLiteral(""));
        verticalLayoutWidget_3->raise();
        transfile->raise();
        link->raise();

        retranslateUi(Music);

        QMetaObject::connectSlotsByName(Music);
    } // setupUi

    void retranslateUi(QWidget *Music)
    {
        Music->setWindowTitle(QApplication::translate("Music", "Form", Q_NULLPTR));
        label_5->setText(QApplication::translate("Music", "\351\237\263\344\271\220\346\222\255\346\224\276\345\231\250", Q_NULLPTR));
        linkk->setText(QApplication::translate("Music", "\346\234\252\350\277\236\346\216\245", Q_NULLPTR));
        label_4->setText(QApplication::translate("Music", "\351\237\263\344\271\220\345\210\227\350\241\250", Q_NULLPTR));
        voice_up->setText(QApplication::translate("Music", "\351\237\263\351\207\217\345\242\236\345\212\240", Q_NULLPTR));
        voice_dowm->setText(QApplication::translate("Music", "\351\237\263\351\207\217\345\207\217\345\260\221", Q_NULLPTR));
        label_2->setText(QApplication::translate("Music", "\351\237\263\351\207\217\346\230\276\347\244\272\357\274\232", Q_NULLPTR));
        transportMusicFile->setText(QApplication::translate("Music", "\344\274\240\350\276\223\351\237\263\344\271\220\346\226\207\344\273\266", Q_NULLPTR));
        mode_lable->setText(QApplication::translate("Music", "\346\222\255\346\224\276\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        ModePush->setText(QApplication::translate("Music", "\351\232\217\346\234\272\346\222\255\346\224\276", Q_NULLPTR));
        label_3->setText(QApplication::translate("Music", "\345\275\223\345\211\215\346\222\255\346\224\276\357\274\232", Q_NULLPTR));
        cur_music->setText(QApplication::translate("Music", "\345\256\211\346\212\232\351\273\230\345\244\232\345\205\213\345\225\246.wav", Q_NULLPTR));
        lastpushButton->setText(QApplication::translate("Music", "\344\270\212\344\270\200\351\246\226", Q_NULLPTR));
        stoppushButton->setText(QApplication::translate("Music", "\346\232\202\345\201\234/\346\222\255\346\224\276", Q_NULLPTR));
        nextpushButton->setText(QApplication::translate("Music", "\344\270\213\344\270\200\351\246\226", Q_NULLPTR));
        Last_Pushbotton->setText(QApplication::translate("Music", "<<", Q_NULLPTR));
        Star_pushButton->setText(QApplication::translate("Music", "|>", Q_NULLPTR));
        next_pushButton->setText(QApplication::translate("Music", ">>", Q_NULLPTR));
        my_addr->setText(QApplication::translate("Music", "192.168.123.29", Q_NULLPTR));
        my_port->setText(QApplication::translate("Music", "8888", Q_NULLPTR));
        addr->setText(QApplication::translate("Music", "addr:", Q_NULLPTR));
        port->setText(QApplication::translate("Music", "port:", Q_NULLPTR));
        Link->setText(QApplication::translate("Music", "Link", Q_NULLPTR));
        label->setText(QApplication::translate("Music", "Link and Bind to Board", Q_NULLPTR));
        Back->setText(QApplication::translate("Music", "Back", Q_NULLPTR));
        Bind->setText(QApplication::translate("Music", "Bind", Q_NULLPTR));
        link->setItemText(link->indexOf(linkPage1_2), QString());
        selectfile->setText(QApplication::translate("Music", "\351\200\211\346\213\251\351\237\263\344\271\220\346\226\207\344\273\266", Q_NULLPTR));
        stop->setText(QApplication::translate("Music", "\345\201\234\346\255\242", Q_NULLPTR));
        quit->setText(QApplication::translate("Music", "\345\217\226\346\266\210", Q_NULLPTR));
        start->setText(QApplication::translate("Music", "\345\274\200\345\247\213\344\274\240\350\276\223", Q_NULLPTR));
        hide->setText(QApplication::translate("Music", "\351\232\220\350\227\217", Q_NULLPTR));
        transfile->setItemText(transfile->indexOf(transportfile), QString());
    } // retranslateUi

};

namespace Ui {
    class Music: public Ui_Music {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSIC_H
