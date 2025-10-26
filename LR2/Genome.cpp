#include <iostream>
#include <sstream>
#include "MySet.h"

using namespace std;

int gen_closeness(const string& firstGen, const string& secondGen){
    int closenessCount = 0;
    MySet<string> gens{10};
    for (int i = 0; i < firstGen.size() - 1; i++){
        string genPair = string(1, firstGen[i]) + firstGen[i+1];
        gens.SETADD(genPair);
    }
    
    for (int i = 0; i < secondGen.size() - 1; i++){
        string genPair = string(1, secondGen[i]) + secondGen[i+1];
        if (gens.SET_AT(genPair)){
            for (int j = 0; j < firstGen.size(); j++){
                string fgenPair = string(1, firstGen[j]) + firstGen[j+1];
                if (fgenPair == genPair){
                    closenessCount++;
                }
            }
        }
    }
    return closenessCount;
}


int main() {
    string gen1, gen2;
    
    cin >> gen1 >> gen2;
    
    cout << gen_closeness(gen1, gen2) << endl;
    
    return 0;
}
