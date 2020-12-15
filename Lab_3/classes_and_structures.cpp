#include <iostream>
#include <cmath>

using namespace std;
/*
 Текст задания №8
 Patient:
      Фамилия,
      Имя,
      Отчество,
      Адрес,
 Номер медицинской карты,
 Диагноз.
 Создать массив объектов.

 Вывести:
 а) список пациентов, имеющих данный диагноз;
 б) список пациентов, номер медицинской карты которых находится в заданном интервале.
 Разработать классы для описанных ниже объектов.
 Включить в класс методы set (...), get (...), show (...).
 Определить другие методы.
*/
struct Person {

    string LastName,
            FirstName,
            FamilyName,
            Address;
};

class Patient {
private:
    Person personalData;
    int HealthRecordNumber;
    string Diagnosis;
public:
    void setPerson() {
        cout << "~~~~~~~~~~~~~~~~~~~~~~\n"; //(╯ ͠° ͟ʖ ͡°)╯┻━┻
        cout << "Input patient's Name: ";
        cin >> personalData.FirstName;
        cout << "Input patient's LastName: ";
        cin >> personalData.LastName;
        cout << "Input patient's FamilyName: ";
        cin >> personalData.FamilyName;
        cout << "Input patient's Address: ";
        cin >> personalData.Address;

    }

    void setDiagnosis() {
        cout << "Input HealthRecordNumber: ";
        cin >> HealthRecordNumber;
        cout << "Input patient's Diagnosis: ";
        cin >> Diagnosis;
    }

    void getInfo(int patientNumber) {

        cout << "Patient No " << patientNumber << "\n";
        cout << "LastName   " << personalData.LastName << "\n";
        cout << "FirstName  " << personalData.FirstName << "\n";
        cout << "LastName   " << personalData.FamilyName << "\n";
        cout << "HealthRecordNumber " << HealthRecordNumber << "\n";
        cout << "Diagnosis  " << Diagnosis << "\n";
    }

    // Cписок пациентов, имеющих данный диагноз
    void getPatientByDiagnosis(string diagnosis, int range, Patient patientArray[]) {
        //Объекты типа bool неявно преобразуются.
        // Значение true превращается в 1, а false – в 0.
        //(╯ ͠° ͟ʖ ͡°)╯┻━┻
        bool token = 0;
        cout << "Patient with Diagnosis :\"" << diagnosis << "\"\n";;
        for (int i = 0; i < range; i++) {
            if (patientArray[i].Diagnosis == diagnosis) {
                token = 1;
                cout << "Patient No " << i <<
                     " " << patientArray[i].personalData.FirstName <<
                     " " << patientArray[i].personalData.LastName <<
                     " " << patientArray[i].personalData.FamilyName << "\n";
            }
        }
        if (token == 0) {
            cout << "Nobody was found with that Diagnosis\n";
        }
    }

    //Cписок пациентов, номер медицинской карты которых находится в заданном интервале.
    void getPatientByMedCardDiapozone(int from, int to, int range, Patient patientArray[]) {
        bool token = 0;
        cout << "Patient with CardDiapozone from " << from << "to " << to << ":\n";
        for (int i = 0; i < range; i++) {
            if (from <= patientArray[i].HealthRecordNumber &&
                patientArray[i].HealthRecordNumber <= to) {
                token = 1;
                cout << "Patient No " << i <<
                     " MedCard No " << patientArray[i].HealthRecordNumber <<
                     " " << patientArray[i].personalData.FirstName <<
                     " " << patientArray[i].personalData.LastName <<
                     " " << patientArray[i].personalData.FamilyName << "\n";
            }
        }
        if (token == 0) {
            cout << "Nobody was found with that Diapozone\n";
        }

    }
};

int main() {

    Patient *PatientsArray;
    int numOfPatients;
    cout << "Input a number of patients: ";
    cin >> numOfPatients;
    PatientsArray = new Patient[numOfPatients];  //Массив пацанчиков класса Пациент
    for (int i = 0; i < numOfPatients; i++) {
        PatientsArray[i].setPerson();
        PatientsArray[i].setDiagnosis();
    }
    for (int i = 0; i < numOfPatients; i++) {
        PatientsArray[i].getInfo(i);
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~\n";
    PatientsArray->getPatientByDiagnosis("cough", numOfPatients, PatientsArray);
    cout << "~~~~~~~~~~~~~~~~~~~~~~\n";
    PatientsArray->getPatientByMedCardDiapozone(1, 10, numOfPatients, PatientsArray);

    return 0;

}

