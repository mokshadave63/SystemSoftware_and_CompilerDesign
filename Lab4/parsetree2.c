#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 100
#define MAX_STEPS_SIZE 1000

char input_[MAX_INPUT_SIZE];
size_t pos_ = 0;
char steps_[MAX_STEPS_SIZE];
size_t steps_length = 0;

bool E();
bool E1();
bool T();
bool T1();
bool F();
void append_steps(const char *text);
bool parse();
char peek();
void next();

void append_steps(const char *text) {
    if (steps_length + strlen(text) < MAX_STEPS_SIZE) {
        strcat(steps_, text);
        steps_length += strlen(text);
    }
}

bool parse() {
    bool result = E();
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

bool E() {
    append_steps("E -> TE'\n");
    if (T()) {
        return E1();
    }
    return false;
}

bool E1() {
    if (peek() == '+') {
        append_steps("E' -> +TE'\n");
        next();
        if (T()) {
            return E1();
        }
        return false;
    }
    append_steps("E' -> epsilon\n");
    return true;
}

bool T() {
    append_steps("T -> FT'\n");
    if (F()) {
        return T1();
    }
    return false;
}

bool T1() {
    if (peek() == '*') {
        append_steps("T' -> *FT'\n");
        next();
        if (F()) {
            return T1();
        }
        return false;
    }
    append_steps("T' -> epsilon\n");
    return true;
}

bool F() {
    if (peek() == '(') {
        append_steps("F -> (E)\n");
        next();
        if (E()) {
            if (peek() == ')') {
                next();
                return true;
            }
        }
        return false;
    } else if (peek() == 'a') {
        append_steps("F -> a\n");
        next();
        return true;
    }
    append_steps("F -> error, expected 'a' or '('\n");
    return false;
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
