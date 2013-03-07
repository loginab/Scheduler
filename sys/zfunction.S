.text 
	.global zfunction
zfunction:

push %ebp		#setup the stack frame
mov %esp,%ebp
mov 0x8(%ebp),%eax
AND $0xff00ffff,%eax	#clearing bits
sar $8,%eax
AND $0x00ffffff,%eax	#setting bit to 0
#mov %ebp, %esp
pop %ebp
ret 
