//Alex Springer, CS163, 4/8/16, Program #1
//This .cpp file handles the member functions of the itinerary class aka
//The second part of the programming assignment.

#include "itinerary.h"
using namespace std;



//constructor for the itinerary class.
itinerary::itinerary()
{
  ptr = NULL;
  temp = NULL;
  size = count();
}



//constructor for the intinerary info struct.
itinerary_info::itinerary_info()
{
  flight_type = '\0';
  fast_pass = '\0';
  airport_name = NULL;
  arrival = 0;
  departure = 0;
  end_trip = '\0';
}



//constructor for the flight_node stuct.
flight_node::flight_node()
{
  name_airport = NULL;
  next = NULL;
  arrival = 0;
  departure = 0;
  time_between = 0;
}



//constructor for the admin_node struct.
admin_node::admin_node()
{
  flight_type = '\0';
  fast_pass = '\0';
}


int itinerary::del_LLL(flight_node * & head)
{ 
  flight_node * temp = head; 
  if (head == NULL)
   return 0;
  head = head -> next;
  delete temp;
  return del_LLL(head) + 1;
}
  


//deallocates the data structure
int itinerary::destroy(int size)
{
  size = count();
  for(int i = 0; i < size; ++i)
  {
    del_LLL(ptr[i] -> head);
  }
    return 1;
}



//This function reads in the flight information from a txt file.
//It is passed an integer from main to size the array of admin pointers.
int itinerary::read(int size)
{
  char temp[50]; //dynamically allocation help
  int i = 0; //indexing variable
  int flag = 0; //Makes it so only reads in one part once.
  int j = 0; //Pass into build for first time thru
  ifstream infile;
  ptr = new admin_node*[size];
  for(int k = 0; k < 5; ++k)
  {
    ptr[i] = NULL;
  }
  infile.open("itinerary.txt");
  if (!infile)
  {
    return 0; //EMPTY FILE
  }

  else
  {
    //First time through will always have atleast one route.
    infile >> info.flight_type;
    infile.ignore(100,':');
    infile >> info.fast_pass;
    infile.ignore(100, ':');
    infile.get(temp, 50, ':');
    infile.ignore(100, ':');
    info.airport_name = new char[strlen(temp) + 1];
    strcpy(info.airport_name,temp);
    infile >> info.arrival;
    infile.ignore(100, ':');
    infile >> info.departure;
    infile.ignore(100, ':');
    infile >> info.end_trip;
    infile.ignore(100, '\n');
    build(i,j);
    delete [] info.airport_name;
    info.airport_name = NULL;
    
    infile.get(temp, 50, ':');
    infile.ignore(100, ':');
    info.airport_name = new char[strlen(temp) + 1];
    strcpy(info.airport_name,temp);
    infile >> info.arrival;
    infile.ignore(100, ':');
    infile >> info.departure;
    infile.ignore(100, ':');
    infile >> info.end_trip;
    infile.ignore(100, '\n');
    build(i,j);
    delete [] info.airport_name;
    info.airport_name = NULL;   

    infile.get(temp, 50, ':');
    infile.ignore(100, ':');
    info.airport_name = new char[strlen(temp) + 1];
    strcpy(info.airport_name,temp);
    infile >> info.arrival;
    infile.ignore(100, ':');
    infile >> info.departure;
    infile.ignore(100, ':');
    infile >> info.end_trip;
    infile.ignore(100, '\n');   
    build(i,j);
    delete [] info.airport_name;
    info.airport_name = NULL;

    infile >> info.flight_type;
    infile.ignore(100,':');
    infile >> info.fast_pass;
    infile.ignore(100, ':');
    infile.get(temp, 50, ':');
    infile.ignore(100, ':');
    info.airport_name = new char[strlen(temp) + 1];
    strcpy(info.airport_name,temp);
    infile >> info.arrival;
    infile.ignore(100, ':');
    infile >> info.departure;
    infile.ignore(100, ':');
    infile >> info.end_trip;
    infile.ignore(100, '\n'); 
    build(i,j);
    delete [] info.airport_name;
    info.airport_name = NULL;   

    infile.get(temp, 50, ':');
    infile.ignore(100, ':');   
    info.airport_name = new char[strlen(temp) + 1];
    strcpy(info.airport_name,temp);
    infile >> info.arrival;
    infile.ignore(100, ':');
    infile >> info.departure;
    infile.ignore(100, ':');
    infile >> info.end_trip;
    infile.ignore(100, '\n');   
    build(i,j);
    delete [] info.airport_name;
    info.airport_name = NULL;
  }
 /* if (info.end_trip == 'Y') //If the first route only has one flight
    {
      ++flag;
    }

    build(i, j); //take the read in info and build the data structure.
    delete [] info.airport_name; //delete the dynamic allocated mem
    info.airport_name = NULL;
    infile.get(temp, 50, '\n');
    infile.ignore();

    while(infile && !infile.eof())
    {
      if (flag == 1)//Only if the first index has a LLL of one flight
      {
        infile >> info.flight_type;
	infile.ignore(100,':');
	infile >> info.fast_pass;
	infile.ignore();
        ++flag;
      }

      info.airport_name = new char[strlen(temp) + 1];
      strcpy(info.airport_name,temp);
      infile >> info.arrival;
      infile.ignore(100,':');
      infile >> info.departure;
      infile.ignore(100,':');
      infile >> info.end_trip;
      infile.ignore(100,':');
      build(i, j);
      delete [] info.airport_name;
      info.airport_name = NULL;

      //Prime the pump
      if (info.end_trip == 'Y') //If the end of the trip we are going
      {
        infile >> info.flight_type;
        infile.ignore(100,':');
        infile >> info.fast_pass;
        infile.ignore(100,':');
      }
      if (info.end_trip == 'N') //If adding on to the flight node.
      {
        infile.get(temp, 50, '\n');
        infile.ignore(100,':');
      }
    }
  }*/
  infile.close();
  infile.clear();
  return 1; //SUCCESS WE HAVE READ
}



//This function takes the data read in from the read function and puts it
//into an array of linear linked lists.
int itinerary::build(int & i, int & j)
{
  flight_node * current;
  int total_time;

  if (j == 0) //Only one the first run through. (for the info before loop).
  {
    ptr[i] = new admin_node;
    ptr[i] -> flight_type = info.flight_type;
    ptr[i] -> fast_pass = info.fast_pass;
 
    current = new flight_node;
    ptr[i] -> head = current;
    current -> name_airport = new char[strlen(info.airport_name) + 1];
    strcpy(current -> name_airport, info.airport_name);
    current -> arrival = info.arrival;
    current -> departure = info.departure;
    total_time = info.departure - info.arrival;
    current -> time_between = total_time;
    temp = current;
    current -> next = NULL;
    ++j;
    return 1;
  }

  if (info.end_trip == 'Y') //New index of the array
  {
    ++i;
    current = NULL;
    ptr[i] -> flight_type = info.flight_type;
    ptr[i] -> fast_pass = info.fast_pass;
    current = new flight_node;
    ptr[i] -> head = current;
    current -> name_airport = new char[strlen(info.airport_name) + 1];
    strcpy(current -> name_airport, info.airport_name);
    current -> arrival = info.arrival;
    current -> departure = info.departure;
    total_time = info.departure - info.arrival;
    current -> time_between = total_time;
    temp = current;
    current -> next = NULL;
    return 1;
  }

  else //adding on to the linear linked list.
  {
    current = temp;
    current -> next = new flight_node;
    current = current -> next;
    current -> name_airport = new char[strlen(info.airport_name) + 1];
    strcpy(current -> name_airport, info.airport_name);
    current -> arrival = info.arrival;
    current -> departure = info.departure;
    total_time = info.departure - info.arrival;
    current -> time_between = total_time;   
    temp = current;
    current -> next = NULL;
  }
  return 1;
}



//A txt file is made to hold the number of trips a person is taking
//The txt file must be manually updated with the number of trips
//to allocate the proper memory for this data sturcture.
int itinerary::count()
{
  ifstream infile;
  int temp = 0;
  infile.open("counter.txt");
  infile >> temp;
  infile.ignore();
  infile.close();
  infile.clear();
  return temp;
}



//displays all trip routes in the database. uses a while loop
//and increments i as both a control variable and for indexing.
int itinerary::display(int size)
{
  int i = 0;
  size = 2;
  while(i <= size - 1)
  {
    flight_node * current = ptr[i] -> head;
    cout << "Flight type: " << ptr[i] -> flight_type << endl
    << "Fast_pass: " << ptr[i] -> fast_pass << endl;
    while (current)
    {
      cout << "Airport: " << current -> name_airport << endl
      << "Arrival time: " << current -> arrival << endl
      << "Departure time: " << current -> departure << endl
      << "Time between flights: " << current -> time_between
      << endl;
      current = current -> next;
    }
    ++i;
  }
  return 1;
}



bool itinerary::compare(int sum, char temp[])
{
  flight_node * current = NULL;
  int i = 0;
  current = ptr[i] -> head;
  while (current -> next)
  {
    if (strcmp(temp, current -> name_airport) == 0)
    {
    }
  }
  return true;
}



//DESTRUCTOR FOR CLASS
itinerary::~itinerary()
{  
  if (ptr)
  {
    destroy(count()); //Deallocats all flight data
    delete [] ptr;
    ptr = NULL;
  }
}



//DESTRUCTOR FOR INFO STRUCT
itinerary_info::~itinerary_info()
{
  flight_type = '\0';
  fast_pass = '\0';
  if (airport_name)
  {
    delete [] airport_name;
    airport_name = NULL;
  }
  arrival = 0;
  departure = 0;
  end_trip = '\0';
}



//DESTRUCTOR FOR FLIGHT STRUCT
flight_node::~flight_node()
{
  if (name_airport)
  {
    delete [] name_airport;
    name_airport = NULL;
  }
  arrival = 0;
  departure = 0;
  time_between = 0;
}



//DESTRUCTOR FOR ADMIN STRUCT
admin_node::~admin_node()
{
  flight_type = '\0';
  fast_pass = '\0';
  if (head)
  {
    delete [] head;
    head = NULL;
  }
}
