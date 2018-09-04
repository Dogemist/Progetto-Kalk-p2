#ifndef MDAMAGE_H
#define MDAMAGE_H
#include "damage.h"

class MDamage : public Damage
{
public:
    MDamage(double v);
    ~MDamage();

    virtual Damage* sum(Damage*) =0;

    virtual double DPS(unsigned int distance=0)=0;
    virtual double DamageByTime(double time,unsigned int distance=0)=0;
    virtual unsigned int HitByTime(double time,unsigned int distance=0)=0;

    double operator+(Damage*) const =0;
    double operator-(Damage*) const =0;
    bool operator==(Damage*) const =0;


};

#endif // MDAMAGE_H
