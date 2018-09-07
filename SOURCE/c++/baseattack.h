#ifndef BASEATTACK_H
#define BASEATTACK_H
#include "pdamage.h"


//enum Mode{add,edit};

class BaseAttack : public PDamage
{
private:
    double anim;
    unsigned int range;
    unsigned int projectileSpeed;
public:
    BaseAttack(double v=0, double a=1, unsigned int r=0, unsigned int p=0);

    ~BaseAttack() = default;
    Damage* sum(Damage *d);
    double DPS(unsigned int distance=0);
    double DamageByTime(double time,unsigned int distance=0);
    unsigned int HitByTime(double time,unsigned int distance=0);
    bool IsCastable(double, unsigned int distance=0);
    double getAnim() const;
    unsigned int getRange() const;
    unsigned int getPP() const;
    double getMaxAnim(BaseAttack*) const;
    void editedValues(double nv,double na,unsigned int nr, unsigned int npp);

    BaseAttack* clone()const;
    double operator+(Damage* d) const;
    double operator-(Damage* d) const ;
    bool operator==(const Damage& d ) const;
    bool operator==(const BaseAttack) const;
};

#endif // BASEATTACK_H
