/*
У файлі "MatrixMarker.cc" реалізуються методи класу MatrixMarker який 
забезпечує роботу з матрицею, пошук дублікатів та їх позначення,
а також вивід таблиці з відповідно зафарбованими клітинками
*/


/*  
Підключаємо заголовковий файл "MatrixMarker.h" у якому оголошено наш 
клас і всі його методи.
Також підключаємо стандартну бібліотеку для використання прапорців і
створення маніпуляторів потоку виводу
*/
#include "MatrixMarker.h"
#include <iomanip>
using namespace std;

/*
Конструктор класу MatrixMarker, який копіює передану матрицю в поле класу 
і ініціалізує масив marked значенням false
*/
MatrixMarker::MatrixMarker(int input[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = input[i][j];
            marked[i][j] = false;
        }
}

/* 
Метод, що перевіряє чи можно зафарбувати елемент за індексом 
по рядку та стовпцю. Перевірка відбувається проходженням по 
рядку і стовпцю в пошуках хоча б одного незафарбованого 
елемента окрім даного елемента
*/
bool MatrixMarker::isMarkAllowed(int row, int col) {
    int unmarkedInRow = 0;
    for (int j = 0; j < COLS; ++j)
        if (!marked[row][j] && j != col)
            ++unmarkedInRow;
    if (unmarkedInRow == 0) return false;

    int unmarkedInCol = 0;
    for (int i = 0; i < ROWS; ++i)
        if (!marked[i][col] && i != row)
            ++unmarkedInCol;
    return unmarkedInCol != 0;
}


/* 
Метод позначає дублікат у рядках матриці.
Для кожного рядка виконується пошук однакових за
значенням елементів, позначаються всі дублікати,
окрім одного, якщо позначення дозволене (Перевірка
здійсньється методом isMarkAllowed)
*/
void MatrixMarker::markRowDuplictes() {
    for (int i = 0; i < ROWS; ++i) {
        bool visited[COLS] = {};
        for (int j = 0; j < COLS; ++j) {
            if (visited[j]) continue;
            int count = 0, indices[COLS];

            for (int k = 0; k < COLS; ++k)
                if (matrix[i][j] == matrix[i][k]) {
                    indices[count++] = k;
                    visited[k] = true;
                }

            if (count > 1)
                for (int x = 1; x < count; ++x)
                    if (isMarkAllowed(i, indices[x]))
                        marked[i][indices[x]] = true;
        }
    }
}

/* 
Метод позначає дублікат у стовпцях матриці.
Для кожного стовпця виконується пошук однакових за
значенням елементів, позначаються всі дублікати,
окрім одного, якщо позначення дозволене (Перевірка
відубувається методом isMarkAllowed)
*/
void MatrixMarker::markColumnDuplicates() {
    for (int j = 0; j < COLS; ++j) {
        bool visited[ROWS] = {};
        for (int i = 0; i < ROWS; ++i) {
            if (visited[i]) continue;
            int count = 0, indices[ROWS];

            for (int k = 0; k < ROWS; ++k)
                if (matrix[i][j] == matrix[k][j]) {
                    indices[count++] = k;
                    visited[k] = true;
                }

            if (count > 1)
                for (int x = 1; x < count; ++x)
                    if (isMarkAllowed(indices[x], j))
                        marked[indices[x]][j] = true;
        }
    }
}

/*
Запуск алгоритма проходження по матриці
в пошуках дублікатів у рядках і стовпцях
*/
void MatrixMarker::run() {
    markRowDuplictes();
    markColumnDuplicates();
}

/* 
Функція для вирівнювання по центру числу у рядку
заданої ширини
*/
string centerText(int number, int width) {
    string str = to_string(number);
    int padding = width - static_cast<int>(str.length());
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    return string(padLeft, ' ') + str + string(padRight, ' ');
}

/*
Функція, що виводить горизонтальну грань матриці
*/
void printHorizontalLine(int cols, int cellWidth) {
    for (int i = 0; i < cols; ++i) {
        cout << "+";
        for (int j = 0; j < cellWidth; ++j)
            cout << "-";
    }
    cout << "+\n";
}

/*
Метод, що виводить матрицю у відформатованому вигляді
для граного та візуально зрозумілого подання. Вивід відбувається за
такою логікою - непозначені елементи виводяться з
використанням кольору, а позначені виводяться у
звичайному чорному вигляді
*/
void MatrixMarker::print() const {
    const int cellWidth = 8;
    const int cellHeight = 3;

    for (int i = 0; i < ROWS; ++i) {
        printHorizontalLine(COLS, cellWidth);

        for (int h = 0; h < cellHeight; ++h) {
            for (int j = 0; j < COLS; ++j) {
                cout << "|";
                bool isHighlighted = !marked[i][j];
                string content;

                if (h == cellHeight / 2) {
                    content = centerText(matrix[i][j], cellWidth);
                } else {
                    content = string(cellWidth, ' ');
                }

                if (isHighlighted)
                    cout << COLOR << content << RESET;
                else
                    cout << content;
            }
            cout << "|\n";
        }
    }

    printHorizontalLine(COLS, cellWidth);
}