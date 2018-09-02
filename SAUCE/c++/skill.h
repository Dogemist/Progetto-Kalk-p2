#ifndef SKILL_H
#define SKILL_H
#include <QString>
#include "mdamage.h"

class Skill : public MDamage
{
private:
    bool ready;
    QString Sname;
    unsigned int manaCost;
    unsigned int cooldown;
    unsigned int range;
    unsigned int level;
    double projectileSpeed;
    double animation;
public:
 Skill(double v=1, QString n="empty",unsigned int m=100, double an=1, unsigned int cd=1,unsigned int r=1, double ps=1,unsigned int lv=0, bool re=true);
   ~Skill() = default;
   bool Heal();
   bool IsCastable(double time, unsigned int distance=0);
   bool IsCastable(double time, unsigned int distance,unsigned int mana);

   double DPS(unsigned int distance=0);
   double DamageByTime(double time,unsigned int distance=0);
   unsigned int HitByTime(double time,unsigned int distance=0);
   double totalTime(unsigned int distance=0)const;

   double getAnimation() const;
   bool getReady() const;
   unsigned int getCooldown()const;
   unsigned int getManaCost() const ;
   QString getName() const;
   void setReady(bool b);
   double getMaxAnim(Skill*) const;

   void editedValues(double nv,unsigned int nm,unsigned int na,unsigned int nc,unsigned int nr,double np,unsigned int nl);

   Damage* sum(Damage*) const;
   double operator+(Damage* d) const;
   double operator-(Damage* d) const;
   bool operator==(Damage* d) const;
   bool operator==(Skill d) const;
 };

#endif // SKILL_H
