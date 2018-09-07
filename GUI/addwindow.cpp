#include "addwindow.h"

addWindow::addWindow(QDialog *parent) : QDialog(parent)
{
    setWindowModality(Qt::ApplicationModal);

    QLabel* nameLabel = new QLabel(tr("Name"));
    QLabel* dannoLabel = new QLabel(tr("Damage"));
    QLabel* animationLabel = new QLabel(tr("Animation"));
    QLabel* rangeLabel = new QLabel(tr("Range"));
    QLabel* projLabel = new QLabel(tr("Projectile Speed"));
    valid = new QDoubleValidator(1,10,2);
    valid->setNotation(QDoubleValidator::StandardNotation);

    validPP = new QDoubleValidator(1,9999,2);
    valid->setNotation(QDoubleValidator::StandardNotation);

    nameLine = new QLineEdit;
    dannoLine = new QLineEdit;
    dannoLine->setValidator(new QIntValidator(0,999,this));
    dannoLine->setText(tr("1"));
    animationLine = new QLineEdit;
    animationLine->setValidator(new QDoubleValidator(0,999,2,this));
    animationLine->setText(tr("1"));
    rangeLine = new QLineEdit;
    rangeLine->setValidator(new QIntValidator(0,9999,this));
    rangeLine->setText(tr("1"));
    projLine = new QLineEdit;
    projLine->setValidator(validPP);
    projLine->setText(tr("1"));

    confirmButton = new QPushButton();
    cancelButton= new QPushButton(tr("Close"));

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(confirmButton, SIGNAL(clicked()),this, SLOT(addClicked()));

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameLine);
    mainLayout->addWidget(dannoLabel);
    mainLayout->addWidget(dannoLine);
    mainLayout->addWidget(animationLabel);
    mainLayout->addWidget(animationLine);
    mainLayout->addWidget(rangeLabel);
    mainLayout->addWidget(rangeLine);
    mainLayout->addWidget(projLabel);
    mainLayout->addWidget(projLine);
    mainLayout->addWidget(confirmButton);
    mainLayout->addWidget(cancelButton);
    setLayout(mainLayout);

}

void addWindow::addClicked(){

    if(nameLine->text() == ""  || dannoLine->text() == "" || animationLine->text() == "" ||
            rangeLine->text() == "" || projLine->text() == ""){
        QMessageBox::information(this,tr("Warning"),tr("All fields need to be filled")); //messaggio di errore
        return;
    }
    else{
        if(addOedit == add)
            nameText = nameLine->text();    //assegna alla string il contenuto della LineEdit

        dannoText = dannoLine->text();
        animationText = animationLine->text();
        rangeText = rangeLine->text();
        projText = projLine->text();
        accept();                       //invia un segnale di accepted
    }

}


void addWindow::clearClicked(){
    close();
}

void addWindow::updateMode(Mode up){
    addOedit = up;

    switch(addOedit){
    case add:
        nameLine->setReadOnly(false);
        confirmButton->setText(tr("Add"));
        setWindowTitle("Add a BaseAttack");
        break;

    case edit:
        nameLine->setReadOnly(true);
        confirmButton->setText(tr("Edit"));
        setWindowTitle("Edit a BaseAttack");
        break;
    }
}

void addWindow::setValues(QString setted,BaseAttack ba) const{
    nameLine->setText(setted);
    dannoLine->setText(QString::number(ba.getValue()));
    animationLine->setText(QString::number(ba.getAnim()));
    rangeLine->setText(QString::number(ba.getRange()));
    projLine->setText(QString::number(ba.getPP()));
}

QString addWindow::getName() const {return nameText;}   //funzioni get per la classe chiamante
QString addWindow::getDanno() const{return dannoText;}
QString addWindow::getAnim() const{return animationText;}
QString addWindow::getRange() const{return rangeText;}
QString addWindow::getProj() const{return projText;}
