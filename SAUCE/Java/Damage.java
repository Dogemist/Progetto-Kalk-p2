public abstract class Damage {
    private double value;
    public Damage(double d){
        value=d;
        }
    public double getValue(){
        return value;
        }
    @Override
    public abstract boolean equals(Object o);
    @Override
    public abstract double sum(Damage d);
    @Override
    public abstract double dif(Damage d);
}
