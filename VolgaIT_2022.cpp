#include <iostream>
#include <algorithm>

#include "fairy_tail.hpp"
#include "Hero.hpp"


#define _size_map 10   // размер квадратного лабиринта







class one_hand_algorithm : public IAlgorithm_search {        // создаём алгорит прохождения лабиринта

private:
    void search_hero_move(Hero& hero) override {             // поиск слудующего хода

        if (get_algorithm_flag(hero)) {                      // по левой руке
            look_around_hero(hero, Turn::back);
            look_around_hero(hero, Turn::right);
            look_around_hero(hero, Turn::forward);
            look_around_hero(hero, Turn::left);
        }
        else {                                               // по правой руке
            look_around_hero(hero, Turn::back);
            look_around_hero(hero, Turn::left);
            look_around_hero(hero, Turn::forward);
            look_around_hero(hero, Turn::right);
        }



        change_direction(hero, get_next_direction(hero));           // меняем своё направление в сторону в которую будем ходить
        get_map_cord(get_direction(hero), &(hero.i), &(hero.j));    // меняем координаты на личной карте в нужную сторону

        if (get_hero_map_count(hero, hero.i, hero.j) >= get_algorithm_area(hero)) {   // когда посетили одну и туже клетку больше барьера - раз меняем руку
            rand_algorithm_area(hero, 3);                                             // задаём новый барьер из отрезка [4;6]
            if (rand() % 2) {                                                         // разварачиваемся на 180 с 50% вероятностью
                change_direction(hero, Turn::back);
            }
            for (int i = 0; i < get_size_map(hero) * 2 + 1; i++)                      // обнуляем количсетво посещений клеток
            {
                for (int j = 0; j < get_size_map(hero) * 2 + 1; j++)
                {
                    set_hero_map_count(hero, i, j, 0);
                }
            }
        }
        set_hero_map_count(hero, hero.i, hero.j, get_hero_map_count(hero, hero.i, hero.j) + 1);   // добавляем 1 в счётчик той колетки на которой стоим
    };

    void finish(Hero& hero, bool result, Hero& companion) override {        // алгоритм после встречи
        if (result) {    // удалось встретиться или нет
            look_around_hero(hero, Turn::back);
            if ((*get_world(hero)).go(get_next_direction(hero), Direction::Pass)) {   // двигаемся Иваном на предыдущую клетку и если мы попадаем на Елену то
                change_direction(hero, get_next_direction(hero));                     // меняем свои координаты и направление
                get_map_cord(get_direction(hero), &(hero.i), &(hero.j));
            }


            std::cout << "Found in " << (*get_world(hero)).getTurnCount() << " turns\n\n";

            set_hero_map(hero, _size_map, _size_map, 3);        // устанавливаем на катру значки Ивана
            set_hero_map(companion, _size_map, _size_map, 4);   // и Елены

            int tmp_step_i = hero.i - companion.i;              // находим смещещение личных карт героев друг от друга
            int tmp_step_j = hero.j - companion.j;

            int min_i = _size_map * 2 + 1, min_j = _size_map * 2 + 1;

            for (int i = 0; i < _size_map * 2 + 1; i++)
            {
                for (int j = 0; j < _size_map * 2 + 1; j++)
                {
                    set_hero_map(hero, i, j, std::max(get_hero_map(hero, i, j), get_hero_map(companion, i - tmp_step_i, j - tmp_step_j))); //  дописываем на карту Ивана карту Елены учитывая смещение
                    if (get_hero_map(hero, i, j) > 0) {   // находим границы карты
                        min_i = std::min(min_i, i);
                        min_j = std::min(min_j, j);
                    }

                }
            }
            min_i++; min_j++;

            for (int i = min_i; i < min_i + _size_map; i++)     // выводим нудную часть карты
            {
                for (int j = min_j; j < min_j + _size_map; j++)
                {
                    hero.print(i, j);
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "Not found for 1500 turns\n";                         // встретиться невозможно
        }
    }

};



Fairyland world;

int main()
{
    Hero Ivan(&world, Character::Ivan, 1, _size_map);    // создаём манчкина(героя)-Ивана :-) 
    Hero Elena(&world, Character::Elena, 0, _size_map);  // и Елену

    one_hand_algorithm algoritmh;                        // алгоритм брождения по лабиринту

    for (int k = 0; k < 1500; k++)
    {
        Ivan.search_hero_move(algoritmh);     // выбор направления хода Ивана
        Elena.search_hero_move(algoritmh);    // выбор направления хода Елены

        if (world.go(Ivan.get_next_direction(), Elena.get_next_direction())) {   // ход в выбранном направлении и проверка на встречу

            Ivan.finish(algoritmh, 1, Elena);            // завершающая обработка информации пары после встречи
            return 0;
        }
    }

    Ivan.finish(algoritmh, 0, Elena);                    // завершающая обработка информации пары если не встретились
    return 0;
}





