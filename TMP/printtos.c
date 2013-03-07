static int    *top;
static int    *var1;
static int    *var2;
static int    *var3;

int printtos(){

int i=1;
int k=2;
int l=3;
int m=4;

asm("mov %ebp,top");
asm("mov %ebp,var2");


//asm("mov 0x10(%esp),%eax");
//asm("movl -0x16(%esp),%eax");
//asm("mov %esp,var1");

printf("\n\n Task 3 (printtos)");
//top+=2;
printf("\n Before[0x%08X]: 0x%08X", top+2,*(top+2));
//top-=2;
printf("\n After[0x%08X]: 0x%08X", top,*top);

var2--;
printf("\n\t element[0x%08X]: 0x%08X ", var2,*var2);
var2--;
printf("\n\t element[0x%08X]: 0x%08X", var2,*var2);
var2--;
printf("\n\t element[0x%08X]: 0x%08X", var2,*var2);
var2--;
printf("\n\t element[0x%08X]: 0x%08X", var2,*var2);


return 0;

}
