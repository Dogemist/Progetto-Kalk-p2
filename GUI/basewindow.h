#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <SAUCE/c++/baseattack.h>
#include "timewindow.h"
#include "addwindow.h"
#include "deletewindow.h"
#include "changewindow.h"


class baseWindow : public QWidget
{
    friend class addWindowH;
    Q_OBJECT
public:
    explicit baseWindow(QWidget *parent = 0);
    ~baseWindow();
    bool firstCheck();
    void insertInBList();
    QListWidget* Blist;
    QMap<QString,BaseAttack> storedBA;
    QMap<QString,Hero> salvH;
    QMap<QString,Skill> salvS;            //mi tocca portarla qua altrimenti se fai
    QMap<QString,SummonedUnit> salvSum;   //skill->change->base->change->skill la lista viene persa
    QMap<QString,QVector<Skill> >salvHS;
    QMap<QString,QString> salvSB;
public slots:

    void changeKalkClicked();
    void addClicked();
    void clearClicked();
    void deleteClicked();
    void dpsClicked();
    void hptClicked();
    void dptClicked();
    void sumClicked();
    void diffClicked();
    void editClicked();

private slots:
    void onItemClicked(QListWidgetItem *item);

private:

    QPushButton* BchangeKalkButton;
    QLineEdit* BdisplayRes;
    QPushButton* BsumButton;
    QPushButton* BdiffButton;
    QPushButton* BdpsButton;
    QPushButton* BhitptButton;
    QPushButton* BdptButton;
    QPushButton* BaddButton;
    QPushButton* BclearButton;
    QPushButton* BdeleteButton;
    QPushButton* BeditButton;
    QLineEdit* displayBA;
    QString name;
    BaseAttack ba;          //BaseAttack principale
    BaseAttack sup;         //supporto per operazioni binarie
    BaseAttack def;
    bool waitForOperand;    //supporto per operazioni binarie
    bool check;
};

#endif // BASEWINDOW_H
