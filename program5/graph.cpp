//Alex Springer, CS163, Program 5, 6/3/16. The purpose of this program is to
//get comfortable with graphs. This is the main.cpp file

#include "graph.h"
using namespace std;



//The constructor for class table.
table::table()
{
  list_size = 5;
  adjacency_list = new vertex[list_size];

  for(int i = 0; i < list_size; ++i)
  {
    //*(adjacency_list + i).head = NULL;
    //*(adjacency_list + i).file_name = NULL;
    adjacency_list[i].head = NULL;
    adjacency_list[i].file_name = NULL;
  }
}



//Takes in a file name from main and creates a vertex.
bool table::insert_vertex(char * file_name)
{
  for(int i = 0; i < list_size; ++i)
  {
    if(!adjacency_list[i].file_name)
    {
      adjacency_list[i].file_name = new char[strlen(file_name) + 1];
      strcpy(adjacency_list[i].file_name,file_name);
      return true;
     }
  }
  return false;
}



//Uses the get location function to get the indexes of the two verticies
//that will be connected.
bool table::insert_edge(char * current_vertex, char * attach)
{
  int a = get_location(current_vertex);
  int b = get_location(attach);
  cout << a << " " << b << endl;
  if(a != -1 && b != -1)
  {
    node * temp = adjacency_list[a].head;
    adjacency_list[a].head = new node;
    node * current = adjacency_list[a].head;
    current -> adjacent = & adjacency_list[b];
    current -> next = temp;
    return true;
  }
  return false;
}



//Looks for a match in the array of verticies. Returns the the index where
//the match is.
int table::get_location(char * key)
{
  for(int i = 0; i < list_size; ++i)
  {
    if(adjacency_list[i].file_name 
      && strcmp(adjacency_list[i].file_name,key) == 0)
    {
      return i;
    }
  }
  return -1;
}
    


//This has a for loop to loop through the adjacency list.
//Calls a function to traverse the edge list at each index.
bool table::display_all()
{
  for(int i = 0; i < list_size; ++i)
  {
    cout << "File name: " << adjacency_list[i].file_name << endl;
    traverse(adjacency_list[i].head); 
  }
  return true;
}



//Traverse the edge list and display all connections. Return true if data.
bool table::traverse(node * head)
{
  if(!head)
  {
    return false;
  }
  cout << "The previous is related to: " <<
    head -> adjacent -> file_name << endl;
  traverse(head -> next);
  return true;
}



//recursive function to call from the destructor. Deallocates the edges.
bool table::destroy(node * & head)
{
  if(!head)
  {
    return false;
  }

  destroy(head -> next);
  delete head;
  head = NULL;
  return true;
}



//The destructor for class table.
table::~table()
{
  for(int i = 0; i < list_size; ++i)
  {
    destroy(adjacency_list[i].head);
    delete [] adjacency_list[i].file_name;
    adjacency_list[i].file_name = NULL;
    adjacency_list[i].head = NULL;
  }
}
