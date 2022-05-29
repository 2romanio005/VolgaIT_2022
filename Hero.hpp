#pragma once

#include <ctime>
#include "fairy_tail.hpp"


enum Turn{               // ���� �����������
    forward,  // �����
    right,    // �����
    back,     // �����
    left      // ����
};




class IAlgorithm_search;


class Hero{                    // ����� ����� �����-������������

    friend IAlgorithm_search;  // ������ ��������� � ����� ������

public:
    Hero(Fairyland* world, Character hero, bool algorithm_flag, int size_map = 10, int area = 3);
    ~Hero();

    void search_hero_move(IAlgorithm_search& algoritmh_search);       // ����� ������� �����������
    void finish(IAlgorithm_search& algoritmh_search, bool result);    // ����� ������� ���� �� ��� � ��������� ����
    void finish(IAlgorithm_search& algoritmh_search, bool result, Hero& companion);   // ����� ������� �����

    Direction get_direction();           // ������ ���� �� ������� �
    Direction get_next_direction();      // ���� ���������� ������

    void print(int i, int j);            // ����� �������� ���������

    int i, j;
private:
    Fairyland* world;                    // ��� ��� � ������� ����� ������
    Character hero;                      // ID �����

    Direction direction;                 // ���� �� ��������
    Direction next_direction;            // ���� ���������� ����

    int** hero_map = nullptr;            // ������ ����� (�������� �� ��� �������)    // 0 - �������������, 1 - �����, 2 - ������, 3 - ����, 4 - �����
    int** hero_map_count = nullptr;      // ������� ��� ������ ������ ������� ��������

    bool algorithm_flag;                 // ���� �� ����� ��� �� ������ ����
    int algorithm_area;                  // ������ ��������� ��������� ����� � ��� �� ������ ������ �������

    int size_map;                        // ������ �����
    int max_size_map;                    // ������ ������ �����
};







class IAlgorithm_search {                                               // ��������� ��� ������ � ������
public:
    void virtual search_hero_move(Hero& hero) = 0;                      // ��� �������� ������ ���������� ����
    void virtual finish(Hero& hero, bool result) {};                    // �������� ����� � ��������
    void virtual finish(Hero& hero, bool result, Hero& companion) {};   // �������� ����� ����
protected:
    void rand_algorithm_area(Hero& hero, int area);                     // ������� ������ ������� [4; 3 + area]
    void look_around_hero(Hero& hero, Turn step);                       // ���������� � �������, �������� � ������ ����� ��� ��� ������������(����� ��� ������), ������ ���� ���� ��� ���
    // ������ � ������
    Fairyland* get_world(Hero& hero);                                   // ����� ���� � ������� ��������


    void change_direction(Hero& hero, Turn step);                       // ����� ����������� �����
    void change_direction(Hero& hero, Direction new_direction);
    Direction get_direction(Hero& hero);                                // ����� �����������
    Direction get_next_direction(Hero& hero);

    int get_hero_map(Hero& hero, int i, int j);                         // ����� ������ �����
    int get_hero_map_count(Hero& hero, int i, int j);                   // ����� �������� 
    void set_hero_map(Hero& hero, int i, int j, int val);               // ����� ������ �����
    void set_hero_map_count(Hero & hero, int i, int j, int val);        // ����� ��������


    bool get_algorithm_flag(Hero& hero);                                // ����� �������
    int get_algorithm_area(Hero& hero);                                 // ����� �������
    int get_size_map(Hero& hero);                                       // ����� ������� �����


};






// ��������� �������
Direction int_to_direction(int val);                       // ������� ����� � �����������
int direction_to_int(Direction direction);                 // ������� ����������� � �����

void get_map_cord(Direction direction, int* i, int* j);    // ������ ���������� � ������ �����������






