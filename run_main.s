
	.section	.rodata
	.align 8
number:  .string "%d"
numberInt:  .string "%d"

string:  .string "%s"
printStr:	.string "%s\n"

	#########################
	.text	#the beginning of the code.

.globl	run_main
	.type	run_main, @function
run_main:
    #push the frame pointer
    pushq	%rbp
    #set the frame pointer to the stack pointer
    movq  %rsp, %rbp

    subq	$256, %rsp
    #get the lentgh of pstring1
 ########################################################################################################
    movq    %rsp, %rsi     # load address of buffer
    movq    $number, %rdi  # load format string
    movq    $0, %rax      # load 0 into rax
    call    scanf       # call scanf


   #get the string of pstring2
#########################################################################################################
    xorq   %rax, %rax
    movq    $string, %rdi  # load format string
    leaq    1(%rsp), %rsi     # load address of buffer
    call    scanf
    xorq    %rax, %rax
    leaq    1(%rsp), %rax # load rsp + 1 address into rax
    addb    (%rsp) , %al # add the length of p1string to rax pointer
    movb    $0 , (%rax)  # add Null to the end of p1string

#############################################################################################################
    subq	$256, %rsp
    #get the lentgh of pstring2
 ########################################################################################################
    movq    %rsp, %rsi     # load address of buffer
    movq    $number, %rdi  # load format string
    movq    $0, %rax      # load 0 into rax
    call    scanf       # call scanf


#########################################################################################################

   #get the string of pstring2
#########################################################################################################
    xorq   %rax, %rax
    movq    $string, %rdi  # load format string
    leaq    1(%rsp), %rsi     # load address of buffer
    call    scanf
    xorq    %rax, %rax
    leaq    1(%rsp), %rax # load rsp + 1 address into rax
    addb    (%rsp) , %al # add the length of p1string to rax pointer
    movb    $0 , (%rax)  # add Null to the end of p1string

   # read the option
#############################################################################################################
    subq	$16, %rsp
    xorq   %rax, %rax
    movq   %rsp, %rsi    # load address of buffer
    movq    $numberInt, %rdi  # load format string
       call    scanf

#############################################################################################################
    movb  (%rsp), %dl # passing the option , third parameter
    leaq  16(%rsp)  , %rsi #passing second psring2 , second parmeter
    leaq  272(%rsp) , %rdi #passing first pstring1 , first parameter
    xorq %rax, %rax
    call  run_func
#########################################################################################################

    leave
	ret			#return to caller function (main)
