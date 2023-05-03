#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*Signup Class is used to write The login credentials to the "credentials.txt" file, it also checks that every user should have a unique
username*/
class SignUp{
    public :
        string username,password,TempUsername;
        void signup(){
            string line = " ";
            string TempUsername,TempPassword;
            ifstream readFile("credentials.txt");
            bool found = false;
            cout << "Enter Username : ";
            cin >> username;
            cout << "\nEnter Password : ";
            cin >> password;
            while(getline(readFile,line)){
                stringstream iss(line);
                iss >> TempUsername;
                if(username==TempUsername){
                    cout << "Username already exists ! , Please try a unique username.\n";
                    found = true;
                    break;
                }
            }
            if(!found){
                ofstream myfile("credentials.txt",ios_base::out | ios_base::app);
                myfile << username << " " << password << " " << 0 << endl;
                cout << "Thanks for signing up, Go to homepage and select Log in to use your account !\n";
                myfile.close();
            }
        }
};

/*Login Class is used to check if the Credentials entered by the user exists in the "credentials.txt" file or not it also returns a boolean
variable to the main menu to check if login process was successful or not.*/

class LogIn{
        public:
            string username,password,TempUserName,TempPassword;
            bool is_login_successfull = false;   
        bool login(){
            string line = " ";
            ifstream readFile("credentials.txt");
            cout << "Enter Username : ";
            cin >> username;
            cout << "\nEnter Password : ";
            cin >> password;
            bool found = false;
            while(getline(readFile,line)){
                stringstream iss(line);
                iss >> TempUserName >> TempPassword;
                
                if(username == TempUserName && password == TempPassword){
                    cout << "Login Successfull!\n";
                    found = true;
                    is_login_successfull = true;
                    break;
                }
            }
            if(!found){
                cout << "Invalid Username or Password !\n ( Make sure you have registered !)\n";
            }
            return is_login_successfull;
        }
};

/*Wallet class consists of only 2 functions wallet  and Walletupdate.*/

class Wallet{
    public:
        bool possible = false;
        string username,password,TempUserName,TempPassword;
        int walletamount,tempprice;
        bool payment_possible = false;

        void Walletupdate(string username, string password, int price2,int choice3){
            string line = " ";
            ifstream filein("credentials.txt");
            ofstream myfile("temp.txt",ios_base::out | ios_base::app);
            cout << choice3 << endl;
            while(getline(filein,line)){
                stringstream iss(line);
                iss >> TempUserName >> TempPassword >> tempprice;  
                if(username==TempUserName && password == TempPassword){
                    if(choice3==1)
                        myfile << username << " " <<  password << " " <<  (tempprice - price2) << endl;
                    else if(choice3==2)
                        myfile << username << " " <<  password << " " <<  (tempprice + price2) << endl;
                }
                else{
                    myfile << TempUserName << " " <<  TempPassword << " " <<  (tempprice) << endl;
                }
            }
            remove("credentials.txt");
            rename("temp.txt","credentials.txt");
        }

        bool wallet(int price,int choice2){
            string line = " ";
            ifstream readFile("credentials.txt");
            cout << "Enter Username : ";
            cin >> username;
            cout << "\nEnter Password : ";
            cin >> password;
            bool found = false;
            while(getline(readFile,line)){
                stringstream iss(line);
                iss >> TempUserName >> TempPassword >> walletamount;
                    if(username == TempUserName && password == TempPassword && walletamount>=price){
                        if(choice2==1){
                            Walletupdate(username,password,price,choice2);
                            cout << "Payment Successfull and the amount has been debited from your E-wallet.\n";
                            payment_possible = true;
                            _Exit(0);
                            break;
                        }
                    }
                    if(username == TempUserName && password == TempPassword){
                        if(choice2==2){
                            Walletupdate(username,password,price,choice2);
                            cout << "Amount has been credited to your E-wallet.\n";
                            payment_possible = true;
                            _Exit(0);
                            break;                           
                        }
                    }                    
            }
            if(!payment_possible){
                cout << "Not Enough money in E-Wallet\n";
                _Exit(0);
            }
        }
};

/*User class just contains the display function to show the content of "items_to_sell.txt" file where as transaction is used
to take the user input and to send the choice and user type to wallet function.*/


class User: public SignUp, public LogIn, public Wallet{
    public:
        int choice,method,price,tu,finalprice,amt;
        string tp;
        string un,pw,tun,tpw;
        void display(){
            string x;
            ifstream inFile;
            inFile.open("items_to_sell.txt");
            cout << endl;
            while(getline(inFile,x)){
                cout << x << endl;
            }
        }

        void transaction(int choice2){
            if(choice2==1)
                cout << "Enter the Item number to buy ";
            if(choice2==2)
                cout << "Enter the Item number to sell ";
            cin >> choice;
            
            if(choice>4){
                cout << "Choose a valid choice\n";
                transaction(choice2);
            }
            else{
                string line = " ";
                ifstream readFile("items_to_sell.txt");
                while(getline(readFile,line)){
                    stringstream iss(line);
                    iss >> tu >> tp >> price;
                    if(tu==choice){
                        finalprice=price;
                        break;
                    }
                }
            }
            cout << "Method of Payment -- >\n [1]. Cash On Delivery\n [2]. Use Website Wallet\n";
            cin >> method;
            bool status = false;
            switch(method){
                case 1:
                    if(choice2==1)
                        cout << "Payment completed Successfully !\n ";
                    if(choice2==2)
                        cout << "Amount will be given at pickup on your saved address !\n";
                    status = true;
                    break;
                case 2:
                    status = wallet(finalprice,choice2);
                    break;
            }
            if(status) {
                cout << "Thanks for Visiting !\n";
                _Exit(0);
            }
        }

        void showamount(){
            cout << "Enter Username : ";
            cin >> un;
            cout << "\nEnter Password : ";
            cin >> pw;
            ifstream readFile("credentials.txt");
            string line = " ";
            while(getline(readFile,line)){
                stringstream iss(line);
                iss >> tun >> tpw >> amt;
                if(tun==un && tpw==pw){
                    cout << "Your Current E-Wallet Balance is " << amt << endl;
                    _Exit(0);
                }
            }
        };
};

void MainMenu(){
    int choice;
    User temp;
    cout << "\t\t\t--- Welcome To Amazon Lite ---\n";
    cout << "[1] Sign Up\n[2] Log In\n[3] Exit\n";
    bool flag = false,login_status = false;
    while(!flag){
        cin >> choice;
        switch(choice){
            case(1):
                temp.signup();
                flag=true;
                break;
            case(2):
                login_status = temp.login();
                flag=true;
                break;
            case(3):
                _Exit(3);
            default:
                cout << "Enter a Valid choice !\n";
                break;
        }
    }
    if(flag && login_status){
        int usertype;
        cout << "\n [1] Buyer\n [2] Seller\n [3] Check Wallet Amount\n";
        bool flag2=false;
        while(!flag2){
            cin >> usertype;
            switch(usertype){
                case(1):
                    temp.display();
                    temp.transaction(usertype);
                    flag2=true;
                    break;
                case(2):
                    temp.display();
                    temp.transaction(usertype);
                    flag2 = true;
                    break;
                case(3):   
                    temp.showamount();
                    flag2 = true;
                    break;
                default:
                    cout << "Enter a Valid Choice !\n";
                    break;
            }
        }
    }
}

int main(){
    MainMenu();
}