#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Declaration of functions

//Calculator terminal
void messageLoop();
//Check and spilt Input
void messageProcess(string rawInput);   
//Calc directory from left to right
void calc(vector<char> sepaSymbol, vector<double> sepaNum);
//Calc follow `*`,`/`,`+`,`-`
void advancedCalc(vector<char> sepaSymbol, vector<double> sepaNum);

void messageLoop() {
    string rawInput;
    cout << "Simple Calc by KiraMint Ver 1.0\nUse \"quit\" or \"exit\" to terminate the program." << endl;
    cout << "Note:\"()\" is not avaliable in this version!\n" << endl;
    while (true)
    {
        cout << ">>> ";
        getline(cin, rawInput);
        if (rawInput != "") {   //Skip empty input
            try {
                messageProcess(rawInput);
            }
            catch (...) {
                cerr << "\033[0;31mUnknown System ERROR\033[0m" << endl;
            }
        }
    }
}

void messageProcess(string rawInput) {
    const char symbols = 6;
    const char symbolSet[symbols] = { '+','-','*','/','#','.'};
    vector<char> sepaSymbol;
    vector<double> sepaNum;
    //If user want to quit
    if (rawInput.find("quit") != rawInput.npos|| rawInput.find("exit") != rawInput.npos) {
        exit(0);
    }
    //Delete backspace
    while (rawInput.find(" ") != rawInput.npos)
    {
        rawInput.erase(rawInput.find(" "), 1);
    }
    //Check input
    for (int letter = 0; letter < rawInput.length(); letter++) {
        char test = rawInput.at(letter);
        if (!(test >= 48 && test <= 57 || \
            test == symbolSet[0] || \
            test == symbolSet[1] || \
            test == symbolSet[2] || \
            test == symbolSet[3] || \
            test == symbolSet[5])) {
            cerr << "\033[0;31mInvade Input!\033[0m" << endl;
            return;
        }        
    }
    for (int letter = 0; letter < rawInput.length(); letter++) {
        char sb1 = rawInput.at(letter);
        if (letter == rawInput.length() - 1) {  //Check symbol at end of the input
            if (sb1 == symbolSet[0] || \
                sb1 == symbolSet[1] || \
                sb1 == symbolSet[2] || \
                sb1 == symbolSet[3] || \
                sb1 == symbolSet[5]) {
                cerr << "\033[0;31mCan't Be End By a Symbol\033[0m" << endl;
                return;
            }
        }
        else
        {   //Chech dual symbol like:'1**3'or'2+-9'
            char sb2 = rawInput.at(letter + 1);
            if (sb1 == symbolSet[0] || \
                sb1 == symbolSet[1] || \
                sb1 == symbolSet[2] || \
                sb1 == symbolSet[3] || \
                sb1 == symbolSet[5]) {
                if (sb2 == symbolSet[0] || \
                    sb2 == symbolSet[1] || \
                    sb2 == symbolSet[2] || \
                    sb2 == symbolSet[3] || \
                    sb2 == symbolSet[5]) {
                    cerr << "\033[0;31mDual Symbol!\033[0m" << endl;
                    return;
                }
            }
        }
    }
    
    //Add "#" after string
    rawInput.append("#");
    //Add "0" before string
    rawInput.insert(0, "0");
    /*
    Search and sort
    It will be like that:
    raw input: 1+2*3/4-5
    sepaSymbol:+ * / - # ("#" mark as end)
    sepaNum:   1 2 3 4 5
    */
    int last = 0;
    string sub;
    for (int content = 0; content < rawInput.length(); content++)
    {
        for (int syb = 0; syb < symbols - 1; syb++) //symbols - 1 is for fractional part
        {
            if (rawInput.at(content) == symbolSet[syb])
            {
                sepaSymbol.push_back(symbolSet[syb]);
                sub = rawInput.substr(last, content - last);
                sepaNum.push_back(stod(sub));
                last = content + 1;
            }
        }
    }
    advancedCalc(sepaSymbol, sepaNum);  //Calculate "*" and "/"
}

//Calculate "+" "-" when it is use by function advancedCalc
void calc(vector<char> sepaSymbol, vector<double> sepaNum) {
    double result = sepaNum[0];
    for (int i = 0; i < sepaSymbol.size(); i++) {
        switch (sepaSymbol[i])
        {
        case '+':
            result = result + sepaNum[i + 1];
            break;
        case '-':
            result -= sepaNum[i + 1];
            break;
        case '#':
            break;
        default:
            throw("Unknown System ERROR");
            break;
        }
    }
    if (isinf(result)) {
        cerr << "\033[0;31mERROR: Your result is out of range or you divide a number by zero\033[0m" << endl;
    }
    else {
        cout << result << endl;
    }
}

void advancedCalc(vector<char> sepaSymbol, vector<double> sepaNum) {    //Calculate "*" and "/"
    vector<char> sepaSymbolSort;
    vector<double> sepaNumSort;
    vector<double>::iterator num = sepaNum.begin();
    double op1, op2;
    for (vector<char>::iterator it = sepaSymbol.begin(); it != sepaSymbol.end(); it++) {
        switch (*it)
        {
        case'*':
            op1 = *num; 
            num++;
            op2 = *num;
            sepaNumSort.push_back(op1*op2);
            it++;
            sepaSymbolSort.push_back(*it);
            break;
        case'/':
            op1 = *num; 
            num++;
            op2 = *num;
            sepaNumSort.push_back(op1 / op2);
            it++;
            sepaSymbolSort.push_back(*it);
            break;
        case'+':
            sepaSymbolSort.push_back(*it);
            sepaNumSort.push_back(*num);
            
            break;
        case'-':
            sepaSymbolSort.push_back(*it);
            sepaNumSort.push_back(*num);
            break;
        case'#':
            sepaSymbolSort.push_back(*it);
            sepaNumSort.push_back(*num);
            break;
        default:
            cerr << "\033[0;31mSystem ERROR\033[0m" << endl;
            break;
        }
        num++;
    }
    sepaSymbol = sepaSymbolSort;
    sepaNum = sepaNumSort;
    /*
    There is a bug that sometime this function cant calculate all of the"*" "/",
    but I am lazy and don't want to fix it. So let do it one more time.（又不是不能用）
    */
    for (int sepa = 0; sepa < sepaSymbolSort.size(); sepa++) {
        if (sepaSymbolSort[sepa] == '*' || sepaSymbolSort[sepa] == '/') {
            advancedCalc(sepaSymbol, sepaNum);
            return;
        }
    }
    calc(sepaSymbol, sepaNum);  //Calculate "+" "-"
    return;
}

int main()
{
    messageLoop();
    return 0;
}
