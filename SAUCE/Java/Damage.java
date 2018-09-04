public abstract class Damage {
    private double value;
    public Damage(double d){
        value=d;
        }
    public double getValue(){
        return value;
        }
    public abstract boolean equals(Object o);
    public abstract double sum(Damage d);
    public abstract double dif(Damage d);
}
