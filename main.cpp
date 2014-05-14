#include <cstdlib>
#include <iostream>

using namespace std;

typedef flight_schedule* link;
//template <class Type> class LinkedList;

//template <class Type>
class flight_schedule {
//class ListElem {
//public:
//	flight_schedule () {prev=next=NULL;}
//	ListElem (const Type elem){prev=next=NULL; data=elem;}
public:
	struct data    // Flight data
	{
		int flight_num;
		char city[30];
		int time;
		int gate;
		char remark[15];  // Flight status
		link next;        // pointer to next element
		link back;        // pointer to previous element
	};
};

flight_schedule::flight_schedule( int in_flight, char in_city[30], int in_time, int in_gate, char in_remark[15])
{
	data.flight_num = in_flight;
	data.city = in_city;
	data.time = in_time;
	data.gate = in_gate;
	data.remark = in_remark;
	data.first = data.last = NULL;
}

//---------------------------------------------------------
//template <class Type>
class airport {
public:
	airport(){pfirst=plast=NULL;}
	~airport();
	void insertFlight (const Type&,int);
	void deleteFlight(int);//delete item from the list
	void printall();//print out all items on the screen
	int countitem();//return the number of items in the list
	link findmin();//show the min item
	link findmax();//show the max item
	link find(int);//find an item
protected:
	link firstptr; // pfirst element in the list
	link lastptr; // last element in the list
public:
	link temp; //for temporary use only
};

//destructor
airport::~airport (void)
{
	link item;
	link next;
	for(item =pfirst; item!= NULL; item= next){
		next = item->next;
		delete item;
	}

}
//insert item

void airport::insertFlight (const Type &elem,int pos)
{
  ListElem<Type> *item = new ListElem<Type>(elem);//new element to be inserted
  bool inserted=false;
  //empty list
  if(pfirst==NULL && plast==NULL){
    item->prev=item->next=NULL;
    pfirst=item;
    plast=item;
    inserted=true;
}
//insert new item at the beginning of the list
else if(pos==1)
  {
     item->next=pfirst;
     item->prev=NULL;
     pfirst=item;
     inserted=true;
   }
//insert new item between items
else if(pos>1 && pos<=countitem()){
     ListElem<Type> *ta;
     ta=pfirst;
     for(int t=1;t<pos;t=t+1){ta=ta->next;} //move to the insertion point
     item->next=ta;
     item->prev=ta->prev;
     ta->prev->next=item;
     ta->prev=item;
     inserted=true;
   }
//insert new item at the end of the list
else if(pos==countitem()+1){

    item->next=NULL; //The next link of the item is null.
    plast->next=item;
    item->prev=plast;
    plast=item;
    inserted=true;

   }
//show message if position is not valid
 else cout<<"Invalid position! Position must be between 1 and "<<countitem()+2<<"\n";

 if(inserted!=false) cout<<"Inserted\n";
}

//Print out all items on the screen

template <class Type>
void LinkedList<Type>::printall()
{
  ListElem<Type> *i;
  i=pfirst;
  if(pfirst!=NULL){
      while(i!=NULL){
            cout<<i->data<<endl;
            i=i->next;
      }
  }
  else cout<<"This is no item.\n";

}

template <class Type>
int LinkedList<Type>::countitem()
{
  ListElem<Type> *i;
  int t=0;
  i=pfirst;
  while(i!=NULL){
      t=t+1;
      i=i->next;

     }

  return t;

}

template <class Type>
ListElem<Type>  *LinkedList<Type>::findmin(){
	ListElem<Type> *min,*tr;
	min=pfirst;
	tr=pfirst;
	if(pfirst!=NULL){

		while(tr!=NULL){
			if(tr->data<min->data) min=tr;
			tr=tr->next;
		}
		return min;
                  }
	else return NULL;//empty list

}

template <class Type>
ListElem<Type> * LinkedList<Type>::findmax(){
	ListElem<Type> *max,*tr;
	max=pfirst;
	tr=pfirst;
	if(pfirst!=NULL){

		while(tr!=NULL){
			if(tr->data>max->data) max=tr;
			tr=tr->next;
		}
		return max;
                  }
	else return NULL;//empty list

}

link  airport::find(int val){
	link tr;
	tr=pfirst;
	if(pfirst!=NULL){

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
  if(pfirst!=NULL){    //make sure the list is not empty.
       link temp,del;

       if(pos==1){//delete the first item
           if(countitem()==1){ //The list contains only one item
    	pfirst=NULL;
    	plast=NULL;
   	deleted=true;
                    }
       else{ //The list contains more than one item
    	 temp=pfirst;
 	 pfirst=pfirst->next;
 	 pfirst->prev=NULL;
  	 temp=NULL;
   	 deleted=true;
                   }

         }

     else if(pos>1 && pos<=countitem()){//delete middle item
      	 temp=pfirst;
      	 for(i=1;i<pos;i=i+1){temp=temp->next;}
      	 if(temp->next==NULL) {plast=temp->prev;plast->next=NULL;}
       	 else{
		 temp->prev->next=temp->next;
    		 temp->next->prev=temp->prev;

		}
    	 temp=NULL;
    	 deleted=true;
    	 }


     else cout<<"Invalid position!\n";

}

  else cout<<"No item found\n";

  if(deleted!=false)cout<<"Deleted\n";

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

void select(){
  airport myAirport = new airport();
  int val, pos, ch;
  char yes='y';
  while(yes=='y'){
	showmenu();
    cout<<"Enter your choice:";cin>>ch;
    switch(ch){
        case 1:
  	cout<<"Value:";
  	cin>>val;
	cout<<"Position:";
	cin>>pos;
	myAirport->insertNode(val,pos);
	break;
         case 2:
	cout<<"Position:";
	cin>>pos;
	myAirport->deleteFlight(pos);
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
 	select();
 	return 0;
}


