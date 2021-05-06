.data
	seed dword 8784

.code
RanduSetSeed PROC
	mov seed, ecx
	push rsp
	lea rsp, [rsp-20h]
	call Randu	
	lea rsp, [rsp + 20h]
	pop rsp
	ret
RanduSetSeed ENDP

Randu PROC
	mov eax, seed
	mov r8d, eax
	xor rdx, rdx
	mov ecx, 65539
	mul ecx
	mov ecx, 80000000h
	div rcx
	mov eax, edx
	mov seed, eax
	mov eax, r8d
	ret
Randu ENDP

END