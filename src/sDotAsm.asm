public sDotAsm

DotSegment segment	read execute
;rcx contains *x rdx contains *y r8 conains len
sDotAsm PROC

	xorps xmm0, xmm0
	test r8,r8
	jz L2
	xor rax, rax
	
L1:
	movups xmm1, dword ptr [rcx + rax]
	movups xmm2, dword ptr [rdx + rax]
	mulps xmm1,xmm2
	haddps xmm1,xmm1
	haddps xmm1,xmm1
	addss xmm0,xmm1
	add rax, 16
	sub r8, 4
	jnz L1
L2:
	ret
sDotAsm ENDP


DotSegment ends

END