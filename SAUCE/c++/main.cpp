#include <QApplication>
#include <GUI/changewindow.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
    changeWindow w;
    w.show();

    return a.exec();

}
