#include <iostream>
#include <sstream>
#include "MyStack.h"
#include "MyArray.h"

using namespace std;

char operation_with(char a, char b, char oper){
    bool first = (a == '1');
    bool second = (b == '1');
    bool result = false;
    if (oper == '|'){result = first || second;}
    if (oper == '&'){result = first && second;}
    if (oper == '^'){result = first ^ second;}
    return result ? '1' : '0';
}

void logic_operation(MyArray<char>& line, int i, char oper){
    char a = line.data[2 * i].key;
    char b =  line.data[2 * i + 2].key;
    MSWAP(line, 2 * i + 1, operation_with(a, b, oper));
    MDEL(line, 2 * i);
    MDEL(line, 2 * i + 1);
}


bool solve_logic(MyArray<char>& line){
    MyStack<char> operations = {'^', '|', '&'};
    for (int i = 0; i < line.size; i++){
        if (line.data[i].key == '!' && line.data[i + 1].key != '('){
            MDEL(line, i);
            MSWAP(line, i, (line.data[i].key == '1') ? '0' : '1');
        }
        if (line.data[i].key == '!' && line.data[i + 1].key == '('){
     
           MDEL(line, i);
           MDEL(line, i);
           MyArray<char> line_in{10};
           while (line.data[i].key != ')'){
               MPUSH_back(line_in, line.data[i].key);
               MDEL(line, i);
           }

           bool result_in = solve_logic(line_in);
           result_in = !result_in;
           MSWAP(line, i, static_cast<char>('0' + result_in));
       }
        
        if (line.data[i].key == '('){
            MDEL(line, i);
            MyArray<char> line_in{10};
            while (line.data[i].key != ')'){
                MPUSH_back(line_in, line.data[i].key);
                MDEL(line, i);
            }
            bool result_in = solve_logic(line_in);
            MSWAP(line, i, static_cast<char>('0' + result_in));
        }
    }
    
    while (line.size != 1){
        char oper = SPOP(operations);
        for (int i = 0; i < line.size / 2; i++){
            if (line.data[2 * i + 1].key == oper){
                logic_operation(line, i, oper);
                break;
            }
            if (oper == '|'){
                if (line.data[2 * i + 1].key == '|'){
                    logic_operation(line, i, oper);
                } else {
                    SPUSH(operations, '^');
                    break;
                }
            } else if (oper == '^'){
                if (line.data[2 * i + 1].key == '^'){
                    logic_operation(line, i, oper);
                } else {
                    SPUSH(operations, '|');
                    break;
                }
            }
        }
    }
    return line.data[0].key == '1';
}

int main() {
    MyArray<char> line{10};
    cout << "> ";
    string command;
    getline(cin, command);
    stringstream s(command);
            
    char word;
            
    while (s >> word) {
        MPUSH_back(line, word);
    }
    cout << solve_logic(line) << endl;
    
    return 0;
}
