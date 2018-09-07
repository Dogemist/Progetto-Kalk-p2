public class Skill extends MDamage {
    private boolean ready;
    private String Sname;
    private int manaCost;
    private int coolDown;
    private int range;
    private int level;
    private double projectileSpeed;
    private double animation;
    public Skill(double v,String s,int m,double an,int cd,int r,double ps,int lv){
        super(v);
        ready=true;
        Sname=s;
        manaCost=m;
        coolDown=cd;
        range=r;
        level=lv;
        projectileSpeed=ps;
        animation=an;
     }
     public Skill(Skill s){
        super(s.getValue());
        ready=true;
        Sname=s.Sname;
        manaCost=s.manaCost;
        coolDown=s.coolDown;
        range=s.range;
        level=s.level;
        projectileSpeed=s.projectileSpeed;
        animation=s.animation;
    }

    public boolean IsCastable(double time,int distance){
        if(time<animation+(distance/projectileSpeed) || distance>range || (level<=0 || level>4))
            return false;
        else
            return true;
        }

    public boolean IsCastable(double time,int distance,int mana){
        if(time<animation+(distance/projectileSpeed) || distance>range || (level<=0 || level>4)||mana<manaCost)
            return false;
        else
            return true;
        }

    public double DPS(int distance){
        return DamageByTime(1,distance);
        }

    public double DamageByTime(double time,int distance){
        return HitByTime(time,distance)*super.getValue();
        }

    public int HitByTime(double time,int distance){
        double aux = time;
        int tiri = 0;
        while(IsCastable(aux,distance)){
            tiri++;
            aux=aux-(animation+coolDown+(distance/projectileSpeed));
            }
        return tiri;
        }

    public double totalTime(int distance){
        return (distance/projectileSpeed)+animation;
        }

    public double getAnimation(){
        return animation;
        }

    public boolean getReady(){
        return ready;
        }

    public int getCooldown(){
        return coolDown;
        }
    public int getManaCost(){
        return manaCost;
        }

    public String getName(){
        return Sname;
        }

    public int getRange(){
        return range;
        }

    void setReady(boolean b){
        ready=b;
        }

    public boolean equals(Object o){
        return(o instanceof Skill)&&(getAnimation()==((Skill)o).getAnimation())&&(getRange()==((Skill)o).getRange())&&(super.getValue()==((Skill)o).getValue())&&(getManaCost()==((Skill)o).getManaCost())&&(getManaCost()==((Skill)o).getManaCost());
        }

    public double sum(Damage s){
        return getValue()+s.getValue();
        }

    public double dif(Damage s){
        return getValue()-s.getValue();
        }
}
