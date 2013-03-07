.text 
	.global zfunction
zfunction:

push %ebp
mov %esp,%ebp
mov 0x8(%ebp),%eax
AND $0xff00ffff,%eax
sar $8,%eax
AND $0x00ffffff,%eax
#mov %ebp, %esp
pop %ebp
ret 
