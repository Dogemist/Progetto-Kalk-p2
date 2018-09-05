import java.util.*;
import java.lang.Double;
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
        return (int)(bArmor+agl*0.16);
        }
    public int GetHP(){
        return (int)(bHp+str*18);
        }
    public int GetMP(){
        return (int)(bMp+inte*12);
        }
    public String getName(){
        return Hname;
        }
    public int getMagicResistance(){
        return magicResistance;
        }
    public Skill getSkill(int i){
        return skills.get(i);
        }
    public double getLongestReadySkill(int distance){
        double max=0;
        for(int i=0;i<4;i++){
            if(skills.get(i).IsCastable(9999,distance)&&skills.get(i).getAnimation()>max)
                max=skills.get(i).getAnimation();
            }
        return max;
    }

    public LinkedList<Damage> MaxDamageByTime(double time,int mana){
        double max;
        double maxDmg;
        int index;
        LinkedList<Damage> v=new LinkedList<Damage>();
        LinkedList<Double> timing=new LinkedList<Double>();
        for(double i=0;i<time;i+=0.2){
            index=0;
            for(int l=0;l<v.size();l++){
                if(v.get(l) instanceof Skill){
                    if(i-timing.get(index)>=((Skill)v.get(l)).getCooldown())
                        ((Skill)v.get(l)).setReady(true);
                    else
                        ((Skill)v.get(l)).setReady(false);
                }
            index++;
            }
        max=0;
        Damage d=new BaseAttack(0,0,0,0);
        for(int l=0;l<4;l++){
            if(skills.get(l).getAnimation()>max&&skills.get(l).IsCastable(time-i,0))
                max=skills.get(l).getAnimation();
        }
        maxDmg=0;
        double oldmaxDmg=-1;
        double rem=time-i;
        if(super.IsCastable(rem,0)){
            if(super.getAnim()>max)
                max=super.getAnim();
                maxDmg=super.DamageByTime(max,0);
            }
        if(maxDmg>0){
            oldmaxDmg=maxDmg;
            }
        for(int l=0;l<4;l++){
            double checkDBT=skills.get(l).DamageByTime(max,0);
            if(checkDBT>maxDmg&&skills.get(l).getReady()&&mana>skills.get(l).getManaCost()){
                maxDmg=checkDBT;
                d=(skills.get(l));
            }
        }
        if(oldmaxDmg==maxDmg){
            if(maxDmg>0)
                d=((BaseAttack)this);
        }
    if(d instanceof Skill){
        if(((Skill)d).getReady()){
           if(((Skill)d).totalTime(0)*((Skill)d).HitByTime(max,0)<max)
              max=((Skill)d).totalTime(0)*((Skill)d).HitByTime(max,0);
              mana=mana-((Skill)d).getManaCost();
              v.add((Skill)d);
              timing.add(i);
            }
     }
    else{
         if(d instanceof BaseAttack&&d.getValue()>0){
            BaseAttack b=(BaseAttack)d;
            if(b.getValue()>0)
                if(super.getAnim()*super.HitByTime(max,0)<max)
                    max=super.getAnim()*super.HitByTime(max,0);
            for(int l=0;l<super.HitByTime(max,0);l++){
                v.add(b);
                timing.add(i+l*super.getAnim());
            }
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
            total=total+v.get(i).getValue();
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
            for(int m=0;m<x.size();m++){
                if(x.get(m) instanceof Skill){
                    dmg1=dmg1+((Skill)x.get(m)).getValue()*(1-h.getMagicResistance()/100);
                    m1=m1-((Skill)x.get(m)).getManaCost();
                }
                else{
                    dmg1=dmg1+(x.get(m).getValue()*(1-(0.05*(h.GetArmor())/(1+(0.05*(h.GetArmor()))))));
                }
            }
            for(int m=0;m<y.size();m++){
                if(y.get(m) instanceof Skill){
                    dmg2=dmg2+(y.get(m).getValue()*(1-magicResistance/100));
                    m2=m2-((Skill)y.get(m)).getManaCost();
                    }
                else{
                    dmg2=dmg2+(y.get(m).getValue()*(1-(0.05*GetArmor()/(1+(0.05*GetArmor())))));
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
