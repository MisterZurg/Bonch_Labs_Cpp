#include <iostream>
/*
 * Задание Общая постановка.
 * Создать программу с абстрактным базовым классом
 * и множественным наследованием, реализовать в нем:
        1.	Конструктор,
        2.	Деструктор,
        3.	Виртуальную функцию просмотра текущего состояния объекта print()
        4.	Функцию Run ().
Производные классы должны содержать переопределенную функцию просмотра состояния объектов (print()).
Используя стандартные потоки, информацию об объектах вывести на экран.

 */
using namespace std;

class Frostbite {
public:
    virtual void printInfo() = 0;

    virtual void Run() = 0;

    // constructor
    Frostbite() {
        cout << "Frostbite constructor called" << endl;
    }

    // destructor
    ~Frostbite() {
        cout << "Frostbite destructor called" << endl;
    }
};

class Shooter : public Frostbite {
public:
    void printInfo() override {
        // cout « age « endl;
    }

    // constructor
    Shooter() {
        cout << "Shooter constructor called" << endl;
    }

    // destructor
    ~Shooter() {
        cout << "Shooter destructor called" << endl;
    }
};

class Battlefield : public Frostbite {
public:
    void printInfo() override {
        cout << "Developing Battlefield" << endl;
    }

    // constructor
    Battlefield() {
        cout << "Shooter constructor called" << endl;
    }

    // destructor
    ~Battlefield() {
        cout << "Shooter destructor called" << endl;
    }
};

class Battlefield3 : public Shooter, public Battlefield {
private:
    int ReleaseDay = 25;
    string ReleaseMonth = "october";
    int ReleaseYear = 2011;
public:
    void printInfo() override {
        cout << "OS: Win 7 64\n"
                "Processor: Intel Core 2 Quad Q6400 2.13GHz / AMD Phenom 9650 Quad-Core\n"
                "Graphics: AMD Radeon HD 6950 or NVIDIA GeForce GTX 560\n"
                "System Memory: 4 GB RAM\n"
                "Storage: 20 GB Hard drive space"
             << endl;
    }

    void Run() override {
        cout << ReleaseDay << ReleaseMonth << ReleaseYear;
    }

    // constructor
    Battlefield3() {
        cout << "Battlefield3 constructor called" << endl;
    }

    // destructor
    ~Battlefield3() {
        cout << "Battlefield3 destructor called" << endl;
    }
};

class Battlefield4 : public Shooter, public Battlefield {
private:
    int ReleaseDay = 29;
    string ReleaseMonth = "october";
    int ReleaseYear = 2013;
public:
    void printInfo() override {
        cout << "OS: Win 7 64\n"
                "Processor: Intel Core i7-930 Quad 2.80GHz / AMD Phenom II X6 1055T\n"
                "Graphics: AMD Radeon HD 7870 or NVIDIA GeForce GTX 660\n"
                "VRAM: 3GB\n"
                "System Memory: 8 GB RAM\n"
                "Storage: 30 GB Hard drive space\n"
             << endl;
    }

    void Run() override {
        cout << ReleaseDay << ReleaseMonth << ReleaseYear;
    }

    // constructor
    Battlefield4() {
        cout << "Battlefield4 constructor called" << endl;
    }

    // destructor
    ~Battlefield4() {
        cout << "Battlefield4 destructor called" << endl;
    }
};

class BattlefieldHardline : public Shooter, public Battlefield {
private:
    int ReleaseDay = 17;
    string ReleaseMonth = "march";
    int ReleaseYear = 2015;
public:
    void printInfo() override {
        cout << "OS: Win 8 64\n"
                "Processor: Intel Core 2 Quad Q9500 2.83GHz / AMD Phenom II X6 1045T\n"
                "Graphics: AMD Radeon R9 270X or NVIDIA GeForce GTX 760\n"
                "VRAM: 3GB\n"
                "System Memory: 8 GB RAM\n"
                "Storage: 60 GB Hard drive space\n"
             << endl;
    }

    void Run() override {
        cout << ReleaseDay << ReleaseMonth << ReleaseYear;
    }

    // constructor
    BattlefieldHardline() {
        cout << "BattlefieldHardline constructor called" << endl;
    }

    // destructor
    ~BattlefieldHardline() {
        cout << "BattlefieldHardline destructor called" << endl;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
