#include <QApplication>
#include "music.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Music music;

    music.show();
    return a.exec();
}
