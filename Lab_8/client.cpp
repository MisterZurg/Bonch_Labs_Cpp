#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <thread>

#define MSGSZ     128

using namespace std;

struct message_buf {
    long mtype;
    char mtext[MSGSZ];
};

void sendMsgLoop(int msqid) {
    message_buf sbuf;
    size_t buf_length;
    sbuf.mtype = 2;

    while (true) {
        sleep(0.2);
        cin >> sbuf.mtext;
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            printf("%d, %l, %s, %l\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
            perror("msgsnd");
            exit(1);
        }
    }
}

void receiveMsgLoop(int msqid) {
    message_buf rbuf;

    while (true) {
        sleep(0.2);
        if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        cout << "Server: " << rbuf.mtext << endl;
    }
}

int main() {
    int msqid;
    key_t key;
    message_buf rbuf;

    /* Получаем id очереди сообщений 1234 */
    key = 1234;

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    thread tSend(sendMsgLoop, msqid);
    thread tReceive(receiveMsgLoop, msqid);
    tSend.join();
    tReceive.join();
}