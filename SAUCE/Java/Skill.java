public class Skill extends Damage {
    private boolean ready;
    private string Sname;
    private int manaCost;
    private int coolDown;
    private int range;
    private int level;
    private double projectileSpeed;
    private double animation;
    public Skill(double v,string s,int m,double an,int cd,int r,double ps,int lv){
        super(v);
        re=true;
        Sname=s;
        manaCost=m;
        coolDown=cd;
        range=r;
        level=lv;
        projectileSpeed=ps;
        animation=an;
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
        return HitByTime(time,distance)*value;
        }

    public int HitByTime(double time,int distance){
        double aux = time;
        unsigned int tiri = 0;
        while(IsCastable(aux,distance)){
            tiri++;
            aux=aux-(animation+cooldown+(distance/projectileSpeed));
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

    public string getName(){
        return Sname;
        }

    void setReady(bool b){
        ready=b;
        }

    public boolean equals(Object o){
        return(o instanceof Skill)&&(getAnim()==((Skill)o).getAnim())&&(getRange()==((Skill)o).getRange())&&(super.getValue()==d.getValue())&&(getManaCost()==((Skill)o).getManaCost())&&(getManaCost()==((Skill)o).getManaCost());
        }

    public double sum(Skill s){
        return getValue()+s.getValue();
        }

    public double dif(Skill s){
        return getValue()-s.getValue();
        }
}
