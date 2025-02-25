#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//CONSOLE INPUT/OUTPUT FUNCTIONS

bool cmp(char* input, const char* checkAgainst){ //simplify input to cstring comparison
  if(!strcasecmp(input,checkAgainst)){
    return true;
  }
  return false;
}

void printErr1(){ //for gibberish text input
  cout << "That is not a valid command. Please refer to the parenthesized commands." << endl << endl;
}

void printErr2(){ //for gibberish text input where int input was expected
  cout << "That is not an int. Please input an int." << endl;
}

int getIntput(){ //Bugfix for infinite loops created by char inputs where int was expected
  int intput;
  cin >> intput; cin.ignore();
  while(cin.fail()){ //Repeatedly asks for int input until a valid one is given
    printErr2();
    cin.clear();
    cin.ignore(1024,'\n');
    cin >> intput; cin.ignore();
  }
  return intput;
}

//HEAP FUNCTIONS

int parent(int position){ //returns parent of a position
  return (position-1)/2;
}

int leftChild(int position){ //returns left child
  return position*2 + 1;
}

int rightChild(int position){ //returns right child
  return position*2 + 2;
}

void sortIndex(int* heap, int originalNode, int index, bool sorted){ //sort a parent index and its children
  int placeholder;
  if(heap[index] < heap[leftChild(index)]){ //swap parent with left and child if needed
    swap(heap[index],heap[leftChild(index)]);
    sorted = false;
  }
  if(heap[index] < heap[rightChild(index)]){
    swap(heap[index],heap[leftChild(index)]);
    sorted = false;
  }
  if(index != 0){ //Move to the parent's parent until the root is reached
    sortIndex(heap,originalNode,parent(index),sorted);
  }else if(sorted){ //Once the root is reached, if sorting might still be necessary, restart recursion from the original node
    sortIndex(heap,originalNode,originalNode,false);
  }
}

void addHeapManual(int* heap, int* index){
  if(*index < 100){ //can only manually add 100 elements
    int ind = *index;
    int value;
    cout << "What is your first parent?" << endl;
    value = getIntput();
    sortIndex(heap,parent(*index),parent(*index),false);
    heap[ind] = value;
    (*index)++;
  }else{
    cout << "The heap is full at the moment. Please try again later." << endl;
  }
  cout << endl;
}

void addHeapFile(int* heap, int* index){
  cout << "How many nodes would you like to add?" << endl;
  int addSize = getIntput();
  if(*index+addSize < 1000){ //prevent the addition of more than 999 nodes in the list (1000 would form an invalid heap)
    int temp;
    fstream n;
    n.open("n.txt",fstream::in);    
    for(int i = 0; i < addSize; i++){
      n >> heap[*index];
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
  cout << endl;
}

void wipeHeap(int* index){ //reset the heap by setting index to 0
  *index = 0;
  cout << "The heap is wiped." << endl << endl;
}

void printHeap(int* heap, int ind, int position){
  if(!ind){
    cout << "The heap is empty." << endl;
  }else{
    if(position < ind){ //print right branch above
      if(rightChild(position) < ind){
	printHeap(heap,ind,rightChild(position));
      }
      int current = position;
      while(current != 0){ //check depth and use it to offset the node print appropriately
	cout << "      ";
	current = parent(current);
      }
      cout << heap[position] << endl; //actual print statement
      if (leftChild(position) < ind){ //print left branch below
	printHeap(heap,ind,leftChild(position));
      }
    }
  } 
}

int main(){
  char* input = new char[10]; //take cstring inputs
  bool running = true; //keep looping the program until it is quit
  int intput; //take int inputs
  int size = 10000; //max heap size
  int* heap = new int[size]; //the actual heap
  int* index = new int; //current heap size, initialized as 0

  cout << endl << "Welcome to Jeep! Your available commands are listed like so (COMMAND or QUIT)" << endl;
  while(true){
    cout << "Would you like to add to the tree, remove its root, or remove it entirely? (PRINT or ADD or ROOT or WIPE or QUIT)" << endl;
    cin.getline(input,20);
    if(cmp(input,"QUIT")){
      cout << endl;
      return 0;
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
  
  delete index;
  delete[] input;
  delete[] heap;
  return 0;
}
