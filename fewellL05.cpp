/******************************************
 *                                        * 
 *      Title: Precison Arithmetic        *
 *      File I.D.: fewellL04.cpp          *
 *      Date: 3/13/13                     *
 *                                        *
 * Description: This Program is able to   *
 *   precisely copute the factorial of    *
 *   any number greater than 1 and less   *
 *   less than 1000. It is also able to   *
 *   the value of 2^k + 3^L where k and   *
 *   L are any numbers between 1 and 1000 *
 *****************************************/


#include <iostream>

using namespace std;

class Node {
public:
  //Node constructors
  Node(int x) {
    if (x <= 99999){
      key = x;
      next = NULL;
    }
    else{
      key = x % 1000000;
      Node* temp = new Node(x / 1000000);
      temp->setNext(NULL);
      next = temp;
    }
  }
  //Node assignment and mutators
  void setNext(Node* p) {next = p;}
  void setKey(int k) {key = k;}
  int getKey() { return key;}
  Node* getNext() { return next;}
  //prints the right number of 0's if needed
  void nodePrint(){
    if (next == NULL)
      cout << key;
      
    if (key < 10)
      cout << "0000" << key;
    else if (key < 100)
      cout << "000" << key;
    else if (key < 1000)
      cout << "00" << key;
    else if (key < 10000)
      cout << "0" << key;
    else
      cout << key;
  }

private:
  int key;
  Node* next;
};

class List {
private:
  //List constructors
  Node* head;
public:
  List() {
    head = 0;
  }

  List(Node* p) {
    head = p;
  }

  List(int x) {
    head = new Node(x);
  }
  //Copies one list into another list one node at a time
  List* copy() {
    if (head == NULL)
      return new List();
    else {
      List* temp = new List(head->getKey());
      List* rest = new List(head->getNext());
      temp->head->setNext(rest->copy()->head);
      return temp;
    }
  }

  void insert(int k) {
    // insert k as the first item of the list
    Node* tmp = new Node(k);
    tmp->setNext(head);
    head = tmp;
  }

  //increments a List by one
  List* increment() {
    if (head==0)
      return new List(1);
    else {
      //if head is less then 99999
      //then the first Node just gets incremented
      if (head->getKey() < 99999) {
	List* temp = copy();
	temp->head->setKey(temp->head->getKey()+1);
	return temp;
      }
      else {
	//If its greater than 99999
	//then we need to make a new list and then
	//concatenate the lists together
	List* temp = new List(0);
	List* rest = new List(head->getNext());
	temp->head->setNext(rest->increment()->head);
	return temp;
      }
    }
  }

  List* add(List* in, int carry) {
    //adds two list at a time by 
    //recursively adding each node at a time
    if (head == NULL && in->head == NULL) {
      if (carry == 0) return new List();
      else return new List(1);
    }
    else if (head==NULL) {
      List* result = in->copy();
      if (carry == 0) return result;
      else return result->increment();
    }
    else if (in->head==NULL) {
      List* result = copy();
      if (carry == 0) return result;
      else return result->increment();
    }
    else {
      int temp = (in->head->getKey() + head->getKey() + carry);
      List* result = new List(temp % 100000);
      List* L1 = new List(in->head->getNext());
      List* L2 = new List(head->getNext());
      List* temp1 = L1->add(L2, temp / 100000);
      result->head->setNext(temp1->head);
      return result;
    }
  }

  List* multiply(int x, int carry) {
    // Multiplies any large number you want by a three digit number
    //each Node gets recursively multipled by the integer
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

  List* fact(int n){
    //Finds the factorial of a number
    //by recursively calling the multiply function
    List*temp = new List(1);
    int carry = 0;
    if (head == NULL)
      return new List(1);
    for (int i = 1; i < n + 1; i++)
      temp = temp->multiply(i, carry);
    return temp;
  }


  List* exp(int x, int y){
    //Finds the Exponential value of any number 
    //recursively calls multiply to get the correct value
    int count = y;
    List* temp = new List(x);
    while (count > 1){
      temp = temp->multiply(x, 0);
      count--;
    }
    return temp; 
  }

    void print(){
      //prints the list from the last Node to the first
      if (head != NULL)
	{
	  List* rest = new List (head->getNext());
	  rest->print();
	  if (head->getNext() != NULL)
	    head->nodePrint();
	  else
	    cout << head->getKey();
	}
    }

      
};

int main ()
{
  int value = 0;
  int value2 = 0;
  int value3 = 0;
  int carry = 0;
  cout << "Problem 1: Enter an integer n, 1 <= n <= 999: " << endl;
  cin >> value;

  cout <<"Factorial of " << value << " is..." << endl;
  List* L = new List(value);
  List* fact = L->fact(value);
  fact->print();
  cout << endl;

  cout << "Problem 2: Enter two integers p and q, 1 <= p, q < = 999: " << endl;
  cin >> value2 >> value3;
  List* L2 = new List (value2);
  List* L3 = new List (value3);
  List* twoExp = L2->exp(2, value2);
  List* threeExp = L3->exp(3, value3);
  List* add = twoExp->add(threeExp, carry);
  cout << "2^p + 3^q is..." << endl;
  add->print();
  cout << endl;

  char key;
  cout << "Press any key to continue..." << endl;
  cout << "Or q to exit." << endl;
  cin >> key;
  if (key != 'q')
    main();
  else
    return 0;
}
