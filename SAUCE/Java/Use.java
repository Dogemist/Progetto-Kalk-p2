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





}
