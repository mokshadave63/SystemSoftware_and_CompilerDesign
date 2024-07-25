#include<stdio.h>
#include<conio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char* str) {
    char keywords[32][10] = {
        "auto", "double", "int", "struct", "break", "else", "switch",
        "case", "enum", "typedef", "char", "return", "const", 
        "float", "for", "void", "goto", "sizeof", "do", "if", "static", "while"
    };
    int i;
    for(i=0; i<32; ++i){
      if(strcmp(keywords[i], str)== 0){
      return 1;
      }
    }
    
    return 0;
}
int isIdentifier(char* str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return 0;
    }
    for (int i = 1; i < strlen(str); ++i) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int isNumber(char* str){
  int i=0;
  if(str[0]== '-'){
    i=1;

  }
  for(; i<strlen(str); ++i){
    if(!isdigit(str[i])){
      return 0;
    }
  }
  return 1;
}

int isOperator(char ch){
  char operators[]= "+-*/%=;";
  for(int i =0; i< strlen(operators); ++i){
    if(ch == operators[i]){
      return 1;
    }
  }
  return 0;
 }

 int main(){
  int count = 0, count_dig = 0, count_op = 0, count_id = 0, count_sep = 0;
  FILE *fp;
  char filename[50];
  char word[50];

  printf("enter the filename:");
  scanf("%s", filename);

  fp=fopen(filename,"r");
  if(fp== NULL){
    printf("error openeing the file %s", filename);
    return 1;
  }

  while (fscanf(fp, "%s", word) != EOF) {
        if (isKeyword(word)) {
            printf("%s is a keyword.\n", word);
            count++;
        } else if (isIdentifier(word)) {
            printf("%s is an identifier.\n", word);
            count_id++;
        } else if (isNumber(word)) {
            printf("%s is a number.\n", word);
            count_dig++;
        } else if (strlen(word) == 1 && isOperator(word[0])) {
            printf("%s is an operator.\n", word);
            count_op++;
        } else {
            printf("Cannot identify %s.\n", word);
        }
    }
    printf("\nKeywords: %d", count);
    printf("\nIdentifiers: %d", count_id);
    printf("\nDigits: %d", count_dig);
    printf("\nOperators: %d", count_op);
     fclose(fp);

    return 0;
 }