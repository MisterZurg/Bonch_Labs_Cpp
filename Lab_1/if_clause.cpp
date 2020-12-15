#include <iostream>
#include <cmath>
/*
 * Тражиционная точка в области
 */
using namespace std;

int main() {
    double x, y;
    cout << "Input x" << endl;
    cin >> x;
    cout << "Input y" << endl;
    cin >> y;

//Line
    double xL_1 = 0, yL_1 = 11, xL_2 = 12, yL_2 = 10, //kL -> коэф. наклона.
    kL = (yL_1 - yL_2) / (xL_1 - xL_2), bL = yL_1 - kL * xL_1;
//Circle
    double xC = 8, yC = 4, rC = 2;

//Проверяем выше линии
    if (y > (kL * x + bL)) {
        if (2 <= x && x <= 8 && 4 <= y && y <= 9) { //Проверяем в квадрате
            cout << "2" << endl;
        } else {
            cout << "1" << endl;
        }
    } else if ((pow(x - xC, 2) + pow(y - yC, 2)) <= pow(rC, 2)) { //Проверяем в круге
        if (6 <= x && x <= 8 && 4 <= y && y <= 6) {
            cout << "4" << endl;
        } else {
            cout << "5" << endl;
        }
    } else if (3 <= x && x <= 8 && 4 <= y) { //Проверяем вне круга в квадрате
        cout << "3" << endl;
    } else {
        cout << "6" << endl;
    }
}
