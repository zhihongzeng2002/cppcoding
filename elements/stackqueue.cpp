#include "stackqueue.h"
#include <sstream>

Stackqueue::Stackqueue()
{
}

int Stackqueue::reverserPolishNotation(string s) {
    stack<int> q;
    stringstream ss(s);
    string symbol;
    while (getline(ss, symbol, ',')) {
        if (symbol=="+" || symbol=="-" || symbol=="*" || symbol=="/") {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            switch (symbol.front()) {
            case '+':
                q.emplace(x+y);
                break;
            case '-':
                q.emplace(y-x);
                break;
            case '*':
                q.emplace(y*x);
                break;
            default:
                q.emplace(y/x);
            }
        } else
            q.emplace(stoi(symbol));
    }
    return q.top();
}

static void insert(stack<int> & S, int x) {
    if (!S.empty() && x>S.top()) {
        int t=S.top();
        S.pop();
        insert(S, x);
        S.push(t);
    } else
        S.push(x);
}

void Stackqueue::sortStackInPlace(stack<int> &S) {
    if (!S.empty()) {
        int x=S.top();
        S.pop();;
        sortStackInPlace(S);
        insert(S, x);
    }
}

static void moveToBottom(stack<int> & S, int x) {
    if (!S.empty()) {
        int t=S.top();
        S.pop();
        moveToBottom(S, x);
        S.push(t);
    } else
        S.push(x);
}

void Stackqueue::reverseStackInPlace(stack<int> &S) {
    if (!S.empty()) {
        int x=S.top();
        S.pop();
        reverseStackInPlace(S);
        moveToBottom(S, x);
    }
}


