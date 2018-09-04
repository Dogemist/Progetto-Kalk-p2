import java.util.*;
public class Hero extends BaseAttack{
    private LinkedList<Skill> skills = new LinkedList<Skill>();
    private String Hname;
    private int str;
    private int agl;
    private int inte;
    private int bHp;
    private int bMp;
    private int bArmor;
    private int magicResistance;
    private int level;
    public Hero(BaseAttack b,String n,int st,int ag,int in,int hp,int mp,int arm,int mr,int lv){
        super(b);
        Hname=n;
        str=st;
        agl=ag;
        inte=in;
        bHp=hp;
        bMp=mp;
        bArmor=arm;
        magicResistance=mr;
        level=lv;
        }
    void InsertSkill(Skill sk){
        skills.add(sk);
        }
    public int GetArmor(){
        return bArmor+agl*0.16;
        }
    public int GetHP(){
        return bHp+str*18;
        }
    public int GetMP(){
        return bMp+inte*12;
        }
    public String getName(){
        return Hname;
        }
    public int getMagicResistance(){
        return magicResistance;
        }
    public Skill getSkill(int i){
        return skills(i);
        }
    public double getLongestReadySkill(int distance){
        double max=0;
        for(int i=0;i<4;i++){
            if(skills[i].isCastable(distance)&&skills[i].getAnimation()>max)
                max=skills[i].getAnimation();
            }
        return max;
    }

    public LinkedList<Damage> MaxDamageByTime(double time,int mana){
        double max;
        double maxDmg;
        int index;
        LinkedList<Damage> v=new LinkedList<Damage>();
        for(double i=0;i<time;i+=0.2){
            index=0;
            for(int i=0;i<v.size();i++){
                if(v[i] instanceof Skill){
                    if(i-timing[index]>=v[i].getCooldown())
                        v[i].setready(true);
                    else
                        v[i].setReady(false);
                }
            }
        max=0;
        Damage d;
        for(int i=0;i<4;i++){
            if(skills[i].getAnimation()>max&&skills[i].isCastable(time-i,0))
                max=skills[i].getAnimation();
        }
        maxDmg=0;
        double rem=time-i;
        if(super.IsCastable(rem)){
            if(super.getAnim()>max)
                max=super.getAnim();
                maxDmg=super.DamageByTime(max);
            }
        if(maxDmg>0){
            d=new BaseAttack(super.getValue());
            }
        for(int i=0;i<4;i++){
            double checkDBT=skills[i].DamageByTime(max);
            if(checkDBT>maxDmg&&skills[i].getReady()&&mana>skills[i].getManaCost()){
                maxDmg=checkDBT;
                d=skills[i];
            }
        }
    if(!(d instanceof BaseAttack)){
        Skill s=(Skill)d ;
        if(s.getReady()){
           if(s.totalTime()*s.HitByTime(max)<max)
              max=s.totalTime()*s.HitByTime(max);
              mana=mana-s.getManaCost();
              v.add(s);
            }
     }
    else{
            BaseAttack b=(BaseAttack)d;
            if(b.getValue()>0)
                if(super.getAnim()*super.HitByTime(max)<max)
                    max=super.getAnim()*super.HitByTime(max);
            for(int l=0;l<super.HitByTime(max);l++){
                v.add(b);
            }
        }
    if(max>0)
        max=max-0.2;
      i=i+max;
      }
    return v;
    }

    public double MaxDamageByTimeDMG(double time,int mana){
        LinkedList<Damage> v=MaxDamageByTime(time,mana);
        double total=0;
        for(int i=0;i<v.size();i++){
            total=total+v[i].getValue();
        }
        return total;
    }

    public char Fight(Hero h){
        int mp1,mp2,hp1,hp2,m1,m2;
        double dmg1,dmg2;
        boolean check=true;
        Skill s;
        mp1=GetMP();
        mp2=h.GetMP();
        m1=mp1;
        m2=mp2;
        hp1=GetHP();
        hp2=h.GetHP();
        LinkedList<Damage> x;
        LinkedList<Damage> y;
        for(double i=0.2;m1+m2>0&&check;i+=0.2){
            x=MaxDamageByTime(i,mp1);
            y=h.MaxDamageByTime(i,mp2);
            dmg1=0;
            dmg2=0;
            for(i=0;i<x.size();i++){
                if(x[i] instanceof Skill){
                    dmg1=dmg1+(x[i].getValue()*(1-h.getMagicResistance()/100));
                    m1=m1-x[i].getManaCost();
                }
                else{
                    dmg1=dmg1+(x[i].getValue()*(1-(0.05*(h.GetArmor())/(1+(0.05*(h.GetArmor()))))));
                }
            }
            for(i=0;i<y.size();i++){
                if(x[i] instanceof Skill){
                    dmg2=dmg2+(y[i].getValue()*(1-magicResistance/100));
                    m2=m2-s.getManaCost();
                    }
                else{
                    dmg2=dmg2+(y[i].getValue()*(1-(0.05*GetArmor()/(1+(0.05*GetArmor())))));
                }
            }
            if(hp2<=dmg1){
                check=false;
                if(hp1<=dmg2)
                    return 't';
                    //std::cout<<"Fight is tied"<<std::endl;

                else
                    return 'w';
                    //std::cout<<"Memes "/*Hero::getName()*/<<" won"<<" in "<<i<<" seconds"<<std::endl;
            }
            else{
                if(hp1<=dmg2){
                    check=false;
                    return 'l';
                    //std::cout<<"Mememino "/*Hero::getName()*/<<" won"<<" in "<<i<<" seconds"<<std::endl;
                }
            }
        }
        return 0;
    }
    public LinkedList<Skill> getSkill(){
        return skills;
    }
}
