//Alex Springer, 5/25/16, Program 4, CS163. This program is a revamp of prog
//ram three but this time with a binary search tree as the data structure.
//Program three was a study guide for the final. This is a continuation of
//that program! This is the .h file for the program.

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>



struct study
{
  study();
  ~study();
  int deallocate();
  int copy(study & info);
  char * keyword;
  char * description;
  int chapter;
  int page_num;
  char flag;
  int value;
};



//Binary search tree
struct node
{
  study data;
  node * left;
  node * right;
 
};



//Table adt
class table
{
  public:
    table();
    ~table();
    int add(study & info);
    bool insert(node * & root, study & info);
    bool insert(study & info);
    bool display_all();
    bool display_all(node * root);
    bool retrieve(study & info);
    bool retrieve(node * root, study & info, int value);
    bool edit(study & info);
    bool edit(node *& root, study & info, int value);
    bool display_range(int a, int b);
    bool display_range(node * root, int a, int b);
    bool remove(study & info);
    bool remove(node * & root, int value, study & info);
    bool find_ios(node * & root, study & info);
    int destroy();
    int destroy(node * & root);

  private:
    node * root;
    int do_math(study & info);
};



void read_in_edit(study & info);
