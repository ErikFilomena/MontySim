public DotAsmAvx

.code
;rcx contains *x rdx contains *y r8 conains len
DotAsmAvx PROC
	mov rax, 0
	xorps xmm0, xmm0
L1:
	vmovups ymm1, ymmword ptr [rdx + rax]
	vmovups ymm2, ymmword ptr [rdx + rax]
	vmulps ymm1, ymm1, ymm2	
	vhaddps ymm1,ymm1, ymm1
	vhaddps ymm1,ymm1, ymm1
	vmovups ymm2,ymm1
	addss xmm0,xmm1
	add rax, 32
	sub r8, 8
	test r8, r8
	jnz L1
	ret
DotAsmAvx ENDP

END


	vhaddps ymm1,ymm1
	vhaddps ymm1,ymm1
	vhaddps ymm1,ymm1
	vhaddps ymm1,ymm1
	addss xmm0,xmm1
	add rax, 32
	sub r8, 8
	test r8, 0
	jnz L1