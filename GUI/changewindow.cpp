#include "changewindow.h"


changeWindow::changeWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300,200);
    baseKalk = new QPushButton(tr("Base Kalk"));
    heroKalk = new QPushButton(tr("Hero Kalk"));
    summonKalk = new QPushButton(tr("Summon Kalk"));
    skillKalk = new QPushButton(tr("Skill Kalk"));

    connect(baseKalk,SIGNAL(clicked()), this, SLOT(openBase()));
    connect(summonKalk, SIGNAL(clicked()),this, SLOT(openSummon()));
    connect(skillKalk, SIGNAL(clicked()),this, SLOT(openSkill()));
    connect(heroKalk, SIGNAL(clicked()),this, SLOT(openHero()));

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(baseKalk);
    mainLayout->addWidget(skillKalk);
    mainLayout->addWidget(summonKalk);
    mainLayout->addWidget(heroKalk);
    setLayout(mainLayout);
    setWindowTitle("Change Kalk");


    bw = new baseWindow();
    sw = new skillWindow();
    hw = new heroWindow();
    suw = new summonedWindow();

    //Inseriamo qua gli eventuali SKill/BaseAttack/Hero/Summoned Unit già preimpostati

    savedB.insert(tr("First"),BaseAttack(10,1,1,1));
    savedB.insert(tr("Second"),BaseAttack(20,1,2,1));

    //savedS.insert(tr("EmptySKILL"),Skill());
    savedS.insert(tr("First"),Skill(100,"First",1,1,1,1,1,2));
    savedS.insert(tr("Second"),Skill(10,"Second",10,20,30,10,10,2,true));
    savedS.insert(tr("Third"),Skill(10,"Third",10,20,30,10,10,2,true));
    savedS.insert(tr("Fourth"),Skill(10,"Fourth",10,20,30,10,10,2,true));
    savedS.insert(tr("Five"),Skill(50,"Five",10,20,30,10,10,2,true));
    savedS.insert(tr("Six"),Skill(60,"Six",10,20,30,10,10,2,true));


}

void changeWindow::openBase(){ //LO STESSO PROCEDIMENTO VA ANCHE PER LE ALTRE KALK

    bw->show();                 //mostro la finestra creata col costruttore
    bw->storedBA = savedB;      //Gli passo le QMap dove stored e' quella che verrà utilizzata
    bw->salvS = savedS;         //mentre saved* è quella di passaggio delle altre kalk
    bw->salvH = savedH;
    bw->salvHS = savedHS;
    bw->salvSum = savedSum;
    bw->salvSB = savedSB;
    bw->insertInBList();


    bw->storedBA.detach();  //detach delle mappe da quella originale
    bw->salvH.detach();
    bw->salvS.detach();
    bw->salvHS.detach();
    bw->salvSum.detach();

    savedB.clear();


    sw->deleteLater();
    bw->setAcceptDrops(Qt::WA_DeleteOnClose);
    close();                //chiusura della change kalk

}


void changeWindow::openSkill(){

    sw->show();
    sw->storedS = savedS;
    sw->salvSum = savedSum;
    sw->salvBA = savedB;
    sw->salvH = savedH;
    sw->salvHS = savedHS;
    sw->salvSB = savedSB;

    sw->insertInSList();
    sw->salvBA.detach();
    sw->salvH.detach();
    sw->salvSum.detach();
    sw->salvHS.detach();
    sw->storedS.detach();
    sw->salvSB.detach();

    savedS.clear();

    hw->deleteLater();
    suw->deleteLater();
    bw->deleteLater();
    sw->setAcceptDrops(Qt::WA_DeleteOnClose);
    close();
    return;
}


void changeWindow::openHero(){

         hw->show();

         hw->storedHeroes = savedH; //passo la mappa
         hw->Hspell = savedHS;
         hw->salvBA = savedB;
         hw->salvS = savedS;
         hw->salvSum = savedSum;
         hw->salvSB = savedSB;
         hw->insertInQListWidget();

         hw->storedHeroes.detach();
         hw->salvSum.detach();
         hw->salvBA.detach();
         hw->salvS.detach();
         hw->Hspell.detach();
         hw->salvSB.detach();

         sw->deleteLater();
         bw->deleteLater();
         suw->deleteLater();
         hw->setAttribute(Qt::WA_DeleteOnClose);
         close();
     }


void changeWindow::openSummon(){
    suw->show();
    suw->storedSummoned = savedSum;
    suw->storedSB = savedSB;
    suw->passedBA = savedB;
    suw->salvS = savedS;
    suw->salvH = savedH;
    suw->salvHS = savedHS;

    suw->insertInSumListWidget();
    suw->salvH.detach();
    suw->salvS.detach();
    suw->salvHS.detach();
    suw->passedBA.detach();
    suw->storedSB.detach();

    sw->deleteLater();
    bw->deleteLater();
    hw->deleteLater();
    suw->setAttribute(Qt::WA_DeleteOnClose);

    close();

}

void changeWindow::SaveMap(QMap<QString, BaseAttack>& base, QMap<QString, Skill>& skill, QMap<QString, Hero> & hero, QMap<QString,SummonedUnit>& summon, QMap<QString, QVector<Skill> >& hs,  QMap<QString,QString>&sb){
    //funzione usata dalle kalk all'atto del cambio di calcolatrice, semplicemnte passa le kalk
    savedH = hero;
    savedB = base;
    savedS = skill;
    savedSum = summon;
    savedHS = hs;
    savedSB = sb;
    savedH.detach();
    savedB.detach();
    savedS.detach();
    savedSum.detach();
    savedHS.detach();
    savedSB.detach();
}
