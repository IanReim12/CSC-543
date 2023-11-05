#include <iostream>

struct Node {
    int row;
    int column;
    int value;
    Node* next;
};

Node* createNode(int row, int column, int value) {
    Node* newNode = new Node;
    newNode->row = row;
    newNode->column = column;
    newNode->value = value;
    newNode->next = nullptr;
    return newNode;
}

void addNode(Node*& head, int row, int column, int value) {
    Node* newNode = createNode(row, column, value);

      if (head == nullptr) {
        // If the list is empty, make the new node the first node.
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printLinkedList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Row: " << current->row << ", Column: " << current->column << ", Value: " << current->value << std::endl;
        current = current->next;
    }
}

int getUserDimensions(char dimension) {
    int dimensionVal;
    std::cout << "Enter the sparceMatrix [" << dimension << "] value:";
    std::cin >> dimensionVal;
    return dimensionVal;
}

int **createMatrix(int dimensionX, int dimensionY) {
    int **matrix = new int *[dimensionX];
    for (int i = 0; i < dimensionX; i++) {
        matrix[i] = new int[dimensionY];
    }
    return matrix;
}

void fillMatrix(int **matrix, int dimensionX, int dimensionY) {
    for (int i = 0; i < dimensionX; i++) {
        for (int j = 0; j < dimensionY; j++) {
            std::cout << "Enter a value for matrix[" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

void deleteMatrix(int **matrix, int dimensionX) {
    for (int i = 0; i < dimensionX; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int **matrix, int dimensionX, int dimensionY) {
    for (int i = 0; i < dimensionX; i++) {
        for (int j = 0; j < dimensionY; j++) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

int main() {
    Node* head = nullptr;

    int dimensionX = getUserDimensions('X');
    int dimensionY = getUserDimensions('Y');

    int **sparseMatrix = createMatrix(dimensionX, dimensionY);

    fillMatrix(sparseMatrix, dimensionX, dimensionY);

    for (int i = 0; i < dimensionX; i++) {
        for (int j = 0; j < dimensionY; j++) {
            if (sparseMatrix[i][j] != 0) {
                addNode(head, i, j, sparseMatrix[i][j]);
            }
        }
    }
    printLinkedList(head);
    printMatrix(sparseMatrix, dimensionX, dimensionY);
    deleteMatrix(sparseMatrix, dimensionX);

    return 0;
}