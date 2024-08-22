%{
#include<stdio.h>
int html_tags = 0;
int sql_tags = 0;
int start_tags = 0;
int end_tags = 0;
%}

%%
"<"[a-zA-Z]+">" {start_tags++; html_tags++; printf("The start tag is: %s\n", yytext);}
"</"[a-zA-Z]+">" {end_tags++; html_tags++; printf("The end tag is: %s\n", yytext); }
"INSERT"|"SELECT"|"UPDATE"|"ALTER"|"DROP" { sql_tags++; printf("The SQL tag is: %s\n", yytext); }
%%

int main(int argc, char* argv[]){
	FILE *input = fopen("sql_html.txt", "r");
	if (!input){
           printf("Error opening file");	
	   return 1;
   	}
	yyin = input; // Set the input file for the Flex
	yylex();
	fclose(input);
	printf("The total number of SQL tags are: %d\n", sql_tags);
	printf("The total number of HTML tags are: %d\n", html_tags);
	printf("The total number of start tags are: %d\n", start_tags);
	printf("The total number of end tags are: %d\n", end_tags);
	return 0;
}

int yywrap(){
    return 1;
}
