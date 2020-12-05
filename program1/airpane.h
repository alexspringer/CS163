//Alex Springer, CS163, 4/8/16, Program #1.
//The purpose of this program is to assit a travler with flight information
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>



struct airport_info
{
  char * airport_name; //Name of the airport
  int customes; //Number of customes checks
  int immigrations; //Number of immigration checks
  int security_checks; //Number of security checks

};



struct airport_node
{
  airport_info airport; //Data from the airport info struct to store in
  			//the LLL
  airport_node * next; //Pointer to the next node for LLL

};



class airport
{
  public:
    airport();
    ~airport();
    int build(void); //Builds LLL.
    int calculate(char * airport_name); //calcs wait time at an airport.
    int display(void); //Displays everything in the LLL
    int destroy(airport_node *& head);


private:
    airport_info info;
    airport_node * head;

};
