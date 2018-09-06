#include "baseattack.h"
#include "iostream"

BaseAttack::BaseAttack(double v, double a, unsigned int r, unsigned int p):PDamage(v), anim(a), range(r), projectileSpeed(p){
}

double BaseAttack::operator+(Damage* d) const{
   BaseAttack* c=new BaseAttack();
   c->setValue(this->getValue()+d->getValue());
   return c->getValue();

}

double BaseAttack::operator-(Damage* d) const{
    return this->getValue()-d->getValue();

}
bool BaseAttack::operator==(const Damage& d) const{
BaseAttack* x=dynamic_cast<BaseAttack*>(&const_cast<Damage&>(d));    if(x)
        return this->getValue()-x->getValue()<0.001&&(anim-x->anim<0.001)&&(projectileSpeed==x->projectileSpeed);
    else return false;
}

bool BaseAttack::operator ==(const BaseAttack ba) const{
    return (this->getValue()-ba.getValue()<0.001)&&(anim-ba.anim<0.001)&&(projectileSpeed==ba.projectileSpeed);

}

bool BaseAttack::IsCastable(double time, unsigned int distance) {
    if(time+0.001<(anim+(distance/projectileSpeed))||distance>range){
        return false;
    }
    else
        return true;

}

unsigned int BaseAttack::HitByTime(double time,unsigned int distance){
    return static_cast<unsigned int>(time/((distance/projectileSpeed)+anim));
}

double BaseAttack::DPS(unsigned int distance) {
    return HitByTime(1,distance)*getValue();
}

double BaseAttack::DamageByTime(double time,unsigned int distance) {
   return HitByTime(time,distance)*getValue();
}

double BaseAttack::getAnim() const {return anim;}

unsigned int BaseAttack::getRange() const {return range;}

BaseAttack* BaseAttack::clone()const{
    return new BaseAttack(getValue(),getAnim(),getRange(),getPP());
}

unsigned int BaseAttack::getPP() const{
    return projectileSpeed;
}

void BaseAttack::editedValues(double nv,double na,unsigned int nr, unsigned int npp){
    this->setValue(nv);
    this->anim = na;
    this->range = nr;
    this->projectileSpeed = npp;
}

double BaseAttack::getMaxAnim(BaseAttack* a) const {
    if(this->anim > a->anim)
        return this->anim;
    else
        return a->anim;
}

Damage* BaseAttack::sum(Damage* d){
    BaseAttack* sum = new BaseAttack();
    BaseAttack* dp = dynamic_cast<BaseAttack*>(d);
    sum->anim = this->getMaxAnim(dp);


    if(this->anim-sum->anim<0.001){
       double value =   dp->DamageByTime(sum->anim);
       sum->setValue(this->getValue() + value);
    }
    else{
        double value = this->DamageByTime(sum->anim);
        sum->setValue(value + dp->getValue());
}
    Damage* ret = sum;

    return ret;

}
