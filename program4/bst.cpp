//Alex Springer, 5/25/16, Program 4, CS163. This program is a revamp of prog
//ram three but this time with a binary search tree as the data structure.
//Program three was a study guide for the final. This is a continuation of
//that program! This is the implementation file for the program.
using namespace std;


#include "bst.h"



//The constructor for the table ADT.
table::table()
{
  root = NULL;
}



//This is the constructor for my study struct.
study::study()
{
  keyword = NULL;
  description = NULL;
  chapter = 0;
  page_num = 0;
  flag = '\0';
  value = 0;
}



//destructor wrapper
int table::destroy()
{
  return destroy(root);
}



//wrapper function for remove, calls a function to assign the keyword a value.
bool table::remove(study & info)
{
  int value = do_math(info);
  return remove(root,value,info);
}



//Remove a match from the BST this function has many special cases.
bool table::remove(node * & root, int value, study & info)
{
  //No data.
  if(!root)
  {
    return false;
  }
  
  if(value == root -> data.value)
  {
    //Remove a leaf.
    if(root -> left == NULL && root -> right == NULL)
    {
      delete [] root -> data.keyword;
      root -> data.keyword = NULL;
      delete [] root -> data.description;
      root -> data.description = NULL;
      delete root;
      root = NULL;
      return true;
    }

    //Internal node with a left child
    if(root -> left && root -> right == NULL)
    {
      node * temp = root -> left;
      delete [] root -> data.keyword;
      root -> data.keyword = NULL;
      delete [] root -> data.description;
      root -> data.description = NULL;
      delete root;
      root = temp;
      return true;
    }

    //Internal node with a right child
    if(!root -> left && root -> right)
    {
      node * temp = root -> right;
      delete [] root -> data.keyword;
      root -> data.keyword = NULL;
      delete [] root -> data.description;
      root -> data.description = NULL;
      delete root;
      root = temp;
      return true;
    }

    //Internal node with two children, right has no left child. Find ios
    //and delete the node                      
    if(root -> left && root -> right && root -> right -> left == NULL)
    {
      node * current = root -> right;
      node * temp = current -> right;
      //Deallocate info before more dynamic mem
      info.deallocate();
      cout << "Where do we segfault? " << endl << endl;
      //copy the data from the ios into info.
      info.keyword = new char[strlen(current -> data.keyword) + 1];
      strcpy(info.keyword, current -> data.keyword);
      info.description = new char[strlen(current -> data.description) + 1];
      strcpy(info.description, current -> data.description);
      info.chapter = current -> data.chapter;
      info.page_num = current -> data.page_num;
      info.flag = current -> data.flag;
      info.value = current -> data.value;
      delete [] current -> data.keyword;
      current -> data.keyword = NULL;
      delete [] current -> data.description;
      current -> data.description = NULL;
      delete current;
      current = NULL;
      root -> right = temp;
      delete [] root -> data.keyword;
      root -> data.keyword = NULL;
      delete [] root -> data.description;
      root -> data.description = NULL;
      root -> data.copy(info);
      info.deallocate();
      return true;
    }

    if(root -> left && root -> right && root -> right -> left)
    {
      find_ios(root -> right, info);
      delete [] root -> data.keyword;
      root -> data.keyword = NULL;
      delete [] root -> data.description;
      root -> data.description = NULL;
      root -> data.copy(info);
      root -> data.value = info.value;
      info.deallocate();
      return true;
    }
  }
  if(value < root -> data.value)
    remove(root -> left,value,info);
  if(value > root -> data.value)
    remove(root -> right,value,info);
  return true;
}



//Finds the inorder successor for the cases that need it. This function also
//Deletes the node the IOS is found in.
bool table::find_ios(node * & root, study & info)
{
  node * previous = root;
  node * current = root;
  while (current -> left)
  {
    previous = current;
    current = current -> left;
  }

  node * temp = current -> right;


  info.deallocate();
  //copy the data from the ios into info.
  info.keyword = new char[strlen(current -> data.keyword) + 1];
  strcpy(info.keyword, current -> data.keyword);
  info.description = new char[strlen(current -> data.description) + 1];
  strcpy(info.description, current -> data.description);
  info.chapter = current -> data.chapter;
  info.page_num = current -> data.page_num;
  info.flag = current -> data.flag;
  info.value = current -> data.value;

  //Delete the dynamic data in the node and delete the node.
  delete [] current -> data.keyword;
  current -> data.keyword = NULL;
  delete [] current -> data.description;
  current -> data.description = NULL;
  previous -> left = temp;
  delete current;
  current = NULL;
  return true;
}



//Travese to leaves then destroy the tree!
int table::destroy(node * & root)
{
  if(!root)
  {
    return 0;
  }

  destroy(root -> left) + destroy(root -> right);
  delete [] root -> data.keyword;
  root -> data.keyword = NULL;
  delete [] root -> data.description;
  root -> data.description = NULL;
  delete root;
  root = NULL;
  return 0;
}



//Recursive function for display range, not much too it.
bool table::display_range(int a, int b)
{
  return display_range(root,a,b);
}



//Two parameters passed in, a and b. only display a nodes data
//if its value is between these two parameters. Return true
//if any display.
bool table::display_range(node * root, int a, int b)
{
  if(!root)
  {
    return false;
  }
  if(root -> data.value >= a && root -> data.value <= b)
  {
    cout << "Keyword: " << root -> data.keyword << endl
    << "Description: " << root -> data.description << endl
    << "Chapter: " << root -> data.chapter << endl
    << "Page Number: " << root -> data.page_num << endl
    << "Do I need to study this more? " << root -> data.flag 
    << endl << endl;
  }
  return display_range(root -> left,a,b) 
    + display_range(root -> right,a,b);
}



//wrapper function for edit. Calls a function to assign the
//keyword a value
bool table::edit(study & info)
{
  int value = do_math(info);
  return edit(root,info,value);
}



//Delete the description in a node and replace it. 
bool table::edit(node * & root, study & info, int value)
{
  if(!root)
  {
    return false;
  }
  if(value == root -> data.value)
  {
    delete [] root -> data.description;
    root -> data.description 
      = new char[strlen(info.description) + 1];
    strcpy(root -> data.description, info.description);
    return true;
  }

  if(value < root -> data.value)
  {
    edit(root -> left,info,value);
  }

  if(value > root -> data.value)
  {
    edit(root -> right,info,value);
  }
  return true;
}



//wrapper function for retrieve. Assigns the key you pass in
//a value using the do math function.
bool table::retrieve(study & info)
{
  int value = do_math(info);
  return retrieve(root,info,value);
}



//The recursive function for retrieval
bool table::retrieve(node * root, study & info, int value)
{
  if(!root)
  {
    return false;
  }

 
  if(value == root -> data.value)
  {
    info.keyword = new char[strlen(root -> data.keyword) + 1];
    strcpy(info.keyword, root -> data.keyword);

    info.description = new char[strlen(root -> data.description) + 1];
    strcpy(info.description, root -> data.description);

    info.chapter = root -> data.chapter;
    info.page_num = root -> data.page_num;
    info.flag = root -> data.flag;

    return true;
  }
  
  if(value < root -> data.value)
  {
    retrieve(root -> left, info, value);
  }

  if(value > root -> data.value)
  {
    retrieve(root -> right, info, value);
  }
  
  else
  {
    return true;
  }
}




//This function assigns the keyword a numerical value.
int table::do_math(study & info)
{
  int value = 0;

  for(int i = 0; i < strlen(info.keyword) - 1; ++i)
  {
    value += info.keyword[i];
  }

  return value;
}



//Deletes the dynamic memory allocated to the data memebers of the struct
int study::deallocate()
{
  if(keyword)
  {
    delete [] keyword;
    keyword = NULL;
  }
  if(description)
  {
    delete [] description;
    description = NULL;
  }
  chapter = 0;
  page_num = 0;
  flag = '\0';
  return 1;
}



//This function reads in data from an external data file, fills up
//a variable of type struct, and then calls the insert function as it
//loops. After inserting deallocate is called to release dynamic mem.
//pass the struct variable to this by ref.
int table::add(study & info)
{
  ifstream infile;
  char temp[100]; //to dynamically allocate!

  infile.open("bst.txt");

  if(infile)
  {
    infile.get(temp,100,':'); infile.ignore(100,':');
  }
  
  while(infile && !infile.eof())
  {
    info.keyword = new char[strlen(temp) + 1];
    strcpy(info.keyword, temp);
    
    infile.get(temp,100,':'); infile.ignore(100,':');
    info.description = new char[strlen(temp) + 1];
    strcpy(info.description, temp);

    infile >> info.chapter; infile.ignore(100,':');
    infile >> info.page_num; infile.ignore(100,':');
    infile >> info.flag; infile.ignore(100,'\n');

    if(insert(info))
      cout << "Success! " << endl;

    info.deallocate();

    //priming the pump
    infile.get(temp,100,':'); infile.ignore(100,':');

  }

  infile.close();
  infile.clear();

  return 1;
}



//copies the data from the variable of type struct into the node.
int study::copy(study & info)
{
  if(keyword)
  {
    delete [] keyword;
    keyword = NULL;
  }

  if(description)
  {
    delete [] description;
    description = NULL;
  }

  keyword = new char[strlen(info.keyword) + 1];
  strcpy(keyword,info.keyword);

  description = new char[strlen(info.description) + 1];
  strcpy(description,info.description);

  chapter = info.chapter;
  page_num = info.page_num;
  flag = info.flag;

  return 1;
}



//Creates and inserts new node into the binary search tree. Needs to be
//passed the struct variable. Returns true when node is added.
bool table::insert(study & info)
{
  return insert(root, info);
}



//Recursive traversal, add when root is NULL. Always returns true because
//There will always be something to add since there is no user error.
bool table::insert(node * & root, study & info)
{
  int num = do_math(info);

  if(!root)
  {
    root = new node;
    root -> data.copy(info);
    root -> data.value = num;
    root -> left = NULL;
    root -> right = NULL;
    return true;
  }

  if(num < root -> data.value)
  {
    insert(root -> left, info);
  }

  if(num > root -> data.value)
  {
    insert(root -> right, info);
  }

  return true;
}



//wrapper function for display_all, returns the value of the recursive 
//function. Called from main.
bool table::display_all()
{
  return display_all(root);
 
}



//Displays all data inside the tree. Return true if there
//is data to display, false otherwise.
bool table::display_all(node * root)
{
  if(!root)
  {
    return false;
  }
  
  //display the nodes data.
  cout << "Keyword: " << root -> data.keyword << endl
  << "Description: " << root -> data.description << endl
  << "Chapter: " << root -> data.chapter << endl
  << "Page Number: " << root -> data.page_num << endl
  << "Do I need to study this more? " << root -> data.flag << endl << endl
  << root -> data.value << endl << endl;

  return display_all(root -> left) + display_all(root -> right);

  return true;



}



//The table destructor calls recursive destory function.
table::~table()
{
  destroy();
}



//destructor for study struct
study::~study()
{
  if(keyword)
  {
    delete [] keyword;
    keyword = NULL;
  }
  if(description)
  {
    delete [] description;
    description = NULL;
  }
  chapter = 0;
  page_num = 0;
  flag = '\0';
  value = 0;
}
