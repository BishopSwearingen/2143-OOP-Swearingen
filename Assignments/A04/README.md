/*
 
  $$$$$$\   $$$$$$\  $$\   $$\                             
 $$  __$$\ $$$ __$$\ $$ |  $$ |                            
 $$ /  $$ |$$$$\ $$ |$$ |  $$ |                            
 $$$$$$$$ |$$\$$\$$ |$$$$$$$$ |                            
 $$  __$$ |$$ \$$$$ |\_____$$ |                            
 $$ |  $$ |$$ |\$$$ |      $$ |                            
 $$ |  $$ |\$$$$$$  /      $$ |                            
 \__|  \__| \______/       \__|                            
                                                           
                                                           
                                                           
  $$$$$$\    $$\ $$\   $$\  $$$$$$\                        
 $$  __$$\ $$$$ |$$ |  $$ |$$ ___$$\                       
 \__/  $$ |\_$$ |$$ |  $$ |\_/   $$ |                      
  $$$$$$  |  $$ |$$$$$$$$ |  $$$$$ /                       
 $$  ____/   $$ |\_____$$ |  \___$$\                       
 $$ |        $$ |      $$ |$$\   $$ |                      
 $$$$$$$$\ $$$$$$\     $$ |\$$$$$$  |                      
 \________|\______|    \__| \______/                       
                                                           
                                                           
                                                           
 $$$$$$$\  $$$$$$\  $$$$$$\  $$\   $$\  $$$$$$\  $$$$$$$\  
 $$  __$$\ \_$$  _|$$  __$$\ $$ |  $$ |$$  __$$\ $$  __$$\ 
 $$ |  $$ |  $$ |  $$ /  \__|$$ |  $$ |$$ /  $$ |$$ |  $$ |
 $$$$$$$\ |  $$ |  \$$$$$$\  $$$$$$$$ |$$ |  $$ |$$$$$$$  |
 $$  __$$\   $$ |   \____$$\ $$  __$$ |$$ |  $$ |$$  ____/ 
 $$ |  $$ |  $$ |  $$\   $$ |$$ |  $$ |$$ |  $$ |$$ |      
 $$$$$$$  |$$$$$$\ \$$$$$$  |$$ |  $$ | $$$$$$  |$$ |      
 \_______/ \______| \______/ \__|  \__| \______/ \__|      
                                                           
                                                           
                                                           
 
*/                                                         
/*****************************************************************************
*                    
*  Author:           Bishop Swearingen
*  Email:            bmswearingen0405@my.msutexas.edu
*  Label:            A04
*  Title:            Basic Project Organization
*  Course:           2143 OOP
*  Semester:         Fall 2022
* 
*  Description:
*        This program is used for practice for commenting on programs.
* 
*  Files:            main.cpp   :driver program
*****************************************************************************/

#include <iostream>

using namespace std;

/**
*CircularArrayQue
*
*Description:
    This class creates a circular array that allows items to pushed and popped onto the queue.
*
*Public Methods:
*               CircularArrayQue()
*               CircularArrayQue(int size)
*       void    Push
*       int     Pop
*
*Private Methods
*       void    init(int size= 0)
*       void    Full()
*
*Usage:
*
*       CircularArrayQue()              //Creates a new Array Queue of the size of 10
*       CircularArrayQue(int size)      //Creates a new Array Queue 
*       Push (int item)                 //Adds a new value on to the queue
*       Pop()                           //Takes a value off of the queue
*       
*/  
 

class CircularArrayQue {
private:
    int *Container;     //Pointer to the Array Queue
    int Front;          //Front of the Queue
    int Rear;           //Back of the Queue
    int QueSize;        // items in the Queue
    int CurrentSize;    //Size of the Queue
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }
/**
     * Public : Push
     * 
     * Description:
     *      Pushes an integer to the rear of the queue.
     * 
     * Params:
     *      int     :  item that user creates
     * 
     * Returns:
     *      Nothing
     */
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }
/**
     * Public : Pop
     * 
     * Description:
     *      Takes a value off the front of the queue
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      temp        : a value that goes on the front of the queue
     */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}
