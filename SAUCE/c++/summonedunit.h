#ifndef SUMMONEDUNIT_H
#define SUMMONEDUNIT_H
#include <QString>
#include "baseattack.h"

class SummonedUnit : public BaseAttack
{
private:
 QString SUMname;
 unsigned int HP;
 unsigned int level;
 double multiplier;
public:
 SummonedUnit(double v=1, double an=1, unsigned int ra=1, unsigned int ps=1, QString n="Empty_Summon", unsigned int h=1, unsigned int l=1, unsigned int m=0);
 SummonedUnit(BaseAttack b,QString n="Empty_Summon", unsigned int h=1, unsigned int l=1, unsigned int m=0);
 ~SummonedUnit() = default;
 double DPS()const;
 double DamageByTime(double time)const;
 char Fight(SummonedUnit s)const;
 unsigned int getHp() const;
 QString getSUMname() const;
 unsigned int getLevel() const;

};

#endif // SUMMONEDUNIT_H
