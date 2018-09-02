#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

namespace Ui {
class deleteWindow;
}

class deleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit deleteWindow(QDialog *parent = 0);
    QString getDelText() const;

public slots:

    void delRClicked();

private:
    QPushButton* delRButton;
    QLineEdit* delLine;
    QString delText;

};

#endif // DELETEWINDOW_H
