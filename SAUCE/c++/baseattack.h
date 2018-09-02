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
    Damage* sum(Damage *d) const;
    ~BaseAttack() = default;
    double DPS(unsigned int distance=0)const;
    double DamageByTime(double time,unsigned int distance=0)const;
    unsigned int HitByTime(double time,unsigned int distance=0)const;
    bool IsCastable(double, unsigned int distance=0)const;
    double getAnim() const;
    unsigned int getRange() const;
    unsigned int getPP() const;
    double getMaxAnim(BaseAttack*) const;
    void editedValues(double nv,double na,unsigned int nr, unsigned int npp);

    BaseAttack* clone()const;
    double operator+(Damage* d) const;
    double operator-(Damage* d) const ;
    bool operator==(Damage* d ) const;
    bool operator==(const BaseAttack) const;
};

#endif // BASEATTACK_H
