#include <iostream>
#include <fstream>
#include <utility>   // для move,swap
#include "Vector.h"

Vector::Vector(bool* p, int n) { //Конструктор из массива
    this->n = n;
    this->p = new bool[n];
    for (int i = 0; i < n; i++)
        this->p[i] = p[i];
    cout << "Vector(bool*, int)" << endl;
}

Vector::Vector(int n) : n(n) { //Конструктор - выделяем память без инициализации
    p = new bool[n];
    cout << "Vector(int n)" << endl;
}

Vector::Vector(const Vector& V) { //Конструктор копирования
    n = V.n;
    p = new bool[n];
    for (int i = 0; i < n; i++)
        p[i] = V.p[i];
    cout << "Vector(const Vector&)" << endl;
}

Vector::Vector(Vector&& V) { //Конструктор перемещения
    swap(p, V.p);
    swap(n, V.n);
    cout << "Vector(Vector&& V) " << endl;
}

Vector::Vector() { //пустой конструктор
    p = nullptr;
    n = 0;
    cout << "Vector() " << endl;
}

Vector::~Vector() { //Деструктор
    cout << "~Vector() " << n << endl;
    if (p != nullptr) delete[] p;
}

bool& Vector::operator[](int i) { //перегрузка оператора []
    return p[i];
}

Vector& Vector::operator=(const Vector& V2) { //перегрузка оператора присваивания (копирование)
    if (this != &V2) { //Запрет копирования вектора на самого себя
        n = V2.n;
        if (p != nullptr) delete[] p;
        p = new bool[n];
        for (int i = 0; i < n; i++)
            p[i] = V2.p[i];
    }
    cout << "Vector & operator=(const Vector& V2) " << endl;
    return *this; //Возвращаем ссылку на текущий объект
}

Vector& Vector::operator=(Vector&& V2) { //перегрузка оператора присваивания перемещением
    if (this != &V2) { //Запрет копирования вектора на самого себя
        swap(p, V2.p);
        swap(n, V2.n);
    }
    cout << "Vector & operator=(Vector&& V2) " << endl;
    return *this; //Возвращаем ссылку на текущий объект
}

Vector operator ^( Vector& V1, Vector& V2) { //перегрузка оператора ^
    if (V1.n != V2.n) { //Проверка на равенство размеров векторов
        cout << "Error: V1.n != V2.n" << endl;
        return Vector();
    }
    Vector V3(V1.n);
    for (int i = 0; i < V1.n; i++)
        V3[i] = V1[i] ^ V2[i]; // логическое исключающее ИЛИ для bool
    return V3;
}

ostream& operator <<(ostream& os, const Vector& V) { //перегрузка оператора << (вывод в поток)
    os << "n= " << V.n << endl;
    for (int i = 0; i < V.n; i++)
        os << V.p[i] << " ";
    os << endl;
    return os; // возвращаем поток для цепочек cout << v1 << v2
}

istream& operator >>(istream& is, Vector& V) { //перегрузка оператора >> (ввод из потока)
    // Освобождаем старую память перед чтением новых данных
    delete[] V.p;
    V.p = nullptr;

    // Читаем размерность
    is >> V.n;
    if (V.n <= 0) {
        V.n = 0;
        return is;
    }

    // Выделяем память под новые элементы
    V.p = new bool[V.n];

    // Читаем элементы (через int, так как bool читается только как 1 или 0)
    for (int i = 0; i < V.n; i++) {
        int tmp;
        is >> tmp;
        V.p[i] = (tmp != 0);
    }
    return is; // возвращаем поток для цепочек cin >> v1 >> v2
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример
    bool a1[] = { true, false, true, false, true };
    bool a2[] = { true, true, false, false, true };

    cout << "Создание v1, v2" << endl;
    Vector v1(a1, 5);
    Vector v2(a2, 5);

    cout << "v1 = " << v1;
    cout << "v2 = " << v2;
	cout << endl;

    cout << "v1 ^ v2" << endl;
    Vector v3 = v1 ^ v2;
    cout << "v3 = " << v3;
    cout << endl;

    cout << "Оператор []" << endl;
    v3[0] = true;
    cout << "v3[0] = " << v3[0] << endl;
    cout << "v3 после изменения = " << v3;
    cout << endl;

    cout << "Конструктор копирования" << endl;
    Vector v4 = v1;   // копирование
    cout << "v4 (копия v1) = " << v4;
    cout << endl;

    cout << "Конструктор перемещения" << endl;
    Vector v5 = std::move(v2);
    cout << "v5 (перемещ. v2) = " << v5;
    cout << "v2 после перемещения = " << v2;   // пустой
    cout << endl;

    cout << "Оператор = (копирование)" << endl;
    Vector v6;
    v6 = v1;   // копирование
    cout << "v6 = " << v6;
    cout << endl;
    
    cout << "Оператор = (перемещение)" << endl;
    Vector v7;
    v7 = std::move(v6);   // перемещение
    cout << "v7 = " << v7;
    cout << "v6 после перемещения = " << v6;   // пустой
    cout << endl;
    
    cout << "Запись в output.txt" << endl;
    ofstream fout("output.txt");
    fout << v1 << v3 << v7;
    fout.close();
    cout << "Записано в output.txt" << endl;
    cout << endl;
    
    cout << "Чтение из input.txt" << endl;
    ifstream fin("input.txt");
    if (fin.is_open()) {
        Vector v8;
        fin >> v8;
        cout << "v8 (из input.txt) = " << v8;
        fin.close();
    }
    else {
        cout << "Не удалось открыть input.txt" << endl;
    }

    return 0;
}
