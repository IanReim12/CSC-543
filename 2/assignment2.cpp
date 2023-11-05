#include <iostream>

int getUserDimensions(char dimension)
{
    int dimensionVal;
    std::cout << "Enter the sparceMatrix [" << dimension << "] value:";
    std::cin >> dimensionVal;
    return dimensionVal;
}

int **createMatrix(int dimensionX, int dimensionY)
{
    // for each x, you have y number of columns assosiated - 2d matrix
    int **matrix = new int *[dimensionX];
    for (int i = 0; i < dimensionX; i++)
    {
        matrix[i] = new int[dimensionY];
    }
    return matrix;
}

void fillMatrix(int **matrix, int dimensionX, int dimensionY)
{
    for (int i = 0; i < dimensionX; i++)
    {
        for (int j = 0; j < dimensionY; j++)
        {
            std::cout << "Enter a value for matrix[" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

void deleteMatrix(int **matrix, int dimensionX)
{
    for (int i = 0; i < dimensionX; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int **matrix, int dimensionX, int dimensionY)
{
    for (int i = 0; i < dimensionX; i++)
    {
        for (int j = 0; j < dimensionY; j++)
        {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

int setValArray(int **matrix, int dimensionX, int dimensionY)
{
    int count = 0;
    for (int i = 0; i < dimensionX; i++)
    {
        for (int j = 0; j < dimensionY; j++)
        {
            if (matrix[i][j] != 0)
            {
                count++;
            }
        }
    }
    return count;
}

int *fillValArray(int **matrix, int dimensionX, int dimensionY, int valArraySize)
{
    int *valArray = new int[valArraySize];
    int valCount = 0;
    for (int i = 0; i < dimensionX; i++)
    {
        for (int j = 0; j < dimensionY; j++)
        {
            if (matrix[i][j] != 0)
            {
                valArray[valCount] = matrix[i][j];
                valCount++;
            }
        }
    }
    return valArray;
}

int *fillRowArray(int **matrix, int dimensionX, int dimensionY, int rowArraySize)
{
    int *rowArray = new int[rowArraySize];
    int rowCount = 0;
    for (int i = 0; i < dimensionX; i++)
    {
        for (int j = 0; j < dimensionY; j++)
        {
            if (matrix[i][j] != 0)
            {
                rowArray[rowCount] = i;
                rowCount++;
            }
        }
    }
    return rowArray;
}

int *fillColArray(int **matrix, int dimensionX, int dimensionY, int colArraySize)
{
    int *colArray = new int[colArraySize];
    int colCount = 0;
    for (int i = 0; i < dimensionX; i++)
    {
        for (int j = 0; j < dimensionY; j++)
        {
            if (matrix[i][j] != 0)
            {
                colArray[colCount] = j;
                colCount++;
            }
        }
    }
    return colArray;
}

void printArray(const int *arr, int size, const char *label)
{
    std::cout << label << ": ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

//-----------------------------------------------------------------------------------------------------------------

int main()
{
    // int sparseMatrix[5][4] = {
    //     {0, 0, 3, 0},
    //     {0, 6, 0, 8},
    //     {0, 0, 0, 12},
    //     {0, 14, 0, 0},
    //     {0, 0, 19, 0}};

    // Fill dimensions
    int dimensionX = getUserDimensions('X');
    int dimensionY = getUserDimensions('Y');

    // Create Matrix - ** = pointer to a pointer pointing at an integer represents 2d arrays
    int **sparseMatrix = createMatrix(dimensionX, dimensionY);

    // Fill the matrix with user input.
    fillMatrix(sparseMatrix, dimensionX, dimensionY);

    int count = setValArray(sparseMatrix, dimensionX, dimensionY);

    int *answerRow;    // vertical
    int *answerColumn; // horizontal
    int *answerValue;

    answerRow = fillRowArray(sparseMatrix, dimensionX, dimensionY, count);
    answerColumn = fillColArray(sparseMatrix, dimensionX, dimensionY, count);
    answerValue = fillValArray(sparseMatrix, dimensionX, dimensionY, count);

    printArray(answerRow, count, "Row");
    printArray(answerColumn, count, "Col");
    printArray(answerValue, count, "Val");

    printMatrix(sparseMatrix, dimensionX, dimensionY);

    deleteMatrix(sparseMatrix, dimensionX);
    delete[] answerValue;
    delete[] answerColumn;
    delete[] answerValue;
    return 0;
}