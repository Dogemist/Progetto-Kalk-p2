#include "addwindowsum.h"

addWindowSum::addWindowSum(QWidget *parent) :
    QDialog(parent)
{
    QLabel* nameLabel = new QLabel(tr("Name"));
    QLabel* hpLabel = new QLabel(tr("Hp"));
    QLabel* levelLabel= new QLabel(tr("Level"));
    QLabel* baseAttackLabel = new QLabel(tr("BaseAttack"));

    nameLine = new QLineEdit;
    hpLine = new QLineEdit;
    hpLine->setValidator(new QIntValidator(0,9999,this));
    hpLine->setText(tr("1"));
    levelLine = new QLineEdit;
    levelLine->setValidator(new QIntValidator(0,4,this));
    levelLine->setText(tr("0"));
    baseAttackBox = new QComboBox;


    confirmButton = new QPushButton();
    clearButton= new QPushButton(tr("Clear"));

    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(confirmButton, SIGNAL(clicked()),this, SLOT(onAddClicked()));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameLine);
    mainLayout->addWidget(hpLabel);
    mainLayout->addWidget(hpLine);
    mainLayout->addWidget(levelLabel);
    mainLayout->addWidget(levelLine);
    mainLayout->addWidget(baseAttackLabel);
    mainLayout->addWidget(baseAttackBox);
    mainLayout->addWidget(levelLabel);
    mainLayout->addWidget(levelLine);
    mainLayout->addWidget(confirmButton);
    mainLayout->addWidget(clearButton);
    setLayout(mainLayout);

}


addWindowSum::~addWindowSum()
{

}


void addWindowSum::onAddClicked(){
    if(nameLine->text() == "" || hpLine->text() == "" || levelLine->text() == "" ){
        QMessageBox::information(this,tr("Error"),tr("All fields must be filled"));
        return;
    }

    if(addOedit == add)
        name = nameLine->text();
    hp = hpLine->text().toInt();
    lv = levelLine->text().toInt();
    ba = baseAttackBox->currentText();
    if(hp == 0 || lv == 0){
        QMessageBox::information(this,tr("Error"),tr("all this fields must be > 0"));
        return;
    }
    else
        accept();
}

void addWindowSum::onClearClicked(){

}

void addWindowSum::insertBA(){
    QMapIterator<QString, BaseAttack>i(usedBA);
    while(i.hasNext()){
        i.next();
        baseAttackBox->addItem(i.key());
    }
}

void addWindowSum::updateMode(Mode up){
    addOedit = up;

    switch(addOedit){
    case add:
        nameLine->setReadOnly(false);
        confirmButton->setText(tr("Add"));
        setWindowTitle("Add an unit");
        break;
    case edit:
        nameLine->setReadOnly(true);
        confirmButton->setText(tr("Edit"));
        setWindowTitle("Edit an unit");
        break;

    }
}

void addWindowSum::setName(SummonedUnit su) const{
    QString tmp;
    nameLine->setText(su.getSUMname());
    hpLine->setText(tmp.number(su.getHp()));
    levelLine->setText(tmp.number(su.getLevel()));
}

QString addWindowSum::getName() const {return name;}
int addWindowSum::getHp() const { return hp;}
int addWindowSum::getLv() const { return lv;}
QString addWindowSum::getBa() const {return ba;}
