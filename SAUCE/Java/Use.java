import java.util.LinkedList;
public class Use {
    public static void main(String[] args){
        LinkedList<Skill> s;
        LinkedList<BaseAttack> b;
        b.add(new BaseAttack(10,1,1,1));
        b.add(new BaseAttack(20,1,2,1));
        s.add(new Skill(200.0,"Storm Hammer",175,0.3,13,600,1000.0,2));
        s.add(new Skill(100.0,"First",1,1.0,1,1,1.0,2));
        s.add(new Skill(10.0,"Second",10,20.0,30,10,10.0,2));
        s.add(new Skill(10.0,"Third",10,20.0,30,10,10.0,2));
        s.add(new Skill(10.0,"Fourth",10,20.0,30,10,10.0,2));
        Hero h2=new Hero(b.get(0),"Grimmstroke",18,20,22,150,100,0,0,12);
        Hero h1=new Hero(b.get(1),"Sven",25,18,20,200,75,2,0,12);
        SummonedUnit s1=new SummonedUnit(20,1,2,1,"Creep",200,1,1);
        SummonedUnit s2=new SummonedUnit(30,1.2,4,1,"Creep",150,1,1);


        //OPERAZIONI BASEATTACK
        double time=20;
        int distance=1;
        boolean check=B.get(0).isCastable(time,distance);
        if(check)
            System.out.print("L'attacco b.get(0) è castabile in "+time+" secondi\n");
        else
            System.out.print("L'attacco b.get(0) è castabile in "+time+" secondi\n");

        int res=b.get(0).HitByTime(time,distance);
        System.out.print("L'attacco b.get(0) colpisce "+res+" volte in "+time+" secondi\n");

        double resb=b.get(0).DPS(distance);
        System.out.print("L'attacco b.get(0) fa "+res+" DPS\n");

        resb=b.get(0).DamageByTime(time,distance);
        System.out.print("L'attacco b.get(0) fa "+resb+" danni in "+time+" secondi\n");

        resb=b.get(0).getAnim();
        System.out.print("L'attacco b.get(0) ha "+resb+" di animazione\n");

        res=b.get(0).getRange();
        System.out.print("L'attacco b.get(0) ha "+res+" di range\n");

        if(b.get(0).equals(b.get(1)))
            System.out.print("I due attacchi sono uguali\n");
        else
            System.out.print("I due attacchi sono diversi\n");

        resb=b.get(0).sum(b.get(1));
        System.out.print("La somma dei due attacchi è: "+resb+"\n");

        resb=b.get(0).dif(b.get(1));
        System.out.print("La differenza dei due attacchi è: "+resb+"\n");

        //OPERAZIONI SKILL
        int mana=600;

        check=s.get(0).isCastable(time, distance);
        System.out.print("La skill "+s.get(0).getName+" è castabile in "+time+" secondi\n");

        check=s.get(0).isCastable(time, distance,mana);
        System.out.print("La skill "+s.get(0).getName+" è castabile in "+time+" secondi con "+mana+" mana\n");

        resb=s.get(0).DPS(distance);
        System.out.print("La skill fa "+resb+" DPS\n");

        resb=s.get(0).DamageByTime(time,distance);
        System.out.print("La skill fa "+resb+" danni in "+time+" secondi\n");

        res=s.get(0).HitByTime(time,distance);
        System.out.print("La skill fa "+res+" colpi in "+time+" secondi\n");

        resb=s.get(0).totalTime(distance);
        System.out.print("La skill colpisce in "+resb+" secondi\n");

        resb=s.get(0).getAnimation();
        res=s.get(0).getCooldown();
        System.out.print("La skill"+s.get(0).getName()+" ha una animazione di "+resb+" secondi, un cooldown di "+res+" secondi e costa "+s.get(0).getMana()+" mana\n");

        s.get(0).setReady(true);
        check=s.get(0).getReady();
        if(check)
            System.out.print("La skill e pronta\n");
        else
            System.out.print("La skill non e pronta\n");

        check=s.get(0).equals(s.get(0));
        if(check)
            System.out.print("Le skill "+s.get(0).getName()+" e "+s.get(0).getName()+" sono uguali\n");
        else
            System.out.print("Le skill "+s.get(0).getName()+" e "+s.get(0).getName()+" sono diverse\n");

        resb=s.get(0).sum(s.get(1));
        System.out.println("Le skill "+s.get(0).getName()+" e "+s.get(0).getName()+" hanno somma: "+resb);

        resb=s.get(0).dif(s.get(1));
        System.out.println("Le skill "+s.get(0).getName()+" e "+s.get(0).getName()+" hanno differenza: "+resb);

        //OPERAZIONI HERO
        h1.InsertSkill(s.get(1));
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
                System.out.print("L'eroe usa la skill "+resl[i].getName()+"\n");
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
                System.out.print("Fight tied \n");
            }

        //OPERAZIONI SUMMONED UNIT
        resb=s1.DPS();
        System.out.print("La Summoned Unit "+s1.getSUMname()+" fa "+resb+" DPS\n");

        resb=s1.DamageByTime(time);
        System.out.print("La Summoned Unit "+s1.getSUMname()+" fa "+resb+" danni in "+time+"secondi\n");

        f=s1.fight(s1);
        if(f=='w')
            System.out.print(s1.getName()+" won\n");
        else{
            if(f=='l')
                System.out.print(s2.getName()+" won\n");
            else
                System.out.print("Fight tied \n");
            }

        System.out.print("La Summoned Unit "+s2.getName()+" ha "+s1.getHp()+" hp ed e' di livello "+s1.getLevel()+"\n");
        }






















}
