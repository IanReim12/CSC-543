#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <bitset>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

//  --- Global Constants ---
// Step 3) --------------------------
const unsigned int k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
//--------------------------------------
//  ------------------------

// Functions

// Pre Processing Functions ---
string convertToBinary(string &input)
{
        string binaryString = "";
        for (char c : input)
        {
                binaryString += bitset<8>(c).to_string(); // create bitset of size 8 based on current char in input.
        }
        return binaryString;
}

string applyPadding(const string &binaryInput)
{
        size_t originalLength = binaryInput.length();
        cout << "originalLength: " << originalLength << '\n';

        string paddedInput = binaryInput + '1';

        size_t totalLength = ((originalLength + 1 + 64 + 511) / 512) * 512;
        size_t zeroPaddingLength = totalLength - originalLength - 1 - 64;

        paddedInput.append(zeroPaddingLength, '0');

        paddedInput += bitset<64>(originalLength).to_string();

        return paddedInput;
}

string appendLength(string &paddedInput, int inputLength)
{
        string lengthBits = bitset<64>(inputLength).to_string();
        paddedInput.replace(paddedInput.length() - 64, 64, lengthBits);
        return paddedInput;
}
//-----------------------------

// Chunk Loop ---

// Helper functions ---
uint32_t rotateRight(uint32_t value, unsigned int count)
{
        return (value >> count) | (value << (32 - count));
}

string toUpperCase(string str)
{
        for (char &c : str)
        {
                c = toupper(c);
        }
        return str;
}
// --------------------

// using pointer decay to access pointer to first value of words
void formatMessageScheduel(const string &block, uint32_t W[64])
{

        // cout << "block: " << block << '\n';
        // int blockLength = block.length();
        // cout << "blockLength: " << blockLength << '\n';

        // Split into sixteen 32-bit words
        for (int i = 0; i < 16; ++i)
        {
                // ensure data is 32 bits in length -- long longs can be 64
                W[i] = static_cast<uint32_t>(stoull(block.substr(i * 32, 32), nullptr, 2));
        }

        // Extend to 64 words --- apply bitwise opporations and xors
        for (int i = 16; i < 64; ++i)
        { // apply formla from slides
                uint32_t s0 = rotateRight(W[i - 15], 7) ^ rotateRight(W[i - 15], 18) ^ (W[i - 15] >> 3);
                uint32_t s1 = rotateRight(W[i - 2], 17) ^ rotateRight(W[i - 2], 19) ^ (W[i - 2] >> 10);
                W[i] = W[i - 16] + s0 + W[i - 7] + s1;
        }
}
//---------------------

// Compression loop ---
void compressionLoop(uint32_t Words[64], uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e, uint32_t &f, uint32_t &g, uint32_t &h)
{
        // Temporary variables
        uint32_t temp1, temp2, S0, S1, ch, maj;

        // apply algo from page 58
        for (int i = 0; i < 64; ++i)
        {
                S1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
                ch = (e & f) ^ ((~e) & g);
                temp1 = h + S1 + ch + k[i] + Words[i];

                S0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
                maj = (a & b) ^ (a & c) ^ (b & c);
                temp2 = S0 + maj;

                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
        }
}
//---------------------

// Display ---
void displayAnswer(uint32_t h0, uint32_t h1, uint32_t h2, uint32_t h3, uint32_t h4, uint32_t h5, uint32_t h6, uint32_t h7)
{
        stringstream ss;
        ss << hex;
        ss << h0 << h1 << h2 << h3 << h4 << h5 << h6 << h7;
        string hash = ss.str();
        string upperCaseHash = toUpperCase(hash);

        cout << "Final Hash: " << upperCaseHash << endl;
}
//-----------

// input ---
string getUserInput()
{
        string input;
        cout << "Enter Input: ";
        getline(cin, input);
        return input;
}

void processBlock(string &binaryBlock, uint32_t &h0, uint32_t &h1, uint32_t &h2, uint32_t &h3, uint32_t &h4, uint32_t &h5, uint32_t &h6, uint32_t &h7)
{
        // Apply padding and length encoding
        // cout << "binaryBlock: " << binaryBlock << '\n';

        // Process the block
        uint32_t Words[64];
        formatMessageScheduel(binaryBlock, Words);
        // cout << "blockWithLength: " << blockWithLength << '\n';

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
        compressionLoop(Words, a, b, c, d, e, f, g, h);
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
}

string readFileContents(const string &fileName)
{
        ifstream file(fileName);
        stringstream buffer;

        if (file)
        {
                buffer << file.rdbuf();
                file.close();
                return buffer.str();
        }
        else
        {
                cerr << "Could not open the file: " << fileName << endl;
                return "";
        }
}
//----------

int main()
{

        // imprement user input fetching

        string input;
        int choice;

        cout << "Press 1 to input your string, Press 2 to use the text from the file (Book of Mark): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        if (choice == 1)
        {
                cout << "Enter Input: ";
                getline(cin, input);
        }
        else if (choice == 2)
        {
                input = readFileContents("./Mark.txt");
        }
        else
        {
                cout << "Invalid choice." << endl;
                return 1;
        }
        // -----------------------

        // variables
        // string input = getUserInput();
        // int inputLength = input.length();
        // uint32_t Words[64];

        // Stepts ---
        /*
        Step 1) Pre-Processing - Convert input 'hello world' to binrary
                a) Begin Padding - start with bit '1'
                b) Fill padding -  fill with all 0 bits untill the total bit count of the message it '512', or nearest multiple
                c) Subtract 64 - subract 64 bits from total
                d) Calculate input length as binrary - 88 bits for 'hello world'
        */
        // Step 1) ----------------------------
        string binaryInput = convertToBinary(input);
        // cout << "binaryInputLength: " << binaryInput.length() << '\n';
        string paddedInput = applyPadding(binaryInput);
        // cout << "paddedInput: " << paddedInput.length() << '\n';

        string inputLengthBits = appendLength(paddedInput, binaryInput.length());
        // cout << "fullconversion: " << inputLengthBits.length() << '\n';

        //-------------------------------------

        /*
        Step 2) Initialize Hash Values (h)
                a) Static 'concrete' hash value for the square root for each of the first 8 prime numbers 2,3,5,7,11,13,17
                b) Set as h0 - 7 = hexVal
        */
        // Step 2) ----------------------------
        uint32_t h0 = 0x6a09e667;
        uint32_t h1 = 0xbb67ae85;
        uint32_t h2 = 0x3c6ef372;
        uint32_t h3 = 0xa54ff53a;
        uint32_t h4 = 0x510e527f;
        uint32_t h5 = 0x9b05688c;
        uint32_t h6 = 0x1f83d9ab;
        uint32_t h7 = 0x5be0cd19;
        //------------------------------------

        /*
        Step 3) Initialize 64 round constants (k) - Used in the compression algo page 58 as (k)
                a) Same like Step 2) static 'concrete' value for the cube root for the forst 64 prime numbers  (2-311)
        */

        /*
        Step 4) Chunk Loop
                a) Aquire input binrary from Step 1)
                b) Split binray input into words represented in an array - Each entry in the array is a word of size 32 bits, or 4 binary chars
                c) Go untill end of 512 block is represented in as 16 entries in the array of bit size 32 page 50

                d) apply 0 index algo on (page 52)
        */

        // Step 4) --------------------------
        // formatMessageScheduel(inputLengthBits, Words);

        // Split input into 512-bit blocks and process each block
        for (size_t i = 0; i < inputLengthBits.length(); i += 512)
        {
                string block = inputLengthBits.substr(i, 512);
                processBlock(block, h0, h1, h2, h3, h4, h5, h6, h7);
        }
        // ----------------------------------

        /*
        Step 5) Compression Loop
                a) initialize 8 variables - a,b,c,d,e,f,g,h - set these equal to their respective hash value - h0,h1,h2,h3,h4,h5,h6,h7
                b) run compression loop (page 57)
                c) save new values for 8 variables
        */

        // Step 5) -------------------------
        // uint32_t a = h0;
        // uint32_t b = h1;
        // uint32_t c = h2;
        // uint32_t d = h3;
        // uint32_t e = h4;
        // uint32_t f = h5;
        // uint32_t g = h6;
        // uint32_t h = h7;
        // alters initialized variables a-h
        // compressionLoop(Words, a, b, c, d, e, f, g, h);

        //----------------------------------

        /*
        Step 6) (7 in book) -  apply result of 8 variables in Step 5) to the hash values in Step 2)
                a) should be - h0 = h0 + a = buncha binrary
                b) apply to each h value and its respective Step 5) variable
        */

        // Step 6) -------------------------
        // h0 += a;
        // h1 += b;
        // h2 += c;
        // h3 += d;
        // h4 += e;
        // h5 += f;
        // h6 += g;
        // h7 += h;
        displayAnswer(h0, h1, h2, h3, h4, h5, h6, h7);
        //----------------------------------

        return 0;
}