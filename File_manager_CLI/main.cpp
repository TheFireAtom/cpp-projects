// Основные используемые библиотеки:
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <filesystem>

// Библиотеки для подключения русского языка:
#include <clocale>
#include <windows.h>

namespace fs = std::filesystem;

void russianLang() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

bool exitFromFileManager = false;
fs::path currentDirectory = fs::current_path();

std::map<std::string, std::string> allCommands = {
{"exit", "\t Выход из файлового менеджера"}, 
{"help", "\t Список команд с пояснениями"},
{"cd", "\t Сменить текущую директорию"},
{"mkdir", "\t Создать папку в текущей директории"},
{"rmdir", "\t Удалить пустую папку"}
};

void checkUserInput(const std::string& opt, const std::string& arg) {
	if (opt == "help") {
		std::cout << "Для получения сведений об определённой команде введите HELP <имя команды> " << std::endl;
		for (const auto& [command, description] : allCommands) {
			std::cout << command << description << "\n";
		}
	} else if (opt == "exit") {
		exitFromFileManager = true;
	} else if (opt == "mkdir") {
		if (fs::is_directory(currentDirectory / arg)) {
			std::cout << "Ошибка: заданная папка уже существует.\n";
		} else {
			fs::create_directory(currentDirectory / arg);
		}
	} else if (opt == "rmdir") {
		if (fs::is_directory(currentDirectory / arg)) {
				fs::remove(currentDirectory / arg);
			} else {
				std::cout << "Ошибка: заданная папка не существует.\n";
			}
	}
	else if (opt == "cd") {
	  	  try {
	  	  	  fs::path target = arg;
	  	  	  fs::path newPath;

	  	  	  if (target.is_absolute()) {
	  	  	  	newPath = target;
	  	  	  } else {
	  	  	  	newPath = currentDirectory / target;
	  	  	  }

	  	  	  newPath = newPath.lexically_normal();

	  	  	  if (fs::is_directory(newPath)) {
	  	  	  	currentDirectory = newPath;
	  	  	  } else {
	  	  	  	std::cout << "Ошибка: пути не существует.\n";
	  	  	  }

	  	   } catch (const fs::filesystem_error& ex) {
	  	   		std::cout << "Filesystem error: " << ex.what() << '\n';
	  	   } 	
	  }  
	else { 
		std::cout << "Неизвестная команда. Попробуйте ещё раз.\n";
	}
}

int main() {
	russianLang();

	while(!exitFromFileManager) {
		std::string userInput;
		std::string userCommand;
		std::string userArgument;	
		
		std::cout << currentDirectory.string() << ">";
		
		if (!std::getline(std::cin, userInput)) {
			break;
		} 

		std::istringstream stream(userInput);

		stream >> userCommand;

		if (userCommand.empty()) {
			continue;
		}

		std::getline(stream >> std::ws, userArgument);
		
		checkUserInput(userCommand, userArgument);
	}

	return 0;
}