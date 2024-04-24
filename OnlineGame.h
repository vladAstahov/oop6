#pragma onlineGame

#include "Game.h"

class OnlineGame : public Game
{
    private:
        int currentOnline;
        std::string popularServer;
    public:
        OnlineGame() : Game(), currentOnline(0), popularServer(""){};

        // объявления перегрузки дружественной функции вывода в консоль
        friend std::ostream& operator<<(std::ostream& os, const OnlineGame& game);
        // объявления перегрузки дружественной функции считывания из консоли
        friend std::istream& operator>>(std::istream& is, OnlineGame& game);
        // объявления перегрузки дружественной функции записи в файл
        friend std::ofstream& operator<<(std::ofstream& ofs, const OnlineGame& game);
        // объявления перегрузки дружественной функции считываения из файла
        friend std::ifstream& operator>>(std::ifstream& ifs, OnlineGame& game);
};