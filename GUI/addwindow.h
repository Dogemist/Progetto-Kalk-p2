#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextLine>
#include <QValidator>

#include <SAUCE/c++/baseattack.h>


class addWindow : public QDialog
{
    Q_OBJECT
public:
    explicit addWindow(QDialog *parent = nullptr);
    QString getName() const;
    QString getDanno() const;
    QString getAnim() const;
    QString getRange() const;
    QString getProj() const;
    void setValues(QString, BaseAttack) const;

    void updateMode(Mode);

signals:

public slots:
    void clearClicked();
    void addClicked();
private:
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QLineEdit* nameLine;
    QString nameText;
    QLineEdit* dannoLine;
    QString dannoText;
    QLineEdit* animationLine;
    QString animationText;
    QLineEdit* rangeLine;
    QString rangeText;
    QLineEdit* projLine;
    QString projText;

    QDoubleValidator* valid;

    Mode addOedit;
};

#endif // ADDWINDOW_H
