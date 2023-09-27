//213073497 Ariel Elbaz

	.align	8	# we want all data to be save in an address that divise with their size.
    .section	.rodata
	.align 8
invalid_option:  .string "invalid input!\n"
####################################################################################################
	.text	#the beginning of the code.

.globl pstrlen
	.type pstrlen ,@function
pstrlen:
    pushq  %rbp             #save the base pointer.
    movq   %rsp, %rbp       #set the base pointer to the stack pointer.
    pushq  %rdi             # callae save the first argument.
    pushq  %rsi             # callae save the second argument.
    xorq   %rax, %rax       #set the return value to 0.
    movb   (%rdi), %al      #move the first argument to the return value.

    popq   %rsi     #restore the first argument.
    popq   %rdi     #restore the second argument.
    jmp .DONE       #jump to the end of the function.



.globl replaceChar
	.type replaceChar, @function
replaceChar:
    # old char in rdi
    # new char in rsi
    # pstring1 in rdx

    pushq  %rbp         #save the base pointer.
    movq   %rsp, %rbp   #set the base pointer to the stack pointer.
    pushq  %r15         # callae save
    pushq  %r14         # callae save
    pushq  %r13         # callae save
    movsbq (%rdi) ,%r15         # new char in r15
    movsbq (%rsi) ,%r14         # old char in r14
    leaq   -255(%rdx), %r13     #  #address of pstring2 in r13
    leaq   (%rdx), %rax         # address of   pstring1 in rax
    jmp .while_replaceChar_P1   #jump to the while loop.
.Loop2:
    popq   %r14         #restore callae
    popq   %r15         #restore callae
    popq   %r13         #restore callae
    jmp .DONE           #jump to the end of the function.


.while_replaceChar_P1:
    cmpb $0,1(%rdx)
    je .while_replaceChar_P2
    cmpb   1(%rdx), %r14b           #compare string[i] to the old char.
    je  .swap_replaceChar_P1        #if they are equal, jump to the replaceChar label.
    incq   %rdx                     #increase the index.
    jmp .while_replaceChar_P1       #jump to the while loop.
.swap_replaceChar_P1:
    movb   %r15b, 1(%rdx)           #replace the old char with the new char.
    incq   %rdx                     #increase the index.
    cmpq  $0, 1(%rdx)               #check if the end of the string was reached.
    jne .while_replaceChar_P1       #jump to the while loop.
    jmp .while_replaceChar_P2       #jump to the end of the function.
.while_replaceChar_P2:
    cmpb  $0,(%r13)
    je .Loop2
    cmpb   (%r13), %r14b       #compare string[i] to the old char.
    je  .swap_replaceChar_P2   #if they are equal, jump to the replaceChar label.
    incq   %r13                #increase the index.
    cmpq  $0, (%r13)           #check if the end of the string was reached.

    jmp .while_replaceChar_P2   #jump to the while loop.
.swap_replaceChar_P2:
    movb   %r15b, (%r13)        #replace the old char with the new char.
    incq    %r13
    jne .while_replaceChar_P2   #jump to the while loop.




   .globl pstrijcpy
   .type pstrijcpy ,@function
pstrijcpy:
    #i  -  in rdx
    #j- pstring1 in rcx
    # src pstring - in rsi
    # dst pstring - in rdi
    pushq  %rbp #save the base pointer.
    movq   %rsp, %rbp   #set the base pointer to the stack pointer.

    pushq  %r15
    pushq  %r14
    pushq  %r13
    pushq  %r12
    movq   %rdi, %rax   #address of dest in rax
    movsbq   (%rdi), %r15  #length of dst in r15
    movsbq   (%rsi), %r14  # length of src in r14
    #index start from 0
    decq   %r15                 #length of dst-1 in r15
    decq   %r14                 #length of src-1 in r14
    cmpb   %r15b,%cl            #check if j is bigger than the length of dst
    jg .invalid_index_cpy       #if it is, jump to the invalid_index label.
    cmpb    %r14b ,%cl          #check if j is bigger than the length of src
    jg .invalid_index_cpy       #if it is, jump to the invalid_index label.
    incq    %rdi                #increase the address of dst
    incq    %rsi                #increade the address of the src
    jmp .for_pstrijcpy

.for_pstrijcpy:
    cmpb    %dl,%cl   #check if i is smaller  or equale than j
    jge .copy_pstrijcpy
    jmp .for_pstrijcpy_end

.copy_pstrijcpy:
    #i in rdx
    #j in rcx
    movb    (%rsi,%rdx,1),%r13b   #copy the char from src to dst - r13b = src[i]
    movb    %r13b,(%rdi,%rdx,1)   #copy the char from src to dst - dst[0+i] = r13b
    incq    %rdx   #increase i
    jmp .for_pstrijcpy

.for_pstrijcpy_end:
    popq    %r12
    popq    %r13
    popq    %r14
    popq    %r15
    jmp .DONE       #jump to the end of the function.


    .globl swapCase
    .type swapCase @function
swapCase:
    pushq  %rbp         #save the base pointer.
    movq   %rsp, %rbp   #set the base pointer to the stack pointer.
    movq   %rdi, %rax   #move the first argument to the return value.
    incq   %rax         #increase the return value.

.while_not_null_terminted:
   cmpb   $0, (%rax)       #compare the first argument to 0.
   je  .DONE_SWAP          #if they are equal, jump to the DONE label.
   cmpb  $122, (%rax)      #compare the first argument to 122
   jg   .next_char         #if the first argument is greater than 122, jump to the next_char label.
   cmpb  $65, (%rax)       #compare the first argument to 65.
   jge   .is_capital       #if they are greater than 65, jump to the if_greater_than_65 label.
   jmp .next_char          #if they are not greater than 65, jump to the next_char label.
.is_capital:
   cmpb   $90, (%rax)       #compare the first argument to 65.
   jg  .is_small            #if they are less, jump to the is_small label.
   addb  $32, (%rax)        #add 32 to the first argument.
   jmp .next_char           #jump to the next_char label.
.is_small:
    cmpb   $97, (%rax)      #compare the first argument to 97.
    jl  .next_char          #if they are less, jump to the next_char label. between 90 to 97.
    subb  $32, (%rax)       #sub 32 to the first argument.
    jmp .next_char          #jump to the next_char label.
.next_char:
   incq  %rax                            #increase the first argument.
   jmp  .while_not_null_terminted        #jump to the while_not_null_terminted label.


 .globl pstrijcmp
 .type pstrijcmp @function
pstrijcmp: #case 37
    #i  -  in rdx
    #j- pstring1 in rcx
    # src pstring - in rsi
    # dst pstring - in rdi
    pushq  %rbp                 #save the base pointer.
    movq   %rsp, %rbp           #set the base pointer to the stack pointer.

    pushq  %r15     #calle save
    pushq  %r14     #calle save
    pushq  %r13     #calle save
    pushq  %r12     #calle save
    movq   %rdi, %rax           #address of dest in rax
    xorq    %rax , %rax         #rax = 05
    movsbq   (%rdi), %r15       #length of dst in r15
    movsbq   (%rsi), %r14       # length of src in r14
    #index start from 0
    decq   %r15             #length of dst-1 in r15
    decq   %r14             #length of src-1 in r14
    cmpb    %r15b,%cl       #check if j is bigger than the length of dst
    jg .Invalid_index_strcmp
    cmpb    %r14b ,%cl      #check if j is bigger than the length of src
    jg .Invalid_index_strcmp
    incq    %rdi            #increase the address of dst
    incq    %rsi            #increade the address of the src
    jmp .for_pstrijcmp


.for_pstrijcmp:
    cmpb    %dl,%cl         #check if i is smaller or equale than j
    jge .compare_pstrijcmp
    jmp .for_pstrijcmp_end

.compare_pstrijcmp:
    #i in rdx
    #j in rcx
    movzbq    (%rsi,%rdx,1),%r13    # dest[i] in r13
    movzbq    (%rdi,%rdx,1),%r12    # src[i] in r12
    incq    %rdx       #increase i
    cmpq   %r13,%r12   #compare the chars
    je .for_pstrijcmp
    jl .dst_bigger
    jg .src_bigger


.src_bigger:
    movq    $1,%rax
    jmp .for_pstrijcmp_end

.dst_bigger:
    movq    $-1,%rax
    jmp .for_pstrijcmp_end

.for_pstrijcmp_end:
    popq    %r12    #calle save restore
    popq    %r13    #calle save restore
    popq    %r14    #calle save restore
    popq    %r15    #calle save restore
    jmp .DONE #jump to the end of the function.



.DONE_SWAP:
   movq   %rdi , %rax   #move the first argument to the return value.
   jmp .DONE   #jump to the end of the function.

.invalid_index_cpy:
    popq    %r12    #calle save restore
    popq    %r13    #calle save restore
    popq    %r14    #calle save restore
    popq    %r15    #calle save restore
    jmp .Invalid_index
.Invalid_index:
movq   $invalid_option, %rdi  # load format string
movq   $0, %rax # return 0
call    printf
jmp .DONE

.Invalid_index_strcmp:
movq   $invalid_option, %rdi  # load format string
xorq    %rax, %rax       # clear rax
call    printf
movq   $-2, %rax        # return -2
    jmp .for_pstrijcmp_end

.DONE:  #end of the function.
movq   %rbp, %rsp       #set the stack pointer to the base pointer.
popq   %rbp             #restore the base pointer.
ret                     #return to the caller.
