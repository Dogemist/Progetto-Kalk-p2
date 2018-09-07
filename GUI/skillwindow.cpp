#include "skillwindow.h"

skillWindow::skillWindow(QWidget *parent): QWidget(parent)
{

    setFixedSize(900,400);

    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    SdisplayRes = new QLineEdit;
    SdisplayRes->setReadOnly(true);
    SdisplayRes->setAlignment(Qt::AlignRight);

    displayS = new QLineEdit(tr("Select or create a skill from the list"));
    displayS->setReadOnly(true);
    displayS->setAlignment(Qt::AlignCenter);
    displayS->setMinimumSize(600,50);

    QFont fontRes = SdisplayRes->font();
    fontRes.setPointSize(fontRes.pointSize() + 5);
    SdisplayRes->setFont(fontRes);

    QFont fontBA = displayS->font();
    fontBA.setPointSize(fontBA.pointSize() + 5);
    displayS->setFont(fontBA);


    SsumButton = new QPushButton(tr("&Sum"));
    SsumButton->setMinimumSize(70,50);

    SdiffButton = new QPushButton(tr("&Difference"));
    SdiffButton->setMinimumSize(70,50);

    SdpsButton = new QPushButton(tr("&Damage Per Sec"));
    SdpsButton->setMinimumSize(70,50);

    ShitptButton = new QPushButton(tr("&Hit Per Time"));
    ShitptButton->setMinimumSize(70,50);

    SdptButton = new QPushButton(tr("&Damage By Time"));
    SdptButton->setMinimumSize(70,50);

    SdpsButton = new QPushButton(tr("&Dps"));
    SdpsButton->setMinimumSize(70,50);

    SaddButton = new QPushButton(tr("&Add"));
    SaddButton->setMinimumSize(70,50);

    SclearButton = new QPushButton(tr("&Clear"));
    SclearButton->setMinimumSize(70,50);

    SchangeKalkButton = new QPushButton(tr("Change"));
    SchangeKalkButton->setMinimumSize(70,50);

    SdeleteButton = new QPushButton(tr("Delete"));
    SdeleteButton->setMinimumSize(70,50);

    SeditButton = new QPushButton(tr("Edit"));
    SeditButton->setMinimumSize(70,50);

    Slist  = new QListWidget;

    defS = Skill(-1);
    s = defS;
    waitForOperand = false;

    connect(SchangeKalkButton, SIGNAL(clicked()),this,SLOT(changeKalkClicked()));
    connect(SaddButton, SIGNAL(clicked()),this,SLOT(addClicked()));
    connect(SclearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(SdeleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(SsumButton, SIGNAL(clicked()), this, SLOT(sumClicked()));
    connect(SdiffButton, SIGNAL(clicked()), this, SLOT(diffClicked()));
    connect(SdpsButton, SIGNAL(clicked()), this, SLOT(dpsClicked()));
    connect(SdptButton, SIGNAL(clicked()), this, SLOT(dptClicked()));
    connect(ShitptButton,SIGNAL(clicked()), this, SLOT(hptClicked()));
    connect(SeditButton,SIGNAL(clicked()), this, SLOT(editClicked()));
    connect (Slist, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));

    QHBoxLayout* op1Layout = new QHBoxLayout;
    op1Layout->addWidget(SsumButton);
    op1Layout->addWidget(SdiffButton);
    op1Layout->addWidget(SdpsButton);

    QHBoxLayout* op2Layout = new QHBoxLayout;
    op2Layout->addWidget(SdptButton);
    op2Layout->addWidget(ShitptButton);


    QHBoxLayout* optLayout = new QHBoxLayout;
    optLayout->addWidget(SaddButton);
    optLayout->addWidget(SdeleteButton);
    optLayout->addWidget(SeditButton);
    optLayout->addWidget(SclearButton);
    optLayout->addWidget(SchangeKalkButton);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(SdisplayRes,0,0,1,1);
    mainLayout->addLayout(op1Layout,1,0);
    mainLayout->addLayout(op2Layout,2,0);
    mainLayout->addLayout(optLayout,3,0,2,0);
    mainLayout->addWidget(displayS,5,0,1,1,Qt::AlignCenter);
    mainLayout->addWidget(displayS,2,0);
    mainLayout->addWidget(Slist);

    setLayout(mainLayout);
    setWindowTitle("Skill Kalk");


}



void skillWindow::onItemClicked(QListWidgetItem *item)
{
    displayS->setText(tr("Selected Skill: %1").arg(item->text()));
    s = storedS[item->text()];
    name = item->text();
}

void skillWindow::changeKalkClicked(){
        changeWindow* cw = new changeWindow;
        cw->SaveMap(salvBA,storedS,salvSum,salvSB);
        storedS.clear();
        salvBA.clear();
        salvSum.clear();
        salvSB.clear();
        cw->show();
        cw->setAttribute(Qt::WA_DeleteOnClose);
        close();
        return;
}

void skillWindow::addClicked(){
    addWindowS* aw = new addWindowS;
    aw->updateMode(add);
    aw->show();
    if(aw->exec() == QDialog::Accepted){
       QString nameTmp = aw->getName();
       if(!storedS.contains(nameTmp)){
            QString dannoTmp = aw->getDanno();
            QString manaTmp = aw->getMana();
            QString animTmp = aw->getAnim();
            QString cdTmp = aw->getCd();
            QString rangeTmp = aw->getRange();
            double projTmp = aw->getProj();
            int lvTmp = aw->getLv();
            Skill tmp(dannoTmp.toDouble(), nameTmp, manaTmp.toInt(),animTmp.toInt(), cdTmp.toInt(),rangeTmp.toDouble(),projTmp, lvTmp);
            storedS.insert(nameTmp,tmp);
            Slist->addItem(nameTmp);
            displayS->setText(tr("Skill \"%1\" added! ").arg(nameTmp));
       }
       else
           QMessageBox::information(this, tr("Warning"),tr("%1 is in the list").arg(nameTmp));
    }
    return;
}

void skillWindow::deleteClicked(){
    deleteWindow* dw = new deleteWindow;
    dw->show();
    if(dw->exec() == QDialog::Accepted){
        QString deleted = dw->getDelText();
        if((storedS.contains(deleted))){
            storedS.remove(deleted);

            QList<QListWidgetItem*>item_list= Slist->findItems(deleted,Qt::MatchExactly);
            QList<QListWidgetItem*>::iterator it= item_list.begin();
            int r = Slist->row(*it);
            Slist->takeItem(r);           

            if(displayS->text() == tr("Selected Skill: %1").arg(deleted))
                displayS->setText(tr("Select or create a skill from the list"));

            s = defS;

            QMessageBox::information(this, tr("Succes"),tr("%1 deleted!").arg(dw->getDelText()));
            return;
        }
        else{
            QMessageBox::information(this, tr("Warning"),tr("%1 isn't store in the kalk").arg(dw->getDelText()));
            return;
        }
    }
}

void skillWindow::editClicked(){

    if(s == defS){
        QMessageBox::information(this,tr("Warning"), tr("You are trying to edit the nothing"));
        return;
    }

   addWindowS* ew = new addWindowS;
   ew->updateMode(edit);
   ew->setValues(s);
   ew->show();

   if(ew->exec() == QDialog::Accepted){
       double dannoTmp = ew->getDanno().toDouble();
       int manaTmp = ew->getMana().toInt();
       int animTmp = ew->getAnim().toInt();
       int cdTmp = ew->getCd().toInt();
       double rangeTmp = ew->getRange().toDouble();
       double projTmp = ew->getProj();
       int  lvTmp = ew->getLv();
       s.editedValues(dannoTmp,manaTmp,animTmp,cdTmp,rangeTmp,projTmp,lvTmp);
       storedS[name]=s;
   }

   return;
}



void skillWindow::clearClicked(){
    displayS->setText(tr("Select or create a skill from the list"));
    SdisplayRes->clear();
    Slist->clearSelection();
    s = defS;
}

void skillWindow::dpsClicked(){
    if(firstCheck()){
        double res = s.DPS();
        QString disp= "Total DPS " + QString::number(res);
        SdisplayRes->setText(disp);
        return;
    }
}

void skillWindow::hptClicked(){
   if(firstCheck()){
    timeWindow* tw = new timeWindow;
    if(tw->exec() == QDialog::Accepted){
       double time = tw->getTime().toDouble();
       double res = s.HitByTime(time);
       QString disp = tr("Hit done in %1 seconds").arg(time)+ " " + QString::number(res);
       SdisplayRes->setText(disp);
   }
}
    return;
}

void skillWindow::dptClicked(){
   if(firstCheck()){
   timeWindow* tw = new timeWindow;
   if(tw->exec() == QDialog::Accepted){
       double time = tw->getTime().toDouble();
       double res = s.DamageByTime(time);
       QString disp = tr("Damage done in %1 seconds").arg(time)+ " " + QString::number(res);
       SdisplayRes->setText(disp);
    }
        return;
    }
}
void skillWindow::sumClicked(){
   if(firstCheck()){
    if(!waitForOperand){     //WaitForOperand: selezionato un baseAttack => diventa true e aspetta un altro operando
        SdisplayRes->clear();
        sup = s;
        waitForOperand=true;
        QMessageBox::information(this,tr("Now select another Skill"), tr("Now select another Skill"));
    }
    else{
        Damage* val = s.sum(&sup);
        Skill* res = dynamic_cast<Skill*>(val);
        QString disp = "The damage of those skill are " + QString::number(res->getValue()) + " casted in " + QString::number(res->getAnimation()) + " second and cost " + QString::number(res->getManaCost()) + " mana";
        SdisplayRes->setText(disp);
        res = 0;
        waitForOperand = false;
    }
}
}

void skillWindow::diffClicked(){
   if(firstCheck()){
    if(!waitForOperand){
        SdisplayRes->clear();
        sup = s;
        waitForOperand = true;
        QMessageBox::information(this,tr("Now select another Skill"), tr("Now select another skill"));
    }
    else
    {
        double res = sup - &s;
        QString disp = "The difference between this skills is: " + QString::number(res);
        SdisplayRes->setText(disp);
        res = 0;
        waitForOperand = false;
    }
    }
}

bool skillWindow::firstCheck(){
    if(s.getValue()<0){
        QMessageBox::information(this,tr("Warning"),tr("Select or create a skill"));
        return false;
    }
    else
        return true;
}

void skillWindow::insertInSList(){
    QMapIterator<QString,Skill>it(storedS);
    while(it.hasNext()){
        it.next();
        Slist->addItem(it.key());
    }
    return;
}
