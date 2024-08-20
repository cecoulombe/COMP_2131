	.file	"fullUnroll.c"
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
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$216, %rsp
	.cfi_def_cfa_offset 240
	movq	%rsp, %rdx
	movl	$0, %eax
.L2:
	addl	$1, %eax
	movl	%eax, (%rdx)
	addq	$4, %rdx
	cmpl	$50, %eax
	jne	.L2
	call	clock
	movq	%rax, %rbx
	movl	4(%rsp), %ebp
	addl	(%rsp), %ebp
	addl	8(%rsp), %ebp
	addl	12(%rsp), %ebp
	addl	16(%rsp), %ebp
	addl	20(%rsp), %ebp
	addl	24(%rsp), %ebp
	addl	28(%rsp), %ebp
	addl	32(%rsp), %ebp
	addl	36(%rsp), %ebp
	addl	40(%rsp), %ebp
	addl	44(%rsp), %ebp
	addl	48(%rsp), %ebp
	addl	52(%rsp), %ebp
	addl	56(%rsp), %ebp
	addl	60(%rsp), %ebp
	addl	64(%rsp), %ebp
	addl	68(%rsp), %ebp
	addl	72(%rsp), %ebp
	addl	76(%rsp), %ebp
	addl	80(%rsp), %ebp
	addl	84(%rsp), %ebp
	addl	88(%rsp), %ebp
	addl	92(%rsp), %ebp
	addl	96(%rsp), %ebp
	addl	100(%rsp), %ebp
	addl	104(%rsp), %ebp
	addl	108(%rsp), %ebp
	addl	112(%rsp), %ebp
	addl	116(%rsp), %ebp
	addl	120(%rsp), %ebp
	addl	124(%rsp), %ebp
	addl	128(%rsp), %ebp
	addl	132(%rsp), %ebp
	addl	136(%rsp), %ebp
	addl	140(%rsp), %ebp
	addl	144(%rsp), %ebp
	addl	148(%rsp), %ebp
	addl	152(%rsp), %ebp
	addl	156(%rsp), %ebp
	addl	160(%rsp), %ebp
	addl	164(%rsp), %ebp
	addl	168(%rsp), %ebp
	addl	172(%rsp), %ebp
	addl	176(%rsp), %ebp
	addl	180(%rsp), %ebp
	addl	184(%rsp), %ebp
	addl	188(%rsp), %ebp
	addl	192(%rsp), %ebp
	addl	196(%rsp), %ebp
	call	clock
	subq	%rbx, %rax
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
	addq	$216, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
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
