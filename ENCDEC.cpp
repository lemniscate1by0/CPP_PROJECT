/*

    Encryptio
    A test case:
   
    Enter string to encrypt: abcdefghijklmnopqrstuvwxyz 1234567890/-*+.,./<>?;':"[]\{}|`=_)(&^%$#@!~
    Decrypted String:        abcdefghijklmnopqrstuvwxyz 1234567890/-*+.,./<>?;':"[]\{}|`=?)(&^%$#@!~
    linecode==]\[ZYXWVUTSRQPONMLKJIHGFED`qrstuvwxypomjknlno|~?{gzb;=<CAB^}?ihf>edc a@
    4 6 7 9 10 11 12 14 15 16 17 18 19 20 22 23 24 25 26 27 28 29 30 31 32 33 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
    realcode==p9q5]h\[2ZYXWmVUTSRQP1ONMLKJIHGFEDa`qrstuvwxypomjknlno|3~?{gzb;=<CAB^}?ihf>edc a@
    Encrypted Code: ]\ZYWVUTRPOMLKJIGED`qstuwypojknln|~?{z;=<CA^}?h>edc @
    Password: p9q5h[2XmSQ1NHFarvxmo3gbBifa


*/



#include<bits/stdc++.h>

using namespace std;

// Function to check if a number is prime
bool isPrime(int num) {
    if (num < 2) return false;
    if(num==2||num==3||num==5)
    return true;
    for (int i = 2; i<= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Function to generate Fibonacci numbers up to a limit
vector<int> generateFibonacci(int limit) {
    vector<int> fib;
    int a = 0, b = 1;
    fib.push_back(0);
    fib.push_back(1);
    while (b < limit) {
        int next = a + b;
        //cout<< next<<" ";
        fib.push_back(next);
        a = b;
        b = next;
    }
    
    return fib;
}

// Function to adjust a character based on the custom rules
char adjustChar(char c) {
    int val = int(c);
    if(val>=32&&val<=63)
    {

        if(val!=63)
        val+=64;
    }
    else if(val>=64&&val<=95)
    {
        val-=32;
    }
    else if(val>=96&&val<=126)  
    {
        val=(126 - (val - 96))-32;
    }
    else{
        cout<<endl<<val;
        printf("\nA invalid charecter is in the code so execution is stoped and please try again.\n");
        exit(1);
    }
    return char(val);
}

// Function to adjust a character back based on the encryption rules
char reverseAdjustChar(char c) {
    int val = int(c);
    
    if (val >= 32 && val <= 63) {
        if(val!=63)
        val += 32;  // Reverse the operation for values in the range 64 to 95
    }
    else if (val >= 64 && val <= 95) {
        val+=32;
        val = (126 - (val - 96));  // Reverse the mapping for ASCII values between 96 and 126
    }
    else if (val >= 96 && val <= 127) {
        val -= 64;  // Reverse the operation for values in the range 32 to 63
    }
    else {
        cout<<endl<<c<<" "<<val;
        printf("\nA invalid charecter is in the code so execution is stoped and please try again.\n");
        exit(1);
    }
    return char(val);
}


// Function to encrypt the input
vector<string> encrypt(string line) {
    int len = line.size();
    int size = len + 10;

    // Create an array of size line + 10 and initialize with '0'
    vector<char> code(size, '0');
    vector<int> fibSeries = generateFibonacci(size);

    // Populate Fibonacci indices with random letters
    int x=1;
    for (int i = 0; i < code.size(); ++i) 
    {
        for(int j=0;j<fibSeries.size();++j)
        {
            if(fibSeries[j]==i)
            {   
                
                if(x)
                code[i] = 'a'+ rand() % 26;
                else
                code[i] = '1'+ rand() % 9;
                //cout<<i<<" "<<code[i]<<endl;
                x=(x+1)%2;
                break;
            }
        }
    }

    // Modify characters in the input string
    for (int i = 0; i < len; i++) {
        line[i] = adjustChar(line[i]);
    }

/*  cout<<"linecode==";
    for(int j=0;j<line.size();++j)
    cout << line[j];
    cout<<endl;
    
    cout<<"(before)realcode==";
    for(int j=0;j<code.size();++j)
    cout << code[j];
    cout<<endl;
*/
    
    // Insert modified characters into the array in non-Fibonacci positions
    int inputIndex = 0;
    for (int i = 0; i < code.size() && inputIndex < line.size(); i++) {
        if (code[i] == '0') {
            //cout<<i<<" ";
            code[i] = line[inputIndex];
            inputIndex++;
        }
    }
    cout<<endl;

    //replace 0 with %
    for(int i=0;i<code.size();++i)
    {
        if(code[i]=='0')
        code[i]='%';
    }
/*
    cout<<"realcode==";
    for(int j=0;j<code.size();++j)
    cout << code[j];
    cout<<endl;
*/  
    // Generate password and encrypted code
   string password, encryptedCode;
    for (int i = 0; i < size; i++) {
        if (find(fibSeries.begin(), fibSeries.end(), i) != fibSeries.end() || isPrime(i)) {
            password += code[i];
        } else {
            encryptedCode += code[i];
        }
    }
    
    // Display encrypted code and password

    cout << "Encrypted Code: " << encryptedCode << endl << endl;
    cout << "Password: " << password << endl;

    return {encryptedCode,password};
}

// Function to decrypt the encrypted code
string decrypt(string encryptedCode, string password) {
    int len = encryptedCode.size() + password.size();
    vector<char> code(len, '0');
    vector<int> fibSeries = generateFibonacci(len);

    // Reconstruct the array from the encrypted code and password
    int encIndex = 0, passIndex = 0;
    for (int i = 0; i < len; i++) {
        if (find(fibSeries.begin(), fibSeries.end(), i) != fibSeries.end() || isPrime(i)) {
            if (passIndex < password.size()) {
                code[i] = password[passIndex++];
            }
        } 
        else {
            if (encIndex < encryptedCode.size()) {
                code[i] = encryptedCode[encIndex++];
            }
        }
    }
    
    // Replace '%' with '0' in the code array
    for (int i = 0; i < code.size(); i++) {
        if (code[i] == '%') code[i] = '0';
    }
/*
    cout<<"realcode==";
    for(int j=0;j<code.size();++j)
    cout << code[j];
    cout<<endl;
*/
    
    for(int i=0;i<code.size();++i)
    {
        for(int j=0;j<fibSeries.size();++j)
        {
            if(i==fibSeries[j])
            {
                //cout<<i<<" ";
                code[i]='0';
                break;
            }
        }
    }
    //cout<<endl;
    string line;
    for(int i=0;i<code.size();++i)
    {
        if(code[i]!='0')
        line+=code[i];
    }

/*
    cout<<endl<<"linecode==";
    cout << line;
    cout<<endl;
*/


    // Reverse the adjustments made during encryption
    string decryptedString;
    for (int i = 0; i < line.size(); i++) {
        decryptedString += reverseAdjustChar(line[i]);
    }

    return decryptedString;

}

// Main function with menu
int main() {
    string line, encryptedCode, password;

    string ch;
    int choice;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        getline(cin,ch);
        choice=stoi(ch);
        //cin.ignore();  // To consume the newline character after input      
        switch (choice) {
            case 1: {
                cout <<endl <<"Enter string to encrypt: ";
                getline(cin, line);

                // Encrypt the string and generate password
                encrypt(line);
                break;
            }
            case 2: 
            {
                cout <<endl<< "Enter encrypted code: ";
                getline(cin, encryptedCode);
                cout <<endl<< "Enter password: ";
                getline(cin, password);
                // Decrypt the string
                string decryptedString1=decrypt(encryptedCode, password);
                vector<string> st=encrypt(decryptedString1);
                string decryptedString2=decrypt(st[0], st[1]);
                if(decryptedString1==decryptedString2)
                {
                    cout<<endl<<"Validation complete."<<endl;
                    cout << endl<< "Decrypted String: " << decryptedString1 << endl;
                }
                else{
                    cout<<endl<<"Not a valid code, password pair."<<endl;
                }

                break;
            }
            case 3:
                cout << endl<<"Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, try again." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
