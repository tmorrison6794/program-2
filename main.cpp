#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include <sstream>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;
    // TODO
    istringstream iss(line);
    string word;
    while (iss >> word) {
        Token token;
        token.value = word;
        tokens.push_back(token);
    }
    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    // TODO
    if (op=="*"||op=="/") return 2;
    if (op=="+"||op=="-") return 1;
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    // TODO
    if (tokens.size()==0)
    return false;

    for (int i=0; i<tokens.size(); i++) {
        if (tokens[i].value=="(" || tokens[i].value==")")
            return false;
    }
    for (int i=0; i<tokens.size(); i++) {
        string op = tokens[i].value;
        bool isNum=!op.empty();
        for (int j=0; j<op.size(); j++) {
            if (!isdigit(op[j])) {
                isNum=false; break;
            }
        }
        if (!isNum&& !isOperator(op)) return false;
    }

        int depth=0;
        for (int i=0; i<tokens.size(); i++) {
            if (isOperator(tokens[i].value)) {
                if (depth<2) return false;
                depth--;
            } else{ depth++; }
        }

        return depth==1;

}

bool isValidInfix(const vector<Token>& tokens) {
    // TODO
    if (tokens.size()==0)
        return false;
    for (int i=0; i<tokens.size(); i++) {
        string op = tokens[i].value;
        bool isNum=!op.empty();
        for (int j=0; j<op.size(); j++) {
            if (!isdigit(op[j])) {
                isNum=false; break;
            }
        }
        if (!isNum&& !isOperator(op)&& op !="("&& op !=")") return false;
    }
    const string& first=tokens[0].value;
    bool firstIsNum=!first.empty();
    for (int j=0; j<first.size(); j++) {
        if (!isdigit(first[j])) {
            firstIsNum=false; break;
        }
    }
    if (!firstIsNum&& first!="(") return false;
    const string&last=tokens[tokens.size()-1].value;
    bool lastIsNum=!last.empty();
    for (int j=0; j<last.size(); j++) {
        if (!isdigit(last[j])) {
            lastIsNum=false; break;
        }
    }
    if (!lastIsNum&& last!=")") return false;
    for (int i=0; i<tokens.size()-1; i++) {
        const string& cur = tokens[i].value;
        const string& next=tokens[i+1].value;
        bool curIsNum=!cur.empty();
        for (int j=0; j<cur.size(); j++) {
            if (!isdigit(cur[j])) {
                curIsNum=false; break;
            }
        }
        bool nextIsNum=!next.empty();
        for (int j=0; j<next.size(); j++) {
            if (!isdigit(next[j])) {
                nextIsNum=false; break;
            }
        }
        if (curIsNum||cur==")") {
            if (!isOperator(next)&&next!=")") return false;
        }
        if (isOperator(cur)||cur=="(") {
            if (!nextIsNum&& next!="(") return false;
        }
    }

    int balance=0;
    for (int i=0; i<tokens.size(); i++) {
        if (tokens[i].value=="(") {
            balance++;
        }else if (tokens[i].value==")") {
                balance--;
                if (balance<0) return false;
            }
        }
        if (balance!=0) return false;
    return true;
}


// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    // TODO
    ArrayStack<string> opStack;
    for (int i=0; i<tokens.size(); i++) {
        const string& op = tokens[i].value;
        bool isNum=!op.empty();
        for (int j=0; j<op.size(); j++) {
            if (!isdigit(op[j])) {
                isNum=false; break;
            }
            }
            if (isNum) {
                output.push_back(tokens[i]);
            } else if (isOperator(op)) {
                while (!opStack.empty()) && isOperator(opStack.top())
                &&precedence((opStack.top())) >= precedence(opStack.top()) {
                    output.push_back(tokens[i]);
                    opStack.pop();
                }
                opStack.push(op);
            } else if (val=="(")

        }
    }
    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    // TODO
    return 0.0;
}

// Main

int main() {
    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
}
