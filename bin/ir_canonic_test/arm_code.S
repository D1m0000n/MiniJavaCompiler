TestClass::main:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11}
	mov %0, #3
	str %0, [::fp, #4]
	mov %1, #2
	str %1, [::fp, #8]
	ldr %2, [::fp, #8]
	cmp %2, #0
	bgt L0
L1:
	ldr %3, [::fp, #8]
	ldr %4, [::fp, #4]
	add %3, %3, %4
	str %3, [::fp, #16]
	ldr %5, [::fp, #16]
	mov r0, %5
	bl print
	b L2
L2:
	ldr %6, [::fp, #4]
	mov r0, %6
	bl print
	b main_done
L0:
	ldr %7, [::fp, #4]
	add %7, %7, #1
	str %7, [::fp, #12]
	ldr %8, [::fp, #12]
	mov r0, %8
	bl print
	b L2
