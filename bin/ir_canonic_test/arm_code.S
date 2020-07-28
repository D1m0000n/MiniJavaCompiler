MainClass::main:
	mov %6, #3
	str %6, [::fp, 4]
	ldr %7, [::fp, 4]
	mov r0, %7
	bl print
	ldr %8, [::fp, 4]
	cmp %8, #2
	bgt L0
L1:
	mov %9, #222
	mov r0, %9
	bl print
	add ::fp, ::fp, #8
	mov %4, ::fp
	mov %10, #0
	mov %11, #3
	mov r2, %11
	mov %12, #2
	mov r1, %12
	mov %13, #1
	mov r0, %13
	bl FuncFoo
	mov %14, r0
	mov %1, %14
	mov %3, %1
	mov %15, #0
	ldr %16, [::fp, 8]
	mov r0, %16
	bl FuncBar
	mov %17, r0
	mov %2, %17
	add %3, %3, %2
	str %3, [%4, 0]
	ldr %18, [::fp, 8]
	mov r0, %18
	bl print
	b L2
L2:
	add ::fp, ::fp, #12
	mov %5, ::fp
	mov %19, #1
	mov %19, %0
	ldr %20, [::fp, 4]
	cmp %20, #2
	bgt L3
L4:
	mov %21, #0
	mov %21, %0
	b L3
L3:
	str %0, [%5, 0]
	ldr %22, [::fp, 4]
	cmp %22, #2
	bgt L5
L6:
	mov %23, #1000
	mov r0, %23
	bl print
	b main_done
L0:
	ldr %24, [::fp, 4]
	add %24, %24, #2
	mov r0, %24
	bl print
	b L2
L5:
	ldr %25, [::fp, 4]
	add %25, %25, #3
	mov r0, %25
	bl print
	b L7
ClassBar::FuncBar:
	b FuncBar_done
ClassFoo::FuncFoo:
	b FuncFoo_done
