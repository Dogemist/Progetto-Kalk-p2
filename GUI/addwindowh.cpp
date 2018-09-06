#include "addwindowh.h"
#include "ui_addwindowh.h"

addWindowH::addWindowH(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindowH)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
}

addWindowH::~addWindowH()
{
     delete ui;
}



void addWindowH::getMapBA() const{

    QMapIterator<QString, BaseAttack>i(showedBA);
    while(i.hasNext()){
        i.next();
        ui->baseAttackBox->addItem(i.key());

    }
    return;
}


void addWindowH::getMapS() const{

    QMapIterator<QString, Skill>i(showedS);
    while(i.hasNext()){
        i.next();
        ui->skill1Box->addItem(i.key());
        ui->skill2Box->addItem(i.key());
        ui->skill3Box->addItem(i.key());
        ui->skill4Box->addItem(i.key());

    }
}

void addWindowH::on_confirmButton_clicked()
{
   if(ui->nameLine->text() == "" || ui->strBox->text() == "" ||  ui->aglBox->text()== "" || ui->intBox->text() == ""
            || ui->hpBox->text() == "" || ui->mpBox->text() == "" || ui->levBox->text() == "" || ui->phyBox->text() == ""
           || ui->magBox->text() == ""){
        QMessageBox::information(this,tr("Error"),tr("All fields need to be filled"));
        return;
    }
   else{
        heroName = ui->nameLine->text();
        heroStr = ui->strBox->text().toInt();
        heroAgl = ui->aglBox->text().toInt();
        heroInt = ui->intBox->text().toInt();
        heroBaseHP = ui->hpBox->text().toInt();
        heroBaseMP = ui->mpBox->text().toInt();
        heroLevel = ui->levBox->text().toInt();
        heroBaseArmor = ui->phyBox->text().toInt();
        heroMagRes = ui->magBox->text().toInt();
        heroBA = ui->baseAttackBox->currentText();
        heroS1 = ui->skill1Box->currentText();
        heroS2 = ui->skill2Box->currentText();
        heroS3 = ui->skill3Box->currentText();
        heroS4 = ui->skill4Box->currentText();

        tmp = Hero(showedBA.value(heroBA),heroName,heroStr,heroAgl,heroInt,heroBaseHP,heroBaseMP,heroBaseArmor,heroMagRes,heroLevel);

        accept();

   }
}


void addWindowH::updateMode(Mode up){
    addOedit = up;
    switch(addOedit){
    case add:
        ui->nameLine->setReadOnly(false);
        ui->confirmButton->setText(tr("Add"));
        setWindowTitle("Add an hero");
        ui->nameLine->setFocus();
        break;
    case edit:
        ui->nameLine->setReadOnly(true);
        ui->confirmButton->setText(tr("Edit"));
        setWindowTitle("Edit an hero");
        break;

    }
}

void addWindowH::setValues(Hero h) const{
    ui->nameLine->setText(h.getName());
    ui->strBox->setValue(h.getStr());
    ui->intBox->setValue(h.getInt());
    ui->aglBox->setValue(h.getAgl());
    ui->hpBox->setValue(h.getbHp());
    ui->mpBox->setValue(h.getbMp());
    ui->levBox->setValue(h.getLevel());
    ui->phyBox->setValue(h.getbArm());
    ui->magBox->setValue(h.getMagicResistance());
    ui->skill1Box->setCurrentIndex(ui->skill1Box->findText(showedS.key(h.getSkill(0))));
    ui->skill2Box->setCurrentIndex(ui->skill1Box->findText(showedS.key(h.getSkill(1))));
    ui->skill3Box->setCurrentIndex(ui->skill1Box->findText(showedS.key(h.getSkill(2))));
    ui->skill4Box->setCurrentIndex(ui->skill1Box->findText(showedS.key(h.getSkill(3))));

}

//IDEA: Possibile evitare il tutto ritornando un hero già impostato senza dover fare millemila get

Hero addWindowH::getHero() const{ return tmp;}
QString addWindowH::getHeroBA() const{ return heroBA;}
QString addWindowH::getHeroS1() const{ return heroS1;}
QString addWindowH::getHeroS2() const{ return heroS2;}
QString addWindowH::getHeroS3() const{ return heroS3;}
QString addWindowH::getHeroS4() const{ return heroS4;}

void addWindowH::on_clearBut_clicked()
{
 close();
}
