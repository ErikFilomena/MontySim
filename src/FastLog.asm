;computes a = inf_a s.t. base^a>= val
public FastLogasm


.code

;rcx contain base rdx constains val
FastLogasm PROC
	push rdx
	push r9
	mov rax, rdx
	xor rdx,rdx
	xor r9,r9
L1:
	inc r9
	div ecx
	xor rdx,rdx
	and eax, eax
	jne L1
	mov rax, r9
	pop r9
	pop rdx
	ret
FastLogasm ENDP
END
