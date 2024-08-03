	.file	"sumWithFor.c"
	.text
.globl sumArguments
	.type	sumArguments, @function
sumArguments:
.LFB31:
	.cfi_startproc
	movl	%edi, %edx
	movl	$0, %eax
	cmpl	%esi, %edi
	jg	.L3
.L6:
	addl	%edx, %eax
	addl	$1, %edx
	cmpl	%edx, %esi
	jge	.L6
.L3:
	rep; ret
	.cfi_endproc
.LFE31:
	.size	sumArguments, .-sumArguments
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"The sum of all the numbers between %d and %d, inclusive, is %d\n"
	.text
.globl main
	.type	main, @function
main:
.LFB30:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$10, %esi
	movl	$5, %edi
	call	sumArguments
	movl	%eax, %ecx
	movl	$10, %edx
	movl	$5, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE30:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-23)"
	.section	.note.GNU-stack,"",@progbits
