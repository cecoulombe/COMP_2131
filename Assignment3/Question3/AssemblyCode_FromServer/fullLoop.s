	.file	"fullLoop.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Unrolled loop time: %f seconds\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"The total is: %d\n"
	.text
.globl main
	.type	main, @function
main:
.LFB19:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$208, %rsp
	.cfi_def_cfa_offset 240
	movq	%rsp, %rbx
	movq	%rsp, %rdx
	movl	$0, %eax
.L2:
	addl	$1, %eax
	movl	%eax, (%rdx)
	addq	$4, %rdx
	cmpl	$50, %eax
	jne	.L2
	call	clock
	movq	%rax, %r12
	leaq	200(%rsp), %rax
	movl	$0, %ebp
.L3:
	addl	(%rbx), %ebp
	addq	$4, %rbx
	cmpq	%rax, %rbx
	jne	.L3
	call	clock
	subq	%r12, %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC0(%rip), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movl	%ebp, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$208, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE19:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1093567616
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-23)"
	.section	.note.GNU-stack,"",@progbits
