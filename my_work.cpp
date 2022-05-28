#include "fairy_tail.hpp"
#include <ctime>
#include <algorithm>


#define size_map 10


Direction get_derect(int der);
int get_der(Direction derect);

void get_map_cord(int der, int* i, int* j);

void finish(bool flag);

int rand_map_count();

void print(int val);








Fairyland world;

int** Elena_map = new int* [size_map * 2 + 1];
int** Ivan_map = new int* [size_map * 2 + 1];
int** Elena_map_count = new int* [size_map * 2 + 1];
int** Ivan_map_count = new int* [size_map * 2 + 1];

int Elena_der = 0, Ivan_der = 0;
int i_Ivan = size_map, j_Ivan = size_map, i_Elena = size_map, j_Elena = size_map;



int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    /*
   
    0 - неизвестность
    1 - стена
    2 - проход
    3 - Иван
    4 - Елена
    
    0 - вверх
    1 - прово
    2 - низ
    3 - лево

    */

    for (int i = 0; i < size_map * 2 + 1; i++)
    {
        Elena_map[i] = new int[size_map * 2 + 1]{};
        Ivan_map[i] = new int[size_map * 2 + 1]{};
        Elena_map_count[i] = new int[size_map * 2 + 1]{};
        Ivan_map_count[i] = new int[size_map * 2 + 1]{};
    }

    



    Direction Ivan_find_derect;
    Direction Elena_find_derect;

    //std::cout << "@-l\t\t&-r" << std::endl;

    bool algorithm_Elena = 1, algorithm_Ivan = 1;
    int revers_Ivan = rand_map_count(), revers_Elena = rand_map_count();
    for (int k = 0; k < 1000; k++)
    {
        auto move_hero = [](Character hero, Direction* hero_find_derect, int hero_der, int** map, int i, int j) {
            Direction tmp = get_derect(hero_der);
            get_map_cord(hero_der, &i, &j);
            map[i][j] = world.canGo(hero, tmp) + 1;
            if (map[i][j] >= 2) {
                *hero_find_derect = tmp;
            }
        };


        if (algorithm_Ivan) {
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 2, Ivan_map, i_Ivan, j_Ivan);
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 1, Ivan_map, i_Ivan, j_Ivan);
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 0, Ivan_map, i_Ivan, j_Ivan);
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 3, Ivan_map, i_Ivan, j_Ivan);
        }
        else {
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 2, Ivan_map, i_Ivan, j_Ivan);
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 3, Ivan_map, i_Ivan, j_Ivan);
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 0, Ivan_map, i_Ivan, j_Ivan);
            move_hero(Character::Ivan, &Ivan_find_derect, Ivan_der + 1, Ivan_map, i_Ivan, j_Ivan);
        }
        Ivan_der = get_der(Ivan_find_derect);
        get_map_cord(Ivan_der, &i_Ivan, &j_Ivan);

        if (Ivan_map_count[i_Ivan][j_Ivan] >= revers_Ivan) {
            revers_Ivan = rand_map_count();
            algorithm_Ivan = !algorithm_Ivan;
            if (rand() % 2) {
                Ivan_der = (Ivan_der + 2) % 4;
            }
            for (int i = 0; i < size_map * 2 + 1; i++)
            {
                for (int j = 0; j < size_map * 2 + 1; j++)
                {
                    Ivan_map_count[i][j] = 0;
                }
            }
        }
        Ivan_map_count[i_Ivan][j_Ivan]++;


        if (algorithm_Elena) {
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 2, Elena_map, i_Elena, j_Elena);
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 3, Elena_map, i_Elena, j_Elena);
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 0, Elena_map, i_Elena, j_Elena);
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 1, Elena_map, i_Elena, j_Elena);
        }
        else {
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 2, Elena_map, i_Elena, j_Elena);
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 1, Elena_map, i_Elena, j_Elena);
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 0, Elena_map, i_Elena, j_Elena);
            move_hero(Character::Elena, &Elena_find_derect, Elena_der + 3, Elena_map, i_Elena, j_Elena);
        }
        Elena_der = get_der(Elena_find_derect);
        get_map_cord(Elena_der, &i_Elena, &j_Elena);

        if (Elena_map_count[i_Elena][j_Elena] >= revers_Elena) {
            revers_Elena = rand_map_count();
            algorithm_Elena = !algorithm_Elena;
            if (rand() % 2) {
                Elena_der = (Elena_der + 2) % 4;
            }
            for (int i = 0; i < size_map * 2 + 1; i++)
            {
                for (int j = 0; j < size_map * 2 + 1; j++)
                {
                    Elena_map_count[i][j] = 0;
                }
            }
        }
        Elena_map_count[i_Elena][j_Elena]++;




        //std::cout << i_Ivan << ' ' << j_Ivan << ' ' << int(algorithm_Ivan) << "\t\t" << i_Elena << ' ' << j_Elena << ' ' << int(algorithm_Elena) << std::endl;

        if (world.go(Ivan_find_derect, Elena_find_derect)) {
            Ivan_find_derect = get_derect(Ivan_der + 2);
            if (world.go(Ivan_find_derect, Direction::Pass)) {
                Ivan_der = get_der(Ivan_find_derect);
                get_map_cord(Ivan_der, &i_Ivan, &j_Ivan);
            }

            finish(1);
        }
    }

    finish(0);
    return 0;
}




Direction get_derect(int der) {

    switch (der % 4)
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

int get_der(Direction derect) {

    switch (derect)
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


void get_map_cord(int der, int* i, int* j) {
    
    switch (der % 4)
    {
    case 0:
        (*i)--;
        return;
    case 1:
        (*j)++;
        return;
    case 2:
        (*i)++;
        return;
    default:
        (*j)--;
        return;
    }

}


void finish(bool flag) {
    Elena_map[size_map][size_map] = 4;
    Ivan_map[size_map][size_map] = 3;
    //Elena_map[i_Elena][j_Elena] = 5;
    //Ivan_map[i_Ivan][j_Ivan] = 5;


    if (flag) {
         std::cout << "Found in " << world.getTurnCount() << " turns" << std::endl << std::endl;

         /*
         for (int i = 0; i < size_map * 2 + 1; i++)
         {
             for (int j = 0; j < size_map * 2 + 1; j++)
             {
                 print(Ivan_map[i][j]);
             }
             std::cout << '\t';

             for (int j = 0; j < size_map * 2 + 1; j++)
             {
                 print(Elena_map[i][j]);
             }

             std::cout << std::endl;
         }
         std::cout << std::endl;
         */
        
         int tmp_step_i = i_Ivan - i_Elena;
         int tmp_step_j = j_Ivan - j_Elena;

         int min_i = size_map * 2 + 1, min_j = size_map * 2 + 1;

         for (int i = 0; i < size_map * 2 + 1; i++)
         {
             for (int j = 0; j < size_map * 2 + 1; j++)
             {
                 if (i - tmp_step_i >= 0 && i - tmp_step_i < size_map * 2 + 1 && j - tmp_step_j >= 0 && j - tmp_step_j < size_map * 2 + 1) {
                     Ivan_map[i][j] = std::max(Ivan_map[i][j], Elena_map[i - tmp_step_i][j - tmp_step_j]);
                 }
                 if (Ivan_map[i][j] > 0) {
                     min_i = std::min(min_i, i);
                     min_j = std::min(min_j, j);
                 }
                 
             }
         }
         min_i++; min_j++;

         for (int i = min_i; i < min_i + size_map; i++)
         {
             for (int j = min_j; j < min_j + size_map; j++)
             {
                 print(Ivan_map[i][j]);
             }
             std::cout << std::endl;
         }

    }
    else {
        std::cout << "Not found" << std::endl;
    }
    //system("Pause");
    exit(1);
}

int rand_map_count() {
    return rand() % 3 + 4;
}

void print(int val) {
    switch (val)
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
    //case 5:
    //    std::cout << 'X';
    //    break;
    default:
        std::cout << '&';
        break;
    }
}