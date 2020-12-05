//Alex Springer, CS163, Program 5, 6/3/16. The purpose of this program is to
//get comfortable with graphs. This is the main.cpp file

#include "graph.h"
using namespace std;



//Main calls all of the other functions created
//in the implementation file.
int main()
{
  char temp[50];
  char file[50];
  table graph;

  for(int i = 0; i < 5; ++i)
  {
    cout << "Enter a file name. ";
    cin.get(temp,50,'\n'); cin.ignore(100,'\n');
    if(graph.insert_vertex(temp))
    {
      cout << "Insert works. " << endl;
    }
  }
  
  cout << "What files are related? ";
  cin.get(temp,50,'\n'); cin.ignore(100,'\n');
  cin.get(file,50,'\n'); cin.ignore(100,'\n');
  if(graph.insert_edge(temp,file))
  {
    cout << "Edge create. " << endl;
  }

  if(graph.display_all())
  {
    cout << "Display works. " << endl;
  }

  return 1;
}
