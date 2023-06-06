#include <iostream>
#include <string>
#include <vector>
using namespace std;

void messageLoop();
void messageProcess(string rawInput);
void calc(vector<char> sepaSymbol, vector<double> sepaNum);

void messageLoop() {
    string rawInput;
    cout << "Simple Calc by KiraMint Ver 1.0\tUse \"quit\" or \"exit\" to terminate the program." << endl;
    cout << "Input your expression, the calculator will calculate from left to right.\n \
Note:\"()\" is not support in this version!" << endl;
    while (true)
    {
        cout << ">>> ";
        getline(cin, rawInput);
        if (rawInput != "") {
            messageProcess(rawInput);
        }
    }
}
void messageProcess(string rawInput) {
    const char symbols = 5;
    const char symbolSet[symbols] = { '+','-','*','/','#' };
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
    //check input

    for (int letter = 0; letter < rawInput.length(); letter++) {
        char test = rawInput.at(letter);
        if (!(test >= 48 && test <= 57 || \
            test == symbolSet[0] || \
            test == symbolSet[1] || \
            test == symbolSet[2] || \
            test == symbolSet[3])) {
            cerr << "Invade Input!" << endl;
            return;
        }
    }

    for (int syb = 0; syb < symbols; syb++) {
        if (rawInput.at(rawInput.length() - 1) == symbolSet[syb]) {
            cerr << "Invade Input!" << endl;
            return;
        }
    }
    //Add "#" after string
    rawInput.append("#");
    //Add "0" before string
    rawInput.insert(0, "0");
    //Search and sort
    int last = 0;
    string sub;
    for (int content = 0; content < rawInput.length(); content++)
    {
        for (int syb = 0; syb < symbols; syb++)
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

    calc(sepaSymbol, sepaNum);
}
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
        case '*':
            result *= sepaNum[i + 1];
            break;
        case '/':
            result /= sepaNum[i + 1];
            break;
        case '#':
            break;
        default:
            cerr << "Syntax ERROR" << endl;
            break;
        }
    }
    cout << result << endl;
}

int main()
{
    messageLoop();
    return 0;
}
