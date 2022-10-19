/*****************************************************************************
 *
 *  Author:           Bishop Swearingen
 *  Title:            Singly linked list vector implementation
 *  Course:           2143
 *  Semester:         Fall 2022
 *
 *  Description:
 *        Uses a singly linked list as the backend for an STL like "vector"
 *        class definition.
 *
 *  Usage:
 *        Use it like a linked list now. More like a vector next program
 *
 *  Files: main.cpp, outfile.txt
 *****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000 // infinity

using namespace std;

// Node for our linked list
struct Node {
  int data;

  Node *next;

  Node(int x) {
    data = x;
    next = NULL;
  }
};

class MyVector {
private:
  Node *head; // base pointer of list
  Node *tail;

  static ofstream fout;
  string fileName;
  bool sorted;

  /**
   * @brief Private version of inOrder push.
   *
   * @param x
   */
  void _inorderPush(int x) {
    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (curr->data > x) { // loop to find proper location
      prev = curr;
      curr = curr->next;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
  }

public:
  int size;
  /*
  ___ ___  _  _ ___ _____ ___ _   _  ___ _____ ___  ___  ___
 / __/ _ \| \| / __|_   _| _ \ | | |/ __|_   _/ _ \| _ \/ __|
| (_| (_) | .` \__ \ | | |   / |_| | (__  | || (_) |   /\__ \
 \___\___/|_|\_|___/ |_| |_|_\\___/ \___| |_| \___/|_|_\|___/
 =============================================================
*/
  /**
   * @brief Default constructor
   *
   */
  MyVector() { init(); }

  /**
   * @brief Overloaded Constructor
   *
   * @param int   *A - pointer to array
   * @param int   aSize - size of array
   */
  MyVector(int A[], int aSize) {
    init();

    for (int i = 0; i < aSize; i++) {
      pushRear(A[i]);
    }
  }

  /**
   * @brief Overloaded Constructor
   *
   * @param string FileName - file to open and read
   *
   * Assumes infile will contain numbers only delimited by spaces or
   * new lines.
   */
  MyVector(string FileName) {
    init();

    ifstream fin;
    int x = 0;

    fin.open(FileName);
    while (!fin.eof()) {
      fin >> x;
      pushRear(x);
    }
  }

  /**
   * @brief Copy Constructor
   *
   * @param MyVector &other
   */
  MyVector(const MyVector &other) {
    init();

    Node *temp = other.head;

    while (temp) {
      pushRear(temp->data);
      temp = temp->next;
    }
  }

  /**
   * @brief - Initialize the data members so we don't
   *      have duplicate lines in each constructor.
   *
   */
  void init() {
    head = tail = NULL;
    fileName = "";
    size = 0;
    sorted = 0;
  }
  /*
    _____   _____ ___ _    ___   _   ___  ___ ___     ___  ___ ___ ___    _ _____ ___  ___  ___
   / _ \ \ / / __| _ \ |  / _ \ /_\ |   \| __|   \   / _ \| _ \ __| _ \  /_\_   _/ _ \| _ \/ __|
  | (_) \ V /| _||   / |_| (_) / _ \| |) | _|| |) | | (_) |  _/ _||   / / _ \| || (_) |   /\__ \
   \___/ \_/ |___|_|_\____\___/_/ \_\___/|___|___/   \___/|_| |___|_|_\/_/ \_\_| \___/|_|_\|___/
   ==============================================================================================
*/
  
  /*
  Purpose: Treats the vector like an array
  Params: int   : the position in the vector
  Returns: the value at the position
  */
  int &operator[](int num) {
    int x = 0;
    Node *curr = head;
    Node *previous = head;

    while (x < num) {
      previous = curr;
      curr = curr->next;
      x++;
    }
    return curr->data;
  }
  /*
  Purpose: Adds the values of two vectors together
  Params: a vector
  Returns: a new Vector containing the values of two vectors added together
  */

  MyVector operator+(const MyVector &rhs) {

    MyVector newV;
    Node *A;
    Node *B;

    // checks for shorter vector
    if (rhs.size < this->size) {
      A = rhs.head;
      B = this->head;
    } else {
      A = this->head;
      B = rhs.head;
    }

    // loop over shorter list adding both valus together and pushing
    while (A) {
      newV.pushRear(A->data + B->data);
      A = A->next;
      B = B->next;
    }

    // continue adding the longer list values to newV
    while (B) {
      newV.pushRear(B->data);
      B = B->next;
    }

    return newV;
  }
  /*
  Purpose: Subtracts the values of two vectors
  Params: a vector
  Returns: a new Vector containing the values of two vectors subtracted
  */

  MyVector operator-(const MyVector &rhs) {
    MyVector newV;
    Node *A;
    Node *B;

    // checks for shorter vector
    if (rhs.size < this->size) {
      A = rhs.head;
      B = this->head;
    } else {
      A = this->head;
      B = rhs.head;
    }

    // loop over shorter list subtracting both values and pushing
    while (A) {
      if(rhs.size > this->size){
      newV.pushRear(A->data - B->data);
      A = A->next;
      B = B->next;
        }
      else {
      newV.pushRear(B->data - A->data);
      A = A->next;
      B = B->next;
      }
      
    }

    // continue adding the longer list values to newV
    while (B) {
      newV.pushRear(B->data);
      B = B->next;
    }
    return newV;
  }
  /*
    Purpose: Multiplies the values of two vectors together
    Params: a vector
    Returns: a new Vector containing the values of two vectors multiplied
    together
    */

  MyVector operator*(const MyVector &rhs) const {
    MyVector newV;
    Node *A;
    Node *B;
    // checks for shorter vector
    
    if (rhs.size < this->size) {
      A = rhs.head;
      B = this->head;
    } else {
      A = this->head;
      B = rhs.head;
    }

    // loop over shorter list multiplying both values together and pushing
    while (A) {
      newV.pushRear(A->data * B->data);
      A = A->next;
      B = B->next;
    }

    // continue adding the longer list values to newV
    while (B) {
      newV.pushRear(B->data);
      B = B->next;
    }
    return newV;
  }
/*
  Purpose: Divides the values of 2 vectors 
  Params: a vector
  Returns: a new Vector containing the values of two vectors divided
  */
  MyVector operator/(const MyVector &rhs) const {
    MyVector newV;
    Node *A;
    Node *B;
    
    // checks for shorter vector
    if (rhs.size < this->size) {
      A = rhs.head;
      B = this->head;
    } else {
      A = this->head;
      B = rhs.head;
    }

    // loop over shorter list dividing both values and pushing
    while (A) {
      if(rhs.size > this->size){
      newV.pushRear(A->data / B->data);
      A = A->next;
      B = B->next;
        }
      else {
      newV.pushRear(B->data / A->data);
      A = A->next;
      B = B->next;
      }
    }

    // continue adding the longer list values to newV
    while (B) {
      newV.pushRear(B->data);
      B = B->next;
    }

    //
    return newV;
  }
  /*
  Purpose: Compares the values of 2 vectors
  Params: a vector
  Returns: a 1 or a 0 depending on if the vectors are the same
  */
  bool operator==(const MyVector &rhs) {
    MyVector newV;
    Node *A = head;
    Node *B = head;
    while (A) {
      newV.pushRear(A->data);
      A = A->next;
    }
    while (B) {
      newV.pushRear(B->data);
      B = B->next;
    }

    if (A->data == B->data && rhs.size == this->size) {
      return 1;
    }

    else
      return 0;
  }
/*
  Purpose: copies the values of one vector into another
  Params: a vector
  Returns: a vector containing the same values as another vector's values
  */

  MyVector operator=(const MyVector &rhs) {
    
    MyVector newV;
    MyVector newVec;
    Node *A;
    Node *B;
    while (A) {
      newV.pushRear(A->data);
      A = A->next;
    }
    newVec = newV;
    return newVec;
  }

  /*
     __  __ ___ _____ _  _  ___  ___  ___
    |  \/  | __|_   _| || |/ _ \|   \/ __|
    | |\/| | _|  | | | __ | (_) | |) \__ \
    |_|  |_|___| |_| |_||_|\___/|___/|___/
    ======================================
  */

  /**
   * @brief Public version of inOrder push.
   *
   * @param x
   */
  void inorderPush(int x) {
    if (!sorted) {
      sortList();
    }

    if (!head) {
      pushFront(x); // call push front for empty list (or pushRear would work)
    } else if (x < head->data) {
      pushFront(x); // call push front if x is less than head
    } else if (x > tail->data) {
      pushRear(x); // call push rear if x > tail
    } else {
      _inorderPush(x); // call private version of push in order
    }
  }

  /**
   * @brief Sort the current values in the linked list.
   *
   * @returns None
   */
  void sortList() {
    Node *newFront = head;
    while (newFront->next) {
      Node *smallest = newFront;
      Node *current = newFront;
      int minimum = INF;
      while (current) {
        if (current->data < minimum) {
          smallest = current;
          minimum = current->data;
        }
        current = current->next;
      }
      smallest->data = newFront->data;
      newFront->data = minimum;
      newFront = newFront->next;
    }
    sorted = true;
  }

  /**
   * @brief Add value to front of list.
   *
   * @param x
   */
  void pushFront(int x) {
    Node *tempPtr = new Node(x);

    // empty list make head and tail
    // point to new value
    if (!head) {
      head = tail = tempPtr;
      // otherwise adjust head pointer
    } else {
      tempPtr->next = head;
      head = tempPtr;
    }
    size++;
  }

  /**
   * @brief This method loads values from 'other' list in 'this' list.
   *          It loads an array first so we can process the values in
   *          reverse so they end up on 'this' list in the proper order.
   *          If we didn't use the array, we would reverse the values
   *          from the 'other' list.
   *
   * @depends - Uses `pushFront(int)`
   * @param MyVector& other
   * @return None
   */
  void pushFront(const MyVector &other) {
    Node *otherPtr = other.head;         // get copy of other lists head
    int *tempData = new int[other.size]; // allocate memory to hold values

    // load other list into array
    int i = 0;
    while (otherPtr) {
      tempData[i] = otherPtr->data;
      otherPtr = otherPtr->next;
      ++i;
    }

    // process list in reverse in order to keep them
    // in their original order.
    for (int i = other.size - 1; i >= 0; i--) {
      pushFront(tempData[i]);
    }
  }

  /**
   * @brief -  Add 'other' list's values to end of 'this' list.
   * @note - Uses `pushRear(int)`
   * @param MyVector& other
   * @return None
   */
  void pushRear(const MyVector &other) {
    Node *otherPtr = other.head; // get copy of other lists head

    while (otherPtr) { // traverse and add
      pushRear(otherPtr->data);
      otherPtr = otherPtr->next;
    }
  }

  /**
   * @brief Push value onto list at soecified position, if it exists.
   *
   * @param int i - location index
   * @param inr x - value to add
   * @return bool - true add successful / false add failed
   */
  bool pushAt(int i, int x) {
    if (i >= size) {
      return false;
    }

    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (i > 0) { // loop to find proper location
      prev = curr;
      curr = curr->next;
      i--;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
    return true;
  }

  /**
   * @brief - Add value to rear of list
   *
   * @param int x - value to be added
   * @return None
   */
  void pushRear(int x) {
    Node *tempPtr = new Node(x);

    if (!head) {
      head = tail = tempPtr;

    } else {
      tail->next = tempPtr;
      tail = tempPtr;
    }
    size++; // add to size of list
  }

  friend ostream &operator<<(ostream &os, const MyVector &rhs) {
    Node *temp = rhs.head; // temp pointer copies head

    while (temp) { // this loops until temp is NULL
                   // same as `while(temp != NULL)`

      os << temp->data; // print data from Node
      if (temp->next) {
        os << "->";
      }
      temp = temp->next; // move to next Node
    }
    os << endl;
    return os;
  }

  /**
   * @brief Destroy the My Vector object
   *
   */
};

// ofstream MyVector::fout;

int main() {
  int a1[] = {1, 2, 3, 4, 5};
  int a2[] = {10, 20, 30};

  MyVector v1(a1, 5);
  MyVector v2(a2, 3);

  ofstream fout;
  fout.open("output.txt");

  cout << v1[2] << endl;

  v1[4] = 9;

  cout << v1 << endl;

  fout << v1 << endl;

  MyVector v3 = v1 + v2;
  cout << v3 << endl;

  MyVector v4 = v1 - v2;
  cout << v4 << endl;

  MyVector v5 = v2 - v1;
  cout << v5 << endl;

  MyVector v6 = v2 * v1;
  cout << v6 << endl;

  MyVector v7 = v1 * v2;
  cout << v7 << endl;

  MyVector v8 = v1 / v2;
  cout << v8 << endl;

  MyVector v9 = v2 / v1;
  cout << v9 << endl;

  cout << (v2 == v1) << endl;

  MyVector v10 = v1;
  cout << (v10 == v1) << endl;
}
