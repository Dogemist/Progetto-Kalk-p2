#ifndef HEROWINDOW_H
#define HEROWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopWidget>
#include <SOURCE/c++/hero.h>
#include "summonedwindow.h"
#include "changewindow.h"
#include "addwindowh.h"
#include "timewindow.h"
#include "deletewindow.h"

namespace Ui {
class heroWindow;
}


class heroWindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit heroWindow(QWidget *parent = 0);
    ~heroWindow();

    QMap<QString, Hero> storedHeroes;
    QMap<QString, Skill> salvS;
    QMap<QString, BaseAttack> salvBA;
    QMap<QString, SummonedUnit> salvSum;
    QMap<QString,QString> salvSB;
    QMap<QString,QVector<Skill> >Hspell;

    void insertInQListWidget();
    bool firstCheck(char);
private slots:

    void on_changeKalkHero_clicked();   //tutti slot definiti
    void on_addButton_clicked();
    void onHItemClicked(QListWidgetItem *item);
    void on_selectHero1_clicked();
    void on_clearButton_clicked();
    void on_selectHero2_clicked();
    void on_dpsH1But_clicked();
    void on_htpH1But_clicked();
    void on_dptH1But_clicked();
    void on_dpsH2But_clicked();
    void on_htpH1But_2_clicked();
    void on_dptH2But_clicked();
    void on_editButton_clicked();
    void on_fightButton_clicked();
    void on_deleteButton_clicked();

    void on_powButton1_clicked();

    void on_powBut2_clicked();

private:

    Hero h;
    Hero selected1;
    Hero selected2;
    Hero def;
    QVector<Skill> spell;
    QString name;
    Skill s1Stored;
    Skill s2Stored;
    Skill s3Stored;
    Skill s4Stored;
    Ui::heroWindow *ui;
    BaseAttack bas;
};

#endif // HEROWINDOW_H
