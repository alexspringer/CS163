//Alex Springer, CS163, 4/8/16, Program #1.
//The purpose of this program is to assit a travler with flight info.

#include "airpane.h"
using namespace std;



//constructor for the airport data type
airport::airport()
{
  head = NULL;
  info.airport_name = '\0';
  info.customes = 0;
  info.immigrations = 0;
  info.security_checks = 0;
}



int airport::destroy(airport_node *& head)
{
  if (head == NULL)
  {
    return 0;
  }
  destroy(head -> next);
  delete head;
  head = NULL;
  return 1;
}



//This function calculates the total amount of time it takes to get through
//the entire airport. Returns time in minutes.
int airport::calculate(char * airport_name)
{
  int sum = 0; //total time you need to wait an an airport
  airport_node * current = head;
  if (head == NULL)
  {
    sum = 0;
    return sum;
  }
  else
  {
    while (current)
    {
      if (strcmp(current -> airport.airport_name, airport_name) == 0)
      {
	sum = 15 * current -> airport.customes 
	+ 15 * current -> airport.immigrations
	+ 15 * current -> airport.security_checks;
      }
      current = current -> next;
    }
  }

  return sum;
}



//Builds the LLL by reading in information from the .txt file and 
//adding it to the list. Reads in one set then repeats. 
//returns 0 if nothing is read and returns 1 if things are read.
int airport::build()
{
  airport_node * current = head;
  ifstream infile;
  char temp[50];
  infile.open("airport.txt");
  if (!infile)
  {
    return 0;
  }
  else
  {
    
    infile.get(temp, 50, ':'); 
    infile.ignore();
    while (infile && !infile.eof())
    {
      info.airport_name = new char[strlen(temp) + 1];
      strcpy(info.airport_name,temp);
      infile >> info.customes;
      infile.ignore();
      infile >> info.immigrations; 
      infile.ignore();
      infile >> info.security_checks; 
      infile.ignore();
      

      if (head == NULL)
      {
        head = new airport_node;
	head -> airport.airport_name = new char[strlen(info.airport_name) +1];
	strcpy(head -> airport.airport_name,temp);
        head -> airport.customes = info.customes;
        head -> airport.immigrations = info.immigrations;
        head -> airport.security_checks = info.security_checks;
        head -> next = NULL;
	delete [] info.airport_name;	
	info.airport_name = '\0';
      }

      else
      {
        current = head;
        while (current -> next)
        {
          current = current -> next;
        }
        current -> next = new airport_node;
        current = current -> next;
	current -> airport.airport_name = new char[strlen(info.airport_name) +1];
	strcpy(current -> airport.airport_name,temp);
        current -> airport.customes = info.customes;
        current -> airport.immigrations = info.immigrations;
        current -> airport.security_checks = info.security_checks;
        current -> next = NULL;
	delete [] info.airport_name;
	info.airport_name ='\0';
      }

      //priming the pump
      infile.get(temp, 50, ':'); 
      infile.ignore();
    }
  }
  infile.close();
  infile.clear();
  return 1;
}



//This function displays all the data inside the LLL 
//returns 1 if there is stuff to display.
//returns 0 if the list is empty.
int airport::display()
{
  airport_node * current = head;
  if (!head)
    return 0;
  else
  {
    while (current)
    {
      cout << "Airport: " << current -> airport.airport_name << endl
      << "Number of customes: " << current -> airport.customes << endl
      << "Number of immigrations: " << current -> airport.immigrations
      << endl
      << "Number of security checks: " 
      << current -> airport.security_checks << endl;
      current = current -> next;
    }
  }
  return 1;
}



//The destrucor... deallocates the memory.
airport::~airport()
{
  if (head)
  {
    destroy(head);
  }
  if (info.airport_name)
  {
    delete [] info.airport_name;
    info.airport_name = 0;
  }
  if (info.customes)
  {
    info.customes = 0;
  }
  if (info.immigrations)
  {
    info.immigrations = 0;
  }
  if (info.security_checks)
  {
    info.security_checks = 0;
  }
}
