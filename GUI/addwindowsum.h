#ifndef ADDWINDOWSUM_H
#define ADDWINDOWSUM_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include "summonedwindow.h"


class addWindowSum : public QDialog
{
    Q_OBJECT

public:
    explicit addWindowSum(QWidget *parent = nullptr);
    ~addWindowSum();

    void insertBA();
    QString getName() const;
    int getHp() const;
    int getLv() const;
    QString getBa() const;
    QMap<QString, BaseAttack> usedBA;

    void updateMode(Mode);
    void setValues(SummonedUnit) const;

private slots:
    void onAddClicked();
    void onClearClicked();

private:
    QLineEdit* nameLine;
    QLineEdit* hpLine;
    QLineEdit* levelLine;
    QComboBox* baseAttackBox;
    QPushButton* confirmButton;
    QPushButton* clearButton;
    QString name;
    int hp;
    int lv;
    QString ba;

    Mode addOedit;
};

#endif // ADDWINDOWSUM_H
