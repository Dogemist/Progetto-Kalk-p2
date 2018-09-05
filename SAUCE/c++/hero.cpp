#include "hero.h"
#include "vector"

Hero::Hero(const BaseAttack b, QString n, unsigned int st, unsigned int ag, unsigned int in, unsigned int hp, unsigned int mp, unsigned int arm, unsigned int mr, unsigned int lv):
    BaseAttack(b),Hname(n),str(st),agl(ag),inte(in),bHp(hp),bMp(mp),bArmor(arm),magicResistance(mr),level(lv){}

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
    Skill* cd;
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
        Damage* d=new BaseAttack();
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
            d = new BaseAttack(BaseAttack::getValue());
        }
        for(it=skills.begin(); it!=skills.end(); it++){    //FOR PER L'ATTACCO + FORTE
            double checkDBT = (*it)->DamageByTime(max);//cerca il DamageByTime della skill puntata da it
            if(checkDBT>maxDmg && (*it)->getReady()&&mana>(*it)->getManaCost()){
                maxDmg=checkDBT;
                d=*it;
            }
        }
        if(!dynamic_cast<BaseAttack*>(d)){
            Skill* s=dynamic_cast<Skill*>(d);
            if(s){
                if(s->getReady()){
                    if(s->totalTime()*s->HitByTime(max)<max)//controllo se il tempo totale di cast della skill è minore del massimo
                        max=s->totalTime()*s->HitByTime(max);
                    mana=mana-s->getManaCost();//tolgo dal mana rimanente il mana per castare la skill
                    v.push_back(s);//inserisco la spell nel vettore dei danni
                    timing.push_back(i);//inserisco il timing dell'azione
                }
            }
        }else{
            if(dynamic_cast<BaseAttack*>(d)){
                if(d->getValue()>0)
                    if(BaseAttack::getAnim()*BaseAttack::HitByTime(max)<max)
                        max=BaseAttack::getAnim()*BaseAttack::HitByTime(max);
                for(unsigned int l=0;l<BaseAttack::HitByTime(max);l++){//inserisco un attacco base per ogni volta che l'ho usato
                    v.push_back(d);
                    timing.push_back(i+l*BaseAttack::getAnim());
                }
            }
        }
        if(max>0)
            max=max-0.2;//tolgo il tempo del tick corrente dall'animazione dell'azione
        i=i+max;//aggiungo il tempo per fare l'azione intrapresa
    }
    return v;
}

double Hero::MaxDamageByTimeDMG(double time,unsigned int mana){//metodo che calcola i danni masssimi in tot tempo con tot mana
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
        x=MaxDamageByTime(i,mp1);
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
                //std::cout<<"Fight is tied"<<std::endl;

            else
                return 'w';
                //std::cout<<"Memes "/*Hero::getName()*/<<" won"<<" in "<<i<<" seconds"<<std::endl;
        }
        else{
            if(hp1-dmg2<0.001){
                check=false;
                return 'l';
                //std::cout<<"Mememino "/*Hero::getName()*/<<" won"<<" in "<<i<<" seconds"<<std::endl;
            }
        }
    }
    return 0;
}

std::vector<Damage*> Hero::MaxPower(double time,unsigned int distance){
    std::vector<Damage*> t;
    std::vector<Damage*> result;
    Damage* DPS=new BaseAttack;
    Damage* DBT=new BaseAttack;
    t.insert(t.end(),skills.begin(),skills.end());
    t.push_back(dynamic_cast<BaseAttack*>(this));
    std::vector<Damage*>::iterator it=t.begin();
    double maxDPS=-1;
    double maxDBT=-1;
    for(;it!=t.end();it++){
        if((*it)->DPS(distance)>maxDPS){
            maxDPS=(*it)->DPS(distance);
            if(dynamic_cast<Skill*>(*it))
                DPS=new Skill(*(dynamic_cast<Skill*>(*it)));
            else
                DPS=new BaseAttack(*(dynamic_cast<BaseAttack*>(*it)));
        }
        if((*it)->DamageByTime(time,distance)>maxDBT){
            maxDBT=(*it)->DamageByTime(distance);
            if(dynamic_cast<Skill*>(*it))
                DBT=new Skill(*(dynamic_cast<Skill*>(*it)));
            else
                DBT=new BaseAttack(*(dynamic_cast<BaseAttack*>(*it)));
        }
    }
    Skill* res;
    res=new Skill((*(dynamic_cast<Skill*>(DPS))));
    if(res)
        result.push_back(new Skill(*(res)));
    else
        result.push_back(new BaseAttack(*(dynamic_cast<BaseAttack*>(DPS))));
    res=new Skill((*(dynamic_cast<Skill*>(DBT))));
    if(res)
        result.push_back(new Skill(*(res)));
    else
        result.push_back(new BaseAttack(*(dynamic_cast<BaseAttack*>(DBT))));
    result[0]->setValue(maxDPS);
    result[1]->setValue(maxDBT);
    return result;
}
Hero Hero::InsertSKill(Skill* sk ){
    if(skills.size()==4){
    return *this;
    }
    else{
        skills.push_back(sk);
        return *this;
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
