#ifndef DAMAGE_H
#define DAMAGE_H

enum Mode{add,edit};

class Damage
{
    public:
//protected:
    double value;
   Damage(double d): value(d){}
   virtual ~Damage() =0;
   double getValue() const;
   virtual Damage* sum(Damage*) const =0;

   virtual double operator+(Damage*) const =0;
   virtual double operator-(Damage*) const =0;
   virtual bool operator==(Damage*) const =0;
};

#endif // DAMAGE_H
