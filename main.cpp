#include <iostream>
// including file stream to get info to and from the disk and the program
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>

using namespace std;
// using the standard library for naming

class loginZeus{
    // public keyword, meaning anyone can access
    public:
        loginZeus(){
            authenticate = false;
        };

// main menu function that will only render if logged in
    void menu()
        {
            system("clear"); //clearing the screen
            cout << "\n\n\n\t\t\t Welcome back:" << username ;
            cout << "\n\n\n\t\t What would you like to do?";
            cout << "\n\n\n\t\t 1. Create a god";
            cout << "\n\n\n\t\t 2. Edit a god";
            cout << "\n\n\n\t\t 3. Delete a god";
            cout << "\n\n\n\t\t 4. See all gods";

            int selection;
            cin >> selection;
            // switch expressions have cases to choice from 
            switch (selection)
            {
                case 1:
                    cout << "\n\n\n\t\t\t create a god" << endl;
                    addGod();
                    break;
                case 2:
                    cout << "edit a god";
                    break;
                case 3:
                    cout << "delete a god";
                    deleteGod();
                    break;
                case 4: 
                    cout << "see all gods";
                    break;
                default:
                    cout << "ivalid choice, for the gods sake try again";
                    menu();
            }
        }

    void addGod()
    {
    // clearing the system
        system("clear");
        fstream file;
        if (file)
        {
            cout << "\n\n\n\t\t\t Welcome, please input new god information. \n" << endl;

            cout << "\t\t please enter the god Id [max 6 digets]: \n" << endl;
            cin >> godId;
            cout << "\t\t please enter the god's name: \n" << endl;
            cin >> godName;
            cout << "\t\t What is their roman name? \n";
            cin >> romanName;

            // inserting the godName into a file, but putting a new line for each new god that is created
            file.open("gods.csv", ios::out | ios::app);
            file << godId << ", " << godName << ", " << romanName << "\n";
            file.close();
        }
        else{
            cout << "unable to acces creation file, try again";
            addGod();
        }
        menu();
    }

    void deleteGod()
    {
        system("clear");
        char matchId[5];
        string line;
        fstream file, newFile;
        int found = 0;
        cout << "\t\t\t Delete a God \t\t\t\n";
        // opening the gods file, ios::in reads, ios:out operation
        file.open("gods.csv", ios::in);
        if(!file)
        {
            cout << "\n\t\t\t The gods are at it again...the file is lost";
            file.close();
        }
        else
        {
            cout << "Please enter the god ID of the god you are sending to Tartarus:";
            cin >> matchId;
            newFile.open("newGods.csv", ios::app | ios::out);
            file >> godId >> godName >> romanName;
            while (!file.eof())
            {
                if(strcmp(matchId, godId) != 0)
                {
                    newFile << " " << godId << ", " << godName << ", " << romanName << "\n";
                }
                else
                {
                    found ++;
                    printf("deleted else statement");
                    cout << "\t\t God was banished";
                }
                file >> godId >> godName >> romanName;
            }
            newFile.close();
            file.close();
            remove("gods.csv");
            rename("newGods.csv", "gods.csv");
            menu();
        }
    }

    void login(){
        // cout is a response in console
        cout << "please enter your almighty name \nUsername:";
        // cin is input from user
        cin >> usernameMatch;

        // retreaving the username from a file
        username = getFile("users.txt");

        if(usernameMatch == username){
            cout << "please enter the almighty password:";
            cin >> passwordMatch;

            password = getFile("password.txt");

            if(passwordMatch == password) {
                cout << "correct password";
                menu();
            }
            else {
                cout << "wrong password";
                login();
            }
        }
        else {
            cout << "wrong username";
            login();
        }
    }

    // define a function to retrieve the password and usernames from a stored file
    string getFile(const char* p_file)
        {
            string line;
            fstream file;

            file.open(p_file, ios::in);
            if(file.is_open())
                {
                    getline(file, line);
                }
            file.close();

            return line;
        }

    // only Zeus can access the following
     private:
        string password;
        string username;
        string usernameMatch;
        string passwordMatch;
        bool authenticate;
        char godId[5];
        char godName[20];
        char romanName[20];
        
};

int main(){
    loginZeus loginZuesObject;
    loginZuesObject.login();

    cin.get();
}