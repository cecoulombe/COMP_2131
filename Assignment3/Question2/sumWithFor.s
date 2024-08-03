	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 4
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w10, #45
	mov	w8, #10
	mov	w9, #5
	stp	x8, x10, [sp, #8]
	str	x9, [sp]
Lloh0:
	adrp	x0, l_.str@PAGE
Lloh1:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	mov	w0, #0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_sumArguments                   ; -- Begin function sumArguments
	.p2align	2
_sumArguments:                          ; @sumArguments
	.cfi_startproc
; %bb.0:
	subs	w8, w1, w0
	b.ge	LBB1_2
; %bb.1:
	mov	w0, #0
	ret
LBB1_2:
	mvn	w9, w0
	add	w9, w9, w1
	umull	x9, w9, w8
	lsr	x9, x9, #1
	madd	w8, w8, w0, w8
	add	w8, w8, w0
	add	w0, w8, w9
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"The sum of all the numbers between %d and %d, inclusive, is %d\n"

.subsections_via_symbols
