ClassFoo::FuncFoo:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
	push r11
	mov r11, sp
	pop r11
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
	b FuncFoo_done
ClassBar::FuncBar:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
	push r11
	mov r11, sp
	pop r11
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
	b FuncBar_done
MainClass::main:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
	push r11
	mov r11, sp
	mov r1, #3
	str r1, [::fp, #4]
	ldr r1, [::fp, #4]
	mov r0, r1
	bl print
	ldr r1, [::fp, #4]
	cmp r1, #2
	bgt L0
L1:
	mov r5, #222
	mov r0, r5
	bl print
	add ::fp, ::fp, #8
	mov r7, ::fp
	mov r1, #0
	mov r4, #3
	mov r2, r4
	mov r3, #2
	mov r1, r3
	mov r2, #1
	mov r0, r2
	bl FuncFoo
	mov r0, r0
	mov r1, r0
	mov r9, r1
	mov r1, #0
	ldr r8, [::fp, #8]
	mov r0, r8
	bl FuncBar
	mov r6, r0
	mov r10, r6
	add r9, r9, r10
	str r9, [r7, #0]
	ldr r1, [::fp, #8]
	mov r0, r1
	bl print
	b L2
L2:
	add ::fp, ::fp, #12
	mov r1, ::fp
	mov r0, #1
	mov r1, r0
	ldr r1, [::fp, #4]
	cmp r1, #2
	bgt L3
L4:
	mov r0, #0
	mov r1, r0
	b L3
L3:
	str r1, [r0, #0]
	ldr r1, [::fp, #4]
	cmp r1, #2
	bgt L5
L6:
	mov r1, #1000
	mov r0, r1
	bl print
	b main_done
L0:
	ldr r1, [::fp, #4]
	add r1, r1, #2
	mov r0, r1
	bl print
	b L2
L5:
	ldr r1, [::fp, #4]
	add r1, r1, #3
	mov r0, r1
	bl print
	b L7
