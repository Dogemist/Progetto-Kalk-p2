#ifndef HERO_H
#define HERO_H
#include <QString>
#include "skill.h"
#include "baseattack.h"
#include <string>
#include <vector>
class Hero : public BaseAttack
{
private:
  QString Hname;
  unsigned int str;
  unsigned int agl;
  unsigned int inte;
  unsigned int bHp;
  unsigned int bMp;
  unsigned int bArmor;
  unsigned int magicResistance;
  unsigned int level;
  std::vector<Skill*> skills;


public:


  Hero(const BaseAttack b=0, QString n="NO_H_NAME", unsigned int st=0, unsigned int ag=0, unsigned int in=0, unsigned int hp=0, unsigned int mp=0, unsigned int arm=0, unsigned int mr=0, unsigned int lv=0);
  Hero(double v, double an, unsigned int rg, unsigned int tt, QString n, unsigned int st, unsigned int ag, unsigned int in, unsigned int hp, unsigned int mp, unsigned int arm, unsigned int mr, unsigned int lv, double ma, double pa);
  ~Hero() = default;
  Hero InsertSKill(Skill* sk);
  void resetSkill();

  unsigned int GetArmor() const;
  unsigned int GetHP() const;
  unsigned int GetMP() const;
  QString getName() const;
  unsigned int getStr()const;
  unsigned int getAgl()const;
  unsigned int getInt()const;
  unsigned int getbHp()const;
  unsigned int getbMp()const;
  unsigned int getbArm() const;
  unsigned int getMagicResistance()const;
  unsigned int getLevel()const;

  Skill getSkill(unsigned int i)const;
  double getLongestReadySkill(unsigned int distance=0);

  std::vector<Damage*> MaxDamageByTime(double,unsigned int);
  double MaxDamageByTimeDMG(double,unsigned int);
  char Fight(Hero*);
};

#endif // HERO_H
