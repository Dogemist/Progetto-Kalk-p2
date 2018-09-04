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

  //savedS.insert(trSkill(danno,nome,mana,animation,cooldown,range,projspeed,livello,ready)
    savedS.insert(tr("Blade Fury"),Skill(100,"Blade Fury",120,5,42,1,0.2,1,true));
    savedS.insert(tr("Omnislash"),Skill(500,"Second",200,2,130,1.5,1,2,true));
    savedS.insert(tr("Arc Lightning"),Skill(75,"Arc Lightning",65,0.9,1.6,85,70,1,true));
    savedS.insert(tr("Soul Assumption"),Skill(70,"Soul Assumption",170,1.75,4,90,0.4,1,true));

    savedS.insert(tr("Boundless Strike"),Skill(175,"Boundless Strike",100,0.9,22,1.2,1,2,true));
    savedS.insert(tr("Searing Chains"),Skill(92,"Searing Chains",65,0.87,12,20,18,2,true));
    savedS.insert(tr("Great Cleave"),Skill(145,"Great Cleave",120,0.3,13,1,0.5,2,true));
    savedS.insert(tr("Avalanche"),Skill(180,"Avalanche",120,0.53,21,5,3,2,true));

    savedS.insert(tr("Tree Throw"),Skill(240,"Tree Throw",150,0.53,20,150,125,3,true));
    savedS.insert(tr("Shockwave"),Skill(230,"Shockwave",130,1.5,10,10,9,3,true));
    savedS.insert(tr("Anchor Smash"),Skill(175,"Anchor Smash",60,0.7,7,70,64,3,true));
    savedS.insert(tr("Spectral Dagger"),Skill(190,"Spectral Dagger",140,0.67,16,10,7,3,true));

    savedS.insert(tr("Nightmare"),Skill(650,"Nightmare",165,0.95,22,77,66,4,true));
    savedS.insert(tr("Wrath Of A God"),Skill(325,"Wrath Of A God",225,1,90,25,0.2,4,true));
    savedS.insert(tr("Freezing Field"),Skill(310,"Freezing Field",350,0.3,100,15,3,4,true));
    savedS.insert(tr("Black Hole"),Skill(750,"Black Hole",600,5,200,27,0.2,4,true));



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
