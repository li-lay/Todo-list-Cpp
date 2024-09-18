// To-do list in C++ with class
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

// Check platforms
#ifdef _WIN32
#define CLEAR_SCREEN "cls" // window
#else
#define CLEAR_SCREEN "clear" // (mac, linux)
#endif

class Todo {
  private:
    struct tasks
    {
      int id;
      string task;
    };
    int ID = 0; // IDs
    bool completed; // completion

  public:

    void clearScreen() {
      system(CLEAR_SCREEN);
    }

    void logo() {
      cout << "#==============================#\n";
      cout << "|          Todo lists          |\n";
      cout << "#==============================#\n";
    }

    void mainMenu() {
      cout << "\n#==============================#\n";
      cout << "|                              |\n";
      cout << "|      [1] Add a new task      |\n";
      cout << "|      [2] Display tasks       |\n";
      cout << "|      [3] Search task         |\n";
      cout << "|      [4] Delete a task       |\n";
      cout << "|      [5] About us            |\n";
      cout << "|      [0] Exit                |\n";
      cout << "|                              |\n";
      cout << "#==============================#\n";
    }

    void about() {
      clearScreen();
      cout << "#==============================#\n";
      cout << "|                              |\n";
      cout << "|            Team 6            |\n";
      cout << "|                              |\n";
      cout << "|        1. Hun LimHeng        |\n";
      cout << "|        2.                    |\n";
      cout << "|        3. Chhou Lilay        |\n";
      cout << "|                              |\n";
      cout << "#==============================#\n";
    }

    void setId(int id) {
      ID = id;
    }

    void print(tasks s) {
      cout << " [" << s.id << "] " << s.task << endl;
    }

    void addTask() {
      clearScreen();
      logo();
      tasks new_task;
      cout << "Enter new task: ";
      cin.get();
      getline(cin, new_task.task);
      ID++;

      ofstream write;
      write.open("todo.txt", ios::app);
      write << "\n" << ID;
      write << "\n" << new_task.task ;
      write.close();

      write.open("id.txt");
      write << ID;
      write.close();

    char ch;
    cout<<"\nDo you want to add more task? y/n: ";
    cin>> ch;

    if(ch == 'y'){
        addTask();
    }
    else{
      clearScreen();
      cout << "\n!!!Task has been added successfully!!!\n\n";
      return;
    }
  }
    void readTask() {
      clearScreen();
      logo();
      tasks read_task;
      ifstream read;
      read.open("todo.txt");
      cout << " Your current tasks:\n\n";

      while (!read.eof()) {
        read >> read_task.id;
        read.ignore();
        getline(read, read_task.task);
        print(read_task);
      }
      read.close();
      }

    int searchTask() {
      clearScreen();
      logo();
      int id;
      cout << "Enter task id: ";
      cin >> id;
      tasks search_task;
      ifstream read;
      read.open("todo.txt");

      while (!read.eof()) {
        read >> search_task.id;
        read.ignore();
        getline(read, search_task.task);
        if (search_task.id == id) {
            print(search_task);
            return id;
        }
    }
    }

    void deleteTask() {
      clearScreen();
      logo();
      int id = searchTask();
      char opt;
      cout << "Delete this task? (y/n): ";
      cin >> opt;
      if (opt == 'y') {
        tasks delete_task;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");

        while (!read.eof()) {
          read >> delete_task.id;
          read.ignore();
          getline(read, delete_task.task);
          if (delete_task.id != id) {
            tempFile << "\n" << delete_task.id;
            tempFile << "\n" << delete_task.task;
          }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\nTask deleted successfully\n\n";
      } 
      else {
        cout << "\nDeletion cancelled!\n";
      }
    }
};

int main() {
  Todo app;

  ifstream read;
  read.open("id.txt"); // read id.txt to ID
  if (!read.fail()) {
    int i;
    read >> i;
    app.setId(i);
  }
  else {
    app.setId(0);
  }
  read.close();

  int option = 1;
  app.logo();

  do
  {
    app.mainMenu();

    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 0:
      app.clearScreen();
      return 0;
      break;
    case 1:
      app.addTask();
      break;
    case 2:
      app.readTask();
      break;
    case 3:
      app.searchTask();
      break;
    case 4:
      app.deleteTask();
      break;
    case 5:
      app.about();
      break;

    default:
      app.clearScreen();
      cout << "\n!!!Please enter valid options [0-4]!!!\n\n";
      break;
    }
  } while (option != 0);

  return 0;
}