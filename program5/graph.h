//Alex Springer, CS163, Program 5, 6/3/16. The purpose of this program is to
//get comfortable with graphs. This is the main.cpp file

#include <iostream>
#include <cctype>
#include <cstring>



struct vertex
{
  char * file_name;
  struct node * head;
};



struct node
{
  vertex * adjacent;
  node * next;
};



class table
{
  public:
    table();
    ~table();
    bool insert_vertex(char * file_name);
    bool insert_edge(char * current_vertex, char * attach);
    int get_location(char * key);
    bool display_all();
    bool traverse(node * head);
    bool destroy(node * & head);

  private:
    vertex * adjacency_list;
    int list_size;
};
