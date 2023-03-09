		.data
			ifmap: 	.byte 0,0,0,0,0,0,1,2,3,0,0,4,5,6,0,0,7,8,9,0,0,0,0,0,0
			kernel: .byte 0,-1,-1,0,2,1,1,0,4
			ofmap: .space 9
			
		.text
			dadd R1, R0, R0		;starting element offset in ifmap matrix
			dadd R3, R3, R0		;submatrix iteration index
			dadd R4, R0, R0		;kernel matrix iteration index
			dadd R5, R5, R0		
			daddui R7, R0, 3	;kernel matrix dimension
			daddui R6, R0, 5	;ifmap matrix dimension
			dadd R20, R0, R0
			
newSubMatrix:	dadd R2, R0, R1
				dadd R4, R0, R0
				dadd R3, R0, R0
				dadd R12, R0, R0
				dmul R18, R5, R6
				dadd R18, R18, R7
 subMatrix: 	lb R10, ifmap(R2)
				lb R11, kernel(R4)
				dmul R11, R10, R11
				dadd R12, R12, R11
				daddui R2, R2, 1
				daddui R4, R4, 1
			
				dmul R8, R3, R6
				dadd R8, R8, R7
				dadd R8, R8, R1
			
				slt R9, R2, R8
				bnez R9, subMatrix
				daddui R2, R2, 2
				daddui R3, R3, 1
				slt R9, R3, R7
				bnez R9, subMatrix
				sb R12, ofmap(R20)
				daddui R20, R20, 1
				daddui R1, R1, 1
			
				
				slt R9, R1, R18
				bnez R9, newSubMatrix
				
				daddui R1, R1, 2
				daddui R5, R5, 1
				slt R9, R5, R7
				bnez R9, newSubMatrix
				halt
				
			
			
			
			
			
			
			
			
			