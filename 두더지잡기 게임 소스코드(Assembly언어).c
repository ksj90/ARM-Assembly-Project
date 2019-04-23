my_get_byte:
		
		ldr r1,= 0x50004024 /*RdURXH1*/
		ldr r2,= 0x50004010 /*rUTRSTAT1*/
		ldr r4,= 0x0
		ldr r4,[r2]
		
		and r4,r4,#0x1
		cmp r4,#0x1
		BNE my_get_byte
		ldrEQ r0,[r1]
		movEQ pc,lr
		 
start_game:
		
		b led_ON

led_ON:
		
		mov r6,#0
		ldr r1,=GPGCON
		ldr r2,=0x5500
		str r2,[r1]
		
		ldr r3,=GPGDAT
		cmp r0,#1
		ldrEQ r4,=0xE0 //4번 째 LED 켜짐  
		strEQ r4,[r3]
		bEQ my_delay2
		
		cmpNE r0,#2
		ldrEQ r4,=0xD0 //5번 째 LED 켜짐
		strEQ r4,[r3]
		bEQ my_delay2
  		 
		cmpNE r0,#3
		ldrEQ r4,=0xB0 //6번 째 LED 켜짐  
		strEQ r4,[r3]
		bEQ my_delay2
		
		cmpNE r0,#4
		ldrEQ r4,=0x70 //7번 째 LED 켜짐
		strEQ r4,[r3]
		bEQ my_delay2
		
led_OFF:
		
		mov r6,#0
		ldr r1,=GPGCON
		ldr r2,=0x5500
		str r2,[r1]
		
		ldr r3,=GPGDAT
		ldr r4,=0xf0
		str r4,[r3]
		b my_delay
		
my_delay:
	
		ldr r5,=0x5ffff
		cmp r5, r6
		addNE r6,#1
		bne my_delay
		movEQ pc,lr
		
my_delay2:
		
		ldr r5,=0xfffff
		cmp r5, r6
		addNE r6,#1
		bne my_delay2
		bEQ led_OFF   -         
		mov pc,lr		

go:
	
		ldr r10,=0x5ffff
		b my_button_init
	 
my_button_init:
		
		ldr r5,=GPFCON
		ldr r6,=0x4000
		str r6,[r5]
		
		ldr r7,=GPFDAT
		ldr r8,=0x0
		str r8,[r7]
		
		ldr r0,[r7]
		cmp r0,#0x7b //4번 스위치
		movEQ r0,#1   
		movEQ pc,lr
		
		cmp r0,#0x77 //5번 스위치
		movEQ r0,#2
		movEQ pc,lr
		
		cmp r0,#0x6f //6번 스위치
		movEQ r0,#3
		movEQ pc,lr
		
		cmp r0,#0x5f //7번 스위치
		movEQ r0,#4
		movEQ pc,lr
		
		cmp r10, #0 
		SUBNE r10,#1
		BNE my_button_init
		movEQ pc,lr
