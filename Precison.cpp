#include <iostream>
using namespace std;


class Node{
public:
  Node (int k){
    key = k;
    next = NULL;
  }
  //accesors & mutators
  void setNext (Node* p) {next = p;}
  void setKey (int k) {key = k;}
  int getKey () {return key;}
  Node* getNext () {return next;}
  void nodePrint(){
    if (next == NULL){
      cout << key;
      if ( key >= 10000 )
	cout << key;
    }
    else if (key < 10)
      cout << "0000" << key;
    else if (key < 100)
      cout << "000" << key;
    else if (key < 1000)
      cout << "00" << key;
    else if (key < 10000)
      cout << "0" << key;
  }
    
private:
  int key;
  Node* next;
};

class List{
private:
  Node* head;
public:
  //constructors for list class
  List (){ head = 0;}
  List(Node* temp){head = temp;}
  List(int k){head = new Node(k);}

  List* copy ()
  {
    if (head == NULL)
      return new List();
    else
      {
	List* temp = new List (head->getKey());
	List* rest = new List (head->getNext());
	temp->head->setNext (rest->copy()->head);
	return temp;
      }
  }

  void insert (int k)
  {
    if (k < 10000)
      Node* temp = new Node(k);
    else{
      int tempk = k % 100000;
      Node* temp = new Node (tempk);
      temp->setNext(head);
      head = temp;
    }
  }

  List* increment ()
  {
    if (head == 0)
      return new List(1);
    else
      {
	if (head->getKey() < 99999)
	  {
	    List* temp = copy();
	    temp->head->setKey(temp->head->getKey() + 1);
	    return temp;
	  }
	else
	  {
	    List* temp = new List(0);
	    List* rest = new List (head->getNext());
	    rest->increment();
	    temp->head->setNext(rest->increment()->head);
	    return temp;
	  }
      }
  }
  
  void print ()
  {
    if (head != NULL)
      {
	List* rest = new List(head->getNext());
	rest->print();
	//cout << rest->head->getKey();
	cout << head->getKey();
	if (head->getNext() != NULL)
	  head->nodePrint();
	else
	  cout << head->getKey();
      }

  }

   List* add (List* in, int carry)
  {
    if (head == NULL && in->head == NULL)
      {
	if (carry == 0)
	  return new List ();
	else
	  return new List(1);
      }
    else if (head == NULL)
      {
	List* result = in->copy();
	if (carry == 0)
	  return result;
	else
	  return result->increment();
      }
    else if (in->head == NULL)
      {
	List* result = copy();
	if (carry == 0)
	  return result;
	else
	  return result->increment();
      }
    else
      {
	int temp = (in->head->getKey() + head->getKey() + carry);
	List* result = new List (temp % 100000);
	List* L1 = new List (in->head->getNext());
	List* L2 = new List (head->getNext());
	List* temp1 = L1->add(L2, temp/100000);
	result->head->setNext(temp1->head);
	return result;
      }
  }

  List* multiply (int x, int carry)
  {
    if (head == NULL)
      if (carry == 0)
	return new List ();
      else
	return new List(carry);
    else{
      List* rest = new List(head->getNext());
      int y = ((head->getKey()) * x + carry);
      int FirstKey = y % 100000;
      int NewCarry = y / 100000;
      List* NewList = rest->multiply(x, NewCarry);
      List* L = new List (FirstKey);
      L->head->setNext(NewList->head);
      return L;
    }
  }

      



};

int main ()
{
  int value = 0;
  int value2 = 0;
  cout << "Enter 2 numbers: " << endl;
  cin >> value >> value2;
  int carry = 0;
  List* L = new List(value);
  //L->insert(value);;
  List* L2 = new List(value2);
  //L2->insert(value2);

  List* add = L->add(L2, carry);
  add->print();
  cout << endl;
  List* multiply = L->multiply(value2, carry);
  multiply->print();
  cout << endl;
  return 0;
}


		   
  
