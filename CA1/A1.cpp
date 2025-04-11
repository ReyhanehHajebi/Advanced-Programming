
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const string FIRST_NAME="-f";
const string LAST_NAME="-l";
const string EMAIL ="-e";
const string PHONE_NUMBER="-p";
const string OK = "Command Ok";
const string FAILED = "Command Failed";

struct Contacts {

    string first_name;
    string last_name;
    string phone;
    string email;
    int id;
} ;

bool check_number(string);
bool check_email(string);
    void printErr()
    {
        cout << FAILED << endl;
    }


vector<string> divide(string input)
{
    string tempWord = "";

	vector<string> dividedWords;
	for (int i = 0; i < (input.size()); i++) {
		if (input[i] != ' ') {
			tempWord += input[i];
		}
		else {
			if (tempWord.size())
				dividedWords.push_back(tempWord);
			tempWord = "";
		}
	}
	if (tempWord.size())
		dividedWords.push_back(tempWord);
	return dividedWords;
}
   

string find_element(vector<string> Wordss,string which_input)
{
    
    for (int i=0;i<Wordss.size()-1;i++){
        if(Wordss[i]== which_input )
        {
            return Wordss[i+1];
        }
        
    }
}


vector<Contacts> adding_person(vector<Contacts> save_contacts , vector<string> temp)

{
    //cout<<"before";
    string save_name = find_element(temp,FIRST_NAME);
    string save_last = find_element(temp,LAST_NAME);
    string save_num = find_element(temp,PHONE_NUMBER);
    string save_email = find_element(temp,EMAIL);
    //cout<<"after";
    int save_id;
    if(save_contacts.size()){
        //cout<<"here2";
        save_id = save_contacts[save_contacts.size()-1].id;
    }
    else{
        //cout << "size0";
        save_id = -1;
    }
    bool flag = true;


    for(int j = 0 ; j < save_contacts.size();j++){

        if( save_num == save_contacts[j].phone ||
            save_email== save_contacts[j].email )
            flag = false;

    }

    if(flag == true && check_number(save_num) && check_email(save_email))
       {
         save_id++;
         Contacts temp_contacts  = {save_name,save_last,save_num,save_email,save_id};
         save_contacts.push_back(temp_contacts);
        //cout<<"saved";
         cout << OK << endl;

       }

    else if( flag==false ||check_number(save_num)== false || check_email(save_email)== false)
        {
            cout << FAILED << endl;

        }
    return save_contacts;
}
   

vector<Contacts> add_contacts(vector<Contacts> save_contacts, vector<string>words)

{ 

   
    save_contacts=adding_person(save_contacts,words);
    //cout <<"here"<< save_contacts.size();
   /* for(int i = 0 ; i < save_contacts.size(); i++)
    {
    cout << save_contacts[i].first_name<< " ";
    cout << save_contacts[i].last_name<< " ";
    cout << save_contacts[i].phone << " ";
    cout << save_contacts[i].email<< " ";
    cout << save_contacts[i].id<<endl;
     
    }*/

    
   
   return  save_contacts;
    
  }


bool check_number(string number)
{
   
   if((number.size() == 11 )  && (number[0] == '0') && (number[1] == '9'))
    return true;
   else 
    return false;
    

}

bool check_email(string email)
{
    int j;
    int c;
    for(int i = 0 ; i < email.length(); i++)
    {
        if(email[i] == '@')
        j = i;
         if(email[i] == '.')
        c = i;

    }
    for (int k = 0;k < j; k++)
    {
        if((email[k] >= 'a' && email[k] <= 'z')|| (email[k] >= 'A' && email[k] <= 'Z') || 
        (email[k] >= '0' && email[k] <= '9'))
        return true;
         if(email != "")
        return false;

    
    }
    for (int i = j ; i < email.length(); i++)
    {
        if((email[i] >= 'a' && email[i] <= 'z')|| (email[i] >= 'A' && email[i] <= 'Z') || 
        (email[i] >= '0' && email[i] <= '9') || (email[i] == '.' ))
        {
        if ((c ==  (j+1)) || (c = email.length()-1))
            return false;
        if((email[i] == '0' && email[i+1] == '0') ||(email[i-1] == '0' && email[i] == '0'))
        {
            return false;

        }
        return true;
        }
    }
}


void search_contacts(vector<Contacts> save_contacts, vector<string> words)

{
 

        for (int i = 0; i < save_contacts.size();i++)
            {
            
                if(strstr(save_contacts[i].first_name.c_str(),words[1].c_str())||
                   strstr(save_contacts[i].last_name.c_str(),words[1].c_str()) ||
                   strstr(save_contacts[i].phone.c_str(),words[1].c_str()) ||
                   strstr(save_contacts[i].email.c_str(),words[1].c_str()) )
                {
                    /*cout << strstr(save_contacts[i].first_name.c_str(),temp.c_str());
                    cout << strstr(save_contacts[i].last_name.c_str(),temp.c_str());
                    cout << strstr(save_contacts[i].phone.c_str(),temp.c_str());
                    cout << strstr(save_contacts[i].email.c_str(),temp.c_str());
                */

                    cout << save_contacts[i].id << "  ";
                    cout << save_contacts[i].first_name<< "  ";
                    cout << save_contacts[i].last_name<< "  ";
                    cout << save_contacts[i].phone<< "  ";
                    cout << save_contacts[i].email << "  ";
                    cout << endl ;

                   
                }

            }
   }



vector<Contacts> delete_contacts(vector<Contacts> save_contacts,vector<string> words)
{

        for(int i = 0; i< save_contacts.size() ; i++) {
            if(save_contacts[i].id==stoi(words[1]))
            {
                save_contacts.erase(save_contacts.begin()+i);
                cout << OK;
                
            }
            else {
                cout << FAILED;
               

            }
                
        }

         return save_contacts;

        
 }



//add -f reyhaneh -l hajebi -p 09374564515 -e reyhanehh2003@gmail.com
//add -f sara -l amini -p 09128765515 -e sara2003@gmail.com

int main()
{
    
    string command;
    vector<Contacts>save_contacts;
    while(getline(cin, command)){
        vector<string>words=divide(command);
    
        if(words[0] == "add"){
            save_contacts=add_contacts(save_contacts, words);
        }
        else if (words[0] == "search") {
            search_contacts(save_contacts, words);
    
        }
        else if (words[0] == "delete")
        {
            save_contacts=delete_contacts(save_contacts, words);
        }

    }

   
    return 0;
}
