#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ansi-functions.h"

int main(void)
{
    print_red();
    printf("                         \n");
    print_yellow();
    printf("AQT123 Frankfurt    20:00\n");
    print_blue();
    printf("AQT123 Frankfurt    20:00\n");
    print_magenta();
    printf("AQT123 Frankfurt    20:00\n");
    print_green();
    printf("AQT123 Frankfurt    20:00\n");
    print_black();
    printf("AQT123 Frankfurt    20:00\n");
    print_cyan();
    printf("AQT123 Frankfurt    20:00\n");
    reset();
}