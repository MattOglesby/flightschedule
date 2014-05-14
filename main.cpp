#include <cstdlib>
#include <iostream>
#include <string.h>

using namespace std;

typedef class flight_schedule * link;

class flight_schedule {
public:
	flight_schedule (int, char* , int, int, char* , int);
    // Flight data
	int flight_num;
	char city[30];
	int time;
	int gate;
	char remark[15];  // Flight status
	link next;        // pointer to next element
	link back;        // pointer to previous element

};

flight_schedule::flight_schedule(int in_flight, char in_city[30], int in_time, int in_gate, char in_remark[15])
{
	flight_num = in_flight;
	strcpy(city,in_city);
	time = in_time;
	gate = in_gate;
	strcpy(remark,in_remark);
	next = back = NULL;
}

//---------------------------------------------------------
//template <class Type>
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
  link item = new link(elem);//new element to be inserted
  bool inserted=false;
  item->next=NULL; //The next link of the item is null.
  lastptr->next=item;
  item->back=lastptr;
  lastptr=item;
  inserted=true;
  if(inserted!=false) cout<<"Inserted\n";
}

//Print out all items on the screen

void airport::printall()
{
  link i;
  i=firstptr;
  if(firstptr!=NULL){
      while(i!=NULL){
            cout<<i->data<<endl;
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
	if(firstptr!=NULL){

		while(tr!=NULL){
			if(tr->data<min->data) min=tr;
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
	if(firstptr!=NULL){

		while(tr!=NULL){
			if(tr->data>max->data) max=tr;
			tr=tr->next;
		}
		return max;
                  }
	else return NULL;//empty list

}

link airport::find(int val){
	link tr;
	tr=firstptr;
	if(firstptr!=NULL){

		while(tr!=NULL){
			if(tr->data==val) break; //found the tartget=>stop searching
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
    		  firstptr->prev=NULL;
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
      		 lastptr=temp->prev;
      		 lastptr->next=NULL;
      	 }
       	 else
       	 {
       		 temp->prev->next=temp->next;
       		 temp->next->prev=temp->prev;
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

void select(airport myAirport)
{
  int val, flightnum, ch;
  char yes='y';
  while(yes=='y'){
	showmenu();
    cout<<"Enter your choice:";
    cin>>ch;
    switch(ch){
        case 1:
        	link newFlight;
        	cout<<"Flight Number? ";
			cin >> newFlight->flight_num;
			cout<<"Destination city? ";
			cin>> newFlight->city;
			cout<<"Departure time? ";
			cin>> newFlight->time;
			cout<<"Gate number? ";
			cin>> newFlight->gate;
			cout<<"Status of flight? ";
			cin>>newFlight->remark;
			myAirport.insertFlight(newFlight);
			break;
		case 2:
	cout<<"Flight number to delete? ";
	cin>>flightnum;
	myAirport.deleteFlight(flightnum);
	break;
        case 3:
	cout<<"Number of items:";cout<<myAirport->countitem()<<endl;
	break;
       case 4:
	myAirport->temp=myAirport->findmin();
	if(myAirport->temp!=NULL)
		cout<<"The min item:"<<myAirport->temp->data<<endl;
	else cout<<"Not found\n";
	break;
        case 5:
	myAirport->temp=myAirport->findmax();
	if(myAirport->temp!=NULL)
		cout<<"The max item:"<<myAirport->temp->data<<endl;
	else cout<<"Not found\n";
	break;
        case 6:
	cout<<"Find what:";
	cin>>val;
	myAirport->temp=myAirport->find(val);
	if(myAirport->temp!=NULL) cout<<"Found:"<<myAirport->temp->data<<endl;
	else cout<<"Not found!"<<endl;
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
	airport myAirport = new airport();
 	select(myAirport);
 	return 0;
}


