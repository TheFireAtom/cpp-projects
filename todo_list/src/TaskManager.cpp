#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include "../include/TaskManager.hpp"
#include <stdexcept>	// For standard exception types

// Task struct constructor and methods

Task::Task(const std::string& desc, short int prio, short int pos, const std::string& cat)
		: description(desc), completed(false), priority(prio), position(pos), category(cat) {};

void Task::markCompleted() {
	completed = true;
}

std::string Task::toString() const {
	std::stringstream ss;
	ss << "Task: " << description << "| Priority: " << priority
	   << "| Category: " << category << "| Completed: " << completed;
	return ss.str();
}

// TaskManager methods and tasks vector

void TaskManager::addTask(const Task& task) {
	taskStorage.push_back(task);
	tasksQuantity++;
}

void TaskManager::deleteTask(const Task& task) {
		
	// This shit is ugly AF, so we use guard clauses (pyramid of doom)

	// if (taskStorage.size() > 0) {
	// 	if (task.position < taskStorage.size()) {
	// 		taskStorage.erase(taskStorage.begin() + task.position);
	// 		std::cout << "Task is successfully deleted!\n"
	// 	} else {
	// 		std::cerr("Error: Task position is out of range\n");
	// 	} 
	// // position in list equals position in vector
	// } else {
	// 	std::cerr << "Error: You can't delete a task from empty list\n";
	// }

	if (taskStorage.empty()) {
		std::cerr << "Error: You can't delete a task from empty list\n";
		return;
	}

	if (task.position >= taskStorage.size()) {
		std::cerr("Error: Task position is out of range\n");
		return;
	}

	taskStorage.erase(taskStorage.begin() + task.position);
	std::cout << "Task is successfully deleted!\n"
}

void TaskManager::changeTask(const Task& task, const Task& newTask) {
	taskStorage.insert(taskStorage.begin() + task.position, newTask);
}

void TaskManager::printAllTasks() {
	for (element : taskStorage) {
		std::stringstream taskStream;
		taskStream << "Task: " << description << "| Priority: " << priority
	   << "| Category: " << category << "| Completed: " << completed; 
	}
}

void TaskManager::deleteList() {
	char userResponse;
	std::cout << "Are you sure that you want to delete current list of tasks?\n" 
	std::cout << "y/n: ";
	std::cin >> userResponse;

	while (userResponse != 'y' && userResponse != 'n') {
		std::cout << "Invalid input. Please enter 'y' or 'n': ";
		std::cin >> userResponse;
	}

	if (userResponse == 'y') {
		taskStorage.clear();
		std::cout << "List was successfully deleted!" << std::endl;
	} 
	
}