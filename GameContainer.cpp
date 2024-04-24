// GameContainer.cpp
#include "GameContainer.h"
#include <fstream>
#include <iostream>

// инициализируем конструктор класса контейнра
GameContainer::GameContainer() {}

// инициализируем деструктор класса контейнра
GameContainer::~GameContainer() {}

// инициализируем метод для добавления новой игры в файл
void GameContainer::appendToFile(const std::string& filename, const Game& newGame) {
    std::ofstream file(filename, std::ios::app); // открываем файл для записи
    // выдаем ошибку если не удалось открыть файл
    if (!file.is_open()) {
        std::cerr << "ошибка открытия файла для добавления новой игры." << std::endl;
        return;
    }

    // вводим в файл кол-во игр
    file << "1\n";
    // вызываем метод класса Game для записи в файл
    file << newGame;

    // закрываем файловый поток
    file.close();
}

void GameContainer::appendToFile(const std::string& filename, const OnlineGame& newGame) {
    std::ofstream file(filename, std::ios::app); // открываем файл для записи
    // выдаем ошибку если не удалось открыть файл
    if (!file.is_open()) {
        std::cerr << "ошибка открытия файла для добавления новой игры." << std::endl;
        return;
    }

    // вводим в файл кол-во игр
    file << "1\n";
    // вызываем метод класса Game для записи в файл
    file << newGame;

    // закрываем файловый поток
    file.close();
}

// иницализируем метод для добавления игры
void GameContainer::addGame(const Game& game) {
    // добавляем игру в конец массива
    games.push_back(game);
}

void GameContainer::addGame(const OnlineGame& game) {
    // добавляем игру в конец массива
    onlineGames.push_back(game);
}


// инициализируем метод для удаления игры по названию
void GameContainer::removeGame(const std::string& title) {
    // ищем игру в массиве игр, игру с переданным заголовком
    auto it = std::find_if(
        games.begin() /*начало массива*/, 
        games.end() /*конец массива*/,  
        [&title](const Game& game) {
            return game.getTitle() == title;
        } /*лямда функция для проверки итерируемой игры*/
    );
    auto onlineGameF = std::find_if(
        onlineGames.begin() /*начало массива*/, 
        onlineGames.end() /*конец массива*/,  
        [&title](const OnlineGame& game) {
            return game.getTitle() == title;
        } /*лямда функция для проверки итерируемой игры*/
    );

    // если индекс такой игры не равен длинне массива ( те найден )
    if (it != games.end()) {
        games.erase(it); // удаляем элемент по индексу
    }
    if (onlineGameF != games.end()) {
        onlineGames.erase(onlineGameF);
    }

    saveToFile(); // вызываем метод для сохранения текущего массива в файл
}

// инициализируем метод для считывания игр из файла
void GameContainer::loadFromFile() {
    // открыаем файл для чтения
    std::ifstream file("games.txt");
    std::ifstream onlineFile("onlineGames.txt");
    // выдаем ошибку если не удалось открыть файл
    if (!file.is_open()) {
        std::cerr << "ошибка открытия файла." << std::endl;
        return;
    }
    
    // считываем из файла кол-во игр
    int numGames;
    file >> numGames;

    // выдяляем необходимую память для хранения данных в массиве
    games.resize(numGames);

    // считываем указаное кол-во игр из файла
    for (int i = 0; i < numGames; ++i) {
        // считываем данные из файла используя перезагрузку фукнции в классе Game
        file >> games[i];
        if (i < numGames - 1) {
            file.ignore();
        }
    }

    int numOnlineGames;
    onlineFile >> numOnlineGames;

    onlineGames.resize(numOnlineGames);

    // считываем указаное кол-во игр из файла
    for (int i = 0; i < numOnlineGames; ++i) {
        // считываем данные из файла используя перезагрузку фукнции в классе Game
        file >> onlineGames[i];
        if (i < numOnlineGames - 1) {
            file.ignore();
        }
    }

    // закрываем файловый поток
    file.close();
    onlineFile.close();

    // выдаем информацию о количестве скаченных игр
    std::cout << "загружено " << numGames + numOnlineGames << " игр из файла." << std::endl;
}

// инициализируем метод для сохранения данных в файл
void GameContainer::saveToFile() {

    // открыаем файл для записи
    std::ofstream file("games.txt");
    std::ofstream onlineFile("onlineGames.txt");
    // выдаем ошибку если не удалось открыть файл
    if (!file.is_open()) {
        std::cerr << "ошибка открытия файла." << std::endl;
        return;
    }

    // записываем в файл кол-во игр
    file << games.size() << "\n";

    // записываем каждую игру в файл
    for (const auto& game : games) {
        // записываем данные в файл используя перезагрузку фукнции в классе Game
        file << game;
    }

    if (!onlineFile.is_open()) {
        std::cerr << "ошибка открытия файла." << std::endl;
        return;
    }

    onlineFile << onlineGames.size() << "\n";

    // записываем каждую игру в файл
    for (const auto& game : onlineGames) {
        // записываем данные в файл используя перезагрузку фукнции в классе Game
        onlineFile << game;
    }

    // закрываем файловый поток
    file.close();
    onlineFile.close();
}

// инициализируем метод для поиска игры по жанру с минимально необходимой оперативкой
void GameContainer::searchGameByGenreAndRAM(const std::string& genre) const {
    // изначальное значение минимальное памяти
    int minRam = -1;
    std::string foundTitle;
    bool isRamFound = false;

    for (const auto& game : games) {
        // проверяем что жанр игр соответсвует искомому и необходимое кол-во оперативной памяти меньше значения minRam
        if (game.getGenre() == genre && (minRam == -1 || game.getMinRAM() < minRam)) {
            // изменяем уже найденный минимум RAM
            minRam = game.getMinRAM();
            // сохраняем название игры
            foundTitle = game.getTitle();
            // устанавливаем флаг что хотя бы одна игра найдена
            isRamFound = true;
        }
    }

    for (const auto& game : onlineGames) {
        // проверяем что жанр игр соответсвует искомому и необходимое кол-во оперативной памяти меньше значения minRam
        if (game.getGenre() == genre && (minRam == -1 || game.getMinRAM() < minRam)) {
            // изменяем уже найденный минимум RAM
            minRam = game.getMinRAM();
            // сохраняем название игры
            foundTitle = game.getTitle();
            // устанавливаем флаг что хотя бы одна игра найдена
            isRamFound = true;
        }
    }

    if (isRamFound) {
        std::cout << "игра с минимальными требованиями по RAM в жанре " << genre << ": " << foundTitle
            << " (" << (minRam != -1 ? std::to_string(minRam) : "не указано") << ")" << std::endl;
    }
    else {
        std::cout << "игры с указанным жанром не найдено или не указаны требования по RAM." << std::endl;
    }
}

// инициализируем метод для поиска игр соответсвующих введеным характеристикам CPU, RAM, HDD
void GameContainer::displayCompatibleGames(int cpu, int ram, int hdd) const {
    for (const auto& game : games) {
        if (game.getMinCPU() <= cpu && game.getMinRAM() <= ram && game.getMinHDD() <= hdd) {
            std::cout << game.getTitle() << std::endl;
        }
    }
    for (const auto& game : onlineGames) {
        if (game.getMinCPU() <= cpu && game.getMinRAM() <= ram && game.getMinHDD() <= hdd) {
            std::cout << game.getTitle() << std::endl;
        }
    }
}

// инициализируем перезагрузку оператора вывода списка игр в консоль
std::ostream& operator<<(std::ostream& os, const GameContainer& container) {
    for (const auto& game : container.games) {
        os << game;
    }
    for (const auto& game : container.onlineGames) {
        os << game;
    }
    return os;
}
