// Основные используемые библиотеки:
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <filesystem>
#include <vector>

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
{"help", "\t Список команд с пояснениями"}
};

void checkUserInput(std::string opt, std::string arg) {
	if (opt == "help") {
		std::cout << "Для получения сведений об определённой команде введите HELP <имя команды> " << std::endl;
		for (const auto& [command, description] : allCommands) {
			std::cout << command << description << "\n";
		}
	} else if (opt == "exit") {
		exitFromFileManager = true;
	} else if (opt == "cd" && arg == "../") {
		std::cout << "Something in the way\n"; 
	}

	else { 
		std::cout << "Неизвестная команда. Попробуйте ещё раз.\n";
	}
}

int main() {
	russianLang();

	std::string userInput;
	std::string userCommand;
	std::string userArgument;

	while(!exitFromFileManager) {
		std::cout << currentDirectory.string() << ">";
		
		std::getline(std::cin, userInput);
		std::istringstream stream(userInput);
		stream >> userCommand;
		std::getline(stream >> std::ws, userArgument);
		
		checkUserInput(userCommand, userArgument);
	}

	return 0;
}