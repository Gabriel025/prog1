%{
#include <stdio.h>
#include <stdlib.h>
int realnums = 0, hexnums = 0;
%}

real_literal    0[xX]([0-9A-F]+|[0-9a-f]+)
hex_literal     [+-]?[0-9]*\.?[0-9]+

%%

{real_literal}      { hexnums++; printf("hex  number found: %s %ld\n", yytext, strtol(yytext, NULL, 0)); }
{hex_literal}       { realnums++; printf("real number found: %s %f\n", yytext, atof(yytext)); }
.|\n ;

%%

int yywrap() { return 1; }

int main(int argc, char **argv)
{
    yylex();

    printf("number of reals in input: %d\nnumber of hex values in input: %d\n", realnums, hexnums);

    return 0;
}