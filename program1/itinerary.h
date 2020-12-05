//Alex Springer, CS163, 4/8/16, Program #1:.
//The purpose of this program is to assit a travler with flight information
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>



//Groups all the information read by the txt file
struct itinerary_info
{
  itinerary_info();
  ~itinerary_info();
  char flight_type;
  char fast_pass;
  char * airport_name;
  int arrival;
  int departure;
  char end_trip;
};



//This is the linear linked list of flights. Each node holds the
//airport name and the arrival / departure times of the flight
//aswell as a pointer to the next node.
struct flight_node
{
  flight_node();
  ~flight_node();
  char * name_airport;
  int arrival;
  int departure;
  int time_between;
  flight_node * next;
};



//This is the array that holds the linear linked list
struct admin_node
{
  admin_node();
  ~admin_node();
  char flight_type; //Answer is I for international D = domestic
  char fast_pass; //Y / N answer from client
  flight_node * head; //Pointer to a flight node
};



//The data type that deals with the route of the travlers trip
class itinerary
{
  public:
    itinerary();
    ~itinerary();
    int display(int size); //displays all routes
    int read(int size); //Builds LLL.
    int build(int & i, int & j); //creates the data structure
    int count(void); //reads in the amount of trips.
    bool compare(int sum, char temp[]);
    int del_LLL(flight_node * & head);
    int destroy(int size);
  private:
    admin_node ** ptr;
    flight_node * temp;
    itinerary_info info;
    int size;
};
