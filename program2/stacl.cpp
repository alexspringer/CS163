//Alex Springer, CS163, 4/27/16, program 2
#include "stack.h"
using namespace std;



//constructor for the stack
stack::stack()
{
  head = NULL;
  top = 0;
  size = 3;
}



//Wrap function for deallocation
int stack::destroy_wrap()
{
  destroy(head);
  head = NULL;
  return 0;
}



//Deallocates all data, called from wrapper in the destructor
int stack::destroy(s_node * & head)
{
  if(head == NULL)
  {
    return 0;
  }
  destroy(head -> next);
  delete [] head -> data;
  delete head;
  return 0;
}



//Pops an item off the top of the stack returns true if something is popped
//false if there is nothing to pop.
bool stack::pop()
{
  if (head == NULL)
  {
    return false;
  }
  if (top == 1)
  {
    s_node * temp = head -> next;
    delete [] head -> data;
    delete head;
    head = temp;
    if (head == NULL)
    {
      top = 0;
    }
    else
    {
      top = size;
    }
    return true;
  }
  else
  {
    top = top -1;
    head -> num -= 1;
    return true;
  }
}



//Wrapper function for my display function
int stack::display_wrap()
{
  return display(head);
}



//What is the top of the stack? return false if the stack is empty,
//Return true if an item has been retrieved.
bool stack::peek(pod & info)
{
  if (head == NULL)
  {
    return false;
  }
  else
  {
    info.sender = 
    	new char [strlen((head -> data + (top-1)) -> sender) + 1];
    strcpy(info.sender,((head -> data + (top-1)) -> sender));     
    
    info.dest = 
    	new char [strlen((head -> data + (top-1)) -> dest) + 1];
    strcpy(info.dest,((head -> data + (top-1)) -> dest));   
    
    info.size = 
    	new char [strlen((head -> data + (top-1)) -> size) + 1];
    strcpy(info.size,((head -> data + (top-1)) -> size));
    return true;
  }
}



//Displays all the data within the linear linked list of arrays
//returns 0 if nothing, 1 if displayed. Recursive
int stack::display(s_node * head)
{
  if (head == NULL)
  {
    return 0;
  }
  
  
  for (int i = head -> num; i >= 0; --i)
  {

    cout << "Sender: " << (head -> data + i) -> sender << endl
    << "Destination: " << (head -> data + i) -> dest << endl
    << "Size of the package: " 
    << (head -> data + i) -> size << endl << endl;
  }

  display(head -> next);
  return 1;
}



//Pushes a new package onto the stack
bool stack::push(pod & info, int max)
{
  if(head == NULL)
  {
    head = new s_node;
    head -> data = new pod[size];

    //Adding data into the array at top.
    (head -> data + top) -> sender = new char [strlen(info.sender) + 1];
    strcpy((head -> data + top) -> sender, info.sender);
    (head -> data + top) -> dest = new char [strlen(info.dest) + 1];
    strcpy((head -> data + top) -> dest, info.dest);
    (head -> data + top) -> size = new char [strlen(info.size) + 1];
    strcpy((head -> data + top) -> size, info.size);

    head -> next = NULL;
    ++top;
    head -> num = 0;
    return true;
  }

  if(top == size)
  {
    s_node * current = head;
    head = new s_node;
    head -> next = current;
    top = 0;
    head -> data = new pod[size];
    
    //ADding data into the array at top.
    (head -> data + top) -> sender = new char [strlen(info.sender) + 1];
    strcpy((head -> data + top) -> sender, info.sender);
    
    (head -> data + top) -> dest = new char [strlen(info.dest) + 1];
    strcpy((head -> data + top) -> dest, info.dest);

    (head -> data + top) -> size = new char [strlen(info.size) + 1];
    strcpy((head -> data + top) -> size, info.size);   
    
    ++top;
    head -> num = 0;
    return true;
  }

   else
   {
     //adding data into the array at top.
     (head -> data + top) -> sender = new char [strlen(info.sender) + 1];
     strcpy((head -> data + top) -> sender, info.sender);
    
     (head -> data + top) -> dest = new char [strlen(info.dest) + 1];
     strcpy((head -> data + top) -> dest, info.dest);

     (head -> data + top) -> size = new char [strlen(info.size) + 1];
     strcpy((head -> data + top) -> size, info.size);

     ++top;
     head -> num += 1;
   }
  return true;
}



//DESTROYS EVERYTHING
stack::~stack()
{
  destroy_wrap(); //Calls recursive destroy function
}
