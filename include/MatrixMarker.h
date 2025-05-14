#pragma once
#include "Config.h"
#include <string>

class MatrixMarker {
public:
    MatrixMarker(int input[Config::ROWS][Config::COLS]);
    void process();
    void print() const;

private:
    int matrix[Config::ROWS][Config::COLS];
    bool marks[Config::ROWS][Config::COLS];

    bool canMark(int row, int col);
    void findDuplicatesInRows();
    void findDuplicatesInCols();
};
