#ifndef PDAMAGE_H
#define PDAMAGE_H
#include "damage.h"

class PDamage : public Damage
{
public:
    PDamage(double d):Damage(d){}
    ~PDamage();
};

#endif // PDAMAGE_H
