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

void russianLang() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

bool exitFromFileManager = false;

std::map<std::string, std::string> allCommands = {
{"exit", "\t Выход из файлового менеджера"}, 
{"help", "\t Список команд с пояснениями"}
};

void checkUserInput(std::string opt) {
	if (opt == "help") {
		std::cout << "Для получения сведений об определённой команде введите HELP <имя команды> " << std::endl;
		for (const auto& [command, description] : allCommands) {
			std::cout << command << description << "\n";
		}
	} else if (opt == "exit") {
		exitFromFileManager = true;
	}
}

int main() {
	russianLang();

	std::string userInput;

	while(!exitFromFileManager) {
		std::cin >> userInput;
		checkUserInput(userInput);
	}

	return 0;
}