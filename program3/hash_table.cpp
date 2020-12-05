//Alex Springer, Program 3, CS163, May 16th. This is the .cpp file or the 
//implementation file for the class table.
#include "hash_table.h"
using namespace std;



//This constructor sets each of the node pointers in the array to NULL when 
//we create the hash table.
table::table(int size)
{
  hash_table = new node*[size];
  hash_table_size = size;
  for (int i = 0; i < size; ++i)
  {
    hash_table[i] = NULL;
  }
}

//reads in information about a topic of study. Takes the struct
//of a topic to study and reads in the information. Some of the
//data will be dynamic so it will need to be deleted later.
int table::read_in(concept & input)
{
  ifstream infile;
  infile.open("hash.txt");
  char temp[50];

  //Need this so we can prime the pump and not mess up reading in
  if(infile)
  {
    infile.get(temp, 50, ':');
    infile.ignore(100,':');
  }

  while(infile && !infile.eof())
  {
    input.keyword = new char [strlen(temp) + 1];
    strcpy(input.keyword, temp);

    infile.get(temp, 50, ':');
    infile.ignore(100,':');
    input.description = new char [strlen(temp) + 1];
    strcpy(input.description, temp);

    infile >> input.page_nums;
    infile.ignore(100,':');

    infile >> input.chapter;
    infile.ignore(100,':');
  
    infile.get(temp, 50, '\n');
    infile.ignore(100,'\n');
    input.flag = new char [strlen(temp) + 1];
    strcpy(input.flag, temp);

    if(insert(input))
    {
      //cout << "Hell ya dude it works! " << endl << endl;
    }
    //prime the pump
    infile.get(temp,50,':');
    infile.ignore(100,':');
    destroy(input);
  }

  
  infile.close();
  infile.clear();
  return 1;
}

//This function takes in a key which will be the topic of a chapter. Then
//this function will assign that key a value in the array by adding up all
//the letters of the key and then modding it by the size of the array of node
//pointers.
int table::hash_func(char * key)
{
  int value = 0;
  for(int i = 0; i < strlen(key); ++i)
  {
    value += key[i];
  }

  return value % hash_table_size;
}



//This function takes in a key value, inserts a node at an
//index in the array and adds data about a concept. This
//function will always return true if it is called.
bool table::insert(concept & input)
{
  char * key = new char [strlen(input.keyword) + 1];
  strcpy(key,input.keyword);
  int index = hash_func(key);
  if(hash_table[index])
  {
    node * current = hash_table[index];
    hash_table[index] = new node;
    
    //Adding data.
    //Keyword
    hash_table[index] -> topic.keyword = new char [strlen(input.keyword) + 1];
    strcpy(hash_table[index] -> topic.keyword,input.keyword);   

    //description of the topic
    hash_table[index] -> topic.description 
    	= new char [strlen(input.description) + 1];
    strcpy(hash_table[index] -> topic.description,input.description);

    //page number
    hash_table[index] -> topic.page_nums = input.page_nums;

    //chapter number
    hash_table[index] -> topic.chapter = input.chapter; 

    //The flag
    hash_table[index] -> topic.flag = new char [strlen(input.flag) + 1];
    strcpy(hash_table[index] -> topic.flag,input.flag);

    hash_table[index] -> next = current;
    return true;
  }
  if(!hash_table[index])
  {
    hash_table[index] = new node;

    //Keyword
    hash_table[index] -> topic.keyword = new char [strlen(input.keyword) + 1];
    strcpy(hash_table[index] -> topic.keyword,input.keyword);   

    //description of the topic
    hash_table[index] -> topic.description 
    	= new char [strlen(input.description) + 1];
    strcpy(hash_table[index] -> topic.description,input.description);

    //page number
    hash_table[index] -> topic.page_nums = input.page_nums;

    //chapter number
    hash_table[index] -> topic.chapter = input.chapter;
    
    //The flag
    hash_table[index] -> topic.flag = new char [strlen(input.flag) + 1];
    strcpy(hash_table[index] -> topic.flag,input.flag);
    
    hash_table[index] -> next = NULL;
    return true;
  }
  else
    return false;
}



//This function takes in a key value and deletes a match.\
//If the match is not in the first node you need to traverse.
//If hash_table[index] is already NULL we return false, all 
//other times we return true.
bool table::remove(char * key)
{
  int index = hash_func(key); //index for the array of LLL
  node * current = hash_table[index]; //current ptr

  if(hash_table[index])
  {
    if(strcmp(hash_table[index] -> topic.keyword, key) == 0)
    {
      current = hash_table[index] -> next;
      //delete dynamic data.A
      delete [] hash_table[index] -> topic.keyword;
      delete [] hash_table[index] -> topic.description;
      delete [] hash_table[index] -> topic.flag;
      delete hash_table[index];
      hash_table[index] = current;
      return true;
    }
    else
    {
      node * current = hash_table[index] -> next;
      node * previous = hash_table[index];
      while(current)
      {
        if(strcmp(current -> topic.keyword, key) == 0)
	{
	  node * temp = current -> next;
	  //delete dynamic data.
	  delete [] current -> topic.keyword;
	  delete [] current -> topic.description;
	  delete [] current -> topic.flag;
	  delete current;
	  previous -> next = temp;
	  current = previous;
	}
	current = current -> next;
      }
    }
  }
  else
    return false;
}



//First the user will be asked for a topic they want to change in their notes
//The key will be passed to the function and that subject will be overwritted
//with the data the user enters in. Returns false if an invalid key is entered.
//Returns true if data is successfully edited.
bool table::edit(char * key, concept & input)
{
  int index = hash_func(key);
  if(!hash_table[index])
  {
    return false;
  }

  if(strcmp(hash_table[index] -> topic.keyword, key) == 0)
  {
    delete [] hash_table[index] -> topic.description;
    hash_table[index] -> topic.description 
      = new char[strlen(input.description) + 1];
    strcpy(hash_table[index] -> topic.description,input.description);
    
    hash_table[index] -> topic.page_nums = input.page_nums;
    hash_table[index] -> topic.chapter = input.chapter;

    delete [] hash_table[index] -> topic.flag;
    hash_table[index] -> topic.flag = new char[strlen(input.flag) + 1];
    strcpy(hash_table[index] -> topic.flag,input.flag);
    return true;
  }

  else
  {
    node * current = hash_table[index] -> next;
    while(current)
    {
      if(strcmp(current -> topic.keyword,key) == 0)
      {
        delete [] current -> topic.description;
        current -> topic.description 
          = new char[strlen(input.description) + 1];
        strcpy(current -> topic.description,input.description);
    
        current -> topic.page_nums = input.page_nums;
        current -> topic.chapter = input.chapter;

        delete [] current -> topic.flag;
        current -> topic.flag = new char[strlen(input.flag) + 1];
        strcpy(current -> topic.flag,input.flag);
        return true;
      }
      current = current -> next;
    }
  }

  return false;
}



//
bool table::retrive(char * key, concept & input)
{
  int i = hash_func(key);
  if(!hash_table[i])
  {
    return false;
  }
  if(strcmp(hash_table[i] -> topic.keyword,key) == 0)
  {
    input.keyword = new char[strlen(key) + 1];
    strcpy(input.keyword,key);

    input.description = 
      new char[strlen(hash_table[i] -> topic.description) + 1];
    strcpy(input.description,hash_table[i] -> topic.description);

    input.page_nums = hash_table[i] -> topic.page_nums;
    input.chapter = hash_table[i] -> topic.chapter;

    input.flag = new char[strlen(hash_table[i] -> topic.flag) + 1];
    strcpy(input.flag, hash_table[i] -> topic.flag);

    return true;
  }
  else
  {
    node * current = hash_table[i] -> next;
    while(current)
    {
      if(strcmp(current -> topic.keyword,key) == 0)
      {
        input.keyword = new char[strlen(key) + 1];
        strcpy(input.keyword,key);

        input.description = 
          new char[strlen(current -> topic.description) + 1];
        strcpy(input.description,current -> topic.description);

        input.page_nums = current -> topic.page_nums;
        input.chapter = current -> topic.chapter;

        input.flag = new char[strlen(current -> topic.flag) + 1];
        strcpy(input.flag, current -> topic.flag);     
        return true;
      }
    }
    return false;
  }
}



//The user will pass in a topic they want displayed. Returns true if the topic
//is found. Returns false if the key is invalid (not in the hash table.)
bool table::display_onechapter(char * key)
{
  int i = hash_func(key);
 
  if(!hash_table[i])
  {
    return false;
  }

  else
  {
    if(strcmp(key,hash_table[i] -> topic.keyword) == 0)
    {
      cout << hash_table[i] -> topic.keyword << endl
      << hash_table[i] -> topic.description << endl
      << hash_table[i] -> topic.page_nums << endl
      << hash_table[i] -> topic.chapter << endl
      << hash_table[i] -> topic.flag << endl << endl;
      return true;
    }
    else
    {
      node * current = hash_table[i];
      while(current)
      {
        if(strcmp(key,current -> topic.keyword) == 0)
	{
          cout << current -> topic.keyword << endl
          << current -> topic.description << endl
          << current -> topic.page_nums << endl
          << current -> topic.chapter << endl
          << current -> topic.flag << endl << endl;
	  return true;
        }
	current = current -> next;
      }
    }
  }
  return false;
}



//This function simply displays all data inside the hash table. returns true 
//If there is any data, false otherwise.
bool table::display_all_wrap()
{
  for(int i = 0; i < hash_table_size; ++i)
  {
    if(hash_table[i])
    {
      node * current = hash_table[i];
      while(current)
      {
         cout << current -> topic.keyword << endl
         << current -> topic.description << endl
         << current -> topic.page_nums << endl
         << current -> topic.chapter << endl
         << current -> topic.flag << endl << endl;
	 current = current -> next;
      }
    }
  }
  return true;
}



//Recursive solution that is not working
bool table::display_all(node * current)
{
  if(!current)
  {
    return false;
  }
  cout << current -> topic.keyword << endl
       << current -> topic.description << endl
       << current -> topic.page_nums << endl
       << current -> topic.chapter << endl
       << current -> topic.flag << endl;
  return display_all(current -> next);
}



//This is the wrapper function for the recursive destructor
//function. This function always will return 0 because success
//or failure doesnt need to be shown to the user.
int table::destroy_allw()
{ 
 for(int i = 0; i < hash_table_size; ++i)
 {
   destroy_all(hash_table[i]);
   hash_table[i] = NULL;
 }
 return 0;
}



//This is the recursive function for the chains. Deletes from
//the begining to the end. A temp pointer holds on to the next
//node so we can reconnect. If the temp becomes NULL so will
//the head pointer and thats when we know we are done.
int table::destroy_all(node * & hash_table)
{
  if(!hash_table)
  {
    return 0;
  }
  node * temp = hash_table -> next;
  delete [] hash_table -> topic.keyword;
  delete [] hash_table -> topic.description;
  delete [] hash_table -> topic.flag;
  delete hash_table;
  hash_table = temp;
  return destroy_all(hash_table);
}



//The destructor... calls a recursive function that deallocates
//memory from the head pointer. After all the memory is dealloc
//ated at a specific index the for loop in the wrapper function
//Will increment itself.
table::~table()
{
  destroy_allw();
}
