public class BaseAttack extends Damage {
    private double animation;
    private int range;
    private double projectileSpeed;
    public BaseAttack(double v,double a,int r,int ps){
        super(v);
        animation=a;
        range=r;
        projectileSpeed=ps;
        }

    public boolean IsCastable(double time,int distance){
        if(time+0.001<(anim+(distance/projectileSpeed))||distance>range){
            return false;
        }
        else
            return true;
     }

    public int HitByTime(double time,int distance){
        if(IsCastable(time,distance))
            return time/((distance/projectileSpeed)+anim);
        return 0;
        }

    public double DPS(int distance){
        return HitByTime(1,distance)*value;
        }

    public double DamageByTime(double time,int distance){
        return HitByTime(time,distance)*value;
        }

    public double getAnim(){
        return animation;
        }

    public int getRange(){
        return range;
        }

    public boolean equals(Object o){
        return(o instanceof BaseAttack)&&(getAnim()==((BaseAttack)o).getAnim())&&(getRange()==((BaseAttack)o).getRange())&&(super.getValue()==d.getValue());
        }

    public double sum(BaseAttack b){
        return super.getValue()+b.getValue();
        }

    public double dif(BaseAttack b){
        return super.getValue()-b.getValue();
        }
}
