#ifndef PDAMAGE_H
#define PDAMAGE_H
#include "damage.h"

class PDamage : public Damage
{
public:
    PDamage(double d):Damage(d){}
    ~PDamage();

    virtual Damage* sum(Damage*) const =0;

    virtual double operator+(Damage*) const =0;
    virtual double operator-(Damage*) const =0;
    virtual bool operator==(Damage*) const =0;
};

#endif // PDAMAGE_H
