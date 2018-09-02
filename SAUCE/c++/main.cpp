
#include <QApplication>
#include <iostream>
#include "skill.h"
#include <GUI/changewindow.h>
#include "baseattack.h"
#include "damage.h"
#include "pdamage.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
    changeWindow w;
    w.show();

    return a.exec();

}
