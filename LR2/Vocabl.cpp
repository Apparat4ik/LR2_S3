#include <iostream>
#include <sstream>
#include "MyArray.h"

using namespace std;

// Подсчёт количества ударений
int count_accents(const string &word) {
    int count = 0;
    for (char c : word) {
        if (c >= 'A' && c <= 'Z') count++;
    }
    return count;
}

string to_lower(const string &s) {
    string res;
    for (char c : s) {
        if (c >= 'A' && c <= 'Z'){
            res += c - 'A' + 'a';
        } else {
            res += c;
        }
    }
    return res;
}


int check_issue(const MyArray<string>& voc, stringstream& text){
    string word;
    
    int issueCount = 0;
    while(text >> word){
        string low = to_lower(word);
        int accents = count_accents(word);
        
        bool inVoc = false;
        bool matchVar = false;
        for (int i = 0; i < voc.size; i++){
            string vocWord = MGET(voc, i);
            if (to_lower(vocWord) == low){
                inVoc = true;
                if (vocWord == word){
                    matchVar = true;
                    break;
                }
            }
        }
        
        if (inVoc){
            if (!matchVar){issueCount++;}
        } else {
            if (accents != 1){issueCount++;}
        }
    }
    return issueCount;
}


int main() {
    int amount;
    cin >> amount;
    MyArray<string> vocablur{10};
    
    for (int i = 0; i < amount; i++){
        string word;
        cin >> word;
        MPUSH_back(vocablur, word);
    }
    string text;
    getline(cin, text);
    getline(cin, text);
    stringstream ss(text);
    
    cout << check_issue(vocablur, ss) << endl;
    
    return 0;
}
