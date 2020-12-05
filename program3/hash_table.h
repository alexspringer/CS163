//Alex Springer, Program 3, CS163, May 16th, This is the .h file for the
//Hash table. The data structure to implement the table is an array of linear
//linked lists. OR a hashtable with chaining as the collision resolution 
//operation.
#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>



//These are the components of a single item to study
struct concept
{
  char * keyword; //The name of the topic, ie arrays or something
  char * description;
  int page_nums; //array of page numbers
  int chapter; //array of chapters
  char * flag; //Is additional study needed? yes / no

};



struct node
{
  node * next;
  concept topic;

};



class table
{
  public:
    table(int size = 5);
    ~table();
    bool insert(concept & input);
    bool remove(char * key);
    bool edit(char * key, concept & input);
    bool retrive(char * key, concept & input);
    bool display_onechapter(char * key);
    bool display_all_wrap();
    bool display_all(node * current);
    int destroy_allw();
    int destroy_all(node * & hash_table);
 int read_in(concept & input);   

  private:
    node ** hash_table;
    int hash_table_size;
    int hash_func(char * key);
};



//prototypes for main organization and reading in from the .txt
//void read_in(concept & input, table hash);
void destroy(concept & input);
void ask_user(concept & input);
