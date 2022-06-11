# Лабораторная работа №10. Сетевое программирование с использованием сокетов
## Цели работы
1. Получение навыков при работе с сокетами.
## Используемое программное обеспечение
При выполнении лабораторной работы будет использовано следующие программное обеспечение: gcc – компилятор С/С++, vi – текстовый редактор.
## Порядок выполнения лабораторной работы
1. Войти в систему Linux, указав имя и пароль, предварительно получив их у администратора.
2. В каталоге вашей группы создать файл программу с расширением *.сpp по варианту.
3. Написать программу на тему «Работа с сокетами в Unix».
4. Собрать программу.
5. Исполнить программу
## Пример создания сокета
Программа устанавливает соединение с заданным хостом получает и посылает ему информацию.
```cpp
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define PORT 666
#define SERVERADDR "127.0.0.1"

using namespace std;
int main(int argc, char* argv[]){
    char buff[1024];
    struct sockaddr_in dest_addr;
    struct hostent *hst;
    int my_sock;
    int nsize;
    
    // создание сокета
    my_sock=socket(AF_INET,SOCK_STREAM,0);
    if (my_sock < 0) {
        cout << "Socket() error\n";
    return -1;
    }
    
    // установка соединения
    
    // заполнение структуры sockaddr_in
    // указание адреса и порта сервера
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(PORT);
    
    // преобразование IP адреса из символьного в
    // сетевой формат
    if (inet_addr(SERVERADDR)!=INADDR_NONE)
        dest_addr.sin_addr.s_addr=inet_addr(SERVERADDR);
    else
    // попытка получить IP адрес по доменному
    // имени сервера
        if (hst=gethostbyname(SERVERADDR))
        // hst->h_addr_list содержит не массив адресов,
        // а массив указателей на адреса
            dest_addr.sin_addr.s_addr= *((unsigned long *) hst->h_addr_list[0]);
        else {
            cout << "Invalid address " << SERVERADDR << "\n";
            close(my_sock);
            return -1;
        }

    // адрес сервера получен – пытаемся установить
    // соединение
    if (connect(my_sock,(struct sockaddr *)&dest_addr, sizeof(dest_addr))) {
        cout << "Connect error\n";
        return -1;
    }
    
    cout << "Соединение с " << SERVERADDR << " успешно установлено\n";
    
    // чтение и передача сообщений
    recv(my_sock, &buff[0], sizeof(buff) - 1, 0);
    // ставим завершающий ноль в конце строки
    buff[nsize]=0;
    
    // выводим на экран
    cout<<buff<<"\n";
    
    //посылаем сообщение
    strcpy(buff, "Privet!");
    send(my_sock, buff, strlen(buff) + 1, 0);
    
    close(my_sock);
    return -1;
}
```