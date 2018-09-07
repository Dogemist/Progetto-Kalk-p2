#include "timewindow.h"

timeWindow::timeWindow(QDialog *parent) : QDialog(parent)
{
    setWindowTitle("Set Time");
    setWindowModality(Qt::ApplicationModal);
    QLabel* timeLabel = new QLabel(tr("Insert time (seconds)"));
    timeButton = new QPushButton(tr("Insert"));
    timeLine = new QLineEdit;
    timeLine->setText("0");
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
    timeText=timeLine->text();
    accept();
}

QString timeWindow::getTime(){return timeText;}
