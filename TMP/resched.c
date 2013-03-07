/* resched.c  -  resched */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <math.h>
#include <sched.h>
unsigned long currSP;	/* REAL sp of current process */

int firstEpoch =1;
int EPOCH=0;

extern int ctxsw(int, int, int, int);
/*-----------------------------------------------------------------------
 * resched  --  reschedule processor to highest priority ready process
 *
 * Notes:	Upon entry, currpid gives current process id.
 *		Proctab[currpid].pstate gives correct NEXT state for
 *			current process if other than PRREADY.
 *------------------------------------------------------------------------
 */
int resched()
{
	register struct	pentry	*optr;	/* pointer to old process entry */
	register struct	pentry	*nptr;	/* pointer to new process entry */
	double eds;
	int k;
	/* no switch needed if current process priority higher than next*/
	
	if(getschedclass()==0)
	{
		if ( ( (optr= &proctab[currpid])->pstate == PRCURR) &&
		   (lastkey(rdytail)<optr->pprio)) {
			return(OK);
		}
	
		/* force context switch */

		if (optr->pstate == PRCURR) {
			optr->pstate = PRREADY;
			insert(currpid,rdyhead,optr->pprio);
		}

		/* remove highest priority process at end of ready list */

		nptr = &proctab[ (currpid = getlast(rdytail)) ];
		nptr->pstate = PRCURR;		/* mark it currently running	*/
		#ifdef	RTCLOCK
		preempt = QUANTUM;		/* reset preemption counter	*/
		#endif
	
		ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
	
		/* The OLD process returns here when resumed. */
		return OK;
	}	
	else if(getschedclass()==1)
	{	int next;
		eds=(int)expdev(.1);
		//kprintf("\neds %d",(int)eds);
		optr= &proctab[currpid];
		if (optr->pstate == PRCURR) {
			optr->pstate = PRREADY;
			insert(currpid,rdyhead,optr->pprio);
		}
		
		if( q[q[rdytail].qprev].qkey < eds)
		{
				next=q[rdytail].qprev;
		} 	
		else
		{	next=q[rdyhead].qnext;
			while (q[next].qkey < eds)
			{	
				next=q[next].qnext; 
		//		kprintf("\n %d  , %d", next,q[next].qkey);
			}
		}
		currpid=dequeue(next);
		nptr = &proctab[currpid];
		nptr->pstate = PRCURR;		/* mark it currently running	*/
		#ifdef	RTCLOCK
		preempt = QUANTUM;		/* reset preemption counter	*/
		#endif
		ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
		return OK;		
	}
	else
	{	int next,epoch,max=0,pid=0,flag=1;
		struct pentry *temp;
		optr= &proctab[currpid];
		if (optr->pstate == PRCURR) {
                        optr->pstate = PRREADY;
                        insert(currpid,rdyhead,optr->pprio);
                }
		
/*		if (firstEpoch==1)
		{
			firstEpoch=0;
							//Caclulate the quantum and goodness
			next=q[rdyhead].qnext;
			while(next !=rdytail)
			{
				temp=&proctab[next];
				temp->quantum=temp->pprio;
				temp->goodness=temp->pprio+temp->quantum;
				next=q[next].qnext;
			}
							//select maximum goodness
			next=q[rdyhead].qnext;max=0;pid=0;
			while(next !=rdytail)
			{
				temp=&proctab[next];
				if(temp->quantum>0)
				{
					if (temp->goodness > max)
					{
						max=temp->goodness;
						pid=next;
					}
				}
				next=q[next].qnext;
			}
			currpid=dequeue(pid);
			nptr = &proctab[currpid];
			nptr->pstate = PRCURR;	
			#ifdef	RTCLOCK
			preempt = nptr->quantum;	
			#endif
			ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
			return OK;		
			
		} 
		else
*/		{
			optr->goodness=optr->goodness-(optr->quantum-preempt);
			optr->quantum=preempt;
							//check for new epoch

			next=q[rdyhead].qnext;flag=1;
			while(next != rdytail)
			{	
				temp=&proctab[next];
				if (temp->quantum !=0)
				{
					flag=0;
				}
				next=q[next].qnext;
			}
			if (flag==1)
			{
								//Caclulate the quantum and goodness
				next=q[rdyhead].qnext;
				while(next !=rdytail)
				{
					temp=&proctab[next];
					temp->quantum=temp->pprio+((int)temp->quantum/2);
					temp->goodness=temp->pprio+temp->quantum;
					next=q[next].qnext;
				}
			}
								//Calculate maximu goodness
			next=q[rdyhead].qnext;max=0;pid=0;
			while(next !=rdytail)
			{
				temp=&proctab[next];
				if(temp->quantum>0)
				{
					if (temp->goodness > max)
					{
						max=temp->goodness;
						pid=next;
					}
				}
				next=q[next].qnext;
			}
			currpid=dequeue(pid);
			nptr = &proctab[currpid];
			nptr->pstate = PRCURR;		/* mark it currently running	*/
			#ifdef	RTCLOCK
			preempt = nptr->quantum;		/* reset preemption counter	*/
			#endif
			ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
			return OK;		
			

		}


	}
}			
