#include<sched.h>
int SCHCLASS =0;
void setschedclass(int sched_class)
{
	SCHCLASS=sched_class;
}

int getschedclass()
{
	return SCHCLASS ;
}
