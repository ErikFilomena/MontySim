public sDotAsmAvx



.code
;rcx contains *x rdx contains *y r8 conains len
sDotAsmAvx PROC
	mov rax, 0
	xorps xmm0, xmm0
L1:
	vmovups ymm1, ymmword ptr [rcx + rax]
	vmovups ymm2, ymmword ptr [rdx + rax]
	vmulps ymm1,ymm1,ymm2
	vperm2f128 ymm2,ymm1,ymm1, 1
	addps xmm1,xmm2
	haddps xmm1,xmm1
	haddps xmm1,xmm1
	addss xmm0,xmm1
	add rax, 32
	sub r8, 8
	test r8, r8
	jnz L1
	ret
sDotAsmAvx ENDP

END
