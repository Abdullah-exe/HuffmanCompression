#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <bitset>


using namespace std;

//structure to represent a node in the huffman tree
struct HuffmanNode
{
    HuffmanNode* left = nullptr;
    HuffmanNode* right = nullptr;
    char character;
    int frequency;

};

//Comparator for priority_queue
struct CompareNodes {
    bool operator()(HuffmanNode* const &node1, HuffmanNode* const &node2) {
        return node1->frequency > node2->frequency;
    }
};

class Huffman
{
    string encoded;
    HuffmanNode* root = nullptr;
    HuffmanNode* root1 = new HuffmanNode;
    unordered_map<char, string> map2;
    unordered_map<char, string> charCodeMap;
    unordered_map<string, char> decodeMap;
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> nodeQueue;

public:

    // Function to calculate frequency of characters in a message
    void calculateFrequency(const string& message) {
        unordered_map<char, int> frequencyMap;

        // Count frequency of each character
        for (char c : message) {
            frequencyMap[c]++;
        }

        // Create leaf nodes for each character and push them into priority_queue
        for (auto it : frequencyMap)
        {
            HuffmanNode* newNode = new HuffmanNode;
            newNode->character = it.first;
            newNode->frequency = it.second;
            nodeQueue.push(newNode);

        }
        //Construct Huffman tree
        while (nodeQueue.size() > 1) {
            HuffmanNode* leftNode = nodeQueue.top();
            nodeQueue.pop();
            HuffmanNode* rightNode = nodeQueue.top();
            nodeQueue.pop();

            HuffmanNode* parentNode = new HuffmanNode;
            parentNode->character = '\0';
            parentNode->frequency = leftNode->frequency + rightNode->frequency;
            parentNode->left = leftNode;
            parentNode->right = rightNode;
            nodeQueue.push(parentNode);
        }

        root = nodeQueue.top();
        buildCodes(root, "");

        ofstream myfile;
        myfile.open("charcode.txt");

        for (auto it : charCodeMap) {
            myfile << it.first << ": " << it.second << endl;
        }
        myfile.close();
        buildCodes(root, "");

    }

    void buildCodes(HuffmanNode* currentNode, string code) {
        if (currentNode == nullptr) {
            return;
        }

        if (!currentNode->left && !currentNode->right) {
            charCodeMap[currentNode->character] = code;
            decodeMap[code] = currentNode->character;
        }

        buildCodes(currentNode->left, code + "0");
        buildCodes(currentNode->right, code + "1");
    }

    string encodeMessage(const string& message) {
        string localencoded;
        for (char c : message) {
            localencoded += charCodeMap[c];
        }
        ofstream file;
        file.open("encryptedstring.txt");
        file << localencoded << endl;
        file.close();
        encoded = localencoded;
        decodingextra();
        return localencoded;
    }

    string decodeMessage(const string& encodedMessage) {
        string decoded;
        HuffmanNode* currentNode = root;
        for (char bit : encodedMessage) {
            if (bit == '0') {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }

            if (!currentNode->left && !currentNode->right) {
                decoded += currentNode->character;
                currentNode = root;
            }
        }
        return decoded;
    }

    void decodingextra() {
        ofstream file("character.txt");

        int size = encoded.size();
        int padding_bits = size % 8 == 0 ? 0 : 8 - (size % 8);
        for (int i = 0; i < padding_bits; i++) {
            encoded += "0";
        }

        int count = 0;
        string temp;
        for (int i = 0; i < encoded.size(); i++) {
            count++;
            temp += encoded[i];

            // When 8 bits are collected, convert them to a character and write to file
            if (count == 8) {
                bitset<8> b1(temp);
                int x = b1.to_ullong();
                char y = (char) x;
                file << y;

                // Reset counters and temporary storage
                count = 0;
                temp = "";
            }

        }

        padding_bits = padding_bits + 97;
        char i = padding_bits;
        file << i << endl;
        file << "@#$" << endl;

        for (auto it : charCodeMap) {
            file << it.first << it.second << endl;
        }
        file.close();

    }

    void decryptwithoutencrypt()
    {
        ifstream file;
        file.open("character.txt");

        string encodedCharacters = "";
        string line = "";
        string encodedfinal = "";
        int paddingBits = 0;

        // Read encoded characters until special marker "@#$"
        while (getline(file, line) && line != "@#$") {
            encodedCharacters += line;
        }

        char parityChar = encodedCharacters.back();
        paddingBits = static_cast<int>(parityChar) - 97;
        encodedCharacters.pop_back();

        // Convert encoded characters to binary
        string decodedMessage;
        for (size_t i = 0; i < encodedCharacters.size(); ++i) {
            bitset<8> binaryCharacter(encodedCharacters[i]);
            decodedMessage += binaryCharacter.to_string();
        }

        if (paddingBits > 0 && decodedMessage.size() % 8 == 0) {
            decodedMessage = decodedMessage.substr(0, decodedMessage.size() - paddingBits);
        }

        string temp1 = "";
        getline(file, line);
        while (!file.eof())
        {
            for (int i = 1; i < line.size(); i++)
            {
                temp1 = temp1 + line[i];
            }
            map2.insert(make_pair(line[0], temp1));
            temp1 = "";
            getline(file, line);;
        }

        treeForDecryptWithoutEncrypt();
        string answer = decodeMessage(decodedMessage);
        cout << "The answer is: " << answer << endl;
    }

    void treeForDecryptWithoutEncrypt() {
        HuffmanNode* currentNode = root1;

        for (const auto& entry : map2) {
            const string& code = entry.second;
            char character = entry.first;

            for (size_t i = 0; i < code.size(); ++i) {
                char bit = code[i];
                if (bit == '0') {
                    if (currentNode->left == nullptr) {
                        currentNode->left = new HuffmanNode;
                    }
                    currentNode = currentNode->left;
                } else {
                    if (currentNode->right == nullptr) {
                        currentNode->right = new HuffmanNode;
                    }
                    currentNode = currentNode->right;
                }
                // Check if we reached a leaf node (end of the code)
                if (i == code.size() - 1) {
                    currentNode->character = character;
                }
            }
            currentNode = root1; // Reset currentNode for next iteration
        }

        root = root1;
    }

};

int main()
{
    Huffman huffmanCoder;
    string message;

    int option;
    cout << "Choose an option:" << endl;
    cout << "1. Encode and Decode Message" << endl;
    cout << "2. Decrypt Without Encryption" << endl;
    cin >> option;

    switch (option) {
        case 1:
        {
            ofstream file;
            file.open("string.txt");
            cout << "Enter the data to encrypt it: ";
            cin.ignore(); // Ignore newline character in input buffer
            getline(cin, message);
            file << message << endl;
            file.close();

            huffmanCoder.calculateFrequency(message);

            string encodedMessage =  huffmanCoder.encodeMessage(message);
            cout << "The encoded form is: " << encodedMessage << endl;

            string decodedMessage = huffmanCoder.decodeMessage(encodedMessage);
            cout << "The decoded message is: " << decodedMessage << endl;
            break; // Add break statement to exit switch statement after case 1
        }
        case 2:
            huffmanCoder.decryptwithoutencrypt();
            break; // Add break statement to exit switch statement after case 2
        default:
            cout << "Invalid option. Exiting program." << endl;
    }

    return 0;
}

