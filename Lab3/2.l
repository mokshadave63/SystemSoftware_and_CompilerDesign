%{
#include<stdio.h>
int nc = 0;
FILE *yyout_comment;
FILE *yyout_code;
int in_comment = 0;
%}
%%
"/*" {
in_comment = 1;
fprintf(yyout_comment, "%s", yytext);
};
"*/" {
if (in_comment) {
in_comment = 0;
fprintf(yyout_comment, "%s\n", yytext);
}
nc++;
};
"//".* {
if (!in_comment)
fprintf(yyout_comment, "%s\n", yytext);
nc++;
};
.|\n {
if (!in_comment)
fprintf(yyout_code, "%s", yytext);
else
fprintf(yyout_comment, "%s", yytext); // Write comment lines
} // Write non-comment code and comments within multiline comments
%%
int main()
{
yyin = fopen("a_ref.txt", "r");
yyout_comment = fopen("comment.txt", "w");
yyout_code = fopen("program.c", "w");
yylex();
fclose(yyin);
fclose(yyout_comment);
fclose(yyout_code);
return 0;
}
int yywrap()
{
return 1;
}