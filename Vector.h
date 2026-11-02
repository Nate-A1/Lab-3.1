#pragma once
#include <iostream>
using namespace std;

class Vector {
    bool* p = nullptr;
    int n = 0;
public:
    Vector(bool* p, int n);            // Конструктор из массива
    Vector(int n);                     // Конструктор размерности
    Vector(const Vector& V);           // Конструктор копирования
    Vector(Vector&& V);                // Конструктор перемещения
    Vector();                          // Пустой конструктор
    ~Vector();                         // Деструктор

    bool& operator[](int i);           // Оператор []
    Vector& operator=(const Vector& V2); // Оператор = (копирование)
    Vector& operator=(Vector&& V2);      // Оператор = (перемещение)

    // Дружественные операторы
    friend Vector operator ^(Vector& V1, Vector& V2);
    friend ostream& operator <<(ostream& os, const Vector& V);
    friend istream& operator >>(istream& is, Vector& V);
};
