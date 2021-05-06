.data
extern CreateThread: PROC
.code

func PROC
	add dword ptr [rcx], 45
	ret
func ENDP


CreateNewThread PROC
	push rbp
	mov rbp, rsp
	mov r9, rcx
	xor rcx,rcx
	xor rdx,rdx
	lea r8, func
	push 0
	push 0
	sub rsp, 20h
	call CreateThread
	mov rsp, rbp
	pop rbp
	ret
CreateNewThread ENDP



END
