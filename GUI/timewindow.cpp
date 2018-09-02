#include "timewindow.h"

timeWindow::timeWindow(QDialog *parent) : QDialog(parent)
{
    setWindowTitle("Set Time");

    QLabel* timeLabel = new QLabel(tr("Insert time (seconds)"));
    timeButton = new QPushButton(tr("Insert"));
    timeLine = new QLineEdit;
    timeLine->setFixedSize(50,30);
    timeLine->setValidator(new QIntValidator(0,9999,this));
    timeText = "";

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(timeLabel);
    mainLayout->addWidget(timeLine);
    mainLayout->addWidget(timeButton);
    setLayout(mainLayout);

    connect(timeButton, SIGNAL(clicked()), this, SLOT(timeClicked()));
}

void timeWindow::timeClicked(){
    timeText=timeLine->text();      //Stesso procedimento degli altri, gli assegno il valore e poi la funzione
    accept();                      //se lo tira via con il get
}

QString timeWindow::getTime(){return timeText;}
