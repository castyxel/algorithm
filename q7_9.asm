assume cs:codesg, ss:stacksg, ds:datasg

stacksg segment
dw 0, 0, 0, 0, 0, 0, 0, 0
stacksg ends

datasg segment
db '1.display       '
db '2.brows         '
db '3.replace       '
db '4.modify        '
datasg ends

codesg segment
start:
mov ax, stacksg
mov ss, ax
mov sp, 16

mov ax, datasg
mov ds, ax

mov bx, 0
mov cx, 4
s:
push cx
mov cx, 4
mov si, 0
sa:
mov al, [bx][2+si]
and al, 11011111b
mov [bx][2+si], al
inc si
loop sa
add bx, 16

pop cx
loop s

mov ax, 4c00h
int 21h
codesg ends

end start
