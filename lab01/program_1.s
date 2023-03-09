		.data	
			v1: .byte 1,2,3,4,5,6,7,8,7,6,5,4,3,2,1
			flag: .space 1
			length: .byte 15
			
		.text	
			dadd R1, R0, R0
			lb R2, length(R0)
			daddui R2, R2, -1
	loop:	lb R4, v1(R2)
			lb R3, v1(R1)
			daddui R1, R1, 1
			daddui R2, R2, -1
			beq R1, R2, Pal
			dsub R3, R3, R4
			beqz R3, loop
			
	notPal:	daddui R1, R0, 0
			sb R1, flag(R0)
			j endP
	Pal:	daddui R1, R0, 1
			sb R1, flag(R0)
			
	endP:	halt