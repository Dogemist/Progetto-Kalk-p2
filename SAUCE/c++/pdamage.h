#ifndef PDAMAGE_H
#define PDAMAGE_H
#include "damage.h"

class PDamage : public Damage
{
public:
    PDamage(double d):Damage(d){}
    ~PDamage();

    virtual Damage* sum(Damage*) =0;

    virtual double DPS(unsigned int distance=0)=0;
    virtual double DamageByTime(double time,unsigned int distance=0)=0;
    virtual unsigned int HitByTime(double time,unsigned int distance=0)=0;


    virtual double operator+(Damage*) const =0;
    virtual double operator-(Damage*) const =0;
    virtual bool operator==(Damage*) const =0;
};

#endif // PDAMAGE_H
