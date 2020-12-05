//Alex Springer, 5/25/16, Program 4, CS163. This program is a revamp of prog
//ram three but this time with a binary search tree as the data structure.
//Program three was a study guide for the final. This is a continuation of
//that program! This is the the client application.
using namespace std;



#include "bst.h"



//Main simply calls the functions of our ADT, it is the client program.
int main()
{
  table tree;
  study info;
  tree.add(info);
  char temp[100];

  if(tree.display_all())
  {
    cout << "Display is successfuly. " << endl;
  }

  cout << "What would you like to retrieve? ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');
  info.keyword = new char[strlen(temp) + 1];
  strcpy(info.keyword,temp);

  tree.retrieve(info);
  if(info.description)
  {
    cout << "Success!, this is what we found. " << endl << endl
    << "Keyword: " << info.keyword << endl
    << "Description: " << info.description << endl
    << "Chapter: " << info.chapter << endl
    << "Page Number: " << info.page_num << endl
    << "Do I need to study this more? " << info.flag << endl
    << endl;
  }
  info.deallocate();

  read_in_edit(info);

  if(tree.edit(info))
  {
    cout << "Your edit is successful! " << endl << endl;
  }

  info.deallocate();

  if(tree.display_all())
  {
    cout << "Display is successfuly. " << endl;
  }
  
  int a = 0;
  int b = 0;
  cout << "What is the first parameter for your search? ";
  cin >> a; cin.ignore(100,'\n');
  cout << "The second? ";
  cin >> b; cin.ignore(100, '\n');

  if(tree.display_range(a,b))
  {
    cout << "Your search was successful! " << endl << endl;
  }

  char response = 'z';
  while(response != 'n')
  {
  cout << "What would you like to delete? ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');
  info.keyword = new char[strlen(temp) + 1];
  strcpy(info.keyword,temp);

  if(tree.remove(info))
  {
    cout << "Delete is a success. " << endl << endl;
  }
  
  if(tree.display_all())
  {
    cout << "Display is successfuly. " << endl;
  }
  cout << "Delete again? (y/n) ";
  cin >> response; cin.ignore(100,'\n');
  }
  return 1;
}



//Reading in the new information for edit.
void read_in_edit(study & info)
{
  char temp[100];
  cout << "What topic would you like to edit? ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');
  info.keyword = new char[strlen(temp) + 1];
  strcpy(info.keyword,temp); 
  
  cout << "What is the new description? ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');
  info.description = new char[strlen(temp) + 1];
  strcpy(info.description,temp);

  return;
}
