public class BaseAttack extends PDamage {
    private double animation;
    private int range;
    private double projectileSpeed;
    public BaseAttack(double v,double a,int r,int ps){
        super(v);
        animation=a;
        range=r;
        projectileSpeed=ps;
        }
    public BaseAttack(BaseAttack b){
        super(b.getValue());
        animation=b.animation;
        range=b.range;
        projectileSpeed=b.projectileSpeed;
    }

    public boolean IsCastable(double time,int distance){
        if(time+0.001<(animation+(distance/projectileSpeed))||distance>range){
            return false;
        }
        else
            return true;
     }

    public int HitByTime(double time,int distance){
        if(IsCastable(time,distance))
            return ((int)(time/((distance/projectileSpeed)+animation)));
        return 0;
        }

    public double DPS(int distance){
        return HitByTime(1,distance)*super.getValue();
        }

    public double DamageByTime(double time,int distance){
        return HitByTime(time,distance)*super.getValue();
        }

    public double getAnim(){
        return animation;
        }

    public int getRange(){
        return range;
        }

    public boolean equals(Object o){
        return(o instanceof BaseAttack)&&(getAnim()==((BaseAttack)o).getAnim())&&(getRange()==((BaseAttack)o).getRange())&&(super.getValue()==((BaseAttack)o).getValue());
        }

    public double sum(Damage b){
        return super.getValue()+b.getValue();
        }

    public double dif(Damage b){
        return super.getValue()-b.getValue();
        }
}
