#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QIntValidator>
class timeWindow : public QDialog
{
    Q_OBJECT
public:
    explicit timeWindow(QDialog *parent = 0);
    QString getTime();


public slots:
    void timeClicked();


private:
    QPushButton* timeButton;
    QLineEdit* timeLine;
    QString timeText;

};

#endif // TIMEWINDOW_H
