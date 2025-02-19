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
  cout << "That is not a valid command. Please refer to the parenthesized commands." << endl;
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

void addToHeap(int value, int* heap, int* size){
  if(!size){
    
  }
  
  return;
}

//MAIN LOGIC

int main(){
  char* input = new char[10];
  bool running = true;
  int intput;
  int* heap = new int[100];
  int* size = new int;
  
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
      }else if(cmp(input,"COMMAND")){
	cout << "Placeholder Text!" << endl;
      }else if(cmp(input,"FILE")){
	//READ FILE INPUT
      }else if(cmp(input,"CONSOLE")){
	cout << "Please enter a number." << endl;
	intput = getIntput();

	
	//ADD INT AND SORT HEAP
      }else{
	printErr1();
      }
    }else if(cmp(input,"ROOT")){
      //Get root
    }else if(cmp(input,"WIPE")){
      //Wipe tree completely
    }else if(cmp(input,"PRINT")){
      for(int i = 0; i < 100; i++){
	cout << i+1 << ": " << heap[i] << endl;
      }

      
    }else{
      printErr1();
    }
  }
  
  delete[] input;
  delete[] heap;
  return 0;
}
