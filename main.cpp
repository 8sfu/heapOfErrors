#include <iostream>
#include <cstring>

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

int getIntput(){
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
    //cout << "SWITCHING " << heap[index] << " WITH " << placeholder;
    sorted = false;
  }
  if(heap[index] < heap[rightChild(index)]){
    placeholder = heap[index];
    heap[index] = heap[rightChild(index)];
    heap[rightChild(index)] = placeholder;
    sorted = false;
    //cout << "SWITCHING " << heap[index] << " WITH " << placeholder;
  }
  if(index != 0){ //A root would have index 0, and no parents to recurse to
    sortIndex(heap,originalNode,parent(index),sorted);
  }else if(sorted){ //If sorting is unfinished, restart recursion from the original node
    sortIndex(heap,originalNode,originalNode,false);
  }
}


void addToHeap(int* heap, int* index){
  if(*index < 100){
    int ind = *index;
    int value;
    if(!ind){ //if the current node is 0
      cout << "What is your first parent?" << endl;
      value = getIntput();
      heap[ind] = value;
    }else{ //else only accept two pairs, to maintain heap validity
      cout << "What is the left child?" << endl;
      value = getIntput();
      heap[ind] = value;
      (*index)++;
      ind = *index;
      sortIndex(heap,parent(*index),parent(*index),false);
      
      cout << "What is the right child?" << endl;
      value = getIntput();
      heap[ind] = value;
      
      sortIndex(heap,parent(*index),parent(*index),false); //Recursively sort the heap of size index from node 0
    }
    (*index)++;
  }else{
    cout << "The heap is full at the moment. Please try again later." << endl;
  }
  cout << endl;
}

void printTest(int* heap, int ind){
  for(int i = 0; i < ind; i++){
    cout << i << ": " << heap[i] << endl;
  }
  cout << endl;
}

void rootHeap(int* heap, int* index){
  char* input = new char[10];
  int bottomParent = parent(*index);
  cout << "The root is " << heap[0] << endl;
  cout << "REPLACING " << heap[0] << " WITH " << heap[*index-1] << endl;
  heap[0] = heap[*index-1];
  (*index)--;
  sortIndex(heap,parent(*index),parent(*index),false);
  
  cout << "Would you like to root your heap again? Or add a new node? (ROOT or ADD)" << endl;
  cin.getline(input,10);
  if(cmp(input,"ROOT")){
    bottomParent = parent(*index);
    cout << "The root is " << heap[0] << endl;
    cout << "REPLACING " << heap[0] << " WITH " << heap[*index-1] << endl;
    heap[0] = heap[*index-1];
    (*index)--;
    sortIndex(heap,parent(*index),parent(*index),false);
  }else if(cmp(input,"ADD")){
    cout << "What is your new last right child?" << endl;
    int value = getIntput();
    cout << value << " IS BEING ADDED TO THE HEAP" << endl;
    heap[*index] = value;
    (*index)++;
    cout << "STARTING SORT FROM " << heap[*index] << endl;
    sortIndex(heap,parent(*index-1),parent(*index-1),false);
  }
  cout << endl;
}


void wipeHeap(int* index){
  *index = 0;
  cout << "The heap is wiped." << endl << endl;
}

//MAIN LOGIC

int main(){
  char* input = new char[10];
  bool running = true;
  int intput;
  int size = 100;
  int* heap = new int[size];
  int* index = new int;

  cout << endl << "Welcome to Jeep! Your available commands are listed like so (COMMAND or QUIT)" << endl;
  
  while(running){
    cout << "Would you like to add to the tree, remove its root, or remove it entirely? (PRINT or ADD or ROOT or WIPE or QUIT)" << endl;
    cin.getline(input,20);
    if(cmp(input,"QUIT")){
      running = false;
    }else if(cmp(input,"ADD")){
      cout << endl << "How would you like to input your numbers? (FILE or CONSOLE or QUIT)" << endl;
      cin.getline(input,10);
      if(cmp(input,"QUIT")){
	running = false;
	cout << endl;
      }else if(cmp(input,"COMMAND")){
	cout << "Placeholder Text!" << endl;
      }else if(cmp(input,"FILE")){
	//READ FILE INPUT
      }else if(cmp(input,"CONSOLE")){
	addToHeap(heap,index);	
      }else{
	printErr1();
      }
    }else if(cmp(input,"ROOT")){
      rootHeap(heap,index);
    }else if(cmp(input,"WIPE")){
      wipeHeap(index);
    }else if(cmp(input,"PRINT")){
      printTest(heap,*index);

      
    }else{
      printErr1();
    }
  }
  
  delete[] input;
  delete[] heap;
  return 0;
}
