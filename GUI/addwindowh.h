#ifndef ADDWINDOWH_H
#define ADDWINDOWH_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include "herowindow.h"
#include "basewindow.h"
#include "skillwindow.h"

namespace Ui {
class addWindowH;
}

class addWindowH : public QDialog
{
   //friend class baseWindow;
   Q_OBJECT

public:
    explicit addWindowH(QWidget *parent = 0);
    ~addWindowH();

    void getMapBA() const;
    void getMapS() const;

    QMap<QString, Skill> showedS;
    QMap<QString, BaseAttack> showedBA;

    Hero getHero() const;
    QString getHeroBA()const;
    QString getHeroS1()const;
    QString getHeroS2()const;
    QString getHeroS3()const;
    QString getHeroS4()const;

    void updateMode(Mode);
    void setName(Hero) const;

private slots:

    void on_confirmButton_clicked();

    void on_clearBut_clicked();

private:
    Ui::addWindowH *ui;
    QString heroName;
    unsigned int heroStr;
    unsigned int heroAgl;
    unsigned int heroInt;
    unsigned int heroBaseHP;
    unsigned int heroBaseMP;
    unsigned int heroLevel;
    unsigned int heroBaseArmor;
    unsigned int heroMagRes;
    QString heroBA;
    QString heroS1;
    QString heroS2;
    QString heroS3;
    QString heroS4;

    Mode addOedit;
};

#endif // ADDWINDOWH_H
