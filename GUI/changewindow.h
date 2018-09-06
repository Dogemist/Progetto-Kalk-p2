#ifndef CHANGEWINDOW_H
#define CHANGEWINDOW_H

#include <QWidget>
#include <QDesktopWidget>
#include "herowindow.h"
#include "summonedwindow.h"
#include "basewindow.h"
#include "skillwindow.h"

class baseWindow;
class skillWindow;
class heroWindow;
class summonedWindow;

class changeWindow : public QWidget
{
    Q_OBJECT

public:

    explicit changeWindow(QWidget *parent = 0);
    QMap<QString,BaseAttack>savedB;
    QMap<QString,Skill>savedS;
    QMap<QString, SummonedUnit> savedSum;
    QMap<QString,QString> savedSB;
    void SaveMap(QMap<QString, BaseAttack>& , QMap<QString, Skill>&, QMap<QString, SummonedUnit> &, QMap<QString,QString>&);

signals:

public slots:
    void openBase();
    void openSummon();
    void openSkill();
    void openHero();

private:
   QPushButton* baseKalk;
   QPushButton* heroKalk;
   QPushButton* summonKalk;
   QPushButton* skillKalk;
   summonedWindow* suw;
   baseWindow* bw;
   skillWindow* sw;
   heroWindow* hw;
};

#endif // CHANGEWINDOW_H
