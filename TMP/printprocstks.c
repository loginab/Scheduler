
#include <conf.h>
#include <kernel.h>
#include <proc.h>



void printprocstks(int priority)
{

	int i;
	struct pentry   *proc ;
	printf("\n\n Task 4 (printprocstks)");
	for(i=0;i<NPROC;i++)
	{	
		proc = &proctab[i];
		if (proc->pprio<priority && proc->pstate !=2)
			{
				printf("\n Process [%s]",proc->pname);
				printf("\n\t pid: %d",i);
				printf("\n\t prority: %d",proc->pprio);
				printf("\n\t base: 0x%08X",proc->pbase);
				printf("\n\t limit: 0x%08X",proc->plimit);
				printf("\n\t len: %d",proc->pstklen);

					printf("\n\t pointer: 0x%08X",proc->pesp);
			}
	}
}
