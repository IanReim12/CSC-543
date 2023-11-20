#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

// Node Object
struct Node
{
    int distance;
    bool visited;
};

void printMatrix(const int graphMatrix[][6], int size, const char vertices[])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == 0 || j == 0)
            {
                cout << vertices[std::abs(graphMatrix[i][j])] << " ";
            }
            else
            {
                cout << graphMatrix[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

void printDistance(const int graphMatrix[][6], int size, const char vertices[])
{
    for (int i = 1; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (graphMatrix[i][j] != 0)
            {
                cout << vertices[i] << vertices[j] << " " << graphMatrix[i][j] << ": ";
            }
        }
    }
    cout << "\n";
}

int getUserStart()
{
    char startNode;
    int returnStartNode;
    cout << "Enter Start Node A-E: ";
    cin >> startNode;
    // ensure upper
    startNode = toupper(startNode);

    switch (startNode)
    {
    case 'A':
        returnStartNode = 1;
        break;
    case 'B':
        returnStartNode = 2;
        break;
    case 'C':
        returnStartNode = 3;
        break;
    case 'D':
        returnStartNode = 4;
        break;
    case 'E':
        returnStartNode = 5;
        break;
    default:
        cout << "Incorrect value";
        returnStartNode = -99999;
    }
    return returnStartNode;
}

int getUserEnd()
{
    char endNode;
    int returnEndNode;
    cout << "Enter End Node A-E: ";
    cin >> endNode;

    // ensure upper
    endNode = toupper(endNode);

    switch (endNode)
    {
    case 'A':
        returnEndNode = 1;
        break;
    case 'B':
        returnEndNode = 2;
        break;
    case 'C':
        returnEndNode = 3;
        break;
    case 'D':
        returnEndNode = 4;
        break;
    case 'E':
        returnEndNode = 5;
        break;
    default:
        cout << "Incorrect value";
        returnEndNode = -99999;
    }

    return returnEndNode;
}

void getFastestPath(const int graphMatrix[][6], int size, const char vertices[], int start, int end)
{
    // Initialize array of node objects
    Node nodes[size];
    for (int i = 0; i < size; ++i)
    {
        // Set each node value distance to infinety and not visited
        nodes[i].distance = std::numeric_limits<int>::max();
        nodes[i].visited = false;
    }

    // Distance of starting node to self = 0
    nodes[start].distance = 0;

    
    for (int count = 0; count < size - 1; ++count)
    {
        // initiate minDistance to infinity
        int minDistance = std::numeric_limits<int>::max();
        int minDistanceNode = -1;

        // iterate through each node
        for (int j = 0; j < size; ++j)
        {
            // Skip the first column and row
            int index = (j == 0) ? 1 : j;
            if (!nodes[index].visited && nodes[index].distance <= minDistance)
            {
                minDistance = nodes[index].distance;
                minDistanceNode = index;
            }
        }

        // Mark the selected node as visited
        nodes[minDistanceNode].visited = true;

        // Update the distance values of the neighboring nodes
        for (int j = 0; j < size; ++j)
        {
            // Skip the first column and row
            int index = (j == 0) ? 1 : j;
            // Check for shorter unvisted path
            if (!nodes[index].visited && graphMatrix[minDistanceNode][index] && nodes[minDistanceNode].distance + graphMatrix[minDistanceNode][index] < nodes[index].distance)
            {
                // Updtate cost
                nodes[index].distance = nodes[minDistanceNode].distance + graphMatrix[minDistanceNode][index];
            }
        }
    }

    // Print the shortest path from start to end
    cout << "Shortest Path from " << vertices[start] << " to " << vertices[end] << ": " << nodes[end].distance << "\n";
}

int main()
{
    // Node Labels
    const char vertices[] = {'X', 'A', 'B', 'C', 'D', 'E'};
    const int size = 6;

    // User input
    int startNode = getUserStart();
    int endNode = getUserEnd();
    // cout << startNode << "   ";
    // cout << "\n";
    // cout << endNode << "   ";
    // cout << "\n";

    // First row and column will be replaced by vertices array
    int graphMatrix[size][size] = {
        {0, 1, 2, 3, 4, 5},
        {1, 0, 1, 3, 0, 0},
        {2, 1, 0, 5, 8, 0},
        {3, 3, 5, 0, 0, 9},
        {4, 0, 8, 0, 0, 5},
        {5, 0, 0, 9, 5, 0}};

    printMatrix(graphMatrix, size, vertices);
    getFastestPath(graphMatrix, size, vertices, startNode, endNode);
    // printDistance(graphMatrix, size, vertices);

    return 0;
}