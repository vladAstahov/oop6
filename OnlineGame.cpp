#include "OnlineGame.h"

// инициализируем перезагрузку оператора вывода в консоль
std::ostream& operator<<(std::ostream& os, const OnlineGame& game) {
    // выводим данные в консоль
    os << static_cast<Game>(game)
        << "Средний онлайн: " << game.currentOnline << "\n"
        << "Популярный сервер: " << game.popularServer << "\n"
        << "----------------------------------------\n";
    return os;
}

// инициализируем перезагрузку оператора считывания из консоли
std::istream& operator>>(std::istream& is, OnlineGame& game) {
    std::cout << "Введите название игры: ";
    is.ignore();
    // считваем введенное значение из консоли
    std::getline(is, game.title);

    std::cout << "Введите жанр игры: ";
    // считваем введенное значение из консоли
    std::getline(is, game.genre);

    std::cout << "Введите платформу игры: ";
    // считваем введенное значение из консоли
    std::getline(is, game.platform);

    std::cout << "Введите год выпуска игры: ";
    // считваем введенное значение из консоли
    is >> game.year;

    std::cout << "Введите разработчика игры: ";
    is.ignore();
    // считваем введенное значение из консоли
    std::getline(is, game.developer);

    do {
        std::cout << "Введите количество игроков (больше 0): ";
        is >> game.players;
    } while (game.players <= 0);  // проверка на положительное количество игроков

    std::cout << "Введите минимальную частоту CPU: ";
    // считваем введенное значение из консоли
    is >> game.min_cpu;

    std::cout << "Введите минимальный объем RAM: ";
    // считваем введенное значение из консоли
    is >> game.min_ram;

    std::cout << "Введите минимальный объем HDD: ";
    // считваем введенное значение из консоли
    is >> game.min_hdd;

    return is;
}

// инициализируем перезагрузку оператора записи в файл
std::ofstream& operator<<(std::ofstream& ofs, const OnlineGame& game) {
    ofs << game.title << "\n"
        << game.genre << "\n"
        << game.platform << "\n"
        << game.year << "\n"
        << game.developer << "\n"
        << game.players << "\n"
        << game.min_cpu << "\n"
        << game.min_ram << "\n"
        << game.min_hdd << "\n"
        << game.currentOnline << "\n"
        << game.popularServer << "\n";
    return ofs;
}

// инициализируем перезагрузку оператора получения записи из файла
std::ifstream& operator>>(std::ifstream& ifs, OnlineGame& game) {
    ifs >> game.title >> game.genre >> game.platform >> game.year >>
        game.developer >> game.players >> game.min_cpu >> game.min_ram >> game.min_hdd >> game.currentOnline >> game.popularServer;
    return ifs;
}