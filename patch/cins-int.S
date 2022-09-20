adr r1, buf
ldr r0, =i
mov r2, '='
str r2, [r1]
top:
add r2, #0x1
cmp r0, 0x1000-1
bgt thousand
cmp r0, 0x500-1
bgt hundred
cmp r0, 0x50-1
bgt fifty
cmp r0, 0x10-1
bgt ten
cmp r0, 0x0
bgt one
mov r2, #0x0
str r2, [r1]
b end
thousand:
mov r2, '#'
sub r0, #0x1000
b top
hundred:
mov r2, '@'
sub r0, #0x500
b top
fifty:
mov r2, '%'
sub r0, #0x50

end:

b exit
 .align 4
 buf: .string "Hello World"
 .align 4
 i: .int 0x1234
exit:
