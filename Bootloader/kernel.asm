org 0x7e00
jmp 0x0000:start

 
; Grupo:
; Alef Gabryel (aglc)
; Ian Karlos (ikts)   
; Thales Christ (tcsr)


data: 
;Usuario
input times 10 db 0 ;Todas as palavras
valor times 2 db 0 ;Qualquer numero inteiro
numero times 10 db 0 ;O valor so que em uma string, usado para debugs

;Cores
vermelho db 4
branco db 15
preto db 0
verde db 2

;Tela de Titulo
jogo1 db "1 - Palavra Aleatoria", 0
jogo2 db "2 - Palavra Especifica", 0

;Valores auxiliares
column db 0
row db 0
offset dw 41 ; Tamanho de cada letra

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

imagem_negacao: 
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

imagem_ira: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X \ / X  ",13,
db "X    X o o X  ",13,
db "X    X  ^  X  ",13,
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

imagem_barganha: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X ^ ^ X  ",13,
db "X    X o o X  ",13,
db "X    X  O  X  ",13,
db "X     XXXXX   ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X     X X     ",13,
db "X    X  X     ",13,
db "X   X   X     ",13,
db "X  X    X     ",13,
db "X       X     ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,
db "X             ",13,0

imagem_depressao: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X     X  ",13,
db "X    X T T X  ",13,
db "X    X  .  X  ",13,
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

imagem_aceitacao: 
db "XXXXXXXXXXXXXX",13,
db "X       X     ",13,
db "X     XXXXX   ",13,
db "X    X     X  ",13,
db "X    X . . X  ",13,
db "X    X  _  X  ",13,
db "X     XXXXX   ",13,
db "X       X     ",13,
db "X       X     ",13,
db "X     X X X   ",13,
db "X    X  X  X  ",13,
db "X   X   X   X ",13,
db "X  X    X    X",13,
db "X       X     ",13,
db "X      X      ",13,
db "X     X       ",13,
db "X    X        ",13,
db "X   X         ",13,
db "X  X          ",13,0

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

espaco:
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

lista: 
db "gangorra", 0, "candeeiro", 0, "flor", 0, "sapato", 0, "caixa", 0, "lapiseira", 0,
db "prancheta", 0,"minissaia",0, "cassetete", 0, "brinquedo", 0, "vassoura",0, "lanterna", 0, 
db "fantoche", 0, "hidrante", 0, "autoctone", 0, "diamante", 0, "baralho", 0, "cadeado", 0, 
db "esmalte", 0, "mochila", 0, "incenso", 0, "scanner", 0, "tijolo", 0, "pijama", 0, "rabeca", 0, 
db "escova", 0, "jaleco", 0,"piano", 0, "jeans", 0, "lacre", 0, "motor", 0, "anzol", 0, "fita", 0,
db "cruz", 0, "arca", 0, "tear", 0, "pneu", 0, "pia", 0, "giz", 0, "fio", 0  

lista_quantity dw 40 ;Quantas palavras tem, e necessario mudar isso para que funcione

;Textos variados
texto_vitoria db "obrigado", 0
texto_derrota db "derrota", 0
QQ_tecla db "Aperte qualquer tecla para continuar", 0
certeza db "E essa palavra que queres? 1-Sim 2-Nao", 0
caso_numero db "Suportamos apenas letras. Aperte qualquer tecla para continuar", 0
pergunta_palavra db "Nao deixe que vejam, max 9 letras:", 0

;Texto do jogo principal
escolhas db "Pressione para colocar   1- Letra  ou  2- Palavra", 0
letras_erradas_strings db "Letras erradas:",0
letra_pergunta db "Aperte uma letra", 0
palavra_pergunta db "Coloque a palavra que voce acha que e:", 0
palavra_erro db "Apenas letras por favor:", 0

palavra_da_derrota db "Voce perdeu para a palavra: ",;Nao possui zero pois na hora ira imprimir
forca_palavra times 10 db 0;Com a palavra da forca em conjunto

salva_endereco dw 0 ;Isso e usado para manter a posição em um ponteiro de letras

;Diversos valores auxiliares
letras_erradas times 6 db 0
adivinhar times 10 db 0
vida db 0
letra db 0

;Funçoes gerais
putchar: ;Coloca o caractere na tela; o al permanece o que pegou; ;Precisa setar o bl antes ;O cx e usado como contador
    mov ah, 0x0e
    cmp al, 0x8
    je .backspace
    cmp al, 0xd
    je .enterkey
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
    dec cx
    jmp .done

    .enterkey:
    int 10h
    mov al,0xa
    int 10h
    mov al,0xd
    .done:
ret   
getchar: ;Pega o caractere e salva em al
  mov ah, 0x00
  int 16h
ret
print: ;Printa o que ta no si, o ultimo char tem que ser 0
    .loop:
    lodsb
    call putchar
    cmp al,0
    je .done
    jmp .loop
    .done:
    mov al, 0xd
    call putchar
ret
storechar: ;Salva o que ta em al no di
    cmp al, 0x8
    je .backspace
    cmp al, 0xd
    je .done
    stosb
    inc cx
    jmp .done
    .backspace:
    cmp cx,0
    je .done
    dec di
    mov [di],byte 0
    .done:
ret
comp: ;Compara duas palavras ate ambas chegarem a 0
    .loop:
    lodsb
    mov cl,byte [di]
    inc di
    ;Chegou no final
    cmp al,0
    je .igual
    cmp al, cl
    je .loop
    ret
    .igual:
    cmp cl, 0;A comparaçao de vitoria carrega pro proximo jump
ret
getline: ;Pega até apertar enter, maximo de 9 caracteres
    xor cx,cx
    mov di,input
    ;Loop principal
    .loop:
    call getchar
    cmp cx, 9
    je .teste
    cmp al, 0xd
    je .end
    .proceed:
    call storechar
    call putchar
    jmp .loop
    ;So modifica se for enter ou backspace
    .teste:
    cmp al, 0xd
    je .end
    cmp al, 0x8
    je .proceed
    jmp .loop
    ;No end adiciona um byte 0
    .end:
    mov [di],byte 0
    mov al, 0xd
    call putchar
    mov di, input
    call normalizar
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

;nao utilizadas normalmente
number:;Salva uma string de numero em 'valor' (nao utilizada)
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
toString: ;Pega o numero em [valor] e salva em [numero] como string; (debug)
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
delay: ;Nao utilizada
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

;funcoes especiais para a forca
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
square_print:;Imprime com si
    ;mantem as colunas e oendereço original
    mov word [salva_endereco],si
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
    ;Caso chega em uma nova linha retorna a coluna original e so incrementa a linha
    .line:
    mov dl, [column]
    inc dh
    call setCursor
    jmp .loop

    .done:
    mov dl,[column]
    mov dh,[row]
    mov si, word [salva_endereco]
ret
letter:;Pega o ascii equivalente a letra
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
paisagem:;Imprime a imagem de titulo
    mov dh,1
    mov dl,2
    mov si, imagem_vazia
    call square_print
    mov dh, 3
    mov dl, 20
    mov si, titulo_imagem
    call square_print
ret
tela_inicial:;Coloca a primeira tela
    call reset
    ;Imprime as imagens
    call paisagem
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
    cmp al, ' '
    je .space
    call letter
    .continue:
    call setCursor
    call square_print
    add dl,9
    jmp .loop
    .space:
    mov si, espaco
    jmp .continue
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
    mov di, texto_vitoria
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
    ;Imprime o texto de derrota
    mov dh, 1
    mov dl, 9
    mov di, texto_derrota
    call setCursor
    call square_word
    ;Imprime Joelson de braços abertos
    mov si, imagem_morto
    mov dh, 10
    mov dl, 30
    call setCursor
    call square_print
    ;Mensagem para continuar
    mov si, QQ_tecla
    mov dh, 7
    call centralizar
    call setCursor
    call print
    mov si, palavra_da_derrota
    mov dh,8
    call centralizar
    call setCursor
    call print
    call getchar
ret
get_limit:; Pega uma palavra de 9 caracteres apenas e toma certeza que nao possui numero
    .loop:
    call reset
    xor cx,cx
    call paisagem
    mov dh,17
    mov si, pergunta_palavra
    call centralizar
    call square_print
    mov dh,18
    mov dl,35
    call setCursor
    mov di, forca_palavra
    ;Limpa imprimindo tudo e reseta a palavra e a quantidade
    mov al, 0
    times 10 stosb
    call getline

    ;Se for de tamanho zero recomeça
    cmp cx, 0
    je .loop
    mov [valor],cx ;Passa antes de contar
    mov si,input
    mov di, forca_palavra
    call copia_contando
    call toString;Debug
    mov di, forca_palavra

    .continuar_loop:
    mov al,[di]
    inc di
    cmp al, 0
    je .done
    call letter
    cmp si, nao_letra
    jne .continuar_loop
    ;Caso for numero exibe a mensagem e reinicia
    mov si, caso_numero
    mov dh, 17
    call centralizar
    call setCursor
    call print
    call getchar
    jmp .loop

    ;Pergunta se tem certeza da escolha
    .done:
    mov al, 0xd
    call putchar
    mov si, certeza
    mov dh,17
    call centralizar
    call setCursor
    call print

    mov di, forca_palavra
    mov dh,23
    mov dl, 1
    call setCursor
    call square_word

    .nenhuma:
    call getchar
    cmp al, '1'
    je .end
    cmp al,'2'
    je .loop
    jmp .nenhuma

    .end:
    xor cx,cx
ret
reset:;Apaga toda a tela
    mov bl,[preto]
    call clear
    mov bl,[branco]
ret
copia_contando:;Copia de si para di, coloca em valor o tamanho
    xor cx,cx
    
    .loop:
    lodsb 
    cmp al, 0
    je .end
    stosb
    inc cx
    jmp .loop

    .end:
    mov [valor],cx
    call toString
ret
random_word: ;Pega uma palava baseada no tempo
    call random
    mov cx, [valor]
    mov di, forca_palavra
    mov si, lista

    .loop:
    cmp cx, 0
    je .end
    .interno:
    lodsb
    cmp al, 0
    je .out
    jmp .interno
    .out:
    dec cx
    jmp .loop

    .end:
    call copia_contando
ret

;Principais funcoes do jogo
boneco_vida:;Decide qual boneco vai imprimir
    cmp word [vida],0
    je .zeroerro
    cmp word [vida],1
    je .umerro
    cmp word [vida],2
    je .doiserro
    cmp word [vida],3
    je .treserro
    cmp word [vida],4
    je .quatroerro
    cmp word [vida],5
    je .cincoerro
    jmp .end

    .zeroerro:
    mov si, imagem_vazia
    jmp .end
    .umerro:
    mov si, imagem_negacao
    jmp .end
    .doiserro:
    mov si, imagem_ira
    jmp .end
    .treserro:
    mov si, imagem_barganha
    jmp .end
    .quatroerro:
    mov si, imagem_depressao
    jmp .end
    .cincoerro:
    mov si, imagem_aceitacao
    .end:
ret
jogo_tela:;Imprime os textos nao mutaveis do jogo
    call reset
    mov dh, 1
    mov dl, 2
    call boneco_vida
    call square_print
    ;Imprime a palavra para adivinhar
    mov di, adivinhar
    mov dh,23
    mov dl,1
    call setCursor
    call square_word
    ;Imprime as letras já erradas
    mov dh, 2
    mov dl, 25
    mov si, letras_erradas_strings
    call setCursor
    call print
    mov dh,4
    mov di, letras_erradas
    call setCursor
    call square_word
ret
jogo_principal:;aqui forca palavra deve estar com as adivinhadas
    ;Coloca espaços na palavra para adivinhar
    mov cx,[valor]
    mov al, ' '
    mov di, letras_erradas
    times 5 stosb
    mov di, adivinhar

    .preencher:
    cmp cx, 0
    je .go
    stosb
    dec cx
    jmp .preencher
    .go:
    mov byte [vida],0 ;Zero o contador de vidas
    
    .loop:
    ;Imprimir a tela
    mov byte [letra],0
    cmp byte [vida], 6
    je .perdeu
    call jogo_tela
    mov dh, 13
    mov dl, 25
    mov si, escolhas
    call setCursor
    call print
    
    ;Começa o jogo
    .wait:
    call getchar
    cmp al,'1'
    je .letra
    cmp al,'2'
    je .palavra
    jmp .wait
    
    ;Escolheu para dizer uma letra
    .letra:
    call jogo_tela
    mov dh, 13
    mov dl,25
    mov si, letra_pergunta
    call setCursor
    call print
    mov si, espaco
    mov dh, 16
    mov dl, 25
    call square_print
    mov si, nao_letra
    ;Termina de imprimir
    .letraloop:
    call getchar
    cmp al, 0xd
    je .try
    mov byte [letra], al
    call letter
    call square_print
    jmp .letraloop
    .try:
    cmp si, nao_letra ;Se nao for uma letra nao sai
    je .letraloop
    jmp .comparassao_letra
    
    ;Imprime a tela e as perguntas
    .palavra:
    call jogo_tela
    mov dh, 13
    mov dl,25
    mov si, palavra_pergunta
    call setCursor
    call print
    mov dh, 16
    mov dl, 25
    call setCursor
    mov di, input
    mov dl, 25
    call setCursor
    call getline
    cmp si, nao_letra
    je .errado
    jmp .comparassao_palavra
    .errado:
    call jogo_tela
    mov dh, 13
    mov dl,25
    mov si, palavra_erro
    call setCursor
    call print
    mov dh, 16
    mov dl, 25
    call setCursor
    mov di, input
    mov dl, 25
    call setCursor
    call getline
    cmp si, nao_letra
    je .errado
    jmp .comparassao_palavra

    .comparassao_letra:
    call letra_comparar
    call completou
    je .ganhou
    jmp .loop

    .comparassao_palavra:
    mov di, input
    mov si, forca_palavra
    call comp
    je .ganhou

    ;Colocar uma carinha e contar como erro
    mov cx,[vida]
    mov di, letras_erradas
    .erro_frase:
    cmp cx, 0
    je .out
    dec cx
    inc di
    jmp .erro_frase
    .out:
    mov al,'1'
    mov [di],al
    inc byte [vida]

    jmp .loop

    .perdeu:
    call tela_derrota
    jmp .end

    .ganhou:
    call tela_vitoria
    jmp .end

    .end:
ret
letra_comparar: ;Ve se existe a letra na palavra
    mov dl,[letra]
    mov si,forca_palavra
    mov di,adivinhar
    xor cx,cx
    
    .loop:
    lodsb
    cmp al, 0
    je .end
    cmp al, dl
    je .colocar
    inc di
    jmp .loop 

    .colocar:
    mov [di],dl
    inc di
    inc cx
    jmp .loop

    .end:
    cmp cx,0
    je .falha ;Se nao ouve a letra
    jmp .done

    .falha:
    mov si, letras_erradas
    .innerloop:
    mov al, [si]
    cmp al, ' '
    je .fora
    cmp [si], dl
    je .done
    inc si
    jmp .innerloop
    .fora:
    mov [si],dl
    inc byte [vida]
    .done:
ret
completou: ;Ve se completou a palavra
    mov di, forca_palavra
    mov si, adivinhar
    .loop:
    lodsb
    mov dl, [di]
    inc di
    cmp al, 0
    je .end
    cmp al,dl
    je .loop
    .end:
    cmp dl,0
ret
normalizar:;Pega o que ta em di e coloca tudo em minuscula
    .loop:
    mov al,[di]
    cmp al,'a'
    jae .minuscula
    cmp al,'A'
    jae .maiuscula
    cmp al,0
    je .done
    inc di
    mov si, nao_letra
    jmp .loop
    .minuscula:
    inc di
    jmp .loop
    .maiuscula:
    add al,32
    mov [di],al
    inc di
    jmp .loop
    .done:
ret

start:
    ;Essencial para nao dar erros
    xor ax,ax
    xor dx,dx
    mov es,ax
    call setCursor

    .loop: ;Reseta todas as variaveis
    mov al,0
    mov di, input
    times 10 stosb
    mov di, forca_palavra
    times 10 stosb
    mov di, adivinhar
    times 10 stosb
    mov di,letras_erradas
    times 6 stosb

    ;testes devem ficar antes
    call tela_inicial
    .wait:
    call getchar
    cmp al, '1'
    je .opcao1
    cmp al, '2'
    je .opcao2
    jmp .wait

    .opcao1:
    call random_word
    jmp .jogo

    .opcao2:
    call get_limit
    jmp .jogo
    
    .jogo:
    call jogo_principal
jmp .loop

done:
    jmp $