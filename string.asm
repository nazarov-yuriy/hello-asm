section .text
	global astrlen

astrlen:
	;rdi - arg1 - char *
	mov		rcx, -1
	xor		al, al
	cld
	repnz scasb

	mov		rax, -2
	sub		rax, rcx
	ret