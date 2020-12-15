 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/sem.h>
 #include <iostream>

#define KEY (149212)

using namespace std;

int main()
{
    int id; 

    union semun {
        int val;
        struct semid_ds *buf;
        ushort * array;
    } argument;
    argument.val = 0;

    id = semget(KEY, 1, 0666 | IPC_CREAT);

    if (id < 0) 
    {
        cerr << "Unable to obtain semaphore.\n"; exit(0);
        id = semget(KEY, 1, 0666 | IPC_CREAT);
    }

    if (semctl(id, 0, SETVAL, argument) < 0)
    {
        cerr << "Cannot set semaphore value.\n";
    }

    else 
    {
        cerr << "Semaphore " << KEY << " initialized.\n";
    }

    int val;

    struct sembuf operations[1];
    int retval;

    while (true)
    {
        cout << "Current semaphore value: " << semctl(id, 0, GETVAL, argument) << endl;

        cout << "Изменить значение семафора на: ";
        cin >> val;

        operations[0].sem_num = 0;
        operations[0].sem_op = val;
        operations[0].sem_flg = 0;
        
        retval = semop(id, operations, 1);

        if(retval == 0)
        {
            cout << "P-operation succeed.\n\n";
        }

        else
        {
            cout << "P-operation failed.\n\n";
        }
    }
    return 0;
}


