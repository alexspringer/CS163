//Alex Springer, CS163, 4/27/16, program 2

#include <iostream>
#include <cctype>
#include <cstring>



struct node
{
  node * next;
  char * recip;
};



class queue
{
  public:
    queue();
    ~queue();
    bool enqueue(char * temp);
    bool dequeue();
    bool destroy(node * & temp);
    bool destroy_wrap();
    int display(node * & temp);
    int display_wrap();
    bool peek(char * temp);


  private:
    node * tail;

};
