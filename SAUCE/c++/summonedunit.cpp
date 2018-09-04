#include "summonedunit.h"
#include "iostream"

SummonedUnit::SummonedUnit(double b,double an,unsigned int ra,unsigned int ps, QString n, unsigned int h, unsigned int l, unsigned int m):BaseAttack(b,an,ra,ps), SUMname(n), HP(h), level(l), multiplier(m){}

SummonedUnit::SummonedUnit(BaseAttack b, QString n,unsigned int h, unsigned int l, unsigned int m)
    :BaseAttack(b),SUMname(n), HP(h), level(l), multiplier(m){}

unsigned int SummonedUnit::getHp() const{
    return HP*level;
}

QString SummonedUnit::getSUMname() const{
    return SUMname;
}

unsigned int SummonedUnit::getLevel()const{
    return level;
}

double SummonedUnit::DPS() {
    return BaseAttack::DPS()*level*multiplier;
}

double SummonedUnit::DamageByTime(double time) {
    return BaseAttack::DamageByTime(time)*level*multiplier;
}

char SummonedUnit::Fight(SummonedUnit* s){
    unsigned int hp1,hp2;
    hp1=getHp();
    hp2=s->getHp();
    for(double i=0;hp1>0&&hp2>0;i+=0.2){
        if(DamageByTime(i)>=hp2){
            hp2=0;
            if(s->DamageByTime(i)>=hp1){
                hp1=0;
                return 't';
            }else
                return 'w';
            }else if(s->DamageByTime(i)>=hp1)
                return 'l';
        }
    return '0';
}
