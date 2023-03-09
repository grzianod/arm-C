		.data
			length: .byte 40
			A: .byte -69,-165,23,35,83,-139,66,-240,-40,6,-126,-11,-230,211,-101,145,-3,-34,57,0,145,66,-174,149,226,-140,251,-219,144,-24,-61,-69,-51,30,-127,36,-195,55,-109
			B: .byte 184,142,-200,214,42,227,-173,-110,60,65,-33,179,-66,159,120,-46,251,60,118,-156,187,73,196,-92,243,-229,23,-256,213,131,-175,-226,195,134,-60,-60,-161,-57,-199,-211
			C: .space 80	;considering that the result could be 9-bit length in the worst case each element of C will be stored in 2 bytes
			min: .word16 0
			max: .word16 0

		.text
main: 	daddu R3, R0, R0	;result register
	daddu R4, R0, R0	;counter
	lb R6, length(R0)
	lh R7, min(R0)
	lh R8, max(R0)
loop: 	lb R1, A(R4)
	lb R2, B(R4)
	dadd R3, R1, R2
	daddi R9, R0, 2
	dmul R10, R4, R9	;multipling index by two to store result values in 2-bytes
 	sh R3, C(R10)
	
	lh R7, min(R0)
	lh R8, max(R0)

	slt R9,R3, R7
	bnez R9, newMin
	j endMin
	
newMin: sh R3, min(R0)
endMin: dsub R9, R8, R3
	slt R9, R9, R0
	bnez R9, newMax
	j endLoop

newMax: sh R3, max(R0)
endLoop: daddi R4, R4, 1
	bne R4, R6, loop
	halt