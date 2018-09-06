#include "addwindows.h"

addWindowS::addWindowS(QDialog *parent) : QDialog(parent)
{
    setWindowModality(Qt::ApplicationModal);

    QLabel* nameLabel = new QLabel(tr("Name"));
    QLabel* dannoLabel = new QLabel(tr("Damage"));
    QLabel* manaLabel = new QLabel(tr("Mana"));
    QLabel* animationLabel = new QLabel(tr("Animation"));
    QLabel* cooldownLabel = new QLabel(tr("Cooldown"));
    QLabel* rangeLabel = new QLabel(tr("Range"));
    QLabel* projLabel = new QLabel(tr("Projectile Speed"));
    QLabel* levelLabel = new QLabel(tr("Level"));

    validAn = new QDoubleValidator(1,9999,2);
    validAn->setNotation(QDoubleValidator::StandardNotation);

    validPP = new QDoubleValidator(1,9999,2);
    validPP->setNotation(QDoubleValidator::StandardNotation);

    nameLineS = new QLineEdit;
    dannoLineS = new QLineEdit;
    dannoLineS->setValidator(new QIntValidator(1,9999,this));
    dannoLineS->setText(tr("1"));
    manaLine = new QLineEdit;
    manaLine->setValidator(new QIntValidator(1,9999,this));
    manaLine->setText(tr("1"));
    animationLineS = new QLineEdit;
    animationLineS->setValidator(validAn);
    animationLineS->setText(tr("1"));
    cooldownLine = new QLineEdit;
    cooldownLine->setValidator(new QIntValidator(1,999,this));
    cooldownLine->setText(tr("1"));
    rangeLineS = new QLineEdit;
    rangeLineS->setValidator(new QIntValidator(1,9999,this));
    rangeLineS->setText(tr("1"));
    projLineS = new QLineEdit;
    projLineS->setValidator(validPP);
    projLineS->setText(tr("1"));
    levelLine = new QLineEdit;
    levelLine->setValidator(new QIntValidator(0,4,this));
    levelLine->setText(tr("0"));

    confirmButtonS = new QPushButton();
    clearButtonS= new QPushButton(tr("Close"));

    connect(clearButtonS, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(confirmButtonS, SIGNAL(clicked()),this, SLOT(addClicked()));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameLineS);
    mainLayout->addWidget(dannoLabel);
    mainLayout->addWidget(dannoLineS);
    mainLayout->addWidget(manaLabel);
    mainLayout->addWidget(manaLine);
    mainLayout->addWidget(animationLabel);
    mainLayout->addWidget(animationLineS);
    mainLayout->addWidget(cooldownLabel);
    mainLayout->addWidget(cooldownLine);
    mainLayout->addWidget(rangeLabel);
    mainLayout->addWidget(rangeLineS);
    mainLayout->addWidget(projLabel);
    mainLayout->addWidget(projLineS);
    mainLayout->addWidget(levelLabel);
    mainLayout->addWidget(levelLine);
    mainLayout->addWidget(confirmButtonS);
    mainLayout->addWidget(clearButtonS);
    setLayout(mainLayout);

}

void addWindowS::addClicked(){
    if(nameLineS->text() == "" || dannoLineS->text() == "" || manaLine->text()== "" || animationLineS->text() == ""
            || cooldownLine->text() == "" || rangeLineS->text() == "" || projLineS->text() == "" || levelLine->text() == ""){
        QMessageBox::information(this,tr("Error"),tr("All fields need to be filled"));
        return;
    }
    else{
        if(addOedit == add)
            nameText = nameLineS->text();

        dannoText = dannoLineS->text();
        manaText = manaLine->text();
        animationText =animationLineS->text();
        cooldownText = cooldownLine->text();
        rangeText = rangeLineS->text();
        projText = projLineS->text().toDouble();
        levelText= levelLine->text().toInt();
        if(projText > 0.001 )
            accept();
        else{
            QMessageBox::information(this,tr("Error"),tr("Projectile Speed must be > 0"));
            return;
        }
        if(levelText == 0)
            QMessageBox::warning(this,tr("Attention"),tr("With the level = 0 the spell won't be casted"));
    }
}

void addWindowS::clearClicked(){
  close();
}

void addWindowS::updateMode(Mode up){
    addOedit = up;

    switch(addOedit){
    case add:
        confirmButtonS->setText(tr("Add"));
        nameLineS->setReadOnly(false);
        setWindowTitle("Add a new Skill");
        nameLineS->setFocus();
        break;
    case edit:
        confirmButtonS->setText(tr("Edit"));
        nameLineS->setReadOnly(true);
        setWindowTitle("Edit a new Skill");
        break;

    }
}

void addWindowS::setValues(Skill sk)const{
    nameLineS->setText(sk.getName());
    dannoLineS->setText(QString::number(sk.getValue()));
    manaLine->setText(QString::number(sk.getManaCost()));
    animationLineS->setText(QString::number(sk.getAnimation()));
    cooldownLine->setText(QString::number(sk.getCooldown()));
    rangeLineS->setText(QString::number(sk.getRange()));
    projLineS->setText(QString::number(sk.getPP()));
    levelLine->setText(QString::number(sk.getLevel()));
}

QString addWindowS::getName() const{return nameText;}
QString addWindowS::getDanno() const{return dannoText;}
QString addWindowS::getMana() const{return manaText;}
QString addWindowS::getAnim() const{return animationText;}
QString addWindowS::getCd() const{return cooldownText;}
QString addWindowS::getRange() const{return rangeText;}
double addWindowS::getProj() const{return projText;}
int addWindowS::getLv() const{return levelText;}
