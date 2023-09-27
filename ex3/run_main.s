//213073497 Ariel Elbaz
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
    pushq	%rbp     #push the frame pointer
    movq    %rsp, %rbp      #set the frame pointer to the stack pointer

    subq	$256, %rsp      #allocate 256 bytes of stack space
    #get the lentgh of pstring1
#############################################################################################################
    movq    %rsp, %rsi      # load address of buffer
    movq    $number, %rdi   # load format string
    movq    $0, %rax        # load 0 into rax
        call    scanf           # call scanf


   #get the string of pstring2
#############################################################################################################
    xorq   %rax, %rax           # Clear rax
    movq    $string, %rdi       # load format string
    leaq    1(%rsp), %rsi       # load address of buffer
        call    scanf               # call scanf to read string
    xorq    %rax, %rax          # Clear rax
    leaq    1(%rsp), %rax       # load rsp + 1 address into rax
    addb    (%rsp) , %al        # add the length of p1string to rax pointer
    movb    $0 , (%rax)         # add Null to the end of p1string

#############################################################################################################
    subq	$256, %rsp          #allocate 256 bytes of stack space
    #get the lentgh of pstring2
#############################################################################################################
    movq    %rsp, %rsi          # load address of buffer
    movq    $number, %rdi       # load format string
    movq    $0, %rax            # load 0 into rax
        call    scanf               # call scanf

   #get the string of pstring2
#########################################################################################################
    xorq   %rax, %rax           # Clear rax
    movq    $string, %rdi       # load format string
    leaq    1(%rsp), %rsi       # load address of rsp + 1 into rsi
    call    scanf               # call scanf to read string2
    xorq    %rax, %rax          # Clear rax
    leaq    1(%rsp), %rax       # load rsp + 1 address into rax
    addb    (%rsp) , %al        # add the length of p1string to rax pointer
    movb    $0 , (%rax)         # add Null to the end of p1string

   # read the option
#############################################################################################################
    subq	$16, %rsp           #allocate 16 bytes of stack space
    xorq   %rax, %rax           # Clear rax
    movq   %rsp, %rsi           # load value of rsp into rsi
    movq    $numberInt, %rdi    # load format string
       call    scanf            # call scanf to read option

#############################################################################################################
movq (%rsp), %rsi
    movzbq %sil , %rdi                    # option  first parameter
    leaq  272(%rsp)  , %rsi #passing second psring1 , second parmeter
    leaq  16(%rsp) , %rdX #passing first pstring2 , third parmeter
    call  run_func
#########################################################################################################

    leave
	ret			#return to caller function (main)
