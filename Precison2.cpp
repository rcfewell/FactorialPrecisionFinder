#include <iostream>

using namespace std;

class Node {
public:
  Node(int x) {
    key = x;
    next = NULL;
  }
  void setNext(Node* p) {next = p;}
  void setKey(int k) {key = k;}
  int getKey() { return key;}
  Node* getNext() { return next;}
private:
  int key;
  Node* next;
};

class List {
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

  List* increment() {
    if (head==0)
      return new List(1);
    else {
      if (head->getKey() < 99999) {
	List* temp = copy();
	temp->head->setKey(temp->head->getKey()+1);
	return temp;
      }
      else {
	List* temp = new List(0);
	List* rest = new List(head->getNext());
	temp->head->setNext(rest->increment()->head);
	return temp;
      }
    }
  }

  List* add(List* in, int carry) {
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
      List* result = new List(temp%100000);
      List* L1 = new List(in->head->getNext());
      List* L2 = new List(head->getNext());
      List* temp1 = L1->add(L2, temp/100000);
      result->head->setNext(temp1->head);
      return result;
    }
  }

  List* multiply(int x, int carry) {
    // to be implemented

  }

  List* fact(int n) {
    // to be implemented
  }

  List* exp1(int base, int exponent) {
    // to be implemented
  }

  void print() {
    // to be implemented
  }

private:
  Node* head;
};

int main() {
  // create a simple interface to solve the two problems
  // first get a number n, compute n! and display. Then ask for two numbers n and m and
  // compute 2^n + 3^m and display the result.
  List* A = new List(7);
  List* B = new List (8);
  int carry = 0;
  List::add (A, carry);
  return 0;
};
