#include <cstdlib>
#include <iostream>

using namespace std;

template <class Type> class LinkedList;

template <class Type>
class ListElem {
public:
	ListElem (const Type elem){prev=next=NULL; data=elem;}
public:
	Type data; // the element data
	ListElem *prev; // previous link
	ListElem *next; // next link
};

//---------------------------------------------------------
template <class Type>
class LinkedList {
public:
	LinkedList(){pfirst=plast=NULL;}
	~LinkedList();
	void insertNode (const Type&,int);
	void deleteNode(int);//delete item from the list
	void printall();//print out all items on the screen
	int countitem();//return the number of items in the list
	ListElem<Type> *findmin();//show the min item
	ListElem<Type> *findmax();//show the max item
	ListElem<Type> *find(int);//find an item
protected:
	ListElem<Type> *pfirst; // pfirst element in the list
	ListElem<Type> *plast; // last element in the list
public:
	ListElem<Type> *temp; //for temporary use only
};

//destructor
template <class Type>
LinkedList<Type>::~LinkedList (void)
{
	ListElem<Type> *item;
	ListElem<Type> *next;
	for(item =pfirst; item!= NULL; item= next){
		next = item->next;
		delete item;
	}

}
//insert item

template <class Type>
void LinkedList<Type>::insertNode (const Type &elem,int pos)
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

template <class Type>
ListElem<Type>  *LinkedList<Type>::find(int val){
	ListElem<Type> *tr;
	tr=pfirst;
	if(pfirst!=NULL){

		while(tr!=NULL){
			if(tr->data==val) break; //found the tartget=>stop searching
			else tr=tr->next;//otherwise continue searching
			}


	}
              return tr;
}

template <class Type>
void LinkedList<Type>::deleteNode(int pos){

  int i;
  bool deleted=false;
  if(pfirst!=NULL){ //make sure the list is not empty.
       ListElem<Type> *temp,*del;

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
cout<<"Doubly Linked List Operations Menu\n";
cout<<"=================================\n";
cout<<"1.Add a new item\n";
cout<<"2.Delete an item\n";
cout<<"3.Show number of items\n";
cout<<"4.Show min item\n";
cout<<"5.Show max item\n";
cout<<"6.Find an item\n";
cout<<"7.Show all items\n";
cout<<"8.Exit\n";


}

void select(){
  LinkedList<int> *MyList=new LinkedList<int>();
  int val, pos, ch;
  char yes='y';
  while(yes=='y'){
	showmenu();
    cout<<"Enter your choice:";cin>>ch;
    switch(ch){
        case 1:
  	cout<<"Value:";cin>>val;
	cout<<"Position:";cin>>pos;
	MyList->insertNode(val,pos);
	break;
         case 2:
	cout<<"Position:";cin>>pos;
	MyList->deleteNode(pos);
	break;
        case 3:
	cout<<"Number of items:";cout<<MyList->countitem()<<endl;
	break;
       case 4:
	MyList->temp=MyList->findmin();
	if(MyList->temp!=NULL)
		cout<<"The min item:"<<MyList->temp->data<<endl;
	else cout<<"Not found\n";
	break;
        case 5:
	MyList->temp=MyList->findmax();
	if(MyList->temp!=NULL)
		cout<<"The max item:"<<MyList->temp->data<<endl;
	else cout<<"Not found\n";
	break;
        case 6:
	cout<<"Find what:";
	cin>>val;
	MyList->temp=MyList->find(val);
	if(MyList->temp!=NULL) cout<<"Found:"<<MyList->temp->data<<endl;
	else cout<<"Not found!"<<endl;
	break;
        case 7:
	cout<<"All items:\n";
	MyList->printall();
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


