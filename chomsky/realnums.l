%{
#include<stdio.h>

int thing;
%}
%%

thing   thing++;

%%

int yywrap()
{
    return 1;
}

int main(int argc, char **argv)
{
    yylex();

    printf("%d", thing);

    return 0;
}