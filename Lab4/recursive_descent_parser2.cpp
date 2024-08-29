#include <bits/stdc++.h>
using namespace std;
// E -> TE'
// E' -> +TE'|_
// T -> FT'
// T' -> *FT'|_
// F -> (E)|a
stack<string> stk;
bool E(string& str, int& ptr);
bool E1(string& str, int& ptr);
bool T(string& str, int& ptr);
bool T1(string& str, int& ptr);
bool F(string& str, int& ptr);

int main() {
    string str("(a*a)+a$");
    int ptr = 0;
    bool res = E(str, ptr) && ptr == str.size()-1;
    // to check if complete string is accepted or not
    cout << res << endl;
    while(!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    return 0;
}

bool E(string& str, int& ptr) {
    if(T(str, ptr)) {
        if(E1(str, ptr)) {
            stk.push("E -> TE'");
            return true;
        }
    }
    return false;
}

bool E1(string& str, int& ptr) {
    if(str[ptr] == '+') {
        ptr++;
        if(T(str, ptr)) {
            if(E1(str, ptr)) {
                stk.push("E' -> +TE'");
                return true;
            }
        }
    }
    else {
        stk.push("E' -> _");
        return true;
    }
    return false;
}

bool T(string& str, int& ptr) {
    if(F(str, ptr)) {
        if(T1(str, ptr)) {
            stk.push("T -> FT'");
            return true;
        }
    }
    return false;
}

bool T1(string& str, int& ptr) {
    if(str[ptr] == '*') {
        ptr++;
        if(F(str, ptr)) {
            if(T1(str, ptr)) {
                stk.push("T' -> *FT'");
                return true;
            }
        }
    }
    else {
        stk.push("T' -> _");
        return true;
    }
    return false;
}

bool F(string& str, int& ptr) {
    if(str[ptr] == '(') {
        ptr++;
        if(E(str, ptr)) {
            if(str[ptr] == ')') {
                ptr++;
                stk.push("F -> (E)");
                return true;
            }
        }
    }
    else if(str[ptr] == 'a') {
        ptr++;
        stk.push("F -> a");
        return true;
    }
    return false;
}