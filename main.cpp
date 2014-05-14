#include <cstdlib>
#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

typedef class flight_schedule * link;

class flight_schedule{
public:
	flight_schedule();
    // Flight data
	int flight;
	char city[30];
	int time;
	int gate;
	char remark[15];  // Flight status
	link next;        // pointer to next element
	link back;        // pointer to previous element

};

flight_schedule::flight_schedule()
{
	flight = 0;
	city[30] = {0};
	time = 0;
	gate = 0;
	remark[15] = {0};
	next = 0;
	back = 0;
}

class airport {
public:
	airport(){firstptr=lastptr=NULL;}
	~airport();
	void insertFlight (link);
	void deleteFlight(int);//delete item from the list
	void printall();//print out all items on the screen
	int countitem();//return the number of items in the list
	link findmin();//show the min item
	link findmax();//show the max item
	link find(int);//find an item
protected:
	link firstptr; // firstptr element in the list
	link lastptr; // last element in the list
public:
	link temp; //for temporary use only
};

//destructor
airport::~airport (void)
{
	link item;
	link next;
	for(item =firstptr; item!= NULL; item= next){
		next = item->next;
		delete item;
	}

}
//insert item

void airport::insertFlight (link myFlight)
{
  //new element to be inserted
  bool inserted=false;
  myFlight->next=0; //The next link of the item is null.
  lastptr->next=myFlight;
  myFlight->back=lastptr;
  lastptr=myFlight;
  inserted=true;
  if(inserted!=false) cout<<"Inserted\n";
}

//Print out all items on the screen
void printFlight(link x)
{
	cout << std::left;
	cout << " | " << std::setw(6) << x->flight
		 << " | " << std::setw(30) << x->city
		 << " | " << std::setw(10) << x->time
		 << " | " << std::setw(6) << x->gate
		 << " | " << std::setw(15) << x->remark
		 << " | " << endl;
}

void airport::printall()
{
  link i;
  i = firstptr;
  if(firstptr!=NULL)
  {
      while(i!=NULL)
      {
    		cout << " | " << std::setw(6) << "Flight"
    			 << " | " << std::setw(30) << "City"
    			 << " | " << std::setw(10) << "Departure"
    			 << " | " << std::setw(6) << "Gate"
    			 << " | " << std::setw(15) << "Status"
    			 << " | " << endl;
            printFlight(i);
            i=i->next;
      }
  }
  else cout<<"This is no item.\n";

}

int airport::countitem()
{
  link i;
  int t=0;
  i=firstptr;
  while(i!=NULL){
      t=t+1;
      i=i->next;

     }

  return t;

}

link airport::findmin(){
	link min,tr;
	min=firstptr;
	tr=firstptr;
	if(firstptr!=NULL)
	{
		while(tr!=NULL)
		{
			if(tr->time < min->time)
				min=tr;
			tr=tr->next;
		}
		return min;
	}
	else return NULL;//empty list

}

link airport::findmax(){
	link max,tr;
	max=firstptr;
	tr=firstptr;
	if(firstptr!=NULL)
	{
		while(tr!=NULL){
			if(tr->time > max->time)
				max=tr;
			tr=tr->next;
		}
		return max;
	}
	else
		return NULL;//empty list
}

link airport::find(int val){
	link tr;
	tr=firstptr;
	if(firstptr!=NULL)
	{
		while(tr!=NULL)
		{
			if(tr->flight == val)
				break; //found the tartget=>stop searching
			else tr=tr->next;//otherwise continue searching
		}
	}
	return tr;
}

void airport::deleteFlight(int pos){

  int i;
  bool deleted=false;
  if(firstptr!=NULL)
  {    //make sure the list is not empty.
	  link temp;
      if(pos==1)
      {//delete the first item
    	  if(countitem()==1){ //The list contains only one item
    	  firstptr=NULL;
    	  lastptr=NULL;
    	  deleted=true;
      }
    	  else
    	  {  //The list contains more than one item
    		  temp=firstptr;
    		  firstptr=firstptr->next;
    		  firstptr->back=NULL;
    		  temp=NULL;
    		  deleted=true;
    	  }
      }
      else if(pos>1 && pos<=countitem())
      {//delete middle item
      	 temp=firstptr;
      	 for(i=1;i<pos;i=i+1)
      	 {
      		 temp=temp->next;
      	 }
      	 if(temp->next==NULL)
      	 {
      		 lastptr=temp->back;
      		 lastptr->next=NULL;
      	 }
       	 else
       	 {
       		 temp->back->next=temp->next;
       		 temp->next->back=temp->back;
       	 }
    	 temp=NULL;
    	 deleted=true;
      }
      else cout<<"Invalid position!\n";
  }
  else cout<<"No item found\n";
  if(deleted!=false)
	  cout<<"Deleted\n";
}

void showmenu(){

cout<<"=================================\n";
cout<<"        Airport Menu\n";
cout<<"=================================\n";
cout<<"1.Add a new flight\n";
cout<<"2.Delete a flight\n";
cout<<"3.Show number of flights\n";
cout<<"4.Show earliest flight\n";
cout<<"5.Show latest flight\n";
cout<<"6.Find a flight\n";
cout<<"7.Show all flights\n";
cout<<"8.Exit\n";


}

void select(airport* myAirport)
{
  int val, flightnum, ch;
  char yes='y';
  while(yes=='y'){
	showmenu();
    cout<<"Enter your choice:";
    cin>>ch;
    switch(ch){
        case 1:
        {
        	link newFlight = new flight_schedule();
          	cout<<"Flight Number? ";
			cin >> newFlight->flight;
			cout<<"Destination city? ";
			cin>> newFlight->city;
			cout<<"Departure time? ";
			cin>> newFlight->time;
			cout<<"Gate number? ";
			cin>> newFlight->gate;
			cout<<"Status of flight? ";
			cin>>newFlight->remark;
			myAirport->insertFlight(newFlight);
        }
			break;
		case 2:
			cout<<"Flight number to delete? ";
			cin>>flightnum;
			myAirport->deleteFlight(flightnum);
			break;
        case 3:
        	cout<<"Number of flights: "
        	    << myAirport->countitem() << endl;
        	break;
        case 4:
        	myAirport->temp = myAirport->findmin();
        	if(myAirport->temp!=NULL)
        		cout << "The earliest flight:" << myAirport->temp->flight <<endl;
        	else
        		cout<<"Not found\n";
        	break;
        case 5:
        	myAirport->temp=myAirport->findmax();
        	if(myAirport->temp!=NULL)
        		cout<<"The latest flight is:"
        		    << myAirport->temp->flight << endl;
        	else
        		cout << "Not found.\n";
        	break;
        case 6:
        	cout<<"Find what:";
        	cin>>val;
        	myAirport->temp = myAirport->find(val);
        	if(myAirport->temp!=NULL)
        		cout << "Found:" << myAirport->temp->flight << endl;
        	else
        		cout<<"Not found!"<<endl;
        	break;
        case 7:
        	cout<<"All items:\n";
        	myAirport->printall();
	break;
        case 8: exit(0);

        default: cout<<"Invalid choice\n";

    }
      cout<<"Continue?y/n:";cin>>yes;
  }

}


int main()

{
	airport* myAirport;
	myAirport = new airport();
 	select(myAirport);
 	return 0;
}


