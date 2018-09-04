import java.util.LinkedList;
public class Use {
    public static void main(Strin[] args){
        LinkedList<Skill> s;
        LinkedList<BaseAttack> b;
        b.add(new BaseAttack(10,1,1,1));
        b.add(new BaseAttack(20,1,2,1));
        s.add(new Skill(200,"Storm Hammer",175,0.3,13,600,1000,2));
        s.add(new SKill(100,"First",1,1,1,1,1,2));
        s.add(new SKill(10,"Second",10,20,30,10,10,2,true));
        s.add(new SKill(10,"Third",10,20,30,10,10,2,true));
        s.add(new SKill(10,"Fourth",10,20,30,10,10,2,true));
        Hero h2=new Hero(b[0],"Grimmstroke",18,20,22,150,100,0,0,12);
        Hero h1=new Hero(b[1],"Sven",25,18,20,200,75,2,0,12);
        SummonedUnit s1=new SummonedUnit(20,1,2,1,"Creep",200,1,1.2)
        SummonedUnit s2=new SummonedUnit(30,1.2,4,1,"Creep",150,1,1.3)


        //OPERAZIONI BASEATTACK
        double time=20;
        int distance=1;
        boolean check=B[0].isCastable(time,distance);
        if(check)
            System.out.print("L'attacco b[0] è castabile in "+time+" secondi\n");
        else
            System.out.print("L'attacco b[0] è castabile in "+time+" secondi\n");

        int res=b[0].HitByTime(time,distance);
        System.out.print("L'attacco b[0] colpisce "+res+" volte in "+time+" secondi\n");

        double resb=b[0].DPS(distance);
        System.out.print("L'attacco b[0] fa "+res+" DPS\n");

        resb=b[0].DamageByTime(time,distance);
        System.out.print("L'attacco b[0] fa "+resb+" danni in "+time+" secondi\n");

        resb=b[0].getAnim();
        System.out.print("L'attacco b[0] ha "+resb+" di animazione\n");

        res=b[0].getRange();
        System.out.print("L'attacco b[0] ha "+res+" di range\n");

        if(b[0].equals(b[1]))
            System.out.print("I due attacchi sono uguali\n");
        else
            System.out.print("I due attacchi sono diversi\n");

        resb=b[0].sum(b[1]);
        System.out.print("La somma dei due attacchi è: "+resb+"\n");

        resb=b[0].dif(b[1]);
        System.out.print("La differenza dei due attacchi è: "+resb+"\n");

        //OPERAZIONI SKILL
        int mana=600;

        check=s[0].isCastable(time, distance);
        System.out.print("La skill "+s[0].getName+" è castabile in "+time+" secondi\n");

        check=s[0].isCastable(time, distance,mana);
        System.out.print("La skill "+s[0].getName+" è castabile in "+time+" secondi con "+mana+" mana\n");

        resb=s[0].DPS(distance);
        System.out.print("La skill fa "+resb+" DPS\n");

        resb=s[0].DamageByTime(time,distance);
        System.out.print("La skill fa "+resb+" danni in "+time+" secondi\n");

        res=s[0].HitByTime(time,distance);
        System.out.print("La skill fa "+res+" colpi in "+time+" secondi\n");

        resb=s[0].totalTime(distance);
        System.out.print("La skill colpisce in "+resb+" secondi\n");

        resb=s[0].getAnimation();
        res=s[0].getCooldown();
        System.out.print("La skill"+s[0].getName()+" ha una animazione di "+resb" secondi, un cooldown di "+res+" secondi e costa "+s[0].getMana()+" mana\n");

        s[0].setReady(true);
        check=s[0].getReady();
        if(check)
            System.out.print("La skill e pronta\n");
        else
            System.out.print("La skill non e pronta\n");

        check=s[0].equals(s[0]);
        if(check)
            System.out.print("Le skill "+s[0].getName()+" e "+s[0].getName()+" sono uguali\n");
        else
            System.out.print("Le skill "+s[0].getName()+" e "+s[0].getName()+" sono diverse\n");

        resb=s[0].sum(s[1]);
        System.out.println("Le skill "+s[0].getName()+" e "+s[0].getName()+" hanno somma: "+resb);

        resb=s[0].dif(s[1]);
        System.out.println("Le skill "+s[0].getName()+" e "+s[0].getName()+" hanno differenza: "+resb);

        //OPERAZIONI HERO
        h1.InsertSkill(s[1]);
        LinkedList<Skill> sl=h1.getSkill();
        for(int i=0;i<sl.size;i++){
            System.out.print("L'eroe ha la skill "+sl[i].getName()+"\n");
            }

        System.out.print("L'eroe "+h1.getName()+" ha "+h1.GetArmor()+"di armor, "+h1.GetHP()+" hp, "+GetMP()+" MP e "+h1.getMagicResistance()+"% di magic resistance\n");

        resb=h1.getLongestReadySkill();
        System.out.print("L'animazione della skill più lunga è: "+resb+"\n");

        LinkedList<Damage> resl=h1.MaxDamageByTime(time,h1.getMana());
        for(int i=0;i<resl.size();i++){
            if(resl[i] instanceof BaseAttack)
                System.out.print("L'eroe usa l'attacco base\n");
            else
                System.out.print("L'eroe usa la skill "+resl[i].getName()"\n");
            }

        resb=h1.MaxDamageByTimeDMG(time,h1.getMana());
        System.out.print("L'eroe fa "+resb+" danni in "+time+" secondi\n");

        char f=h1.fight(h2);
        if(f=='w')
            System.out.print(h1.getName()+" won\n");
        else{
            if(f=='l')
                System.out.print(h2.getName()+" won\n");
            else
                System.out.print("Fight tied \n")
            }

        //OPERAZIONI SUMMONED UNIT
        resb=s1.DPS();
        System.out.print("La Summoned Unit "+s1.getSUMname()+" fa "+resb+" DPS\n")

        resb=s1.DamageByTime(time);
        System.out.print("La Summoned Unit "+s1.getSUMname()+" fa "+resb+" danni in "+time+"secondi\n")

        f=s1.fight(s1);
        if(f=='w')
            System.out.print(s1.getName()+" won\n");
        else{
            if(f=='l')
                System.out.print(s2.getName()+" won\n");
            else
                System.out.print("Fight tied \n")
            }

        System.out.print("La Summoned Unit "+s2.getName()+" ha "+s1.getHp()+" hp ed e' di livello "+s1.getLevel()+"\n");
        }






















}
