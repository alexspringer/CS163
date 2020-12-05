//Alex Springer, CS163, 4/8/16, Program #1
//This program assits with helping someone travel via airplanes
#include "airpane.h"
#include "itinerary.h"
using namespace std;


int main()
{
  char * airport_name; //Which airport do they need to know the wait time?
  int sum; //The total time needed to wait at a specific airport.
  char temp[100]; // Used for dynamically allocated memory.
  int size = 0;
  airport input; // Variable of the airport class.
  itinerary route;

  input.build();
  input.display();

  cout << "What airport do you need to know the estimated wait time for? "
  << endl;
  cin.get(temp, 100, '\n'); cin.ignore(100, '\n');
  airport_name = new char[strlen(temp) + 1];
  strcpy(airport_name,temp);
  
  sum = input.calculate(airport_name);
  cout << "The total wait time at " << airport_name << " is "
       << sum << "minute(s)." << endl;

//  size = route.count();
  //cout << "size: " << size << endl;
  route.read(size);
  route.display(size);
 /* if(route.compare(sum, temp))
  {
    cout << "There is a problem with time at " << temp << endl;
  }
  cout << "There are no problems with your flights! " << endl;
*/

  return 0;
}

