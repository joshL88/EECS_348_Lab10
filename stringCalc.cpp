#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

bool validDouble(string num){
    bool hasDecimal = false;
    for(int i = 0; i < num.length(); i++){
        char c = num[i];
        if (!isdigit(c)){
            if (c == '.' && !hasDecimal){

                if (i == (num.length() - 1) || i == 0 || !isdigit(num[i-1])){
                    return false;
                }
                hasDecimal = true; 
                
            }
            else if (c == '+' || c == '-'){
                if(i != 0 || num.length() == 1){
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

string stringSign(string num){
    if (num[0] == '-'){
        return "-";
    }
    else{
        return "+";
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

    string sign1 = stringSign(num1);
    string sign2 = stringSign(num2);

    num1 = signLess(num1);
    num2 = signLess(num2);

    int decimal1 = num1.find('.');
    int decimal2 = num2.find('.');
    if (decimal1 == -1){
        num1 += '.';
        decimal1 = num1.length() - 1;
    }

    if (decimal2 == -1){
        num2 += '.';
        decimal2 = num2.length() - 1;
    }

    if (decimal1 != decimal2){
        while (decimal1 > decimal2){
            num2.insert(0, 1, '0');
            decimal2++;
        }
        while (decimal2 > decimal1){
            num1.insert(0, 1, '0');
            decimal1++;
        } 
    }

    while (num1.length() > num2.length()){
        num2 += '0';
    }

    while (num2.length() > num1.length()){
        num1 += '0';
    }
    
    if (num1 == num2){
        return "0";
    }
    else if(num2 > num1){
        return addNums(sign2 + num2, sign1 + num1);
    } 


    char carry_out = '0';
    char d1;
    char d2;
    int n = num1.length();
    if (sign1 != sign2){
       for(int i = 1; i <= n; i++){
            d1 = num1[n-i];
            d2 = num2[n-i];
            if(d1 == '.' && d2 == '.'){
                if(i > 1){
                    result.insert(0, 1, '.');
                }
            }
            else{
                char sum = (d1 - d2 - carry_out + '0');
                carry_out = '0';
                while (sum < 0){
                    sum+=10;
                    carry_out += 1;
                }
                char digit = (sum) % 10 + '0';
                result.insert(0, 1, digit);
            }
        } 
    }else{
        for(int i = 1; i <= n; i++){
            d1 = num1[n-i];
            d2 = num2[n-i];
            if(d1 == '.' && d2 == '.'){
                if(i > 1){
                    result.insert(0, 1, '.');
                }
            }
            else{
                char sum = (d1 + d2 + carry_out - 3*'0');
                char digit = (sum) % 10 + '0';
                carry_out = (sum)/10 + '0';
                result.insert(0, 1, digit);
            }
        }
    }
    if (carry_out != '0'){
        result.insert(0, 1, carry_out);
    }


    return sign1 + result;
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
                cout << addNums(word1, word2) << endl << endl;
            }
            else{
                cout<< "Not Valid Doubles" << endl << endl;
            }
        }
    }
    else{
        cout << "Unable to open file";
        return 0;
    }
    

}