public LCGAsm

.code

;rax contains seed cvtsi2sd xmm0,dword ptr [rcx]
LCGAsm PROC
	push rdx
	mov rax, rcx
	mul rdx
	add rax, r8
	div r9
	mov rax, rdx
	pop rdx
	ret
LCGAsm ENDP

END
