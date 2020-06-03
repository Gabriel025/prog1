%{
#include<stdio.h>
#include<ctype.h>

char from[20] = {'w',      'e', 't', 'z', 'i', 'o', 'p',  'a', 's', 'd',  'g', 'h',   'k',  'l', 'x', 'c',  'v',   'b',  'n',    'm'};
char *to[20] =  {"\\/\\/", "3", "7", "2", "1", "0", "|°", "4", "5", "|)", "9", "|-|", "|<", "1", "><", "(", "\\/", "|3", "|\\|", "|\\/|"};
%}

%%

. {
    int found = 0;
    for(int i = 0; i < 20; i++)
    {
        if(tolower(*yytext) == from[i])
        {
            printf("%s", to[i]);
            found = 1;
            break;
        }
    }
    if(!found) printf("%c", *yytext);
}

%%

int main(int argc, char **argv)
{
    yylex();

    return 0;
}