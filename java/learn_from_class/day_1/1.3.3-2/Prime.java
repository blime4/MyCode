public class Prime{
    public static void main(String args[]){
        int i,j;
        outer:
        for(i=200;i<=300;i++){
            for(j=2;j<i-1;j++){
                if(i%j==0){
                    continue outer;
                }
            }
            System.out.print(i+" ");
        }
    }
}