#include "summonedwindow.h"
#include "ui_summonedwindow.h"

summonedWindow::summonedWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::summonedWindow)
{
    ui->setupUi(this);

    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    def= SummonedUnit(-1,"Empty_Sum");
    su = def;
    selected1 = def;
    selected2 = def;
}

summonedWindow::~summonedWindow()
{
    delete ui;
}


void summonedWindow::onSUMItemClicked(QListWidgetItem * item){

    su = storedSummoned[item->text()];
    ui->displayRes->setText(tr("Unit selected: %1").arg(item->text()));
    nameA = item->text();
    BaseAttack* tmp = su.clone();
    bas = passedBA.key(*tmp);
}

void summonedWindow::on_addButton_clicked()
{
    addWindowSum* auw = new addWindowSum;
    auw->updateMode(add);
    auw->usedBA = passedBA;
    auw->usedBA.detach();
    auw->insertBA();
    auw->show();

     if(auw->exec() == QDialog::Accepted){
         QString nameT = auw->getName();
       if(!storedSummoned.contains(nameT)){
         int hpT = auw->getHp();
         int lvT = auw->getLv();
         bas = auw->getBa();
         SummonedUnit tmp(passedBA.value(bas), nameT, hpT,lvT);

         storedSB.insert(nameT,bas);

         storedSummoned.insert(nameT,tmp);
         ui->summList->addItem(nameT);
         ui->displayRes->setText(tr("%1 unit added!").arg(nameT));
         }
         else
            QMessageBox::information(this,tr("Warning"),tr("%1 is in the list").arg(nameT));

}
     delete auw;
}

void summonedWindow::on_select1Button_clicked()
{   if(firstCheck('c'))
    {
        selected1 = su;
        ui->nameLine1->setText(su.getSUMname());
        ui->HPLine1->setText(QString::number(su.getHp()));
        ui->baLine1->setText(storedSB.value(su.getSUMname()));
    }
    else
        return;

}

void summonedWindow::on_select2Button_clicked()
{
    if(firstCheck('c'))
    {
        selected2 = su;
        ui->nameLine2->setText(su.getSUMname());
        ui->HPLine2->setText(QString::number(su.getHp()));
        ui->baLine2->setText(storedSB.value(su.getSUMname()));
    }
    else
        return;
}


void summonedWindow::on_editButton_clicked()
{
    if(su == def){
        QMessageBox::information(this,tr("Warning"), tr("You are trying to edit the nothing"));
        return;
    }
    addWindowSum* euw = new addWindowSum;
    euw->updateMode(edit);
    euw->usedBA = passedBA;
    euw->usedBA.detach();
    euw->insertBA();
    euw->setValues(su);
    euw->show();

    if(euw->exec() == QDialog::Accepted){
        int hp = euw->getHp();
        int lv = euw->getLv();
        bas = euw->getBa();
        SummonedUnit tmp(passedBA.value(bas), nameA, hp,lv);
        su = tmp;
        storedSummoned[nameA] = su;
    }
}

void summonedWindow::on_fightButton_clicked()
{
    if(firstCheck('s') && firstCheck('f')){
        char result = selected1.Fight(&selected2);
        if(result == 't')
            ui->displayRes->setText(tr("Fight is tied"));
        else if(result == 'w')
            ui->displayRes->setText(tr("%1 win the fight").arg(selected1.getSUMname()));
        else
            ui->displayRes->setText(tr("%1 win the fight").arg(selected2.getSUMname()));
  }
}

void summonedWindow::on_removeButton_clicked()
{
   deleteWindow* dw = new deleteWindow;
   dw->show();
   if(dw->exec() == QDialog::Accepted){
       QString deleted = dw->getDelText();
       if((storedSummoned.contains(deleted))){
           storedSummoned.remove(deleted);
           storedSB.remove(deleted);
           //ovviamente non c'è collegamento tra oggetto QMap e QListWidget => bisogna rimuovere anche quello
           //creo una QList di QListWidgetItem che conterrà un solo elemento: deleted [MatchExactly]
           QList<QListWidgetItem*>item_list= ui->summList->findItems(deleted,Qt::MatchExactly);
           QList<QListWidgetItem*>::iterator it= item_list.begin();
           int r = ui->summList->row(*it);
           ui->summList->takeItem(r);

           ui->displayRes->setText(tr("Select or create an unit"));
           su = def;

           on_clearButton_clicked();

           QMessageBox::information(this, tr("Succes"),tr("%1 deleted!").arg(dw->getDelText())); //messaggio di successo
           return;
       }
       else{   //messaggio di errore, stai eliminando un valore che non esiste
           QMessageBox::information(this, tr("Warning"),tr("%1 isn't store in the kalk").arg(dw->getDelText()));
           return;
       }
    }
    delete dw;
    return;
}

void summonedWindow::insertInSumListWidget(){
    QMapIterator<QString,SummonedUnit>i(this->storedSummoned);
    while(i.hasNext()){
        i.next();
        ui->summList->addItem(i.key());
    }
    return;
}

void summonedWindow::on_changeKalkHero_clicked()
{
    changeWindow* cw = new changeWindow;
    cw->SaveMap(passedBA,salvS,storedSummoned,storedSB);
    passedBA.clear();
    salvS.clear();
    storedSummoned.clear();
    cw->setAttribute(Qt::WA_DeleteOnClose);
    cw->show();
    close();
}

void summonedWindow::on_dpsButton_clicked()
{
    if(firstCheck('f')){
        int res = selected1.getValue();
        QString disp = tr("Total DPS ") + QString::number(res);
        ui->displayRes->setText(disp);
        return;
    }
    else
        return;
}

void summonedWindow::on_dpsButton_2_clicked()
{
    if(firstCheck('s')){
    int res = selected2.getValue();
    QString disp = tr("Total DPS ") + QString::number(res);
    ui->displayRes->setText(disp);
    return;
    }
    else
        return;
}

void summonedWindow::on_dbtButton_clicked()
{
    if(firstCheck('f')){
     timeWindow* tw = new timeWindow;
        if(tw->exec() == QDialog::Accepted){
        double time = tw->getTime().toDouble();
        double res = selected1.DamageByTime(time);
        QString disp = tr("Damage done in %1 seconds ").arg(time)+ " " + QString::number(res);
         ui->displayRes->setText(disp);
      }
    }
    else return;
}

void summonedWindow::on_dbtButton2_clicked()
{
    if(firstCheck('s')){
        timeWindow* tw = new timeWindow;
        if(tw->exec() == QDialog::Accepted){
            double time = tw->getTime().toDouble();
            double res = selected2.DamageByTime(time);
            QString disp = tr("Damage done in %1 seconds ").arg(time)+ " " + QString::number(res);
            ui->displayRes->setText(disp);
            }
        }
    else
        return;
}

void summonedWindow::on_clearButton_clicked()
{
    ui->nameLine1->clear();
    ui->HPLine1->clear();
    ui->baLine1->clear();
    ui->nameLine2->clear();
    ui->HPLine2->clear();
    ui->baLine2->clear();

    selected1 = def;
    selected2 = def;
    ui->displayRes->setText("Select or create an unit");

}

bool summonedWindow::firstCheck(char controll){
    if(controll == 'f' && selected1 == def){
             QMessageBox::information(this,tr("Warning"),tr("Select or create an unit"));
             return false;
        }
    else if(controll == 's' && selected2 == def){
            QMessageBox::information(this,tr("Warning"),tr("Select or create an unit"));
            return false;
        }
    else if(controll == 'c' && su == def){
        QMessageBox::information(this,tr("Warning"),tr("You haven't select any unit"));
        return false;
        }
     else
         return true;
}
