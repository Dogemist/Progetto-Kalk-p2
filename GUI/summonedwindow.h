#ifndef SUMMONEDWINDOW_H
#define SUMMONEDWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <SAUCE/c++/summonedunit.h>
#include "addwindowsum.h"
#include "deletewindow.h"
#include "timewindow.h"
#include "changewindow.h"

namespace Ui {
class summonedWindow;
}

class summonedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit summonedWindow(QWidget *parent = 0);
    ~summonedWindow();
    QMap<QString,SummonedUnit> storedSummoned;
    QMap<QString,BaseAttack> passedBA;
    QMap<QString,Skill> salvS;
    QMap<QString,Hero> salvH;
    QMap<QString,QVector<Skill> > salvHS;
    QMap<QString,QString> storedSB;

    void insertInSumListWidget();
    bool firstCheck(char);

private slots:
    void on_addButton_clicked();

    void on_select1Button_clicked();

    void on_select2Button_clicked();
    void onSUMItemClicked(QListWidgetItem*);
    void on_editButton_clicked();

    void on_fightButton_clicked();

    void on_removeButton_clicked();

    void on_changeKalkHero_clicked();

    void on_dpsButton_clicked();
    void on_dpsButton_2_clicked();

    void on_dbtButton_clicked();

    void on_dbtButton2_clicked();

    void on_clearButton_clicked();

private:
    Ui::summonedWindow *ui;
    SummonedUnit su;
    SummonedUnit def;
    SummonedUnit selected1;
    SummonedUnit selected2;
    QString nameA;
    QString bas;
};

#endif // SUMMONEDWINDOW_H
