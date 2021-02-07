/**
 * @param X : start
 * @param Y : end
 * @return : number of operations
 * */
int brokenCalc(int X, int Y){
        int tamX=X;
        if(X > Y){
            while(X > Y)X--;
            return tamX-X;
        }
        else if(X==Y)return 0;
        else{
            long int cont = 0;         
            while(X<Y){     
                (Y%2==0) ?  Y/=2 : Y++;
                cont++;
            }  
            return cont + X - Y;
        }
}