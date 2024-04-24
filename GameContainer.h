// GameContainer.h
#pragma once

#include "OnlineGame.h"
#include <vector>

class GameContainer {
private:
    std::vector<Game> games;
    std::vector<OnlineGame> onlineGames;
public:
    // конструктор
    GameContainer();
    // диструктор
    ~GameContainer();

    // метод для добавления игры
    void addGame(const Game& game);
    void addGame(const OnlineGame& game);
    // метод для удаления игры
    void removeGame(const std::string& title);
    // метод для загрузки игр с файла
    void loadFromFile();
    // метод для сохранения игр в файл
    void saveToFile();
    // метод для поиска игр по жанру
    void searchGameByGenreAndRAM(const std::string& genre) const;
    // метод для поиска игры подходящих под ваш пк
    void displayCompatibleGames(int cpu, int ram, int hdd) const;
    // метод для добавления нового элемента в файл
    void appendToFile(const std::string& filename, const Game& newGame);
    void appendToFile(const std::string& filename, const OnlineGame& newGame);
    // объявления перегрузки дружественной функции вывода в консоль
    friend std::ostream& operator<<(std::ostream& os, const GameContainer& container);
};