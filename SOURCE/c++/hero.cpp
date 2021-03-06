#include "hero.h"
#include "vector"

Hero::Hero(const BaseAttack b, QString n, unsigned int st, unsigned int ag, unsigned int in, unsigned int hp, unsigned int mp, unsigned int arm, unsigned int mr, unsigned int lv):
    BaseAttack(b),Hname(n),str(st),agl(ag),inte(in),bHp(hp),bMp(mp),bArmor(arm),magicResistance(mr),level(lv){}

/*Hero::Hero(const Hero& h):BaseAttack(static_cast<BaseAttack>(h)){
//    BaseAttack(static_cast<BaseAttack>(h));
    Hname=h.Hname;
    str=h.str;
    agl=h.agl;
    inte=h.inte;
    bHp=h.bHp;
    bArmor=h.bArmor;
    magicResistance=h.magicResistance;
    level=h.level;
    if(h.skills.size()>0)
      for(unsigned int i=0;i<skills.size();i++)
        skills.push_back(new Skill(h.getSkill(i)));
}*/

/*Hero::~Hero(){
    std::vector<Skill*>::const_iterator it = skills.begin();
    Skill* aux;
    for(;it!= skills.end(); it++){
        aux=(*it);
        delete  aux;
        skills.erase(skills.begin());
    }
}*/

unsigned int Hero::getStr()const {return str;}
unsigned int Hero::getAgl()const {return agl;}
unsigned int Hero::getInt()const {return inte;}
unsigned int Hero::getbHp()const {return bHp;}
unsigned int Hero::getbMp()const {return bMp;}
unsigned int Hero::getbArm() const {return bArmor;}
unsigned int Hero::getMagicResistance()const {return magicResistance;}
unsigned int Hero::getLevel()const {return level;}

unsigned int Hero::GetArmor() const {
    return static_cast<unsigned int>(bArmor+agl*0.16);
}
unsigned int Hero::GetHP() const {
    return bHp+str*18;
}
unsigned int Hero::GetMP() const{
    return bMp+inte*12;
}
QString Hero::getName() const{
    return Hname;
}

double Hero::getLongestReadySkill(unsigned int distance){//ritorna l'animazione più lunga tra le skill castabili
    double max=0;
    std::vector<Skill*>::iterator its ;
    its=skills.begin();
    for(;its!=skills.end();its++){
        if((*its)->IsCastable(distance)&&(*its)->getAnimation()>max)
            max=(*its)->getAnimation();
    }
    return max;
}



std::vector<Damage*> Hero::MaxDamageByTime(double time,unsigned int mana){//restituisce un vector con le skill usate per massimaizzare il danno in quel lasso di tempo, tenendo conto anche del mana
    double max;
    double maxDmg;
    unsigned int index;
    Skill* cd=nullptr;
    std::vector<Damage*> v;
    std::vector<Skill*>::iterator it;
    std::vector<Damage*>::iterator itd;
    std::vector<double> timing;
    for(double i=0; i<time; i=i+0.2){//ogni tick dura 0.2 sec
        index=0;
        for(itd=v.begin();itd!=v.end();itd++){//ciclo per i cooldown delle skill
            cd=dynamic_cast<Skill*>(*itd);
            if(cd){
                if(i-timing[index]>=cd->getCooldown())
                    cd->setReady(true);
                else
                    cd->setReady(false);
            }
            index++;
        }
        max=0;//animazione massima inizializzata/resettata a 0
        // Damage* d =new BaseAttack();
        Damage* d = nullptr;
        it = skills.begin();
        for(; it!=skills.end(); it++){    //FOR PER L'ANIMAZIONE + LUNGA
           if((*it)->getAnimation()>max &&  (*it)->IsCastable(time-i))    //animazione skill
                max=(*it)->getAnimation();
        }
        maxDmg=0;//danno massimo inizializzato/resettato a 0
        double rem = time-i;
        if(BaseAttack::IsCastable(rem)){//controllo se attacco castabile nel tempo rimanente
            if(BaseAttack::getAnim()>max)//se animazione maggiore di max, diventa max
                max=BaseAttack::getAnim();
            maxDmg=BaseAttack::DamageByTime(max);//setto a maxdmg il danno del base attack
        }
        if(maxDmg>0){
            if(d){
                Damage*aux=d;
                delete aux;
            }
            d = new BaseAttack(*this);
        }
        for(it=skills.begin(); it!=skills.end(); it++){    //FOR PER L'ATTACCO + FORTE
            double checkDBT = (*it)->DamageByTime(max);//cerca il DamageByTime della skill puntata da it
            if(checkDBT>maxDmg && (*it)->getReady()&&mana>((*it)->getManaCost()*(*it)->HitByTime(max))){
                maxDmg=checkDBT;
                if(d){
                    Damage*aux=d;
                    delete aux;
                }
                d=*it;
            }
        }
        if(!dynamic_cast<BaseAttack*>(d)){
            Skill* s=dynamic_cast<Skill*>(d);
            if(s){
                if(s->getReady()){
                    if(s->totalTime()*s->HitByTime(max)<max)//controllo se il tempo totale di cast della skill è minore del massimo
                        max=s->totalTime()*s->HitByTime(max);
                    mana=mana-s->getManaCost()*s->HitByTime(max);//tolgo dal mana rimanente il mana per castare la skill
                    for(unsigned int x=0;x<s->HitByTime(max);x++){
                        v.push_back(s);//inserisco la spell nel vettore dei danni
                        timing.push_back(i+x*s->totalTime());//inserisco il timing dell'azione
                    }
                }
            }
        }else{
            if(dynamic_cast<BaseAttack*>(d)){
                    if(BaseAttack::getAnim()*BaseAttack::HitByTime(max)<max)
                        max=BaseAttack::getAnim()*BaseAttack::HitByTime(max);
                for(unsigned int l=0;l<BaseAttack::HitByTime(max);l++){//inserisco un attacco base per ogni volta che l'ho usato
                    v.push_back(new BaseAttack(*this));
                    timing.push_back(i+l*BaseAttack::getAnim());
                }
            }
        }
        delete d;
        if(max>0)
            max=max-0.2;//tolgo il tempo del tick corrente dall'animazione dell'azione
        i=i+max;//aggiungo il tempo per fare l'azione intrapresa
    }
    delete cd;
    return v;
}

double Hero::MaxDamageByTimeDMG(double time,unsigned int mana){//metodo che calcola i danni massimi in tot tempo con tot mana
    std::vector<Damage*> v=MaxDamageByTime(time,mana);
    double total=0;
    std::vector<Damage*>::iterator it=v.begin();
    for(;it!=v.end();it++){
        total=total+(*it)->getValue();
    }
    return total;
}


char Hero::Fight(Hero* h){
    unsigned int mp1,mp2,hp1,hp2,m1,m2;
    double dmg1,dmg2;
    bool check=true;
    Skill* s;
    mp1=Hero::GetMP();
    mp2=h->GetMP();
    m1=mp1;
    m2=mp2;
    hp1=Hero::GetHP();
    hp2=h->GetHP();
    std::vector<Damage*> x;
    std::vector<Damage*> y;
    std::vector<Damage*>::iterator xi;
    std::vector<Damage*>::iterator yi;
    for(double i=0.2;m1+m2>0&&check;i+=0.2){
        x = MaxDamageByTime(i,mp1);
        y=h->MaxDamageByTime(i,mp2);
        dmg1=0;
        dmg2=0;
        for(xi=x.begin();xi!=x.end();xi++){
            s=dynamic_cast<Skill*>((*xi));
            if(s){
                dmg1=dmg1+((*xi)->getValue()*(1-h->getMagicResistance()/100));
                m1=m1-s->getManaCost();
            }
            else{
                dmg1=dmg1+((*xi)->getValue()*(1-(0.05*(h->GetArmor())/(1+(0.05*(h->GetArmor()))))));
            }
        }
        for(yi=y.begin();yi!=y.end();yi++){
            s=dynamic_cast<Skill*>((*yi));
            if(s){
                dmg2=dmg2+((*yi)->getValue()*(1-magicResistance/100));
                m2=m2-s->getManaCost();
                }
            else{
                dmg2=dmg2+((*yi)->getValue()*(1-(0.05*GetArmor()/(1+(0.05*GetArmor())))));
            }
        }
        if(hp2-dmg1<0.001){
            check=false;
            if(hp1-dmg2<0.001)
                return 't';
            else
                return 'w';
        }
        else{
            if(hp1-dmg2<0.001){
                check=false;
                return 'l';
            }
        }
    }
    return 0;
}

std::vector<Damage*> Hero::MaxPower(double time,unsigned int distance){
    std::vector<Damage*> t;
    std::vector<Damage*> result;
    Damage* DPS=nullptr;
    Damage* DBT=nullptr;
    t.insert(t.end(),skills.begin(),skills.end());
    t.push_back(dynamic_cast<BaseAttack*>(this));
    std::vector<Damage*>::iterator it=t.begin();
    double maxDPS=-1;
    double maxDBT=-1;
    for(;it!=t.end();it++){
        if((*it)->DPS(distance)>maxDPS){
            maxDPS=(*it)->DPS(distance);
            if(dynamic_cast<Skill*>(*it)){
                if(DPS){
                    Damage* aux=DPS;
                    delete aux;
                }
                DPS=new Skill(*(dynamic_cast<Skill*>(*it)));
            }
            else{
                if(DPS){
                    Damage* aux=DPS;
                    delete aux;
                }
                DPS=new BaseAttack(*(dynamic_cast<BaseAttack*>(*it)));
            }
        }
        if((*it)->DamageByTime(time,distance)>maxDBT){
            maxDBT=(*it)->DamageByTime(time,distance);
            if(dynamic_cast<Skill*>(*it)){
                if(DBT){
                    Damage* aux=DBT;
                    delete aux;
                }
                DBT=new Skill(*(dynamic_cast<Skill*>(*it)));
            }
            else{
                if(DBT){
                    Damage* aux=DBT;
                    delete aux;
                }
                DBT=new BaseAttack(*(dynamic_cast<BaseAttack*>(*it)));
            }
        }
    }

     if((dynamic_cast<Skill*>(DPS)))
        result.push_back(new Skill((*(dynamic_cast<Skill*>(DPS)))));
    else
        result.push_back(new BaseAttack(*(dynamic_cast<BaseAttack*>(DPS))));

    if((dynamic_cast<Skill*>(DBT)))
        result.push_back(new Skill((*(dynamic_cast<Skill*>(DBT)))));
    else
        result.push_back(new BaseAttack(*(dynamic_cast<BaseAttack*>(DBT))));

    result[0]->setValue(maxDPS);
    result[1]->setValue(maxDBT);
    return result;
}


void Hero::InsertSKill(Skill* sk ){
    if(skills.size()==4){
    }
    else{
        skills.push_back(sk);
    }
}

Skill Hero::getSkill(unsigned int i) const{

    Skill* s = skills[i];
    return *s;
}

void Hero::resetSkill(){
    std::vector<Skill*>::iterator it=skills.begin();
    for(;it!=skills.end();it++)
        skills.erase(it);
}
