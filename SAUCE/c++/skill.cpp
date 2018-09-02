#include "skill.h"
#include <iostream>
Skill::Skill(double v, QString n,unsigned int m, double an, unsigned int cd,unsigned int r, double ps,unsigned int lv, bool re):MDamage(v), ready(re),Sname(n), manaCost(m), cooldown(cd), range(r), level(lv),projectileSpeed(ps),animation(an){
}


bool Skill::IsCastable(double time, unsigned int distance){
    if(time<animation+(distance/projectileSpeed) || distance>range || (level<=0 || level>4))
        return false;
    else
        return true;
}

bool Skill::IsCastable(double time, unsigned int distance,unsigned int mana){
    if(time<animation+(distance/projectileSpeed) || distance>range || (level<=0 || level>4)||mana<manaCost)
        return false;
    else
        return true;
}

double Skill::DPS(unsigned int distance){
        return DamageByTime(1,distance);
}

double Skill::DamageByTime(double time,unsigned int distance){
  return HitByTime(time,distance)*value;
}

unsigned int Skill::HitByTime(double time,unsigned int distance){
    double aux = time;
    unsigned int tiri = 0;
    while(IsCastable(aux,distance)){
        tiri++;
        aux=aux-(animation+cooldown+(distance/projectileSpeed));
        }
    return tiri;
}

double Skill::totalTime(unsigned int distance) const{
 return (distance/projectileSpeed)+animation;
}

bool Skill::Heal(){
    if(this->getValue()<0)
        return true;
    else
        return false;
}

double Skill::getAnimation() const {return animation;}
bool Skill::getReady() const {return ready;}
unsigned int Skill::getCooldown() const {return cooldown;}
unsigned int Skill::getManaCost() const {return manaCost;}
QString Skill::getName() const {return Sname;}
void Skill::setReady(bool b) {ready=b;}

double Skill::operator+(Damage* d) const{
    return this->getValue()+d->getValue();
}

double Skill::operator-(Damage* d) const{
     return this->getValue()-d->getValue();
}
bool Skill::operator==(Damage* d) const{
    Skill* x;
    x=dynamic_cast<Skill*>(d);
    if(x)
        return this->Sname==x->Sname;
    else
        return false;
}

bool Skill::operator==(Skill d) const{
    return this->Sname==d.Sname;
}
void Skill::editedValues(double nv,unsigned int nm,unsigned int na,unsigned int nc,unsigned int nr,double np,unsigned int nl){
    this->value = nv;
    this->manaCost = nm;
    this->animation = na;
    this->cooldown = nc;
    this->range = nr;
    this->projectileSpeed = np;
    this->level = nl;
}

Damage* Skill::sum(Damage * s) const{
    Skill* sum = new Skill;
    sum->value = *this + s ;
    sum->animation= this->animation + dynamic_cast<Skill*>(s)->animation;
    sum->manaCost = this->manaCost + dynamic_cast<Skill*>(s)->manaCost;

    Damage* ret = sum;

    return ret;

}

double Skill::getMaxAnim(Skill* s) const{
    if(this->animation > s->animation)
        return this->animation;
    else
        return s->animation;
}


unsigned int Skill::getLevel() const{
    return level;
}
