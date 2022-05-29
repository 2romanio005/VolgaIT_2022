#include "Hero.hpp"

Hero::Hero(Fairyland* world, Character hero, bool algorithm_flag, int size_map, int area)
{
    srand(static_cast<unsigned int>(time(nullptr)));   // для рандома

    this->world = world;

    this->direction = Direction::Up;
    this->next_direction = Direction::Up;

    this->algorithm_flag = algorithm_flag;
    this->algorithm_area = rand() % area + 4;
    this->hero = hero;

    this->i = size_map; this->j = size_map;
    this->size_map = size_map;
    this->max_size_map = size_map * 2 + 1;

    hero_map = new int* [size_map * 2 + 1];
    hero_map_count = new int* [size_map * 2 + 1];
    for (int i = 0; i < size_map * 2 + 1; i++)
    {
        hero_map[i] = new int[size_map * 2 + 1]{};
        hero_map_count[i] = new int[size_map * 2 + 1]{};
    }



}
Hero::~Hero()
{
    for (int i = 0; i < size_map * 2 + 1; i++)
    {
        delete[] this->hero_map[i];
        delete[] this->hero_map_count[i];
    }
    delete[] this->hero_map;
    delete[] this->hero_map_count;
    this->hero_map = nullptr;
    this->hero_map_count = nullptr;
}

void Hero::search_hero_move(IAlgorithm_search& algoritmh_search)
{
    algoritmh_search.search_hero_move(*this);
}
void Hero::finish(IAlgorithm_search& algoritmh_search, bool result)
{
    algoritmh_search.finish(*this, result);
}
void Hero::finish(IAlgorithm_search& algoritmh_search, bool result, Hero& companion)
{
    algoritmh_search.finish(*this, result, companion);
}

Direction Hero::get_direction()
{
    return this->direction;
}
Direction Hero::get_next_direction()
{
    return this->next_direction;
}

void Hero::print(int i, int j)
{
    if (i >= 0 && i < this->max_size_map && j >= 0 && j < this->max_size_map) {  // не выходим за рамки массива
        switch (hero_map[i][j])
        {
        case 0:
            std::cout << '?';
            break;
        case 1:
            std::cout << '#';
            break;
        case 2:
            std::cout << '.';
            break;
        case 3:
            std::cout << '@';
            break;
        default:
            std::cout << '&';
            break;
        }
    }
    else {
        std::cout << '_';
    }
}







void IAlgorithm_search::rand_algorithm_area(Hero& hero, int area)
{
    hero.algorithm_flag = !hero.algorithm_flag;
    hero.algorithm_area = rand() % area + 4;
}
void IAlgorithm_search::look_around_hero(Hero& hero, Turn step)
{
    int i = hero.i, j = hero.j;   // ракрепляем коордианты

    Direction tmp = int_to_direction((direction_to_int(hero.direction) + step) % 4);     // находим направление када смотреть
    get_map_cord(tmp, &i, &j);    // узнаём координаты куда мы смотрим
    hero.hero_map[i][j] = (*(hero.world)).canGo(hero.hero, tmp) + 1;                     // записываем на личную карту что перед нами
    if (hero.hero_map[i][j] >= 2) { // если тыда можно пойти то
        hero.next_direction = tmp;  // раписываем это направление в преоритетные
    }
}

Fairyland* IAlgorithm_search::get_world(Hero& hero)
{
    return hero.world;
}


void IAlgorithm_search::change_direction(Hero& hero, Turn step)
{
    hero.direction = int_to_direction((direction_to_int(hero.direction) + step) % 4);
}
void IAlgorithm_search::change_direction(Hero& hero, Direction new_direction)
{
    hero.direction = new_direction;
}
Direction IAlgorithm_search::get_direction(Hero& hero)
{
    return hero.direction;
}
Direction IAlgorithm_search::get_next_direction(Hero& hero)
{
    return hero.next_direction;
}

int IAlgorithm_search::get_hero_map(Hero& hero, int i, int j) {
    if (i >= 0 && i < hero.max_size_map && j >= 0 && j < hero.max_size_map) {  // не выходим за рамки массива
        return hero.hero_map[i][j];
    }
    return 0;
}
int IAlgorithm_search::get_hero_map_count(Hero& hero, int i, int j){ // не выходим за рамки массива
if (i >= 0 && i < hero.max_size_map && j >= 0 && j < hero.max_size_map) {
        return hero.hero_map_count[i][j];
    }
    return 0;
}
void IAlgorithm_search::set_hero_map(Hero& hero, int i, int j, int val) {
    if (i >= 0 && i < hero.max_size_map && j >= 0 && j < hero.max_size_map) { // не выходим за рамки массива
        hero.hero_map[i][j] = val;
    }
}
void IAlgorithm_search::set_hero_map_count(Hero& hero, int i, int j, int val) {
    if (i >= 0 && i < hero.max_size_map && j >= 0 && j < hero.max_size_map) { // не выходим за рамки массива
        hero.hero_map_count[i][j] = val;
    }
}

bool IAlgorithm_search::get_algorithm_flag(Hero& hero)
{
    return hero.algorithm_flag;
}
int IAlgorithm_search::get_algorithm_area(Hero& hero)
{
    return hero.algorithm_area;
}
int IAlgorithm_search::get_size_map(Hero& hero)
{
    return hero.size_map;
}










Direction int_to_direction(int val) {

    switch (val % 4)
    {
    case 0:
        return Direction::Up;
    case 1:
        return Direction::Right;
    case 2:
        return Direction::Down;
    default:
        return Direction::Left;
    }

}
int direction_to_int(Direction direction) {

    switch (direction)
    {
    case Direction::Up:
        return 0;
    case Direction::Right:
        return 1;
    case Direction::Down:
        return 2;
    default:
        return 3;
    }

}

void get_map_cord(Direction direction, int* i, int* j) {

    switch (direction)
    {
    case Direction::Up:
        (*i)--;
        return;
    case Direction::Right:
        (*j)++;
        return;
    case Direction::Down:
        (*i)++;
        return;
    default:
        (*j)--;
        return;
    }

}





