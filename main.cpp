#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <ctype.h>

using namespace std;
void RegisteredUsers();
string extractIntegerWords(string);

ofstream OutputFile;

vector<string> nameVec;
vector<string> typeVec;
vector<string> emailVec;

map<string,string> NameDate;
map<string,string> EmailDate;
map<string,string> NumberDate;
vector<string> NameNumber;

int main() {
    OutputFile.open("Output.csv");

    ifstream inFile("PayPal_List.csv");//change location based on location of file
    std::string name,type,email,date,number;
    getline(inFile,name);

    OutputFile<<"Name,Type,Email,Date,Number\n";

    if (inFile.is_open()) {
        while(getline(inFile, name)){
            std::stringstream ss(name);

            getline(ss , name , ',');
            getline(ss , name , ',');
            getline(ss , name , ',');
            getline(ss , name , ','); //store name

            getline(ss , type , ','); //store type


            getline(ss , email , ',');
            getline(ss , email , ',');
            getline(ss , email , ',');
            getline(ss , email , ',');
            getline(ss , email , ',');
            getline(ss , email , ','); //store email

            if(type!="\"General Withdrawal\""&&type!="\"Donation Payment\""){

                name.erase(name.begin());name.erase(name.size()-1);
                transform(name.begin(), name.end(), name.begin(), ::tolower);
                nameVec.push_back(name);
                OutputFile<<name<<",";

                typeVec.push_back(type);
                OutputFile<<type<<",";

                email.erase(email.begin());email.erase(email.size()-1);
                std::transform(email.begin(), email.end(), email.begin(), ::tolower);
                emailVec.push_back(email);
                OutputFile<<email<<",";

                getline(ss , date , ',');
                getline(ss , date , ',');
                getline(ss , date , ',');
                getline(ss , date , '"');
                getline(ss , date , ',');
                getline(ss,date,',');
                getline(ss,date,',');
                stringstream pp(date);
                getline(pp,date,'-');
                getline(pp,date,'"');
                NameDate.insert(pair<string,string>(name,date));
                EmailDate.insert(pair<string,string>(email,date));
                OutputFile<<date<<",";

                getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');
                getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');
                getline(ss,number,'}');getline(ss,number,',');
//                cout<<"Number : "<<number<<endl;
                getline(ss,number,',');getline(ss,number,',');getline(ss,number,'"');getline(ss,number,'"');getline(ss,number,',');
                getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');getline(ss,number,',');
                getline(ss,number,',');getline(ss,number,',');
//                getline(ss,number,',');
                NameNumber.push_back(number);
                NumberDate.insert(pair<string,string>(number,date));
                OutputFile<<number<<"\n";

            }
        }
    }
    OutputFile.close();
    inFile.close();
    RegisteredUsers();
    return 0;
}
string extractIntegerWords(string str) {
    string found="";
    for(int x=0;x<str.size();x+=1){
        if(isdigit(str[x])){
            found+=str[x];
        }
    }
    return found;
}

void RegisteredUsers() {
    //C:\Users\shazmaan\Desktop\BlossomWork\Takeout\Mail
    OutputFile.open("copy-mbox-output.csv");
    ifstream inFile("mbox-output.csv");
    string RowData, Parent, Email, Number, SecContact, SecNumber;
    getline(inFile, RowData);
    OutputFile << RowData + ",Payed,Date\n";

    if (inFile.is_open()) {
        while (getline(inFile, RowData)) {
            std::stringstream ss(RowData);
            std::stringstream ss2(RowData);

            getline(ss2, Parent, ',');
            getline(ss, RowData);

            char c=ss2.peek();
            if(c=='"'){
                getline(ss2,Email,'"');
                getline(ss2,Email,'"');
                getline(ss2,Email,',');
                ss2.get();
            }else{
                getline(ss2,Email,',');
            }
//            getline(ss2, Email, ',');
            getline(ss2, Email, ',');
            getline(ss2, Email, ',');
            getline(ss2, Email, ',');
            getline(ss2, Email, ',');
//            cout<<"Email : "<<Email<<endl;

            getline(ss2, Number, ',');
            Number=extractIntegerWords(Number);

            getline(ss2, SecContact,',');
            getline(ss2, SecNumber,',');
            SecNumber = extractIntegerWords(SecNumber);
//            extractIntegerWords(Number);
//            cout<<"Number : "<<extractIntegerWords(SecNumber)<<endl;

            std::transform(Parent.begin(), Parent.end(), Parent.begin(), ::tolower);
            std::transform(Email.begin(), Email.end(), Email.begin(), ::tolower);
            std::transform(SecContact.begin(), SecContact.end(), SecContact.begin(), ::tolower);

            bool Pcheck= (find(nameVec.begin(), nameVec.end(), Parent) != nameVec.end());
            bool Echeck= (find(emailVec.begin(), emailVec.end(), Email) != emailVec.end());
            bool Ncheck= (find(NameNumber.begin(),NameNumber.end(),"\""+Number+"\"")!=NameNumber.end());
            bool Scheck= (find(NameNumber.begin(),NameNumber.end(),"\""+SecNumber+"\"")!=NameNumber.end());
            bool Ccheck= (find(nameVec.begin(), nameVec.end(), SecContact) != nameVec.end());

//            cout<<"Parent : "<<Parent<<" Secondary Number : "<<SecNumber<<" Scheck : "<<Scheck<<endl;
//            cout<<"-----------------------------"<<endl;

            if (Pcheck || Echeck || Ncheck || Scheck || Ccheck) {
                OutputFile << RowData + ",Yes,";
                if(Pcheck){
//                    cout<<"Pcheck "<<endl;
                    OutputFile<<NameDate[Parent]+"\n";
                }else if(Echeck){
//                    cout<<"Echeck "<<endl;
                    OutputFile<<EmailDate[Email]+"\n";
                }else if(Ncheck){
//                    cout<<"Ncheck "<<endl;
                    OutputFile<<NumberDate["\""+Number+"\""]+"\n";
                }else if(Scheck){
//                    cout<<"Scheck "<<endl;
                    OutputFile<<NumberDate["\""+SecNumber+"\""]+"\n";
                }else{
//                    cout<<"else "<<endl;
                    OutputFile<<NameDate[SecContact]+"\n";
                }
            } else {
                OutputFile << RowData + ",No,\n";
            }
        }
        OutputFile.close();
        inFile.close();
    }
}