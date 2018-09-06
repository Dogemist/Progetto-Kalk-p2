#ifndef DAMAGE_H
#define DAMAGE_H
#include<QString>
enum Mode{add,edit};

class Damage
{
private:
    double value;
public:

   Damage(double d): value(d){}
   virtual ~Damage() =0;
   double getValue() const;
   void setValue(double d);

   virtual bool IsCastable(double,unsigned int distance=0)=0;
   virtual Damage* sum(Damage*) =0;
   virtual double DPS(unsigned int distance=0)=0;
   virtual double DamageByTime(double time,unsigned int distance=0)=0;
   virtual unsigned int HitByTime(double time,unsigned int distance=0)=0;


   virtual double operator+(Damage*) const =0;
   virtual double operator-(Damage*) const =0;
   virtual bool operator==(const Damage&) const =0;
};

#endif // DAMAGE_H
