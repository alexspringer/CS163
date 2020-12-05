//Alex Springer, Program 3, CS163, May 16th, This is the main.cpp file for the
//program. This file calls all of the implementation functions to actually
//preform the tasks they were made to do.
#include "hash_table.h"
using namespace std;



//This is the main function of the program. This is also 
//the client program so it does not have direct access to the
//class
int main()
{
  concept input;
  table hash;
  char temp[50];
  char * key;
  char reponse = 'z';

  //Create the data structure and display all
  hash.read_in(input);
  if(hash.display_all_wrap())
  {
    cout << "I think it worked dude... " << endl;
  }

  //Display all data under a given keyword
  cout << "What subject do you need to study? ";
  cin.get(temp,50,'\n'); cin.ignore(100,'\n');
  key = new char[strlen(temp) + 1];
  strcpy(key,temp);

  if(hash.display_onechapter(key))
  {
    cout << "Success! " << endl;
  }
  delete [] key; key = NULL;

  //Removing data given the keyword. Loop to delete multiple items. Also
  //Display all after deleting.
  while(reponse != 'n')
  {
    cout << "What item would you like to remove? ";
    cin.get(temp,50,'\n'); cin.ignore(100,'\n');
    key = new char[strlen(temp) + 1];
    strcpy(key,temp);
    hash.remove(key);
    cout << "Remove again? (type n to stop) ";
    cin >> reponse;
    cin.ignore(100,'\n');
    delete [] key; key = NULL;

    if(hash.display_all_wrap())
    {
      cout << "I think it worked dude... " << endl;
    }
  }

  //Edit a topic and then retrieve the data given a keyword.
  cout << "What topic would you like to edit? and retrieve?" << endl;
  cin.get(temp,50,'\n'); cin.ignore(100,'\n');
  key = new char[strlen(temp) + 1];
  strcpy(key,temp);
  ask_user(input);
  if(hash.edit(key, input))
    cout << "Success! " << endl;
  destroy(input);
  if(hash.display_all_wrap())
  {
    cout << "I think it worked dude... " << endl;   
  }

  if(hash.retrive(key, input))
  {
    cout << "Success~! " << endl;
  }
  destroy(input);
  delete [] key; key = NULL;

  return 1;
}



//This function takes in a variable of type struct and deallocates all
//dynamic memory given from reading in the data from the read in fucntion
void destroy(concept & input)
{
  if(input.keyword)
  {
    delete [] input.keyword;
    input.keyword = NULL;
  }
  if(input.description)
  {
    delete [] input.description;
    input.description = NULL;
  } 
  if(input.flag)
  {
    delete [] input.flag;
    input.flag = NULL;
  }
  
  input.page_nums = 0;
  input.chapter = 0;
  
  return;
}



//Asks the user what they want to change about the information
//at a certain key
void ask_user(concept & input)
{
  char temp[50];

  cout << "What is the new description? ";
  cin.get(temp,50,'\n'); cin.ignore(100,'\n');
  input.description = new char[strlen(temp) + 1];
  strcpy(input.description,temp);

  cout << "What is the new page number? ";
  cin >> input.page_nums; cin.ignore(100,'\n');

  cout << "What is the new chapter number ";
  cin >> input.chapter; cin.ignore(100,'\n');

  cout << "What is the new flag? (do you need to study more?) ";
  cin.get(temp,50,'\n'); cin.ignore(100,'\n');
  input.flag = new char[strlen(temp) + 1];
  strcpy(input.flag,temp);

  return;
}
