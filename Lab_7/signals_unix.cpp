#include <cstdlib>
#include <unistd.h>
// Задание № 4
// Напишите «часы», выдающие текущее время каждые 3 секунды.
using namespace std;

void Delay() {
    sleep(3);
}

int main() {
    for (;;) {
        system("date")
        Delay();
    }
    return 0;
}
