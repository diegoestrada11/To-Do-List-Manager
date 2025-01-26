#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Represents a task in the to-do list
class Task {
public:
   string description;
   bool completed;

   // Constructor to set task description and mark it as not completed
   Task(string desc) : description(desc), completed(false) {}

   // Marks the task as completed
   void markCompleted() {
      completed = true;
   }
};

// Manages the to-do list
class ToDoList {
private:
   vector<Task> tasks; // Stores a list of tasks

public:
   // Loads tasks from a file
   void loadFromFile(const string& filename) {
      ifstream file(filename);
      if (file.is_open()) {
         string desc;
         bool completed;
         while (getline(file, desc, ',') && file >> completed) {
            file.ignore(); // Ignore the newline character after the bool
            Task task(desc);
            task.completed = completed;
            tasks.push_back(task);
         }
         file.close();
         cout << "Tasks loaded from " << filename << " successfully.\n";
      }
      else {
         cout << "Error opening file.\n";
      }
   }

   // Adds a new task to the list
   void addTask(const string& desc) {
      tasks.push_back(Task(desc));
   }

   // Removes a task from the list by index
   void removeTask(int index) {
      if (index >= 0 && index < tasks.size()) {
         tasks.erase(tasks.begin() + index);
         cout << "Task removed.\n";
      }
      else {
         cout << "Invalid task number.\n";
      }
   }

   // Marks a task as completed by index
   void markTaskCompleted(int index) {
      if (index >= 0 && index < tasks.size()) {
         tasks[index].markCompleted();
         cout << "Task marked as completed.\n";
      }
      else {
         cout << "Invalid task number.\n";
      }
   }

   // Displays all tasks in the list
   void displayTasks() const {
      if (tasks.empty()) {
         cout << "No tasks in the list.\n";
         return;
      }
      for (size_t i = 0; i < tasks.size(); ++i) {
         cout << i + 1 << ". " << tasks[i].description
            << (tasks[i].completed ? " [Completed]" : " [Pending]") << endl;
      }
   }

   // Saves all tasks to a file
   void saveToFile(const string& filename) const {
      ofstream file(filename);
      if (file.is_open()) {
         for (const auto& task : tasks) {
            file << task.description << "," << task.completed << endl;
         }
         file.close();
         cout << "Tasks saved to " << filename << " successfully.\n";
      }
      else {
         cout << "Error opening file.\n";
      }
   }
};

int main() {
   ToDoList myList; // Creates a to-do list manager
   myList.loadFromFile("tasks.txt"); // Load existing tasks from file

   int choice; // Stores user's menu choice
   string desc; // Stores task description
   int index; // Stores task number

   do {
      // Display menu options
      cout << "\n=====================\n";
      cout << "To-Do List Manager\n";
      cout << "1. Add Task\n";
      cout << "2. Remove Task\n";
      cout << "3. Mark Task Completed\n";
      cout << "4. View Tasks\n";
      cout << "5. Save to File\n";
      cout << "6. Exit\n";
      cout << "Enter your choice: ";
      cin >> choice;
      cin.ignore();

      // Perform action based on user choice
      switch (choice) {
      case 1:
         cout << "Enter task description: ";
         getline(cin, desc);
         myList.addTask(desc);
         break;
      case 2:
         cout << "Enter task number to remove: ";
         cin >> index;
         myList.removeTask(index - 1);
         break;
      case 3:
         cout << "Enter task number to mark completed: ";
         cin >> index;
         myList.markTaskCompleted(index - 1);
         break;
      case 4:
         myList.displayTasks();
         break;
      case 5:
         myList.saveToFile("tasks.txt");
         break;
      case 6:
         myList.saveToFile("tasks.txt"); // Save tasks on exit
         cout << "Exiting...\n";
         break;
      default:
         cout << "Invalid choice. Please try again.\n";
      }
      // Repeat menu until user chooses to exit
   } while (choice != 6);

   return 0; // End of program
}
