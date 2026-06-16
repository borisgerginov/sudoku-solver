#include <iostream>

unsigned const int SIZE = 9;
std::size_t counter = 0;    //ще брои решенията

bool areRowsValid(int board[][SIZE], std::size_t currRow)
{
    if (currRow == SIZE) return true;   //ако currRow стигне SIZE, редовете са валидни

    int bufferRows[SIZE] = {0};     //в буфера на място i запазваме колко пъти сме срещнали числото i
    for (std::size_t currCol = 0; currCol < SIZE; ++currCol)
    {
        if (board[currRow][currCol] != 0) //проверка, защото функцията ще проверява и непопълнени таблици
        {
            if (bufferRows[board[currRow][currCol]-1] > 0) return false;
            else ++bufferRows[board[currRow][currCol]-1];
        }
    }

    return areRowsValid(board, currRow + 1);
}

bool areColsValid(int board[][SIZE], std::size_t currCol)
{
    if (currCol == SIZE) return true;

    int bufferCols[SIZE] = {0};
    for (std::size_t currRow = 0; currRow < SIZE; ++currRow)
    {
        if (board[currRow][currCol] != 0)
        {
            if (bufferCols[board[currRow][currCol]-1] > 0) return false;
            else ++bufferCols[board[currRow][currCol]-1];
        }
    }

    return areColsValid(board, currCol + 1);
}

bool areSquaresValid(int board[][SIZE], std::size_t squareIndex) //ако разделим таблицата на 9 квадрата, 3х3 squareIndex е номера на квадрата, който проверяваме
{
    if (squareIndex == SIZE) return true;

    std::size_t startRow = (squareIndex / 3) * 3;
    std::size_t startCol = (squareIndex % 3) * 3;
    int buffer[SIZE] = {0};

    for (std::size_t row = startRow; row < startRow + 3; ++row)
    {
        for (std::size_t col = startCol; col < startCol + 3; ++col)
        {
            if (board[row][col] != 0)
            {
                if (buffer[board[row][col]-1] > 0) return false;
                buffer[board[row][col]-1]++;
            }
        }
    }

    return areSquaresValid(board, squareIndex + 1);
}

bool isSudokuValid(int board[][SIZE])
{
    return areRowsValid(board, 0) && areColsValid(board, 0) && areSquaresValid(board, 0);
}

void printSudoku(int board[][SIZE])
{
    std::cout << "Sudoku " << counter << ":" << std::endl;

    for (std::size_t i = 0; i < SIZE; ++i)
    {
        for (std::size_t j = 0; j < SIZE; ++j)
        {
            std::cout << board[i][j];
            if(j%3 == 2 && j != 8) std::cout << '|';
            else std::cout << ' ';
        }
        std::cout << std::endl;
        if(i%3 == 2 && i != 8) std::cout << "-----|-----|------" << std::endl;
    
    }
    std::cout << std::endl;
}

void sudokuSolver(int board[][SIZE], std::size_t currRow, std::size_t currCol)
{
    if (currRow == SIZE)   //намерили сме валидна дъска
    {
        ++counter;
        printSudoku(board);
        return;
    }

    std::size_t nextRow, nextCol;
    if (currCol == SIZE - 1)        //проверка дали редът е приключил
    {
        nextRow = currRow + 1;      //nextRow и nextCol са индексите, с които ще извикваме рекурсията
        nextCol = 0;
    }
    else                            //ако редът не е приключил, увеличаваме колоната с 1
    {
        nextRow = currRow;
        nextCol = currCol + 1;
    }

    if (board[currRow][currCol] != 0)
    {
        return sudokuSolver(board, nextRow, nextCol);
    }

    for (unsigned i = 1; i <= 9; ++i) 
    {
        board[currRow][currCol] = i;
        if (isSudokuValid(board))  //проверка дали при добавяне на ново число в судокуто то остава валидно
        {
            sudokuSolver(board, nextRow, nextCol);
        }
        board[currRow][currCol] = 0; //зануляваме конкретното поле, за да си осигурим, че рекурсията не работи с остатъчни стойности
    }
}

int main()
{
    //Тестове:
    
    int board[SIZE][SIZE] =
    {
    {3, 0, 6,  5, 0, 8,  4, 0, 0},
    {5, 2, 0,  0, 0, 0,  0, 0, 0},
    {0, 8, 7,  0, 0, 0,  0, 3, 1},

    {0, 0, 3,  0, 1, 0,  0, 8, 0},
    {9, 0, 0,  8, 6, 3,  0, 0, 5},
    {0, 5, 0,  0, 9, 0,  6, 0, 0},

    {1, 3, 0,  0, 0, 0,  2, 5, 0},
    {0, 0, 0,  0, 0, 0,  0, 7, 4},
    {0, 0, 5,  2, 0, 6,  3, 0, 0}
    };

    sudokuSolver(board,0,0);
    if(counter == 1) std::cout << "The sudoku is valid";
    else std::cout << "The sudoku is not valid";

    return 0;
}