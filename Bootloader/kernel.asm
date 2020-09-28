org 0x7e00
jmp 0x0000:start

data: 
;Usuario
input times 50 db 0 ;Todas as palavras
valor times 2 db 0 ;Qualquer numero inteiro
numero times 10 db 0 ;O valor so que em uma string
RND db 0,0

;Cores
vermelho db 4
amarelo db 14
branco db 15
preto db 0
verde db 2
azul db 1
magenta db 5

;Tela de Titulo
jogo1 db "1 - Palavra Aleatoria", 0
jogo2 db "2 - Palavra Especifica", 0

;Valores auxiliares
column db 0
row db 0
offset dw 41

forca_palavra times 10 db 0
size db 0 ;Deve ir de 1-9
mostrar times 10 db 0

;Jogo ascii art
imagem_vazia: 
db "XXXXXXXXXXXXXX",13,
db "X      X      ",13,
db "X      X      ",13,
db "X      X      ",13,
db "X      X      ",13,
db "X      X      ",13,
db "X      X      ",13,
db "X    X   X    ",13,
db "X    X   X    ",13,
db "X      X      ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,0

imagem_cabeca: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X ~ ~ X  ",13,
db "X    X O O X  ",13,
db "X    X ___ X  ",13,
db "X     XXXXX   ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,0

imagem_cabeca_tronco: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X     X  ",13,
db "X    X T T X  ",13,
db "X    X  .  X  ",13,
db "X     XXXXX   ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,0

imagem_cabeca_tronco_braco: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X \ / X  ",13,
db "X    X o o X  ",13,
db "X    X  ^  X  ",13,
db "X     XXXXX   ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X     X X X   ",13,
db "X    X  X  X  ",13,
db "X   X   X   X ",13,
db "X  X    X    X",13,
db "X       X     ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,0

imagem_morto: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X ~ ~ X  ",13,
db "X    X X X X  ",13,
db "X    X ___ X  ",13,
db "X     XXXXX   ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X     X X X   ",13,
db "X    X  X  X  ",13,
db "X   X   X   X ",13,
db "X  X    X    X",13,
db "X       X     ",13,
db "X      X X    ",13,
db "X     X   X   ",13,
db "X    X     X  ",13,
db "X   X       X ",13,
db "X  X         X",13,0

imagem_saved: 
db "              ",13,
db "              ",13,
db "     XXXXX    ",13,
db "    X ~ ~ X   ",13,
db "    X ^ ^ X   ",13,
db "    X  v  X   ",13,
db " X   XXXXX   X",13,
db "  X    X    X ",13,
db "   X   X   X  ",13,
db "     X X X    ",13,
db "       X      ",13,
db "       X      ",13,
db "       X      ",13,
db "       X      ",13,
db "      X X     ",13,
db "     X   X    ",13,
db "    X     X   ",13,
db "   X       X  ",13,
db "  X         X ",13,0

letra_vazia:
db "       " ,13,
db "       " ,13,
db "       " ,13,
db "       " ,13,
db "_______" ,13,0

nao_letra:
db " ????? " ,13,
db "? O O ?" ,13,
db "? ___ ?" ,13,
db " ????? " ,13,
db "Invalid" ,13,0


alfabeto:
db " AAAAA ",13,
db "A     A",13,
db "A     A",13,
db "AAAAAAA",13,
db "A     A",13,0,

db "BBBBBB ",13,
db "B     B",13,
db "BBBBBB ",13,
db "B     B",13,
db "BBBBBB ",13,0,

db " CCCCCC",13
db "C      ",13
db "C      ",13
db "C      ",13
db " CCCCCC",13,0,

db "DDDDDD ",13,
db "D     D",13,
db "D     D",13,
db "D     D",13,
db "DDDDDD ",13,0,

db "EEEEEEE",13,
db "E      ",13,
db "EEEEEEE",13,
db "E      ",13,
db "EEEEEEE",13,0,

db "FFFFFFF",13,
db "F      ",13,
db "FFFFFFF",13,
db "F      ",13,
db "F      ",13,0,

db " GGGGGG",13,
db "G      ",13,
db "G   GGG",13,
db "G     G",13,
db " GGGGGG",13,0,

db "H     H",13,
db "H     H",13,
db "HHHHHHH",13,
db "H     H",13,
db "H     H",13,0,

db "IIIIIII",13,
db "  III  ",13,
db "  III  ",13,
db "  III  ",13,
db "IIIIIII",13,0,

db "     JJ",13,
db "      J",13,
db "      J",13,
db "J     J",13,
db " JJJJJ ",13,0,

db "K     K",13,
db "K    K ",13,
db "KKKKK  ",13,
db "K    K ",13,
db "K     K",13,0,

db "L      ",13,
db "L      ",13,
db "L      ",13,
db "L      ",13,
db "LLLLLLL",13,0,

db "M     M",13,
db "M M M M",13,
db "M  M  M",13,
db "M     M",13,
db "M     M",13,0,

db "NN    N",13,
db "N N   N",13,
db "N  N  N",13,
db "N   N N",13,
db "N    NN",13,0,

db " OOOOO ",13,
db "O     O",13,
db "O     O",13,
db "O     O",13,
db " OOOOO ",13,0,

db " PPPPP ",13,
db "P     P",13,
db "PPPPPPP",13,
db "P      ",13,
db "P      ",13,0,

db " QQQQ  ",13,
db "Q    Q ",13,
db "Q    Q ",13,
db "Q   QQ ",13,
db " QQQQ Q",13,0,

db " RRRRR ",13,
db "R     R",13,
db "RRRRRR ",13,
db "R    R ",13,
db "R     R",13,0,

db " SSSSSS",13,
db "S      ",13,
db " SSSSS ",13,
db "      S",13,
db "SSSSSS ",13,0,

db "TTTTTTT",13,
db "  TTT  ",13,
db "  TTT  ",13,
db "  TTT  ",13,
db "  TTT  ",13,0,

db "U     U",13,
db "U     U",13,
db "U     U",13,
db "U     U",13,
db " UUUUU ",13,0,

db "V     V",13,     
db "V     V",13,
db " V   V ",13,
db "  V V  ",13,
db "   V   ",13,0,

db "W     W",13,
db "W  W  W",13,
db "W W W W",13,
db "WW   WW",13,
db "W     W",13,0,

db "X     X",13,
db " X   X ",13, 
db "  XXX  ",13,  
db " X   X ",13, 
db "X     X",13,0,

db "Y     Y",13,
db " Y   Y ",13, 
db "  Y Y  ",13,  
db "   Y   ",13,   
db "   Y   ",13,0,

db "ZZZZZZZ",13,
db "    ZZ ",13, 
db "  ZZ   ",13,   
db "ZZ     ",13,     
db "ZZZZZZZ",13,0

titulo_imagem:
db "     SSSSSS  AAAAA  V     V IIIIIII NN    N  GGGGGG    ",13,
db "    S       A     A V     V   III   N N   N G          ",13,
db "     SSSSS  A     A  V   V    III   N  N  N G   GGG    ",13,
db "          S AAAAAAA   V V     III   N   N N G     G    ",13,
db "    SSSSSS  A     A    V    IIIIIII N    NN  GGGGGG    ",13,
db 13,
db "     JJ  OOOOO  EEEEEEE L        SSSSSS  OOOOO  NN    N",13,
db "      J O     O E       L       S       O     O N N   N",13,
db "      J O     O EEEEEEE L        SSSSS  O     O N  N  N",13,
db "J     J O     O E       L             S O     O N   N N",13,
db " JJJJJ   OOOOO  EEEEEEE LLLLLLL SSSSSS   OOOOO  N    NN",13,0

lista db "corroborar", 0
lista_quantity dw 1
obrigado db "obrigado", 0
derrota db "derrota", 0
QQ_tecla db "Aperte qualquer tecla para continuar", 0



;Funçoes gerais
putchar:    ;Coloca o caractere na tela; o al permanece o que pegou; precisa setar bl antes
    mov ah, 0x0e
    cmp al, 0x8
    je .backspace
    cmp al, 0xd
    je .enterkey
    inc cx
    int 10h
    jmp .done

    .backspace:
    cmp cx, 0
    je .done
    int 10h
    mov al, ' '
    int 10h
    mov al, 0x08          
    int 10h
    jmp .done

    .enterkey:
    int 10h
    mov al,0xa
    int 10h
    mov al, 0xd
    .done:
ret   
getchar:
  mov ah, 0x00
  int 16h
ret
print:; Printa o que ta no si, o ultimo char tem que ser 0
    .loop:
    lodsb
    call putchar
    cmp al,0
    je .done
    jmp .loop
    .done:
ret
storechar:
    cmp al, 0x8
    je .backspace
    stosb
    jmp .done
    .backspace:
    cmp cx,0
    je .done
    dec cx
    dec di
    mov [di],byte 0
    .done:
ret
comp: ;Compara duas palavras ate ambas chegarem a 13 ou 0xd (enter)
    .loop:
    lodsb
    mov cl,byte [di]
    inc di
    ;Chegou no final
    cmp al,0xd
    je .vitoria
    cmp al, cl
    je .loop
    ret
    .vitoria:
    cmp cl, 0xd
ret
getline: ;Pega até apertar enter
    xor cx,cx
    .loop:
    call getchar
    call storechar
    call putchar
    cmp al, 0xd
    jne .loop
ret
clear: ;Equivale a video; Coloca tudo preto serve para limpar a tela; Precisa colocar bl zero antes
    mov ah,0
    mov al,12h
    int 10h

    mov ah,0xb
    mov bh,0
    int 10h
ret
setCursor:;Dh row 0-29 ;Dl column 0-79
    mov bh,0
    mov ah,0x2
    int 10h
ret
number:;Salva um input em 'valor'
    mov di, input
    call getline
    ;Pegar numero
    mov si, input
    mov [valor],word 0
    mov bx,10
    .loop:
    lodsb
    cmp al, 0xd
    je .done
    sub al, 48
    xor cx,cx
    mov cl,al
    mov ax,[valor]
    mul bx
    add ax,cx
    mov [valor],ax
    jmp .loop
    .done:
    call toString
ret
toString: ;Pega o numero em [valor] e salva em [numero];
    mov ax, [valor]
    mov cx,10
    push 0xd
    .loop:
    xor dx,dx
    div cx
    cmp ax, 0
    je .acabou
    add dx,48
    push dx
    jmp .loop
    .acabou:
    add dx, 48
    push dx
    mov di, numero
    .reverse:
    pop ax
    cmp ax,0xd
    je .done
    stosb
    jmp .reverse
    .done:
    mov al, 0
    stosb
ret
delay:
    xor dx,dx
    .delay:
	inc dx
	mov cx, 0
		.time:
			inc cx
			cmp cx, 190000
			jne .time

	cmp dx, 1000
	jne .delay
ret

;Funções para aleatoriedade
ticks: ;Pega os valores dos ticks desde a meia noite e salva em [valor]
    mov ah,0
    int 0x1A
    ;CX:DX ticks desde a meia noite
    mov [valor],dx
ret
random: ;Pega um valor aleatorio das listas pela quantidade
    call ticks
    mov ax, [valor]
    mov cx, word [lista_quantity]
    xor dx,dx
    div cx
    mov [valor], dx
    call toString
ret
;Funçoes para aleatoriedade

centralizar:;Coloca dl para imprimir uma String no centro; Tamanho de referencai si
    xor cx,cx
    .loop:
    lodsb
    cmp al,0
    je .end
    inc cx
    jmp .loop
    .end:
    ;Retorna o curso pra posicao inicial
    sub si, cx
    dec si
    ;Agora divide em dois e coloca em dh (coluna)
    ;Tela
    xor ax,ax
    mov al,cl
    mov cl,2
    div cl
    mov dl, 39
    sub dl, al
ret
epilepsia:
    mov bl,[vermelho]
    call clear
    call delay
    mov bl, [azul]
    call clear
    call delay
    mov bl, [verde]
    call clear
    call delay
    mov bl, [magenta]
    call clear
    call delay
ret

;funcoes especiais para a forca
square_print:
    mov [column], dl
    mov [row], dh
    call setCursor
    
    .loop:
    lodsb
    cmp al,0xd
    je .line
    cmp al, 0
    je .done
    call putchar
    jmp .loop

    .line:
    mov dl, [column]
    inc dh
    call setCursor
    jmp .loop

    .done:
    mov dl,[column]
    mov dh,[row]
ret
letter:
    mov si, alfabeto
    xor cx,cx
    ;Ve se e uma letra
    cmp al, 'a'
    jae .small
    cmp al, 'A'
    jae .big
    jmp .nao_letra

    .small:
    cmp al, 'z'
    ja .nao_letra
    sub al,'a'
    jmp .count
    .big:
    cmp al,'Z'
    ja .nao_letra
    sub al,'A'
    jmp .count

    .count:
    cmp cl,al
    je .end
    add si,[offset]
    inc cl
    jmp .count

    .nao_letra:
    mov si,nao_letra
    .end:
ret
tela_inicial:
    mov bl,[preto]
    call clear
    mov bl,[branco]
    ;Imprime as imagens
    mov dh,0
    mov dl,2
    mov si, imagem_vazia
    call square_print
    mov dh, 3
    mov dl, 20
    mov si, titulo_imagem
    call square_print
    ;Imprime os titulos
    mov dh, 20
    mov si, jogo1
    call centralizar
    call setCursor
    call print
    add dh,5
    mov si, jogo2
    call centralizar
    call setCursor
    call print
ret
square_word: ;Precisa referenciar a palavra em di primeiro, imprime toda ela
    .loop:
    mov al,[di]
    inc di
    cmp al,0
    je .end
    call letter
    call setCursor
    call square_print
    add dl,9
    jmp .loop
    .end:
ret
tela_vitoria:
    ;limpa a tela
    mov bl,[preto]
    call clear
    mov bl, [verde]
    ;Imprime o texto de obrigado
    mov dh, 3
    mov dl, 5
    mov di, obrigado
    call setCursor
    call square_word
    ;Imprime Joelson de braços abertos
    mov si, imagem_saved
    mov dh, 9
    mov dl, 30
    call setCursor
    call square_print
    ;Mensagem para continuar
    mov si, QQ_tecla
    mov dh, 9
    call centralizar
    call setCursor
    call print
    call getchar
ret
tela_derrota:
    ;limpa a tela
    mov bl,[preto]
    call clear
    mov bl, [vermelho]
    ;Imprime o texto de obrigado
    mov dh, 1
    mov dl, 9
    mov di, derrota
    call setCursor
    call square_word
    ;Imprime Joelson de braços abertos
    mov si, imagem_morto
    mov dh, 9
    mov dl, 30
    call setCursor
    call square_print
    ;Mensagem para continuar
    mov si, QQ_tecla
    mov dh, 7
    call centralizar
    call setCursor
    call print
    call getchar
ret

;Palavra aleatoria ainda nao funciona


start:
    ;Essencial para nao dar erros
    xor ax,ax
    xor dx,dx
    mov es,ax

    ;Começa aqui
    .loop:
    call tela_inicial
    call getchar
    call tela_vitoria
    call tela_derrota
    jmp .loop

    


    ;Aqui ficara o jogo proprio, antes devem ficar os testes
    ; .loop:
    ; call tela_inicial
    ; call getchar
    ; cmp al, '1'
    ; je .opcao1
    ; cmp al, '2'
    ; je .opcao2
    ; jmp .loop

    ; .opcao1
    ; mov bl, [preto]
    ; call clear
    ; jmp .opcao1

    ; .opcao2
    ; mov bl,[preto]
    ; call clear
    ; jmp .opcao2
    

jmp done

done:
    jmp $