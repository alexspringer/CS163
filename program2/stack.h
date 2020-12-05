//Alex Springer, CS163, 4/27/16, program 2

#include <iostream>
#include <cctype>
#include <cstring>



//This struct is a description of a box that will be stored at an index
//of a linear linked list of arrays.
struct pod
{
  char * sender; //Sender of the package
  char * dest; //Destination of the package
  char * size; //Size of the package
};



//One node of our stack.
struct s_node
{
  s_node * next; //Pointer to the next node
  pod * data; //Pointer to a pod struct
  int num; //Allows to count the amount of boxes ina pod
};



//Deals with boxes being sent.
class stack
{
  public:
    stack();
    ~stack();
    bool pop();
    bool push(pod & info, int boxes);
    bool peek(pod & info);
    int display(s_node * head);
    int display_wrap();
    int destroy_wrap();
    int destroy(s_node * & head);
    int copy(pod & info);

  private:
  s_node * head; //Head of our LLL.
  int top; //top index
  int size; //size of the pod (array of type pod)
};



//prototypes for main organization functions.
void read_in(pod & info, char temp[]);
void delete_dynamic(pod & info);
