#include <string>
#include <iostream>

using namespace std;

bool validatePassword(string&);
void toUpperCase(string&);
string myEncryption (string, string);
string myDecryption (string, string);


int main(){
    cout << "Starting up your cipher!" << endl << endl;

    int numChosen = -1;
    string message = "";
    string passCode = "";

    do{
        cout    << "Please select an option:" << endl << "\t1. Encrypt Message" << endl << "\t2. Decrypt Message"
                << endl << "\t3. Quit"<< endl << "Enter: ";

        cin >> numChosen;

        getline(cin, message);

        switch(numChosen){
            case 1:
                cout << endl << "Enter your passcode: ";
                getline(cin, passCode);

                while(!validatePassword(passCode)){
                    cout << endl << "Password entered is invalid" << endl << endl << "Enter your passcode: ";
                    getline(cin, passCode);
                }

                cout << "Enter the message to be encrypted: ";
                getline(cin, message);

                toUpperCase(message);

                cout << endl << "Encrypting your message..." << endl << endl;
                cout << "Passcode: " << passCode << endl << "Plaintext message: " << message;
                cout << endl << "Ciphertext Message: " << myEncryption(passCode, message) << endl << endl;
                break;
            case 2:
                cout << endl << "Enter the message to be decrypted: ";
                getline(cin, message);

                toUpperCase(message);

                cout << "Enter your passcode: ";
                getline(cin, passCode);

                cout << endl << "Decrypting your message..." << endl << endl;
                cout << "Passcode: " << passCode << endl << "Ciphertext message: " << message;
                cout << endl << "Plaintext Message: " << myDecryption(passCode, message) << endl << endl;
                break;
            case 3:
                cout << endl << "Goodbye!";
                break;
            default:
                cout << endl << "Incorrect input, please select an option from the menu." << endl << endl;
        }



    }while(numChosen != 3);

    return 0;
}

bool validatePassword(string &str){
    if(str.length() < 1)
        return false;

    for(int k = 0; k < str.length(); k++){
        char temp = str.at(k);

        if(isspace(temp)){
            str.erase(k, 1);
            k--;
        } else{
            if(isalpha(temp)){
                if(islower(temp)){
                    str.at(k) = toupper(temp);
                }
            } else {
                return false;
            }
        }
    }

    return true;
}

void toUpperCase(string &str){
    for(int k = 0; k < str.length(); k++){
        str.at(k) = toupper(str.at(k));
    }
}

string myEncryption (string passCode, string message) { //passing in arguements
    //initialize temporary variables
    string output = "";
    int index = 0;

    //loop over the plain text message
    for(index = 0; index < message.length(); index += passCode.length()){
        //loop over the pass phrase
        for(int k = 0; k < passCode.length(); k++){
            //stops the program if the whole plaintext message has been encrypted
            if((index + k) >= message.length()){
                break;
            }

            //checks if the character is not an alphabet character
            if(!isalpha(message.at(index + k))){
                //adds the character to the output
                output += message.at(index + k);

                //increases the plaintext index and decrements the passcode index to skip the space or punctuation
                index++;
                k--;

                //skips to the next iteration of the loop
                continue;
            }

            //gets the character's index in the alphabet
            int charNum = (int)(message.at(index + k)) - 65;

            //gets the transfer number based on the character in the passcode
            int transferNum = (int)(passCode.at(k)) - 65;

            //change the original character by the given amount and convert to an ascii character
            output += (char)(((charNum + transferNum) % 26) + 65);
        }
    }

    return output;
}

string myDecryption (string passCode, string message) { //passing in arguements
    string output = "";

    int index = 0;

    //loop over the plain text message
    for(index = 0; index < message.length(); index += passCode.length()){
        //loop over the pass phrase
        for(int k = 0; k < passCode.length(); k++){
            //stops the program if the whole plaintext message has been encrypted
            if((index + k) >= message.length()){
                break;
            }

            //checks if the character is not an alphabet character
            if(!isalpha(message.at(index + k))){
                //adds the character to the output
                output += message.at(index + k);

                //increases the plaintext index and decrements the passcode index to skip the space or punctuation
                index++;
                k--;

                //skips to the next iteration of the loop
                continue;
            }

            //gets the character's index in the alphabet
            int charNum = (int)(message.at(index + k)) - 65;

            //gets the transfer number based on the character in the passcode
            int transferNum = (int)(passCode.at(k)) - 65;

            //change the original character by the given amount and convert to an ascii character
            output += (char)((((charNum - transferNum) + 26) % 26) + 65);
        }
    }

    return output;
}
//