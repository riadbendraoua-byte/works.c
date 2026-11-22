chiffre [0-9];
lettere [a-zA-Z];
%%
{lettere}({chiffre}|{lettere})*{printf("IDENTIFIER: %.*s\n", yyleng, yytext);}
({chiffre})+ {printf("NUMBER: %.*s\n", yyleng, yytext);}

%%