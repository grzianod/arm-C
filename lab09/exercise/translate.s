	AREA translate_func, CODE, READONLY
	EXPORT translate
	
store PROC
		IMPORT _table
			
		LDR R0, =_table
		LDRB R1, [R0, R10]
		STRB R1, [R2, R3]
		
		BX LR
	ENDP
		
translate		PROC
				IMPORT _table
				IMPORT  LED_Out
                LDR     R12, =LED_Out
				LDMFD SP!, {R4-R6}
				MOV R9, #1
				SUB R3, R3, #1
				MOV R11, R3
				SUB R1, R1, #1
				SUB R7, R7, #1
				
loop			LDRB R8, [R0, R1]

				CMP R8, #48
				MULEQ R8, R8, R9
				ADDEQ R10, R10, R8
				LSLEQ R9, R9, #1
				
				
				CMP R8, #49
				MULEQ R8, R8, R9
				ADDEQ R10, R10, R8 
				LSLEQ R9, R9, #1
				
				CMP R8, R4
				
				STMFDEQ SP!, {R0-R12, LR}
				BLEQ store
				LDMFDEQ SP!, {R0-R12, LR}
				SUBEQ R3, R3, #1
				
				STREQ R0, [SP, #4]
				SUBEQ R9, R11, R3
				MOVEQ R0, R9
				STMFDEQ SP!, {R0-R4, LR}
				BLXEQ R12
				LDMFDEQ SP!, {R0-R4, LR}
				LDREQ R0, [SP, #4]
				MOVEQ R9, #1
				MOVEQ R10, #0
				
				CMP R8, R5
				
				STMFDEQ SP!, {R0-R12, LR}
				BLEQ store
				LDMFDEQ SP!, {R0-R12, LR}
				SUBEQ R3, R3, #1
				
				STREQ R0, [SP, #4]
				SUBEQ R9, R11, R3
				MOVEQ R0, R9
				STMFDEQ SP!, {R0-R4, LR}
				BLXEQ R12
				LDMFDEQ SP!, {R0-R4, LR}
				LDREQ R0, [SP, #4]
				
				MOVEQ R10, #32
				STRBEQ R10, [R2, R3]
				SUBEQ R3, R3, #1
				
				STREQ R0, [SP, #4]
				SUBEQ R9, R11, R3
				MOVEQ R0, R9
				STMFDEQ SP!, {R0-R4, LR}
				BLXEQ R12
				LDMFDEQ SP!, {R0-R4, LR}
				LDREQ R0, [SP, #4]
				MOVEQ R9, #1
				MOVEQ R10, #0
				
				CMP R8, R6
				MOVEQ R9, #1
				MOVEQ R10, #0
				
				SUB R1, R1, #1
				CMP R1, #0
				
				BGE loop
				
				STMFD SP!, {R0-R12, LR}
				BL store
				LDMFD SP!, {R0-R12, LR}
				SUB R3, R3, #1
				
				STR R0, [SP, #4]
				SUB R9, R11, R3
				MOV R0, R9
				STMFD SP!, {R0-R4, LR}
				BLX R12
				LDMFD SP!, {R0-R4, LR}
				LDR R0, [SP, #4]
				
				STMFD SP!, {R0-R12, LR}
				MOV R0, #255
				BLX R12
				LDMFD SP!, {R0-R12, LR}
				
				MOV R0, R11
				ADD R0, R0, #1
				STMFD SP!, {R4-R6}
				BX LR
				
				ENDP
	END