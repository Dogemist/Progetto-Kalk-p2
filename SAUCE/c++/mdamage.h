#ifndef MDAMAGE_H
#define MDAMAGE_H
#include "damage.h"

class MDamage : public Damage
{
public:
    MDamage(double v);
    ~MDamage();

     virtual Damage* sum(Damage*) const =0;

    double operator+(Damage*) const =0;
    double operator-(Damage*) const =0;
    bool operator==(Damage*) const =0;


};

#endif // MDAMAGE_H
