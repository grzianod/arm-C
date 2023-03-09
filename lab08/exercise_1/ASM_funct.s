				AREA check_square_function, CODE, READONLY				
                EXPORT  check_square
check_square PROC
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}
				
				; setup a value for R0 to return
				LDR R6, [R0]
				LDR R7, [R1]
				MUL R6, R6, R6
				MUL R7, R7, R7
				ADD R8, R6, R7
				MUL R2, R2, R2
				
				SUBS R8,R8, R2
				MOVLE R0, #1
				MOVGT R0, #0
				
				
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                ENDP
			
		
				AREA my_division_function, CODE, READONLY				
                EXPORT my_division
my_division PROC
				IMPORT __aeabi_fdiv
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}
				
				; setup a value for R0 to return
				LDR R6, [R0]
				LDR R7,[R1]
				MOV R1, R6
				MOV R0, R7
				BL __aeabi_fdiv
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                ENDP
				END