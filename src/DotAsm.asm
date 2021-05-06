public DotAsm

.code
;rcx contains *x rdx contains *y r8 conains len
DotAsm PROC
	mov rax, 0
	xorps xmm0, xmm0
L1:
	movups xmm1, dword ptr [rcx + rax]
	movups xmm2, dword ptr [rdx + rax]
	mulps xmm1,xmm2
	haddps xmm1,xmm1
	haddps xmm1,xmm1
	addss xmm0,xmm1
	add rax, 16
	sub r8, 4
	test r8,r8
	jnz L1
	ret
DotAsm ENDP

END