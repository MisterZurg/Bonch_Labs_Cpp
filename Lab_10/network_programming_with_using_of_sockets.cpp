/*
 * Лабораторная работа No10. Сетевое программирование с использованием сокетов
 * Необходимо написать программу, которая устанавливает соединение с выбранным веб сервером
 * и сохраняет на диск его корневую страницу как html файл.
 */


#include <unistd.h> // close() was not declared in this scope
#include <fstream>  // для работы с файлами

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
// Номер порта на который подключаемся
#define PORT 80 // HTTP соответственно 80 ; HTTPS 443
// IP сервера, то бишь сайта куда идём
#define SERVERADDR "128.59.105.24"
using namespace std;

int main(int argc, char *argv[]) {
    char buff[1024];
    struct sockaddr_in dest_addr;
    struct hostent *hst;
    int my_sock;
    int nsize;
// Создание сокета
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0) {
        cout << "Socket() error\n";
        return -1;
    }
// установка соединения
// заполнение структуры sockaddr_in
// указание адреса и порта сервера
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
// преобразование IP адреса из символьного вида в
// сетевой формат
    if (inet_addr(SERVERADDR) != INADDR_NONE)
        dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
// попытка получить IP адрес по доменному
// имени сервера
    if (hst = gethostbyname(SERVERADDR))
// hst->h_addr_list содержит не массив адресов,
// а массив указателей на адреса
        dest_addr.sin_addr.s_addr = *((unsigned long *) hst->h_addr_list[0]);
    else {
        cout << "Invalid address " << SERVERADDR << "\n";
        close(my_sock);
        return -1;
    }
// адрес сервера получен – пытаемся установить
// соединение
    if (connect(my_sock, (struct sockaddr *) &dest_addr,
                sizeof(dest_addr))) {
        cout << "Connect error\n";
        return -1;
    }
    cout << "Соединение с " << SERVERADDR << " успешно установлено\n";

//посылаем сообщение
// C сайта
    char msg[] = "GET /~fdc/sample.html HTTP/1.1\nHOST: www.columbia.edu\n\n";
    char answ[1024];
    send(my_sock, msg, sizeof(msg), 0);
    ssize_t len;
// Создадим объект "fout" для записи
    ofstream fout("GETreq.txt");
    while ((len = recv(my_sock, answ, 1024, 0)) > 0)
        //cout.write(buff, len);
        fout << answ;
    cout << flush;
    if (len < 0) {
        cout << "O' Oh! Error!";
    }

    fout.close();
    close(my_sock);
    return 0;
}
