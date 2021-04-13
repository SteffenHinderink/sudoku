#include <iostream>
#include <vector>
#include <fstream>

void draw(std::vector<int> sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << (sudoku[9 * i + j] == 0 ? " " : std::to_string(sudoku[9 * i + j])) << " ";
        }
        std::cout << std::endl;
    }
}

bool solve(std::vector<int> sudoku) {
    bool solved = true;
    for (int i = 0; i < 9 && solved; i++) {
        for (int j = 0; j < 9 && solved; j++) {
            if (sudoku[9 * i + j] == 0) {
                solved = false;
            }
        }
    }
    if (solved) {
        draw(sudoku);
        return true;
    }
    std::vector<std::vector<int>> options(81);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::vector<bool> valid(9, true);
            if (sudoku[9 * i + j] == 0) {
                for (int row = 0; row < 9; row++) {
                    if (sudoku[9 * row + j] != 0) {
                        valid[sudoku[9 * row + j] - 1] = false;
                    }
                }
                for (int col = 0; col < 9; col++) {
                    if (sudoku[9 * i + col] != 0) {
                        valid[sudoku[9 * i + col] - 1] = false;
                    }
                }
                for (int row = 3 * (i / 3); row < 3 * (i / 3) + 3; row++) {
                    for (int col = 3 * (j / 3); col < 3 * (j / 3) + 3; col++) {
                        if (sudoku[9 * row + col] != 0) {
                            valid[sudoku[9 * row + col] - 1] = false;
                        }
                    }
                }
                for (int k = 0; k < 9; k++) {
                    if (valid[k]) {
                        options[9 * i + j].push_back(k + 1);
                    }
                }
            }
        }
    }
    int min = 9;
    int index = 0;
    for (int i = 0; i < 81; i++) {
        if (options[i].size() > 0 && options[i].size() < min) {
            min = options[i].size();
            index = i;
        }
    }
    for (int i = 0; i < options[index].size(); i++) {
        std::vector<int> copy = sudoku;
        copy[index] = options[index][i];
        if (solve(copy)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    std::ifstream file(argv[1]);
    int x;
    std::vector<int> sudoku;
    while (file >> x) {
        sudoku.push_back(x);
    }
    draw(sudoku);
    std::cout << std::endl;
    solve(sudoku);
    return 0;
}
