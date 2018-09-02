#ifndef ADDWINDOWS_H
#define ADDWINDOWS_H


#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextLine>
#include <QValidator>
#include <SAUCE/c++/skill.h>


class addWindowS : public QDialog
{
    Q_OBJECT

public:
    explicit addWindowS(QDialog *parent = nullptr);
    QString getName() const;
    QString getDanno() const;
    QString getMana() const;
    QString getAnim() const;
    QString getCd() const;
    QString getRange() const;
    double getProj() const;
    int getLv() const;


     void updateMode(Mode);
     void setName(QString) const;

signals:

public slots:
    void clearClicked();
    void addClicked();
private:
    QPushButton* confirmButtonS;
    QPushButton* clearButtonS;
    QLineEdit* nameLineS;
    QString nameText;
    QLineEdit* dannoLineS;
    QString dannoText;
    QLineEdit* manaLine;
    QString manaText;
    QLineEdit* cooldownLine;
    QString cooldownText;
    QLineEdit* animationLineS;
    QString animationText;
    QLineEdit* rangeLineS;
    QString rangeText;
    QLineEdit* projLineS;
    double projText;
    QLineEdit* levelLine;
    int levelText;

    QDoubleValidator* validAn;
    Mode addOedit;
};

#endif // ADDWINDOWS_H
