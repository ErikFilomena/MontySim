
.code

;rcx contains *x, rdx constains *y, r8 contains *dst r9 contains len
sHadAsm PROC
	
L1:	
	vmovups ymm0, ymmword ptr [rcx]
	vmovups ymm1, ymmword ptr [rdx]
	vmulps	ymm2,ymm1,ymm0 
	vmovups ymmword ptr [r8], ymm2
	add rcx, 32
	add rdx, 32
	add r8, 32
	sub r9, 8
	ret
sHadAsm ENDP

END