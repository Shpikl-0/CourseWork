/* 
Файл task26.cc є точкою входу в програму.
Тут ініцалізується матрия, створюється 
об'єкт класу MatrixMarker і надає користувачу
за допомогою меню керувати перетвореннями матриці
*/

#include "../include/MatrixMarker.h"
using namespace std;

void option(int choice, MatrixMarker marker);       //Прототип функції яка обробляє вибір користувача у меню

int main() {
    int choice;                     // Змінна для опрацювання вибору користувача
    int Matrix[ROWS][COLS] = {      // Початкова матриця дана в завданні
        {1,1,4,3,4,1,3,2,2},
        {1,1,2,3,2,1,3,2,2},
        {3,2,1,4,3,3,2,1,3},
        {4,3,4,2,3,1,1,2,4},
        {4,2,1,1,2,3,3,4,1},
        {2,2,3,3,4,4,4,1,2},
        {2,3,3,1,3,2,2,4,1},
        {4,4,2,1,3,1,2,3,3},
        {4,4,2,1,1,1,2,3,3}
    };

    MatrixMarker marker(Matrix);    // Cтворення об'єкту класу MatrixMarker

    //Виведення довідки для користувача, що може програма
    cout << "This program can color the cells of a matrix so that there\nis at least 1 non-colored element in each column and row\n";

    /* 
    Головний цикл за допомогою якого реалізується меню
    */
    while(choice != 3)
    { 
        cout << "Menu:\n"
            << "1.Show initial matrix\n"
            << "2.Convert matrix\n"
            << "3.Exit\n";

        do{
            cout << "Choice the option: ";
            cin  >> choice;


            if (cin.fail()) {       //Перевірка на правильність введень користувача
                cin.clear();                
                cin.ignore(1000, '\n');    
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            if(choice == 1 || choice == 2 || choice == 3)
                break;
            cout << "Wrong choice, choose existing option!\n";
        }while(1);

        option(choice, marker);
    }

    return 0;
}

/* 
Реалізація функції яка обробляє ввeдeння користувача
*/
void option(int choice, MatrixMarker marker){
    switch (choice){
        case 1:
            cout << "Initial matrix:\n";
            marker.print();
            break;
        case 2:
            cout << "\nConvert matrix:\n";
            marker.run(); 
            marker.print();
            break;
        case 3:
            cout << "The program ends";
            break;
    }
}