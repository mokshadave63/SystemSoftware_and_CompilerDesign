%{
    
%}

%%
"while"|"if"|"else"|"const"|"final"|"break"|"for"  { printf("keyword: %s\n", yytext); }

[a-zA-Z]+[a-zA-Z0-9]* { printf("identifier: %s\n", yytext); }

">"|"<"|">="|"<="|"=="|"!="|"=" { printf("Relational Operator: %s\n", yytext); }

[0-9]+ { printf("Number: %s\n", yytext); }

","|"("|")"|";"|"{"|"}" { printf("separator: %s\n", yytext); }

%%

int main() {
    printf("Enter a lexeme:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
