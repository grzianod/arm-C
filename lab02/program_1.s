		.data
			v1: 	.double 12.3, 34.5, 15.6, 34.7, 56.9, 10.2, 23.6, 26.8, 98.6, 54.9
					.double 76.7, 90.7, 12.6, 23.9, 67.8, 98.3, 90.2, 10.2, 23.6, 26.8
					.double 10.2, 23.6, 26.8, 98.6, 54.9, 11.1, 09.5, 87.4, 76.7, 90.7
					.double 12.3, 34.5, 15.6, 34.7, 56.9, 10.2, 23.6, 26.8, 98.6, 54.9
					.double 12.3, 34.5, 15.6, 34.7, 56.9, 10.2, 23.6, 26.8, 98.6, 54.9
					.double 12.6, 23.9, 67.8, 98.3, 90.2, 12.3, 34.5, 15.6, 34.7, 56.9
			v2: 	.double 10.2, 23.6, 26.8, 98.6, 54.9, 11.1, 09.5, 87.4, 76.7, 90.7
					.double	90.2, 12.3, 34.5, 15.6, 34.7, 56.9, 12.3, 34.5, 15.6, 34.7
					.double 10.2, 23.6, 26.8, 98.6, 54.9, 11.1, 09.5, 87.4, 76.7, 90.5
					.double 12.3, 34.5, 15.6, 34.7, 56.9, 10.2, 23.6, 26.8, 98.6, 54.9
					.double 10.2, 23.6, 26.8, 98.6, 54.9, 11.1, 09.5, 87.4, 76.7, 90.7
					.double 12.3, 34.5, 15.6, 34.7, 56.9, 10.2, 23.6, 26.8, 98.6, 54.9
			v3: 	.double 12.6, 23.9, 67.8, 98.3, 90.2, 12.3, 34.5, 15.6, 34.7, 56.9
					.double 34.6, 23.6, 88.6, 45.3, 45.7, 98.5, 12.4, 25.4, 67.8, 56.8
					.double 12.5, 34.5, 67.6, 23.8, 72.8, 98.3, 28.7, 27.6, 23.5, 87.4
					.double 11.1, 73.1, 25.7, 37.9, 26.9, 64.8, 41.7, 72.7, 73.7, 88.8
					.double 12.3, 34.5, 15.6, 34.7, 56.9, 10.2, 23.6, 26.8, 98.6, 54.9
					.double 10.2, 23.6, 26.8, 98.6, 54.9, 11.1, 09.5, 87.4, 76.7, 90.5
			v4:	 	.double 11.1, 09.5, 87.4, 76.7, 90.7, 12.6, 23.9, 67.8, 98.3, 90.2
					.double 12.5, 34.5, 67.6, 23.8, 72.8, 98.3, 28.7, 27.6, 23.5, 87.4
					.double 10.2, 23.6, 26.8, 98.6, 54.9, 11.1, 09.5, 87.4, 76.7, 90.7
					.double 90.3, 43.1, 62.7, 25.7, 84.8, 62.6, 72.8, 64.6, 52.4, 73.6
					.double 34.6, 23.6, 88.6, 45.3, 45.7, 98.5, 12.4, 25.4, 67.8, 56.8
					.double 12.6, 23.9, 67.8, 98.3, 90.2, 12.3, 34.5, 15.6, 34.7, 56.9
			v5: 	.space 480
			v6: 	.space 480
			v7: 	.space 480
			length: .byte 60
		.text
			lb R9, length(R0)
			daddui R9, R9, -1
			daddui R8, R0, 8 
			dmul R9, R9, R8 
	  loop: l.d F1, v1(R9)
			l.d F2, v2(R9)
			l.d F3, v3(R9)
			l.d F4, v4(R9)
			add.d F5, F1, F2
			mul.d F5, F3, F5
			add.d F5, F5, F4
			s.d F5, v5(R9)
			
			mul.d F6, F4, F1
			div.d F6, F5, F6
			s.d F6, v6(R9)
			
			add.d F7, F2, F3
			mul.d F7, F6, F7
			s.d F7, v7(R9)
			
			
			daddui R9, R9, -8
			bnez R9, loop
		halt
			
			
			