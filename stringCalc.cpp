#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

bool validDouble(string num){
    bool hasDecimal = false;
    for(int i; i < num.length(); i++){
        char c = num[i];
        if (!isdigit(c)){
            if (c == '.' && !hasDecimal){

                if (i == (num.length() - 1) || i==0){
                    return false;
                }

                hasDecimal = true; 
                
            }
            else if (c == '+' || c == '-'){
                if(i != 0){
                    return false;
                }
            }
            else{
                return false;
            }
        }
    }
    return true;
}

bool boolSign(string num){
    if (num[0] == '-'){
        return false;
    }
    else{
        return true;
    }
}

string signLess(string num){
    if (num[0] == '-' || num[0] == '+'){
        return num.erase(0, 1);;
    }
    else{
        return num;
    }
}

string addNums(string num1, string num2){
    
    string result;

    bool sign1 = boolSign(num1);
    bool sign2 = boolSign(num2);

    num1 = signLess(num1);
    num2 = signLess(num2);

    int decimal1 = num1.length() - num1.find('.');
    int decimal2 = num2.length() - num2.find('.');

    if (decimal1 == -1){
        decimal1 = 0;
    }
    if (decimal2 == -1){
        decimal2 = 0;
    }

    if (decimal2 > decimal1){
        return addNums(num2, num1);
    }

    while (decimal1 >= decimal2){
        num2 += '0';
        decimal2++;
    }

    char carry_out = '0';
    int size1 = num1.length();
    int size2 = num2.length();
    for(int i = 1; i <= max( size1, size2 ); i++){
        char d1 = '0';
        char d2 = '0';
        if ( i < size1){
            d1 = num1[size1-i];
        }
        if (i < size2){
            d2 = num2[size2-i];
        }
        
        string digit = (d1 + d2 + carry_out) % 10;
        carry_out = (d1 + d2 + carry_out)/10;
        result.insert(0, 1, digit);
    }
    if (carry_out != '0'){
        result.insert(0, 1, carry_out);
    }



    return result;
}

int main(){
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    ifstream inputFile(fileName);

    string word1;
    string word2;
    if (inputFile.is_open()) {
        while ( inputFile >> word1 && inputFile >> word2) { 
            cout << word1 << " " << word2 << ": ";
            if (validDouble(word1) && validDouble(word2)){
                cout << "Valid Doubles" << endl; 
                cout << addNums(word1, word2) << endl;
            }
            else{
                cout<< "Not Valid Doubles" << endl;
            }
        }
    }
    else{
        cout << "Unable to open file";
        return 0;
    }
    

}