section .text
	global adump

adump:
	mov		[rdi+0], rax
	mov		[rdi+8], rbx
	mov		[rdi+16], rcx
	mov		[rdi+24], rdx

	mov		[rdi+32], rsi
	mov		[rdi+40], rdi
	mov		[rdi+48], rsp
	mov		[rdi+56], rbp

	mov		[rdi+64], r8
	mov		[rdi+72], r9
	mov		[rdi+80], r10
	mov		[rdi+88], r11

	mov		[rdi+96], r12
	mov		[rdi+104], r13
	mov		[rdi+112], r14
	mov		[rdi+120], r15
	add		rdi, 128

	vmovdqa	[rdi+0], ymm0
	vmovdqa	[rdi+32], ymm1
	vmovdqa	[rdi+64], ymm2
	vmovdqa	[rdi+96], ymm3
	add		rdi, 128

	vmovdqa	[rdi+0], ymm4
	vmovdqa	[rdi+32], ymm5
	vmovdqa	[rdi+64], ymm6
	vmovdqa	[rdi+96], ymm7
	add		rdi, 128

	vmovdqa	[rdi+0], ymm8
	vmovdqa	[rdi+32], ymm9
	vmovdqa	[rdi+64], ymm10
	vmovdqa	[rdi+96], ymm11
	add		rdi, 128

	vmovdqa	[rdi+0], ymm12
	vmovdqa	[rdi+32], ymm13
	vmovdqa	[rdi+64], ymm14
	vmovdqa	[rdi+96], ymm15
	add		rdi, 128

	fxsave	[rdi]
	ret