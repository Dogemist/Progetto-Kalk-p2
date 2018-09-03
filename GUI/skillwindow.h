#ifndef SKILLWINDOW_H
#define SKILLWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <SAUCE/c++/skill.h>
#include "addwindows.h"
#include "deletewindow.h"
#include "changewindow.h"


class skillWindow : public QWidget
{
    Q_OBJECT
public:
    explicit skillWindow(QWidget *parent = 0);

    QListWidget* Slist;

    void insertInSList();
    bool firstCheck();
    QMap<QString,Skill> storedS;
    QMap<QString,Hero> salvH;
    QMap<QString,BaseAttack> salvBA;
    QMap<QString,SummonedUnit> salvSum;
    QMap<QString,QVector<Skill> > salvHS;
    QMap<QString,QString> salvSB;


public slots:

    void changeKalkClicked();
    void addClicked();
    void clearClicked();
    void deleteClicked();
    void dpsClicked();
    void sumClicked();
    void diffClicked();
    void dptClicked();
    void hptClicked();
    void editClicked();

private slots:
    void onItemClicked(QListWidgetItem *item);
private:

    QPushButton* SchangeKalkButton;
    QLineEdit* SdisplayRes;
    QPushButton* SsumButton;
    QPushButton* SdiffButton;
    QPushButton* SdpsButton;
    QPushButton* ShitptButton;
    QPushButton* SdptButton;
    QPushButton* SaddButton;
    QPushButton* SclearButton;
    QPushButton* SdeleteButton;
    QPushButton* SeditButton;
    QLineEdit* displayS;
    QString name;
    Skill defS;
    Skill s;                //skill principale
    Skill sup;              //skill di supporto
    bool waitForOperand;    //bool di supporto per op binarie

    Mode addOedit;
};

#endif // SKILLWINDOW_H
