#include "herowindow.h"
#include "ui_herowindow.h"

#include <iostream>

heroWindow::heroWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::heroWindow)
{
    ui->setupUi(this);
    def = Hero(-1,"Default");
    h = def;
    selected1 = def;
    selected2 = def;
}

heroWindow::~heroWindow()
{
    delete ui;
}

void heroWindow::onHItemClicked(QListWidgetItem * item) //stesso connect dei QListWidget precedenti (vedi BaseAttackWindow.cpp)
{
    h = storedHeroes[item->text()];
    ui->displayRes->setText(tr("Hero selected: %1").arg(item->text()));
    name = item->text();

}

void heroWindow::insertInQListWidget(){

    QMapIterator<QString,Hero>it(storedHeroes);
    while(it.hasNext()){
        it.next();
        ui->HList->addItem(it.key());
    }
}

void heroWindow::on_changeKalkHero_clicked()    //stesso concetto dei precendenti
{
    changeWindow* cw = new  changeWindow;
    cw->SaveMap(salvBA,salvS,storedHeroes,salvSum,Hspell,salvSB);
    salvBA.clear();
    salvS.clear();
    salvSum.clear();
    storedHeroes.clear();
    cw->show();
    cw->setAttribute(Qt::WA_DeleteOnClose);
    close();
    return;
}


void heroWindow::on_addButton_clicked() //diverse aggiunte rispetto ai precendeti add
{
    addWindowH* ah = new addWindowH;            //creo la finestra di add
    ah->updateMode(add);
    ah->showedBA = salvBA;              //gli passo le QMap di BaseAttack e Skill
    ah->showedS = salvS;
    ah->showedBA.detach();              //crea una copia della mappa e la stacca dalla QMap passata
    ah->showedS.detach();
    ah->getMapBA();                     //gli carico le mappe
    ah->getMapS();
    ah->show();                         //mostro la finestra

    if(ah->exec() == QDialog::Accepted){
        Hero tmp = ah->getHero();
        //QString nameTmp = ah->getHeroName();;
        if(!storedHeroes.contains(nameTmp)){
        /*unsigned int StrTmp = ah->getHeroStr();
        unsigned int AglTmp = ah->getHeroAgl();
        unsigned int IntTmp = ah->getHeroInt();
        unsigned int bHPTmp = ah->getHeroBaseHP();
        unsigned int bMPTmp = ah->getHeroBaseMP();
        unsigned int lvTmp = ah->getHeroLevel();
        double phyResTmp = ah->getHeroPhyRes();
        double MagResTmp = ah->getHeroMagRes();
        QString BATmp = ah->getHeroBA();
*/
        QString S1string = ah->getHeroS1();     //creo solita stringa per prendere il nome della skill
        s1Stored = salvS.value(S1string);   //assegno alla s1Stored la skill corrispondente sulla QMap tramite la key
        Skill* S1ind= &s1Stored;    //siccome il vector accetta solo puntatori, gli ho dovuto passare un puntatore all'indirizzo

        QString S2string = ah->getHeroS2();
        s2Stored = salvS.value(S2string);
        Skill* S2ind= &s2Stored;

        QString S3string = ah->getHeroS3();
        s3Stored = salvS.value(S3string);
        Skill* S3ind= &s3Stored;

        QString S4string = ah->getHeroS4();
        s4Stored = salvS.value(S4string);
        Skill* S4ind= &s4Stored;

        unsigned int FullLvSkill = s1Stored.getLevel()+s2Stored.getLevel()+s3Stored.getLevel()+s4Stored.getLevel();

        if(tmp.getLevel()<FullLvSkill){
            QMessageBox::information(this,tr("Error"),tr("The of this Hero isn't enougth to contail all this skill (required lv %1)").arg(FullLvSkill));
            return;
        }

        tmp.InsertSKill(S1ind); //inserisci le skill
        tmp.InsertSKill(S2ind);
        tmp.InsertSKill(S3ind);
        tmp.InsertSKill(S4ind);

        QVector<Skill> VectTemp;
        VectTemp.push_back(s1Stored);
        VectTemp.push_back(s2Stored);
        VectTemp.push_back(s3Stored);
        VectTemp.push_back(s4Stored);
        Hspell.insert(nameTmp,VectTemp);

        storedHeroes.insert(tmp.getName,tmp);
        ui->HList->addItem(tmp.getName);
        ui->displayRes->setText(tr("Hero \"%1\" added! ").arg(tmp.getName));
    }
    else
        QMessageBox::information(this, tr("Error"),tr("%1 is in the list").arg(tmp.getName));
    }
    return;
}

void heroWindow::on_editButton_clicked()
{
    if(h == def){
        QMessageBox::information(this,tr("Error"),tr("You are trying to edit the nothing"));
        return;
    }
    addWindowH* eh = new addWindowH;    //creo la finestra di add
    eh->updateMode(edit);
    eh->showedBA = salvBA;              //gli passo le QMap di BaseAttack e Skill
    eh->showedS = salvS;
    eh->showedBA.detach();              //crea una copia della mappa e la stacca dalla QMap passata
    eh->showedS.detach();
    eh->getMapBA();                     //gli carico le mappe
    eh->getMapS();
    eh->setName(name);
    eh->show();                         //mostro la finestra

    if(eh->exec() == QDialog::Accepted){
        Hero edit = eh->getHero();
        h.resetSkill();

        QString S1string = eh->getHeroS1();     //creo solita stringa per prendere il nome della skill
        s1Stored = salvS.value(S1string);   //assegno alla s1Stored la skill corrispondente sulla QMap tramite la key
        Skill* S1ind= &s1Stored;    //siccome il vector accetta solo puntatori, gli ho dovuto passare un puntatore all'indirizzo

        QString S2string = eh->getHeroS2();
        s2Stored = salvS.value(S2string);
        Skill* S2ind= &s2Stored;

        QString S3string = eh->getHeroS3();
        s3Stored = salvS.value(S3string);
        Skill* S3ind= &s3Stored;

        QString S4string = eh->getHeroS4();
        s4Stored = salvS.value(S4string);
        Skill* S4ind= &s4Stored;

        unsigned int FullLvSkill = s1Stored.getLevel()+s2Stored.getLevel()+s3Stored.getLevel()+s4Stored.getLevel();

        if(edit.getLevel()<FullLvSkill){
            QMessageBox::information(this,tr("Error"),tr("The of this Hero isn't enougth to contail all this skill (required lv %1)").arg(FullLvSkill));
            return;
        }

        tmp.InsertSKill(S1ind); //inserisci le skill
        tmp.InsertSKill(S2ind);
        tmp.InsertSKill(S3ind);
        tmp.InsertSKill(S4ind);

        QVector<Skill> temp;                //creo vettore di supporto temporaneo
        temp.push_back(s1Stored);       //gli inserisco le skill modificate
        temp.push_back(s2Stored);
        temp.push_back(s3Stored);
        temp.push_back(s4Stored);

        h = edit;                        //all'H selezionato lo rendo uguale a tm
        Hspell[name] = temp;            //alla QMap per salvare le spell, seleziono la stringa modificata e gli metto il vettore nuovo
        storedHeroes[name]=h;           //alla QMap per salvare gli eroi, seleziono la stringa modificata e gli metto il valore nuovo
    }

 }

void heroWindow::on_selectHero1_clicked()   //assegni alle LineEdit le stringhe dell'hero h
{
    if(firstCheck('c')){
    selected1 = h;
    ui->heroLine1->setText(h.getName());    //nota che per accederci devi fare sempre ui->
    ui->HPLine1->setText(QString::number(h.GetHP()));
    ui->MPLine1->setText(QString::number(h.GetMP()));

    spell = Hspell.value(h.getName());

    ui->skill1Line1->setText(spell[0].getName());
    ui->skill2Line1->setText(spell[1].getName());
    ui->skill3Line1->setText(spell[2].getName());
    ui->skill4Line1->setText(spell[3].getName());
    ui->displayRes->setText(tr("Hero 1: %1 ").arg(h.getName()));
    }
}

void heroWindow::on_clearButton_clicked()
{


    ui->heroLine1->clear();
    ui->HPLine1->clear();
    ui->MPLine1->clear();
    ui->skill1Line1->clear();
    ui->skill2Line1->clear();
    ui->skill3Line1->clear();
    ui->skill4Line1->clear();
    ui->displayRes->clear();
    ui->heroLine2->clear();
    ui->HPLine2->clear();
    ui->MPLine2->clear();
    ui->skill1Line2->clear();
    ui->skill2Line2->clear();
    ui->skill3Line2->clear();
    ui->skill4Line2->clear();
    selected1 = def;
    selected2 = def;
    h = def;
    ui->HList->clearSelection();
    ui->displayRes->setText(tr("SELECT OR CREATE AN HERO"));
}


void heroWindow::on_selectHero2_clicked() {
    if(firstCheck('c')){
        selected2 = h;
        ui->heroLine2->setText(h.getName());
        ui->HPLine2->setText(QString::number(h.GetHP()));
        ui->MPLine2->setText(QString::number(h.GetMP()));

        spell = Hspell.value(h.getName());

        ui->skill1Line2->setText(spell[0].getName());
        ui->skill2Line2->setText(spell[1].getName());
        ui->skill3Line2->setText(spell[2].getName());
        ui->skill4Line2->setText(spell[3].getName());
        ui->displayRes->setText(tr("Hero 2: %1 ").arg(h.getName()));
    }
}
void heroWindow::on_dpsH1But_clicked()  //DPS DEL SOLO BASEATTACK E DPS DELLA SKILL
{
    if(firstCheck('f')){
        Hero hero1 = storedHeroes.value(ui->heroLine1->text());
         double res = hero1.MaxDamageByTimeDMG(1,hero1.GetMP());
        QString disp = tr("%1 do DPS for :").arg(hero1.getName())+QString::number(res);
        ui->displayRes->setText(disp);
        }
    else
        return;
}

void heroWindow::on_htpH1But_clicked()  //HIT BY TIME DEL SOLO BASEATTACK E DPS DELLA SKILL
{

    if(firstCheck('f')){
        Hero hero1 = storedHeroes.value(ui->heroLine1->text());
        timeWindow* tw = new timeWindow;
        if(tw->exec() == QDialog::Accepted){
            double time = tw->getTime().toDouble();
            double res = hero1.MaxDamageByTime(time,hero1.GetMP()).size();
            QString disp = tr("%1 does ").arg(hero1.getName())+QString::number(res) + tr(" hit in %1 sec").arg(time);
            ui->displayRes->setText(disp);
        }
    }
    else
        return;
}

void heroWindow::on_dptH1But_clicked()   //DAMAGE BY TIME DEL SOLO BASEATTACK E DPS DELLA SKILL
{
    if(firstCheck('f')){
        Hero hero1 = storedHeroes.value(ui->heroLine1->text());
        timeWindow* tw = new timeWindow;
        if(tw->exec() == QDialog::Accepted){
            double time = tw->getTime().toDouble();
            double res = hero1.MaxDamageByTimeDMG(time,hero1.GetMP());
            QString disp = tr("%1 does ").arg(hero1.getName())+QString::number(res) + tr(" damage in %1 sec").arg(time);
            ui->displayRes->setText(disp);
        }
    }
    else
        return;
}

void heroWindow::on_dpsH2But_clicked()
{
    if(firstCheck('s')){
    Hero hero2 = storedHeroes.value(ui->heroLine2->text());
    double res = hero2.MaxDamageByTimeDMG(1,hero2.GetMP());
    QString disp = tr("%1 do DPS for :").arg(hero2.getName())+QString::number(res);
    ui->displayRes->setText(disp);
    }
    else
        return;
}

void heroWindow::on_htpH1But_2_clicked()
{
     if(firstCheck('s')){
        Hero hero2 = storedHeroes.value(ui->heroLine2->text());
        timeWindow* tw = new timeWindow;
        if(tw->exec() == QDialog::Accepted){
            double time = tw->getTime().toDouble();
            double res = hero2.MaxDamageByTime(time,hero2.GetMP()).size();
            QString disp = tr("%1 does ").arg(hero2.getName())+QString::number(res) + tr(" hit in %1 sec").arg(time);
            ui->displayRes->setText(disp);
        }
    }
     else
         return;
}

void heroWindow::on_dptH2But_clicked()
{
    if(firstCheck('s')){
        Hero hero2 = storedHeroes.value(ui->heroLine2->text());
        timeWindow* tw = new timeWindow;
        if(tw->exec() == QDialog::Accepted){
            double time = tw->getTime().toDouble();
            double res = hero2.MaxDamageByTimeDMG(time,hero2.GetMP());
            QString disp = tr("%1 does ").arg(hero2.getName())+QString::number(res) + tr(" damage in %1 sec").arg(time);
            ui->displayRes->setText(disp);
        }
    }
    else
        return;
}

void heroWindow::on_fightButton_clicked()
{
    if(firstCheck('f') && firstCheck('s'))
    {
        char result = selected1.Fight(&selected2);
        if(result == 't')
            ui->displayRes->setText(tr("Fight is tied"));
        else if(result == 'w')
            ui->displayRes->setText(tr("%1 won the fight").arg(selected1.getName()));
        else
            ui->displayRes->setText(tr("%1 won the fight").arg(selected2.getName()));
    }
}

bool heroWindow::firstCheck(char control){
   if(control == 'c' && ui->displayRes->text() == "SELECT OR CREATE AN HERO"){ //c per check
       QMessageBox::information(this,tr("Error"),tr("Select or create an hero"));
        return false;
    }
    else if(control == 'f' && selected1.getName() == "Default"){ //per le funzioni del primo eroe
         QMessageBox::information(this,tr("Error"),tr("Select or create an hero"));
            return false;
        }
    else if (control == 's' && selected2.getName() == "Default"){ //per le funzioni del secondo eroe
           QMessageBox::information(this,tr("Error"),tr("Select or create an hero"));
            return false;
        }
    else
       return true;
    }


void heroWindow::on_deleteButton_clicked()
{
    deleteWindow* dw = new deleteWindow;
    dw->show();
    if(dw->exec() == QDialog::Accepted){
        QString deleted = dw->getDelText();
        if((storedHeroes.contains(deleted))){
            storedHeroes.remove(deleted);
            Hspell.remove(deleted);
            //ovviamente non c'è collegamento tra oggetto QMap e QListWidget => bisogna rimuovere anche quello
            //creo una QList di QListWidgetItem che conterrà un solo elemento: deleted [MatchExactly]
            QList<QListWidgetItem*>item_list= ui->HList->findItems(deleted,Qt::MatchExactly);
            QList<QListWidgetItem*>::iterator it= item_list.begin();
            int r = ui->HList->row(*it);    //per eliminare un elemento dalla QListWidget devi sapere la row
            ui->HList->takeItem(r);         //elimini l'elemento
            ui->displayRes->setText(tr("SELECT OR CREATE AN HERO"));
            h = def;

            on_clearButton_clicked();

            QMessageBox::information(this, tr("Succes"),tr("%1 deleted!").arg(dw->getDelText())); //messaggio di successo
            return;
        }
        else{   //messaggio di errore, stai eliminando un valore che non esiste
            QMessageBox::information(this, tr("Error"),tr("%1 isn't store in the kalk").arg(dw->getDelText()));
            return;
        }
    }
    delete dw;
    return;
}
