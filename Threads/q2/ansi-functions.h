#include <stdio.h>
// Funções para mover o cursor
void left(int n)    {printf("\u001b[%dD", n);}
void right(int n)   {printf("\u001b[%dC", n);}
void up(int n)      {printf("\u001b[%dA", n);}
void down(int n)    {printf("\u001b[%dB", n);}

void next_line(int n){printf("\u001b[%dE",n);}
void prev_line(int n){printf("\u001b[%dF",n);}

void save_pos(){printf("\u001b[s");}
void ret_pos(){printf("\u001b[u");}

void erase_line(){printf("\u001b[2K");}
void erase_display(){printf("\u001b[2J");}

// \033[38;2;<r>;<g>;<b>m     #Select RGB foreground color
// \033[48;2;<r>;<g>;<b>m     #Select RGB background color

void print_red()    {printf("\033[38;2;0;0;0m"); printf("\033[48;2;255;0;0m");}
void print_yellow() {printf("\033[38;2;0;0;0m"); printf("\033[48;2;255;255;0m");}
void print_blue()   {printf("\033[38;2;0;0;0m"); printf("\033[48;2;0;0;255m");}
void print_magenta(){printf("\033[38;2;0;0;0m"); printf("\033[48;2;255;0;255m");}
void print_green()  {printf("\033[38;2;0;0;0m"); printf("\033[48;2;0;255;0m");}
void print_black()  {printf("\033[38;2;255;255;255m"); printf("\033[48;2;0;0;0m");}
void print_cyan()   {printf("\033[38;2;0;0;0m"); printf("\033[48;2;0;255;255m");}

void reset(){printf("\e[0m");}
