#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

// Huffman Node structure definition
struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode* left, * right;

    // initialize huffman node by providing data and frequency. Sets left and rights to null
    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

bool compareNodes(HuffmanNode* left, HuffmanNode* right) {
    return left->frequency > right->frequency;
}


// returns a pointer to huffman node  ----- Takes ref to const string and vecrtor as params
HuffmanNode* buildHuffManTree(const string& characters, const vector<unsigned>& frequencies) {
    //create priority queue minHeap  ---- contains pointers to huffManNode
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(&compareNodes)> minHeap(&compareNodes);  // specifiies type of of compare nodes function based on reference 
    

    // create huffman node for each char populate min heap
    for (size_t i = 0; i < characters.size(); ++i) {
        minHeap.push(new HuffmanNode(characters[i], frequencies[i]));
    }


    // loop as long as there is 1 nod ein priority q
    while (minHeap.size() > 1) {
        // popu left & right with top 2 nodes
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();


        // the -> is used to access member of a class trough a pointer, $ represents the new internal node char
        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root) {
        if (!root->left && !root->right) {
            huffmanCodes[root->data] = code;
        }

        generateHuffmanCodes(root->left, code + '0', huffmanCodes);
        generateHuffmanCodes(root->right, code + '1', huffmanCodes);
    }
}

void printHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << "  ";
    }
    cout << endl;
}

string input(int size) {
    cout << "Enter String - " << size << " letters: ";
    string result = "";

    for (int i = 0; i < size; ++i) {
        char inputChar;
        cin >> inputChar;

        result += inputChar;
    }

    return result;
}

vector<unsigned> inputFrequencies(int size) {
    vector<unsigned> frequencies;
    frequencies.reserve(size);

    cout << "Enter Frequencies - " << size << " values: ";
    for (int i = 0; i < size; ++i) {
        unsigned frequency;
        cin >> frequency;

        frequencies.push_back(frequency);
    }

    return frequencies;
}



int main() {

    cout << "Enter String Length: ";
    int stringLength;
    cin >> stringLength;


    string inputString = input(stringLength);
    vector<unsigned> frequencies = inputFrequencies(stringLength);



    // const size_t arraySize = 6;
    // const string inputString = "abcdef";
    // const vector<unsigned> frequencies = {5, 9, 12, 13, 16, 45};

    HuffmanNode* root = buildHuffManTree(inputString, frequencies);
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);
    printHuffmanCodes(huffmanCodes);

    return 0;
}