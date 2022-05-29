#pragma once

#include <ctime>
#include "fairy_tail.hpp"


enum Turn{               // куда повернуться
    forward,  // вперёд
    right,    // право
    back,     // назад
    left      // лево
};




class IAlgorithm_search;


class Hero{                    // класс наших герое-бродильщиков

    friend IAlgorithm_search;  // доступ алгоритму к нашем данным

public:
    Hero(Fairyland* world, Character hero, bool algorithm_flag, int size_map = 10, int area = 3);
    ~Hero();

    void search_hero_move(IAlgorithm_search& algoritmh_search);       // поиск нужного направления
    void finish(IAlgorithm_search& algoritmh_search, bool result);    // после встречи если ты был в лабиринте один
    void finish(IAlgorithm_search& algoritmh_search, bool result, Hero& companion);   // после встречи вдвоём

    Direction get_direction();           // геторы куда мы смотрим и
    Direction get_next_direction();      // куда собираемся ходить

    void print(int i, int j);            // вывод элемента лабиринта

    int i, j;
private:
    Fairyland* world;                    // тот мир в котором герой бродит
    Character hero;                      // ID героя

    Direction direction;                 // куда мы повёрнуты
    Direction next_direction;            // куда собираемся идти

    int** hero_map = nullptr;            // личная карта (записано всё что увидели)    // 0 - неизвестность, 1 - стена, 2 - проход, 3 - Иван, 4 - Елена
    int** hero_map_count = nullptr;      // счётчик для каждой клетки личного лабринта

    bool algorithm_flag;                 // идти по левой или по правой руке
    int algorithm_area;                  // кпосле сколькоих посещений одной и той же клетки менять рукость

    int size_map;                        // размер катры
    int max_size_map;                    // размер личной карты
};







class IAlgorithm_search {                                               // интерфейс для работы с героем
public:
    void virtual search_hero_move(Hero& hero) = 0;                      // наш алгоритм поиска следующего шага
    void virtual finish(Hero& hero, bool result) {};                    // алгоритм конца в одиночку
    void virtual finish(Hero& hero, bool result, Hero& companion) {};   // алгоритм конца пары
protected:
    void rand_algorithm_area(Hero& hero, int area);                     // задание нового барьера [4; 3 + area]
    void look_around_hero(Hero& hero, Turn step);                       // посмотреть в сторону, записать в личную карту что там рассположено(стена или проход), решить идти туда или нет
    // геторы и сеторы
    Fairyland* get_world(Hero& hero);                                   // гетор мира в котором персонаж


    void change_direction(Hero& hero, Turn step);                       // сетор направления героя
    void change_direction(Hero& hero, Direction new_direction);
    Direction get_direction(Hero& hero);                                // гетор направления
    Direction get_next_direction(Hero& hero);

    int get_hero_map(Hero& hero, int i, int j);                         // гетор личной карты
    int get_hero_map_count(Hero& hero, int i, int j);                   // гетор счётчика 
    void set_hero_map(Hero& hero, int i, int j, int val);               // сетор личной карты
    void set_hero_map_count(Hero & hero, int i, int j, int val);        // сетор счётчика


    bool get_algorithm_flag(Hero& hero);                                // гетор рукости
    int get_algorithm_area(Hero& hero);                                 // герор барьера
    int get_size_map(Hero& hero);                                       // гетор размера карты


};






// отдельный функции
Direction int_to_direction(int val);                       // перевод числа в направление
int direction_to_int(Direction direction);                 // перевод направления в число

void get_map_cord(Direction direction, int* i, int* j);    // меняет координаты в нужном направлении






