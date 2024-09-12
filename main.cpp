#include <iostream>

// Task.h
#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

class Task {
public:
    Task(int id, const std::string& description, const std::string& dueDate);

    int getId() const;
    std::string getDescription() const;
    std::string getDueDate() const;

private:
    int id;
    std::string description;
    std::string dueDate;
};

#endif // TASK_H
// Task.cpp
#include "Task.h"

Task::Task(int id, const std::string& description, const std::string& dueDate)
        : id(id), description(description), dueDate(dueDate) {}

int Task::getId() const { return id; }
std::string Task::getDescription() const { return description; }
std::string Task::getDueDate() const { return dueDate; }
// TaskManager.h
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <string>

class TaskManager {
public:
    void addTask(const Task& task);
    void viewTasks() const;
    void deleteTask(int id);
    void saveTasks(const std::string& filename) const;
    void loadTasks(const std::string& filename);

private:
    std::vector<Task> tasks;
};

#endif // TASKMANAGER_H
// TaskManager.cpp
#include "TaskManager.h"
#include <fstream>
#include <sstream>

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskManager::viewTasks() const {
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.getId() << ", Description: " << task.getDescription()
                  << ", Due Date: " << task.getDueDate() << std::endl;
    }
}

void TaskManager::deleteTask(int id) {
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                               [id](const Task& task) { return task.getId() == id; }),
                tasks.end());
}

void TaskManager::saveTasks(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& task : tasks) {
        file << task.getId() << "," << task.getDescription() << "," << task.getDueDate() << std::endl;
    }
}

void TaskManager::loadTasks(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int id;
        std::string description;
        std::string dueDate;
        char comma;
        ss >> id >> comma;
        std::getline(ss, description, ',');
        std::getline(ss, dueDate);
        addTask(Task(id, description, dueDate));
    }
}
#include "TaskManager.h"
#include <iostream>

int main() {
    TaskManager manager;

    manager.loadTasks("tasks.txt");

    manager.addTask(Task(1, "Finish homework", "2024-09-30"));
    manager.addTask(Task(2, "Read a book", "2024-10-05"));

    std::cout << "Tasks:" << std::endl;
    manager.viewTasks();

    manager.saveTasks("tasks.txt");

    return 0;
}
