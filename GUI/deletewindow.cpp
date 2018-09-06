#include "deletewindow.h"


deleteWindow::deleteWindow(QDialog *parent) : QDialog(parent)
{
     setWindowModality(Qt::ApplicationModal);

    delRButton = new QPushButton(tr("Delete"));
    delLine = new QLineEdit;
    delText = "";
    QLabel* delLab = new QLabel(tr("Name"));

    connect(delRButton, SIGNAL(clicked()), this, SLOT(delRClicked()));

    QHBoxLayout* main = new QHBoxLayout;
    main->addWidget(delLab);
    main->addWidget(delLine);
    main->addWidget(delRButton);
    setLayout(main);
    setWindowTitle(tr("Delete voice"));

}


void deleteWindow::delRClicked(){
    QString text = delLine->text();

    if(text.isEmpty()){
        QMessageBox::information(this, tr("Error"), tr("Insert a name if you want delete it"));
        return;
    }
    else{
        int button = QMessageBox::question(this,tr("Delete"),tr("Are you sure"), QMessageBox::Yes,QMessageBox::No);
        if(button == QMessageBox::Yes){
            delText = text;
            delLine->clear();
            accept();
        }
        else{
            delLine->clear();
            return;
        }
    }
}

QString deleteWindow::getDelText() const {return delText;}
