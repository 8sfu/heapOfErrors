#include <iostream>
#include <cstring>

using namespace std;

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

int main(){
  char* input = new char[10];
  bool running = true;
  int intput;
  
  cout << "Welcome to Jeep! Your available commands are listed like so (COMMAND or QUIT)" << endl;
  
  while(running){
    cout << "Would you like to add to the tree, remove its root, or remove it entirely? (ADD or ROOT or WIPE or QUIT)" << endl;
    cin.getline(input,20);
    if(cmp(input,"ADD")){
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
    }else{
      printErr1();
    }
  }

  delete[] input;
  return 0;
}
