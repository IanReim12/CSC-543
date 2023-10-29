#include <iostream>

int main()
{
    int target = 8;
    int numberArray[] = {1, 5, 2, 1, 3, 4};
    int answerArray[2];

    int arraySize = sizeof(numberArray) / sizeof(numberArray[0]);
    
    for (int i = 0; i < arraySize; i++){
        for (int j = i + 1; j < arraySize; j++) {
            if (numberArray[i] + numberArray[j] == target) {
                answerArray[0] = i;
                answerArray[1] = j;
                std::cout << answerArray[0];
                std::cout << answerArray[1];
                return 0;
            }
        }
    }


    
    return 0;
    }
