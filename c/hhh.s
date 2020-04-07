	.file	"integer.c"
	.text
	.section	.rodata
.LC0:
	.string	"size: %d, %d\n"
.LC1:
	.string	"x = %u = %d\n"
.LC2:
	.string	"u = %u = %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$-1, -8(%rbp)
	movl	$-2147483648, -4(%rbp)
	movl	$4, %edx
	movl	$4, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-8(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
