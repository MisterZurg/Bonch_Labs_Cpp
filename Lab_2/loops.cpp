#include <iostream>
/*
 * Текст задания №8
 * Определить точность вычислений ЭВМ.
 * Для этого необходимо прибавлять к 1 все уменьшающиеся числа до тех пор,
 * пока текущее значение величины и ее предыдущие значения не будут совпадать.
 * Выполнить это задание для двух типов: float и double.
 */
using namespace std;

int main() {
    //Вариант для float
    float oneFl = 1;
    float twoFl = oneFl / 10;
    int i;
    for (i = 0; oneFl != twoFl; i++) {
        oneFl /= 10;
        twoFl /= 10;
        //cout <<"\n" << oneFl << " " << twoFl; //For test
    }
    cout << "Float accuracy is " << 1 << "*10^-" << i << "\n";
    //Вариант для double
    double oneDb = 1;
    double twoDb = oneDb / 10;
    int j;
    for (j = 0; oneDb != twoDb; j++) {
        oneDb /= 10;
        twoDb /= 10;
    }
    cout << "Double accuracy is " << 1 << "*10^-" << j;
    return 0;
}
