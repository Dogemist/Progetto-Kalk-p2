public abstract class Damage {
    private double value;
    public Damage(double d){
        value=d;
        }
    public double getValue(){
        return value;
        }
    public void setValue(double d){
        value=d;
        }
    public abstract boolean IsCastable(double d,int distance);
    public abstract double DPS(int distance);
    public abstract double DamageByTime(double time,int distance);
    public abstract int HitByTime(double time,int distance);
    public abstract boolean equals(Object o);
    public abstract double sum(Damage d);
    public abstract double dif(Damage d);
}
