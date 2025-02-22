#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//CONSOLE INPUT/OUTPUT FUNCTIONS

bool cmp(char* input, const char* checkAgainst){
  if(!strcmp(input,(char*)checkAgainst)){
    return true;
  }
  return false;
}

void printErr1(){
  cout << "That is not a valid command. Please refer to the parenthesized commands." << endl << endl;
}

void printErr2(){
  cout << "That is not an int. Please input an int." << endl;
}

int getIntput(){ //Bugfix for infinite loops created by char inputs where int was expected
  int intput;
  cin >> intput; cin.ignore();
  while(cin.fail()){
    printErr2();
    cin.clear();
    cin.ignore(1024,'\n');
    cin >> intput; cin.ignore();
  }
  return intput;
}

//HEAP FUNCTIONS

int parent(int position){
  return (position-1)/2;
}

int leftChild(int position){
  return position*2 + 1;
}

int rightChild(int position){
  return position*2 + 2;
}

void sortIndex(int* heap, int originalNode, int index, bool sorted){ //sort a parent index and its children
  int placeholder;
  if(heap[index] < heap[leftChild(index)]){
    placeholder = heap[index];
    heap[index] = heap[leftChild(index)];
    heap[leftChild(index)] = placeholder;
    sorted = false;
  }
  if(heap[index] < heap[rightChild(index)]){
    placeholder = heap[index];
    heap[index] = heap[rightChild(index)];
    heap[rightChild(index)] = placeholder;
    sorted = false;
  }
  if(index != 0){ //A root would have index 0, and no parents to recurse to
    sortIndex(heap,originalNode,parent(index),sorted);
  }else if(sorted){ //If sorting is unfinished, restart recursion from the original node
    sortIndex(heap,originalNode,originalNode,false);
  }
}

void addHeapManual(int* heap, int* index){
  if(*index < 100){ //can only manually add 100 elements
    int ind = *index;
    int value;
    if(!ind){ //if the current node is 0
      cout << "What is your first parent?" << endl;
      value = getIntput();
      heap[ind] = value;
    }else{//only accept pairs, to maintain heap validity
      cout << "What is the left child?" << endl;
      value = getIntput();
      heap[ind] = value;
      sortIndex(heap,parent(*index),parent(*index),false);
      (*index)++;
      ind = *index;

      cout << "What is the right child?" << endl;
      value = getIntput();
      heap[ind] = value;
      sortIndex(heap,parent(*index),parent(*index),false);//Recursively sort the heap from the added node
    }
    (*index)++;
  }else{
    cout << "The heap is full at the moment. Please try again later." << endl;
  }
  cout << endl;
}

void addHeapFile(int* heap, int* index){
  cout << "How many nodes would you like to add?" << endl;
  int addSize = getIntput();
  while((*index) && (addSize % 2)){ //check if index is not 0 and size is odd
    cout << "You need to add an even number of nodes to maintain heap validity. How many nodes would you like to add?" << endl;
    addSize = getIntput();
  }
  while(!(*index) && !(addSize % 2)){ //check if index is 0 and size is even
    cout << "You need to add an odd number of nodes to maintain heap validity. How many nodes would you like to add?" << endl;
    addSize = getIntput();
  }
  if(*index+addSize < 1000){
    int temp;
    fstream n;
    n.open("n.txt",fstream::in);    
    for(int i = 0; i < addSize; i++){
      n >> heap[*index];
      //      cout << "SETTING " << temp << " AT " << *index << endl;
      sortIndex(heap,parent(*index),parent(*index),false); //Sort the heap from the added node
      (*index)++;
    }
    n.close();
    cout << endl;
  }else{
    cout << "There are not enough numbers in the file n.txt for this operation." << endl << endl;
  }
}

void rootHeap(int* heap, int* index){
  char* input = new char[10];
  int bottomParent = parent(*index);
  cout << "The root is " << heap[0] << endl; //move the last leaf to the root, output the root
  heap[0] = heap[*index-1];
  (*index)--;
  sortIndex(heap,parent(*index),parent(*index),false);
  cout << "Would you like to root your heap again or add a new node? (ROOT or ADD)" << endl; //need to add or subtract one more leaf to maintain heap validity
  cin.getline(input,10);
  if(cmp(input,"ROOT")){
    bottomParent = parent(*index);
    cout << "The root is " << heap[0] << endl;
    heap[0] = heap[*index-1];
    (*index)--;
    sortIndex(heap,parent(*index),parent(*index),false);
  }else if(cmp(input,"ADD")){
    cout << "What is your new last right child?" << endl;
    int value = getIntput();
    heap[*index] = value;
    (*index)++;
    sortIndex(heap,parent(*index-1),parent(*index-1),false);
  }else{
    printErr1();
  }
  cout << endl;
}

void wipeHeap(int* index){ //reset the heap by setting index to 0
  *index = 0;
  cout << "The heap is wiped." << endl << endl;
}

void printHeap(int* heap, int ind, int position){
  if(position < ind){ //print right branch above
    if(rightChild(position) < ind){
      printHeap(heap,ind,rightChild(position));
    }
    int current = position;
    while(current != 0){ //check depth and use it to offset the node print appropriately
      cout << "      ";
      current-=1;
      current/=2;
    }
    cout << heap[position] << endl; //actual print statement
    if (leftChild(position) < ind){ //print left branch below
      printHeap(heap,ind,leftChild(position));
    }
  }
}

int main(){
  char* input = new char[10]; //take cstring inputs
  bool running = true; //keep looping the program until it is quit
  int intput; //take int inputs
  int size = 100; //max heap size
  int* heap = new int[size]; //the actual heap
  int* index = new int; //current heap size, initialized as 0

  cout << endl << "Welcome to Jeep! Your available commands are listed like so (COMMAND or QUIT)" << endl;
  
  while(running){ //basic option dialog
    cout << "Would you like to add to the tree, remove its root, or remove it entirely? (PRINT or ADD or ROOT or WIPE or QUIT)" << endl;
    cin.getline(input,20);
    if(cmp(input,"QUIT")){
      running = false;
    }else if(cmp(input,"ADD")){ //allow for console and file inputss
      cout << endl << "How would you like to input your numbers? (FILE or CONSOLE or QUIT)" << endl;
      cin.getline(input,10);
      if(cmp(input,"QUIT")){
	running = false;
	cout << endl << endl;
      }else if(cmp(input,"COMMAND")){
	cout << "Placeholder Text!" << endl;
      }else if(cmp(input,"FILE")){
	addHeapFile(heap,index);
      }else if(cmp(input,"CONSOLE")){
	addHeapManual(heap,index);	
      }else{
	printErr1();
      }
    }else if(cmp(input,"ROOT")){
      rootHeap(heap,index);
    }else if(cmp(input,"WIPE")){
      wipeHeap(index);
    }else if(cmp(input,"PRINT")){
      printHeap(heap,*index,0);
      cout << endl;      
    }else{
      printErr1();
    }
  }
  
  delete[] input;
  delete[] heap;
  return 0;
}
