import java.util.LinkedList;
public class Use {
    public static void main(Strin[] args){
        LinkedList<Skill> s;
        LinkedList<BaseAttack> b;
        b.add(new BaseAttack(10,1,1,1));
        b.add(new BaseAttack(20,1,2,1));
        s.add(new Skill(200,"Storm Hammer",175,0.3,13,600,1000,2));
        s.add(new SKill(100,"First",1,1,1,1,1,2));
        s.add(new SKill(10,"Second",10,20,30,10,10,2,true);
        s.add(new SKill(10,"Third",10,20,30,10,10,2,true);
        s.add(new SKill(10,"Fourth",10,20,30,10,10,2,true));
        Hero h2=new Hero(b[0],"Grimmstroke",18,20,22,150,100,0,0,12);
        Hero h1=new Hero(b[1],"Sven",25,18,20,200,75,2,0,12);

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

        if(b[0].equals(b[1])
            System.out.print("I due attacchi sono uguali\n");
        else
            System.out.print("I due attacchi sono diversi\n");

        resb=b[0].sum(b[1]);
        System.out.print("La somma dei due attacchi è: "+resb+"\n");

        resb=b[0].dif(b[1];
        System.out.print("La differenza dei due attacchi è: "+resb+"\n");

        //OPERAZIONI SKILL
        int mana=600;

        check=s[0].isCastable(time, distance);
        System.out.print("La skill "+s[0].getName+" è castabile in "+time+" secondi\n";

        check=s[0].isCastable(time, distance,mana);
        System.out.print("La skill "+s[0].getName+" è castabile in "+time+" secondi con "+mana+" mana\n";

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













}
