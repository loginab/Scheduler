#define RAND_MAX 0x7fffffff;
#define RAND_MX  32767;

double pw(double number,double power)
{
        double i=0,k=number;
        if (number ==0)
                printf("\n Floating point exception");
        if(power==0)
                return 1;
        for( i=2;i<=power;i++)
                number=number*k;
        return number;
}


double log(double dummy )
{
        int i=1;
        double sum=0;
        for (i=1;i<=20;i++)
        {       if (i%2!=0)
                        sum+=(pw(dummy-1,i)/i);
                else
                        sum-=(pw(dummy-1,i)/i);
        }
return sum;
}

double expdev(double lambda)
{       
	double dummy;
        do
        {
                dummy =(double)rand()/RAND_MX;
         }while(dummy==0);
//        printf ("\n%d",(int)(-log(dummy)/lambda));
	return -log(dummy)/lambda;

}


