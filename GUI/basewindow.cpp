#include "basewindow.h"
#include <QDesktopServices>

baseWindow::baseWindow(QWidget *parent): QWidget(parent)
{
    setFixedSize(900,400);

    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    BdisplayRes = new QLineEdit;                      //assegnazione    [BARRA IN ALTO]
    BdisplayRes->setReadOnly(true);                  //si può solo leggere e non scrivere
    BdisplayRes->setAlignment(Qt::AlignRight);        //allineamento a destra
    BdisplayRes->setMaxLength(70);                    //numero massimo di caratteri che può contener

    displayBA = new QLineEdit(tr("Select or create a BaseAttack from the list")); //assegnazione con testo base [BARRA BASSA]
    displayBA->setReadOnly(true);
    displayBA->setAlignment(Qt::AlignCenter);
    displayBA->setMinimumSize(600,50);

    QFont fontRes = BdisplayRes->font();                //modifica del font
    fontRes.setPointSize(fontRes.pointSize() + 5);      //aumento di 5 il valore base del font
    BdisplayRes->setFont(fontRes);                      //assegno il font alla Line

    QFont fontBA = displayBA->font();
    fontBA.setPointSize(fontBA.pointSize() + 5);
    displayBA->setFont(fontBA);


    BsumButton = new QPushButton(tr("Sum"));  //assegnazione del button con testo base
    BsumButton->setMinimumSize(70,50);         //Size minima (non fissa)

    BdiffButton = new QPushButton(tr("Difference"));
    BdiffButton->setMinimumSize(70,50);

    BdpsButton = new QPushButton(tr("Damage Per Sec"));
    BdpsButton->setMinimumSize(70,50);

    BhitptButton = new QPushButton(tr("Hit Per Time"));
    BhitptButton->setMinimumSize(70,50);

    BdptButton = new QPushButton(tr("Damage By Time"));
    BdptButton->setMinimumSize(70,50);

    BdpsButton = new QPushButton(tr("Dps"));
    BdpsButton->setMinimumSize(70,50);

    BaddButton = new QPushButton(tr("Add"));
    BaddButton->setMinimumSize(70,50);

    BclearButton = new QPushButton(tr("Clear"));
    BclearButton->setMinimumSize(70,50);

    BchangeKalkButton = new QPushButton(tr("Change"));
    BchangeKalkButton->setMinimumSize(70,50);

    BdeleteButton = new QPushButton(tr("Delete"));
    BdeleteButton->setMinimumSize(70,50);

    BeditButton = new QPushButton(tr("Edit"));
    BeditButton->setMinimumSize(70,50);

    Blist  = new QListWidget;       //assegnazione lista in basso

    def = BaseAttack(-1);
    ba = def;
    sup = BaseAttack(0,0,0,0);      //BaseAttack di supporto per le operazioni binarie
    waitForOperand = false;         //Supporto per le operazioni binarie

    //connect dei bottoni: sono tutti "quando clicco sul bottone X, faccio la funzione "XClicked()"
    //clicked è della libreria di QT, XClicked() sono tutte definite in basso
    connect(BchangeKalkButton, SIGNAL(clicked()),this,SLOT(changeKalkClicked()));
    connect(BaddButton, SIGNAL(clicked()),this,SLOT(addClicked()));
    connect(BclearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(BdeleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(BdpsButton, SIGNAL(clicked()), this, SLOT(dpsClicked()));
    connect(BhitptButton, SIGNAL(clicked()), this, SLOT(hptClicked()));
    connect(BdptButton, SIGNAL(clicked()), this, SLOT(dptClicked()));
    connect(BsumButton, SIGNAL(clicked()), this, SLOT(sumClicked()));
    connect(BdiffButton,SIGNAL(clicked()), this, SLOT(diffClicked()));
    connect(BeditButton, SIGNAL(clicked()), this, SLOT(editClicked()));
    connect (Blist, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
    /*connect della lista widget alla finestra. Se clicco su un oggetto della lista, lo setta come attivo
    itemClicked(QListWidgetItem*) libreria QT, onItemClicked(QListWidgetItem*) definita sul c++*/

    QHBoxLayout* op1Layout = new QHBoxLayout;   //assegnazione Layout Orizzontale (H = Horizzontal)
    op1Layout->addWidget(BsumButton);           //inserisci l'oggetto nel layout
    op1Layout->addWidget(BdiffButton);
    op1Layout->addWidget(BdpsButton);

    QHBoxLayout* op2Layout = new QHBoxLayout;
    op2Layout->addWidget(BdptButton);
    op2Layout->addWidget(BhitptButton);


    QHBoxLayout* optLayout = new QHBoxLayout;
    optLayout->addWidget(BaddButton);
    optLayout->addWidget(BdeleteButton);
    optLayout->addWidget(BeditButton);
    optLayout->addWidget(BclearButton);
    optLayout->addWidget(BchangeKalkButton);


    QGridLayout* mainLayout = new QGridLayout;  //Assegnazione Layout a griglia
    mainLayout->addWidget(BdisplayRes,0,0,1,1); //oltre all'elemento, devi inserire la sua posizione in griglia
    mainLayout->addLayout(op1Layout,1,0);       //e l'eventuale span / allineamento
    mainLayout->addLayout(op2Layout,2,0);
    mainLayout->addLayout(optLayout,3,0,2,0);
    mainLayout->addWidget(displayBA,5,0,1,1,Qt::AlignCenter);
    mainLayout->addWidget(displayBA,2,0);
    mainLayout->addWidget(Blist);

    setLayout(mainLayout);                  //O lo metti o non si vede
    setWindowTitle("BaseAttack Kalk");      //titolo della finestra in alto nella barra nera

}

baseWindow::~baseWindow(){
}

void baseWindow::onItemClicked(QListWidgetItem *item)   //Connect della BList, quando clicco su un oggetto:
{
/*Sul display dei messaggi viene scritto "Selected BaseAttack: X"
arg ritorna una copia della stringa con il minor numero messo sotto il marker %, siccome ne abbiamo solo uno
sostituisce a %1 il testo presente nell'item passato dalla BList*/
    displayBA->setText(tr("Selected BaseAttack: %1").arg(item->text()));
    ba = storedBA[item->text()]; //cerca e assegna a ba il BaseAttack contenuto nella mappa sotto la key corrispondente al testo dell'item selezionato
    name= item->text();
}

void baseWindow::changeKalkClicked(){
    changeWindow* cw = new changeWindow; //Nuova finestra per il cambio di kalk
    cw->SaveMap(storedBA,salvS,salvSum,salvSB); //Pass le QMap StoredBA, SalvH e SalvS a changeKalk
    storedBA.clear();                   //svuoto le mappe presenti per evitare eventuali doppioni
    salvS.clear();
    salvSum.clear();
    cw->show();
    cw->setAttribute(Qt::WA_DeleteOnClose);
    close();                                //chiudo
}


void baseWindow::addClicked(){
    addWindow* aw = new addWindow;
    aw->updateMode(add);
    aw->show();                                 //mostro la finestra
    if(aw->exec() == QDialog::Accepted){        //se la finestra mi manda un segnale "Accepted"
       QString nameTmp = aw->getName();         //assegno il nome inserito ad una variabile temporanea
       if(!storedBA.contains(nameTmp)){         //Se il nome NON è presente nella mappa
            QString dannoTmp = aw->getDanno();  //assegno i valori del BaseAttack a stringhe
            QString animTmp = aw->getAnim();
            QString rangeTmp = aw->getRange();
            QString projTmp = aw->getProj();
            //creo un BaseAttack temporaneo con i dati appena ricevuti
            BaseAttack tmp(dannoTmp.toDouble(),animTmp.toDouble(),rangeTmp.toInt(),projTmp.toInt());
            storedBA.insert(nameTmp,tmp); //lo inserisco nella mappa sotto Key "Nome del BaseAttack" e Value il baseAttack tmp
            Blist->addItem(nameTmp);      //aggiungo il nome del BaseAttack alla list widget.
            displayBA->setText(tr("Base attack \"%1\" added! ").arg(nameTmp));   //messaggio di successo
        }
        else //Nome già presente nella QMap, ritona un valore diverso da storedBA.end
            QMessageBox::information(this, tr("Error"),tr("%1 is in the list").arg(nameTmp));
    }
    delete aw;
    return;
}

void baseWindow::deleteClicked(){
    deleteWindow* dw = new deleteWindow;
    dw->show();
    if(dw->exec() == QDialog::Accepted){
        QString deleted = dw->getDelText();
        if((storedBA.contains(deleted))){
            storedBA.remove(deleted);
            //ovviamente non c'è collegamento tra oggetto QMap e QListWidget => bisogna rimuoverlo manualmente
            QList<QListWidgetItem*>item_list= Blist->findItems(deleted,Qt::MatchExactly);  //creo una QList di QListWidgetItem che conterrà un solo elemento: deleted [MatchExactly]
            QList<QListWidgetItem*>::iterator it= item_list.begin();
            int r = Blist->row(*it);    //per eliminare un elemento dalla QListWidget devi sapere la row
            Blist->takeItem(r);         //elimini l'elemento

            if(displayBA->text() == tr("Selected BaseAttack: %1").arg(deleted)){    //se il testo nella riga delle info è quella
                displayBA->setText(tr("Select or create a BaseAttack from the list"));
                ba = def;
            }

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

void baseWindow::editClicked(){
    if(ba == def){
        QMessageBox::information(this,tr("Error"),tr("You are trying to edit the nothing"));
        return;
    }
   addWindow* ew = new addWindow;
   ew->setValues(name,ba);
   ew->updateMode(edit);
   ew->show();

   if(ew->exec() == QDialog::Accepted){
       double dannoTmp = ew->getDanno().toDouble();               //assegno i valori del BaseAttack a stringhe
       double animTmp = ew->getAnim().toDouble();
       unsigned int rangeTmp = ew->getRange().toInt();
       unsigned int projTmp = ew->getProj().toInt();
       ba.editedValues(dannoTmp,animTmp,rangeTmp,projTmp);
       storedBA[name]=ba;

   }
   delete ew;
   return;
}

void baseWindow::clearClicked(){
    //setta il display delle info con il valore di default e cancella il contenuto di quello del risultato
    displayBA->setText(tr("Select or create BaseAttack from the list"));
    BdisplayRes->clear();
    Blist->clearSelection();
    ba = def;

}

void baseWindow::dpsClicked(){  //connect del pulsante dps,
    if(firstCheck()){
    double res = ba.DPS();      //richiami il metodo DPS del BaseAttack selezionato
    QString disp= "Total DPS " + QString::number(res); //inserisco il risultato in una stringa "personalizzata"
    BdisplayRes->setText(disp); //lo mostro come risultato
    return;
    }
    else
        return;
}

void baseWindow::hptClicked(){
   if(firstCheck()){
    timeWindow* tw = new timeWindow;
    if(tw->exec() == QDialog::Accepted){
        double time = tw->getTime().toDouble();
        double res = ba.HitByTime(time);    //ottenuto dalla timeWindow
        QString disp = tr("Hit done in %1 seconds ").arg(time)+ " " + QString::number(res);
        BdisplayRes->setText(disp);
       }
   }
   return;
}

void baseWindow::dptClicked(){
   if(firstCheck()){
    timeWindow* tw = new timeWindow;
    if(tw->exec() == QDialog::Accepted){
       double time = tw->getTime().toDouble();
       double res = ba.DamageByTime(time); //ottenuto dalla timeWindow
       QString disp = tr("Damage done in %1 seconds ").arg(time)+ " " + QString::number(res);
       BdisplayRes->setText(disp);
       }
   }

    // DA INSERIRE CONDIZIONE D'ERRORE PER IL TEMPO
    return;
}

void baseWindow::sumClicked(){
if (firstCheck()){
    if(!waitForOperand){     //WaitForOperand: selezionato un baseAttack => diventa true e aspetta un altro operando
        BdisplayRes->clear();
        sup = ba;            //assegno a sup il valore del BA selezionato
        waitForOperand=true; //imposto a true per indicare che aspetto il secondo operando
        QMessageBox::information(this,tr("Now select another BaseAttack"), tr("Now select another BaseAttack"));
    }
    else{                     //se ho già selezionato il primo valore

        Damage* val = ba.sum(&sup);//eseguo il calcolo
        BaseAttack* res = dynamic_cast<BaseAttack*>(val);
        QString disp = "I due BaseAttack fanno " + QString::number(res->getValue()) + " Danno in " + QString::number(res->getAnim()) + " secondi";
        BdisplayRes->setText(disp);//mostro il risultato
        res = 0;                     //importo res a 0
        waitForOperand = false;
    }
  }
}

void baseWindow::diffClicked(){
  if (firstCheck()){
    if(!waitForOperand){
        BdisplayRes->clear();
        sup = ba;
        waitForOperand = true;
         QMessageBox::information(this,tr("Now select another BaseAttack"), tr("Now select another BaseAttack"));
    }
    else
    {
        double res = sup - &ba;
        QString disp = "la somma dei due BaseAttack è: " + QString::number(res);
        BdisplayRes->setText(disp);
        res = 0;
        waitForOperand = false;


    }
  }
}

bool baseWindow::firstCheck(){
    if(ba == def){
        QMessageBox::information(this,tr("Error"),tr("You haven't select any BaseAttack"));
        return false;
    }
    else
        return true;
}

void baseWindow::insertInBList(){
QMapIterator<QString, BaseAttack> i(storedBA);  //procedimento di popolamento della QListWidet
  while (i.hasNext()) {
      i.next();
      Blist->addItem(i.key());
  }
  return;
}
