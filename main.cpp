#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include<ctime>

using namespace std;

// ================= Task Structure =================
struct Task {
    string employeeName;
    string title;
    string description;
    string assignedDate;
    string endingDate;
    int priority; // 1 (least) - 10 (most)

    // Descending order by priority
    bool operator<(const Task& t) const {
        return priority < t.priority;
    }
};

// ================= Priority Queue =================
priority_queue<Task> tasks;

// ================= GUI Menu =================
void showMenu() {
    cout << "\n=====================================\n";
    cout << "     EMPLOYEES TASK MANAGER SYSTEM    \n";
    cout << "=====================================\n";
    cout << " [1] Add New Task\n";
    cout << " [2] Display Sorted Tasks\n";
    cout << " [3] Reminder (Next Task)\n";
    cout << " [4] Edit Task or Priority   (Bonus)\n";
    cout << " [5] Postpone Task           (Bonus)\n";
    cout << " [6] Mark Task as Done\n";
    cout << " [0] Exit\n";
    cout << "=====================================\n";
    cout << "Enter your choice: ";
}

// ================= Encouraging Quote =================
void encouragingQuote() {
    string quotes[] = {
        "Great job! Keep pushing forward 💪",
        "Excellent work! You're doing amazing 🌟",
        "All tasks completed! Success is yours 🎉",
        "Well done! Hard work always pays off 🚀"
    };
    cout << "\n🎉 " << quotes[rand() % 4] << endl;
}

// ================= Add Task =================
void addTask() {
    Task t;
    cin.ignore();

    cout << "Enter Employee Name: ";
    getline(cin, t.employeeName);

    cout << "Enter Task Title: ";
    getline(cin, t.title);

    cout << "Enter Description: ";
    getline(cin, t.description);

    cout << "Enter Assigned Date: ";
    getline(cin, t.assignedDate);

    cout << "Enter Required Ending Date: ";
    getline(cin, t.endingDate);

    do {
        cout << "Enter Priority (1 - 10): ";
        cin >> t.priority;
    } while (t.priority < 1 || t.priority > 10);

    tasks.push(t);
    cout << "\n✔ Task Added Successfully!\n";
}

// ================= Display Tasks =================
void displayTasks() {
    if (tasks.empty()) {
        cout << "\n⚠ No Tasks Available!\n";
        return;
    }

    priority_queue<Task> temp = tasks;
    cout << "\n--------- SORTED TASKS (DESCENDING) ---------\n";

    while (!temp.empty()) {
        Task t = temp.top();
        temp.pop();

        cout << "Employee Name : " << t.employeeName << endl;
        cout << "Task Title    : " << t.title << endl;
        cout << "Description   : " << t.description << endl;
        cout << "Assigned Date : " << t.assignedDate << endl;
        cout << "Ending Date   : " << t.endingDate << endl;
        cout << "Priority      : " << t.priority << endl;
        cout << "--------------------------------------------\n";
    }
}

// ================= Reminder =================
void remindTask() {
    if (tasks.empty()) {
        encouragingQuote();
        return;
    }

    Task t = tasks.top();
    cout << "\n🔔 NEXT TASK REMINDER\n";
    cout << "Employee : " << t.employeeName << endl;
    cout << "Task     : " << t.title << endl;
    cout << "Priority : " << t.priority << endl;
}

// ================= Edit Task or Priority (Bonus) =================
void editTask() {
    if (tasks.empty()) {
        cout << "\n⚠ No tasks to edit.\n";
        return;
    }

    vector<Task> temp;
    Task t = tasks.top();
    tasks.pop();

    cout << "\nEditing Task: " << t.title << endl;
    cout << "1. Edit Task Title\n";
    cout << "2. Edit Priority\n";
    cout << "Choose option: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter New Title: ";
        getline(cin, t.title);
    } else if (choice == 2) {
        do {
            cout << "Enter New Priority (1 - 10): ";
            cin >> t.priority;
        } while (t.priority < 1 || t.priority > 10);
    }

    temp.push_back(t);

    while (!tasks.empty()) {
        temp.push_back(tasks.top());
        tasks.pop();
    }

    for (auto &x : temp)
        tasks.push(x);

    cout << "\n✔ Task Updated Successfully!\n";
}

// ================= Postpone Task (Bonus) =================
void postponeTask() {
    if (tasks.empty()) {
        cout << "\n⚠ No tasks available.\n";
        return;
    }

    Task t = tasks.top();
    tasks.pop();
    cin.ignore();

    cout << "Current Ending Date: " << t.endingDate << endl;
    cout << "Enter New Ending Date: ";
    getline(cin, t.endingDate);

    tasks.push(t);
    cout << "\n✔ Task Postponed Successfully!\n";
}

// ================= Mark Task as Done =================
void markTaskDone() {
    if (tasks.empty()) {
        encouragingQuote();
        return;
    }

    Task t = tasks.top();
    tasks.pop();

    cout << "\n✔ Task Completed Successfully!\n";
    cout << "Completed Task: " << t.title << endl;

    if (tasks.empty())
        encouragingQuote();
}

// ================= Main =================
int main() {
    int choice;
    srand(time(0));

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: displayTasks(); break;
            case 3: remindTask(); break;
            case 4: editTask(); break;
            case 5: postponeTask(); break;
            case 6: markTaskDone(); break;
            case 0:
                cout << "\nThank you for using the system. Goodbye 👋\n";
                break;
            default:
                cout << "\n❌ Invalid choice, try again.\n";
        }

    } while (choice != 0);

    return 0;
}
