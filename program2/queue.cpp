//Alex Springer, CS163, 4/27/16, program 2
#include "queue.h"
using namespace std;



//The constructor for the class queue.
queue::queue()
{
  tail = NULL;
}



//Copies the next up recipient into temp and returns it back to the calling
//routine. Retruns true if there is data, false otherwise.
bool queue::peek(char temp[])
{
  if (tail == NULL)
  {
    return false;
  }
  
  else
  {
    node * peek = tail -> next;
    strcpy(temp, peek -> recip);
  }
  return true;
}



//This is the wrap function for deallocation of the 
//circular linked list. First I break the linked list
//So I can use it like a linear linked list.
bool queue::destroy_wrap()
{
  if (tail == NULL)
  {
    return false;
  }
  else
  {
    node * temp = tail -> next;
    tail -> next = NULL; //break the list
    destroy(temp);
    tail = NULL;
  }
  return true;
}



//Get to the end of the list and delete the memory
//From the end to the front of the list. Doesnt matter what we return
//because this is called from the destructor.
bool queue::destroy(node * & temp)
{
  if(temp == NULL)
  {
    return true;
  }
  destroy(temp -> next);
  delete temp -> recip;
  delete temp;
  temp = NULL;
  return true;
}



//deletes the node at the start of the list if there
//is a node at the front. Returns false if the list is empty, and returns
//true if things are deleted.
bool queue::dequeue()
{
  if(tail == NULL) //no nodes
  {
   return false;
  }

  if (tail -> next == tail) //one node
  {
    delete [] tail -> recip;
    delete tail;
    tail = NULL;
    return true;
  }

  else //many nodes
  {
    node * temp = tail -> next;
    tail -> next = temp -> next;
    delete [] temp -> recip;
    delete temp;
    temp = NULL;
  }
  return true;
}
    


//Adds a new node to the end of the list. Returns true if a new node is 
//added so always returns true.
bool queue::enqueue(char * temp)
{
  //Got a really strange error that the tutors were unsure about so thats 
  //why I use another temp variable.
  char temp2[50];
  strcpy(temp2, temp);
  int length = strlen(temp) + 1;
  if (tail == NULL) //no nodes
  {
    tail = new node;
    tail -> recip = new char [length];
    strcpy(tail -> recip,temp2);
    tail -> next = tail;
    return true;
  }

  if (tail -> next == tail) //one node
  {
    node * temp = tail;
    tail -> next = new node;
    tail = tail -> next;
    tail -> recip = new char [length];
    strcpy(tail -> recip,temp2);
    tail -> next = temp;
    return true;
  }

  else //many nodes
  {
    node * temp = tail -> next;
    tail -> next = new node;
    tail = tail -> next;
    tail -> recip = new char [length];
    strcpy(tail -> recip,temp2);
    tail -> next = temp;
  }
  return true;
 
}



//The wrap function for displaying all contents.
//First I break the list and then I display like a
//normal LLL. After I display I reconnect and make 
//the list circular again.
int queue::display_wrap()
{
  if (tail == NULL)
  {
    return 0;
  }
  else
  {
    node * temp = tail -> next;
    tail -> next = NULL; //break the list
    display(temp);
    tail -> next = temp; //reconnect the list
  }
  return 1;
}



//Displays data in each node for the circular linked 
//list.
int queue::display(node * & temp)
{
  if(temp == NULL)
  {
    return 0;
  }
  cout << "Recipient: " << temp -> recip << endl;
  display(temp -> next);


  return 1;
}



//The desctructor for the queue class. It calls a 
//recursive function that deallocates the memory and
//sets tail to NULL if it isn't already.
queue::~queue()
{
  if (tail)
  {
    destroy_wrap();
  }
}
