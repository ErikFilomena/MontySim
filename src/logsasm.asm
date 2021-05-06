.data
extern __vdecl_logf8: PROC
.code 
useasm PROC
	vmovups ymm0,ymmword ptr [rcx]
	call __vdecl_logf8
	vhaddps ymm0, ymm0,ymm0
	vperm2f128	ymm1,ymm0,ymm0,1
	addps xmm0, xmm1
	haddps xmm0, xmm0
	ret
useasm ENDP

END