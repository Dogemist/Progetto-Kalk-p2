public class SummonedUnit extends BaseAttack{
    private String SUMname;
    private int HP;
    private int level;
    private double multiplier;
    public SummonedUnit(double v,double an,int ra,int ps,String n,int h,int l,int m){
        super(v,an,ra,ps);
        SUMname=n;
        HP=h;
        level=l;
        multiplier=m;
        }
    public double DPS{
        super.DPS()*level*multiplier;
        }
    public double DamageByTime(double time){
        super.DamageByTime(time)*level*multiplier;
        }
    public char Fight(SummonedUnit s){
        int hp1,hp2;
        hp1=getHp();
        hp2=s.getHp();
        for(double i=0;hp1>0&&hp2>0;i+=0.2){
            if(DamageByTime(i)>=hp2){
                hp2=0;
                if(s.DamageByTime(i)>=hp1){
                    hp1=0;
                    return 't';
                }else
                    return 'w';
            }else if(s.DamageByTime(i)>=hp1)
                    return 'l';
        }
        return '0';

        }
    public int getHp(){
        return HP;
        }
    public String getSUMname(){
        return SUMname;
        }
    public int getLevel(){
        return level;
        }

}
