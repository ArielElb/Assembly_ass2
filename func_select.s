//213073497 Ariel Elbaz
    .section	.rodata
	.align 8
invalid_option:  .string "invalid option!\n"
string:  .string "%s"
printStr:	.string "%s\n"
printLen:   .string "first pstring length: %d, second pstring length: %d\n"
printSwap:  .string "length: %d, string: %s\n"
char: .string "%c"
TwoChars: .string "%c %c"
TwoInts: .string "%d %d"
int: .string "%d"
compare: .string "compare result: %d\n"

swapChars: .string "old char: %c, new char: %c, first string: %s, second string: %s\n"
    .align	8	# we want all data to be save in an address that divise with their size.
   .Table:
        .quad  .L3      # case 31
        .quad  .L4      # case 32
        .quad  .L4      # case 33
        .quad  .Invalid_Option      # case 34
        .quad  .L5      # case 35
        .quad  .L6      # case 36
        .quad  .L7      # case 37

	#########################

.text	#the beginning of the code.


.global run_func
	.type run_func, @function
run_func:
    #option in rdi
    # pstring1 in rsi
    # pstring2 in rdx

    pushq  %rbp #save the base pointer.
    movq   %rsp, %rbp   #set the base pointer to the stack pointer.
    pushq  %r15         #save the registers.
    pushq  %r14         #save the registers.
    pushq  %r13         #save the registers.
    pushq  %r12         #save the registers.
    movq   %rdx, %r15   #save the second string.
    movq   %rsi, %r14   #save the first string.

    subq   $31, %rdi          #subtract 31 from the input.
    cmpq   $6, %rdi           #check if the option is between 1-6.
    ja     .Invalid_Option    #if not, jump to the end of the function.
    jmp    *.Table(,%rdi,8)   #jump to the right function.


   .L3:      #case 31 - print the length of the first string and the second string.
    movq   %r14, %rdi
    xorq   %rax, %rax   # clear the return value.
    call   pstrlen      #call the pstrlen function.
    movq   %rax, %r14   #save the length of the first string.

    xorq   %rax, %rax   #clear the return value.
    movq   %r15, %rdi   # pass the second pstring  address to the function.
    call   pstrlen      #call the pstrlen function.
    movq   %rax, %r13   #save the length of the second string.

    movq   %r13, %rdx   # pass the second pstring length to the function.
    movq   %r14, %rsi   # pass the first pstring length to the function.
    movq   $printLen, %rdi      # load format string
        call    printf
    jmp .DONE
   .L4:   # case 32 and 33
    xorq   %rax, %rax
    #get the /n from the last scanf.
    leaq   (%rsp), %rsi    # overrite the option of the switch case
     movq    $char, %rdi  # load format string
          call    scanf



     xorq   %rax, %rax          # clear the return value.
     movq  %rsp, %rdx           # new char in the addres of $rsp
     leaq   1(%rsp), %rsi       # old char in the addrest of $rsp + 1.
     movq    $TwoChars, %rdi    # load format string
        call    scanf

     movq   %r14, %rdx          # pass the first pstring address to the function.
     leaq   1(%rsp), %rsi       # pass the address of the old char
     leaq   (%rsp), %rdi        # pass the  new char address to the function.
     xorq   %rax, %rax          # clear the return value.
     call    replaceChar

     leaq   1(%r13) ,%r8        # first string address - 4th parameter
     leaq   1(%rax), %rcx       # second string address - 3rd parameter
     movzbq   (%rsp), %rdx      # old char address - 2nd parameter
     movzbq  1(%rsp), %rsi      # new char address - 1st parameter
     movq   $swapChars, %rdi    # load format string
        call    printf

     popq %r15
     popq %r14
     jmp .DONE


    .L5:   # case 35
     xorq   %rax, %rax
     #get the /n from the last scanf.
     leaq   (%rsp), %rsi        # overrite the option of the switch case
     movq    $char, %rdi        # load format string
          call    scanf

     xorq  %rax, %rax           # clear the return value.
     movq  %rsp, %rdx           # new char in the addres of $rsp
     leaq  (%rsp), %rsi         # old char in the addrest of $rsp + 1.
     movq    $int, %rdi         # load format string
        call    scanf

      xorq   %rax, %rax         # clear the return value.
      movq  %rsp, %rdx          # new char in the addres of $rsp
      leaq   1(%rsp), %rsi      # old char in the addrest of $rsp + 1.
      movq    $int, %rdi        #load format string
         call    scanf

     movzbq   1(%rsp), %rcx     # passing j
     movzbq   (%rsp), %rdx      # passing i
     movq   %r15, %rsi          # pass the src pstring address to the function.
     movq   %r14, %rdi          # pass the dst pstring address to the function.
     xorq   %rax, %rax          # clear the return value.
     call    pstrijcpy
     leaq   1(%r14), %rdx       # pass the first pstring length to the function.
     movzbq   (%r14), %rsi      # pass the lenth of the first pstring to the function.\
     movq   $printSwap, %rdi    # load format string
            call    printf
     leaq   1(%r15), %rdx       # pass the second pstring length to the function.
     movzbq   (%r15), %rsi      # pass the lenth of the second pstring to the function.
     movq   $printSwap, %rdi    # load format string
            call    printf

      jmp .DONE


   .L6:      #case 36- swapCase
        # pstring1 in rsi
        # pstring2 in rdi
    xorq   %rax, %rax           # clear the return value.
    movq   %r14, %rdi           # pass the first pstring address to the function.
    call   swapCase
    leaq   1(%rax), %rdx        # pass the first pstring length to the function.
    movzbq   (%rax), %rsi       # pass the lenth of the first pstring to the function.
    xorq   %rax, %rax
    movq   $printSwap, %rdi     # load format string
        call    printf

    xorq   %rax, %rax           # clear the return value.
    movq   %r15 , %rdi          # pass the second pstring address to the function.
    call   swapCase
    leaq   1(%rax), %rdx        # pass the first pstring length to the function.
    movzbq   (%rax), %rsi       # pass the lenth of the first pstring to the function.
    xorq   %rax, %rax
    movq   $printSwap, %rdi     # load format string
        call    printf

    jmp .DONE

   .L7:      #case 37
   xorq   %rax, %rax
   #get the /n from the last scanf.
   leaq   (%rsp), %rsi      # overrite the option of the switch case
   movq    $char, %rdi      # load format string
        call    scanf
   xorq   %rax, %rax        # clear the return value.
   movq  %rsp, %rdx         # new char in the addres of $rsp
   leaq  (%rsp), %rsi       # old char in the addrest of $rsp + 1.
   movq    $int, %rdi       # load format string
      call    scanf
   xorq   %rax, %rax       # clear the return value.
   movq  %rsp, %rdx        # new char in the addres of $rsp
   leaq   1(%rsp), %rsi    # old char in the addrest of $rsp + 1.
   movq    $int, %rdi      # load format string
      call    scanf
   movzbq   1(%rsp), %rcx   # passing j
   movzbq   (%rsp), %rdx    # passing i
   movq   %r15, %rsi        # pass the src pstring address to the function.
   movq   %r14, %rdi        # pass the dst pstring address to the function.
   xorq   %rax, %rax        # clear the return value.
   call    pstrijcmp
   movq   %rax, %rsi        # comapre result
   movq   $compare, %rdi    # load format string
      call    printf
   jmp .DONE


   .Invalid_Option:
    movq   $invalid_option, %rdi  # load format string
    movq   $0, %rax # return 0
    call    printf
    jmp .DONE

   .DONE:  #end of the function.
   popq  %r14     # restore the registers
   popq  %r15
   popq  %r13
   popq  %r12
   movq   %rbp, %rsp   #set the stack pointer to the base pointer.
   popq   %rbp #restore the base pointer.
      ret #return to the caller.