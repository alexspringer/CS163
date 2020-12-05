//Alex Springer, CS163, 4/27/16, program 2
//This is the main file of the program This program essentially asks
//the user for the number of boxes and then they give information about the
//boxes. This information is stored and a array of LLL and a CLL are created
//from this data.
#include "queue.h"
#include "stack.h"
using namespace std;



int main()
{
  char temp[50]; //Temp to help allocated dynamic memory
  int boxes = 0; //How many boxes will the user add?
  char response = 'z'; //Loop control variable for deleteing (pop /dequeue)
  
  queue location;  //queue variable
  stack s1;  //stack variable
  pod info;  //strut of char * that are info about a box.

  cout << "How many Packages are there today? ";
  cin >> boxes;
  cin.ignore(100,'\n');
   
  for (int i = 0; i < boxes; ++i)
  {

    read_in(info, temp);

    if(location.enqueue(temp))
    {
      cout << "Recipient has been added! " << endl << endl;
    }
    if(s1.push(info, boxes))
    {
      cout << "Data added. " << endl;
    }

    //Delete all the dynamically allocated arrays. If they
    //exist of course.
    delete_dynamic(info);
  }

  s1.display_wrap();
  location.display_wrap();

  //What is on the top of the stack.
  s1.peek(info);
  cout << "Here is the top most box. " << endl
    << "Sender: " << info.sender << endl
    << "Destination: " << info.dest << endl
    << "Size: " << info.size << endl;

  //Allocated again from peek and we need to delete it again.
  delete_dynamic(info);

  
  temp[0] = '\0'; //make sure temp is empty.
  location.peek(temp);
  cout << "The next recipient is: " << temp << endl << endl << endl;
  
  //Pop loop and dequeue!
  while(response != 'n')
  {

    if(s1.pop() && location.dequeue())
    {
      cout << "Dude you're poppin off! -imaqtpie " << endl
      << endl;
    }
    s1.display_wrap();
    cout << "delete again? y/n";
    cin >> response;
  }
   
  return 0;
}



//Reads in data from the user and then dynamically allocates
//Char pointers from struct pod.
void read_in(pod & info, char temp[])
{
  cout << "What is the name of the sender? ";
  cin.get(temp, 50, '\n'); 
  cin.ignore(100,'\n');
  info.sender = new char[strlen(temp) + 1];
  strcpy(info.sender, temp);

  cout << "What is the destination? ";
  cin.get(temp, 50, '\n'); 
  cin.ignore(100,'\n');
  info.dest = new char[strlen(temp) + 1];
  strcpy(info.dest, temp);   

  cout << "What is the size of the package? ";
  cin.get(temp, 50, '\n'); 
  cin.ignore(100,'\n');
  info.size = new char[strlen(temp) + 1];
  strcpy(info.size, temp);

  cout << "Who is the recipient? ";
  cin.get(temp,50,'\n');
  cin.ignore(100,'\n');

  return;
}



//Since this code is needed twice in my main I thought it would
//look cleaner if it was a function called from main. This
//Function just deletes the dynamic data I get from the user.
void delete_dynamic(pod & info)
{
  if (info.sender)
  {
    delete [] info.sender;
    info.sender = NULL;
  }   
  if (info.dest)
  {
    delete [] info.dest;
    info.dest = NULL;
  }
  if(info.size)
  {
    delete [] info.size;
    info.size = NULL;
  }
  return;
}
