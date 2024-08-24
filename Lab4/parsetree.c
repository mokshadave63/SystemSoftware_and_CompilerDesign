#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


char input_[100];
size_t pos_ = 0;
char steps_[1000];
size_t steps_length = 0;

void append_steps(const char *text) {
    if (steps_length + strlen(text) < 1000) {
        strcat(steps_, text);
        steps_length += strlen(text);
    }
}

bool S();
bool A();
bool B();

bool parse() {
    bool result = S();
    if (result && pos_ == strlen(input_)) {
        printf("The input string is valid according to the grammar.\n");
        printf("Steps:\n%s", steps_);
    } else {
        printf("The input string is not valid according to the grammar.\n");
    }
    return result;
}

char peek() {
    return pos_ < strlen(input_) ? input_[pos_] : '\0';
}

void next() {
    if (pos_ < strlen(input_)) {
        ++pos_;
    }
}

bool S() {
    append_steps("S -> AA\n");
    return A() && A();
}

bool A() {
    append_steps("A ");
    if (peek() == 'a') {
        append_steps("-> aB\n");
        next();
        return B();
    } else {
        append_steps("-> epsilon\n");
        return true;
    }
}

bool B() {
    append_steps("B ");
    if (peek() == 'b') {
        append_steps("-> b\n");
        next();
        return true;
    } else {
        append_steps("-> error, expected 'b'\n");
        return false;
    }
}

int main() {
    printf("Enter the input string: ");
    if (fgets(input_, sizeof(input_), stdin) != NULL) {
        size_t len = strlen(input_);
        if (len > 0 && input_[len - 1] == '\n') {
            input_[len - 1] = '\0';
        }

        steps_[0] = '\0';
        steps_length = 0;

        parse();
    }
    return 0;
}