#include <iostream>
#include <string>
using namespace std;
#include <cctype>

int **fillTable(const string string1, const string string2, int size, int &maxLength, int &location)
{
    int **array = new int *[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = new int[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // On hit
            if (string1[i] == string2[j])
            {
                // Record for table
                array[i][j] = (i > 0 && j > 0) ? array[i - 1][j - 1] + 1 : 1;

                // Check if the current substring is longer than the recorded max
                if (array[i][j] > maxLength)
                {
                    maxLength = array[i][j];
                    location = i;
                }
            }
            else
            {
                array[i][j] = 0;
            }
        }
    }

    return array;
}

void printString(const string string1, const string string2, int maxLength, int location)
{
    cout << "strings: " << string1 << " and " << string2 << "\n";
    cout << "Longest Common Substring: ";

    if (maxLength > 0)
    {
        string substring = string1.substr(location - maxLength + 1, maxLength);
        cout << substring << " (Length: " << maxLength << ")";
    }
    else
    {
        cout << "No common substring found.";
    }

    cout << "\n";
}

// delete for mem
void delete2DArray(int **arr, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

void printTable(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << std::endl;
    }
}

string input(int size)
{
    std::cout << "Enter String - " << size << " letters: ";
    std::string result = "";

    for (int i = 0; i < 10; ++i)
    {
        char inputChar;
        std::cin >> inputChar;

        if (inputChar == '\n')
        {
            break; // Exit the loop if Enter key is pressed
        }

        result += std::toupper(inputChar);
    }

    return result;
}

int main()
{
    cout << "Enter String Length: ";
    int stringLength;
    cin >> stringLength;

    string string1 = input(stringLength);
    string string2 = input(stringLength);

    int maxLength = 0;
    int location = 0;

    int **substringTable = fillTable(string1, string2, stringLength, maxLength, location);

    printTable(substringTable, stringLength);
    delete2DArray(substringTable, stringLength);
    printString(string1, string2, maxLength, location);

    return 0;
}