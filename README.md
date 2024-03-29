# Huffman Encoding and Decoding with Compression
This program implements Huffman encoding and decoding techniques along with an option for decryption without encryption. Huffman encoding is a popular algorithm used for lossless data compression, particularly in applications where text data needs to be compressed efficiently.

Table of Contents:<br>
Introduction<br>
File Descriptions<br>
Usage Instructions<br>
Compression Process<br>



Introduction<br>
Huffman coding is a method used to compress data without losing any information. It works by assigning variable-length codes to input characters, with shorter codes assigned to more frequent characters. This encoding scheme minimizes the total number of bits required to represent the original data.

The program consists of the following components:

Huffman Encoding and Decoding: Allows the user to input a message, which is then encoded using Huffman coding. The encoded message can be decoded back to the original message.
Decryption Without Encryption: Provides an option to decrypt a message that was encoded using Huffman coding, without having access to the original encoding.


File Descriptions:<br>
charcode.txt: Contains the mapping of characters to their Huffman codes.<br>
encryptedstring.txt: Stores the encoded message.<br>
character.txt: Contains additional information required for decoding the message without encryption.<br>


Usage Instructions<br>
Running the Program:<br>
Compile and run the program using a C++ compiler.<br>


Choose an option:<br>
Enter 1 to encode and decode a message.<br>
Enter 2 to decrypt a message without encryption.<br>


Encoding and Decoding:<br>
When selecting option 1, the user is prompted to input a message.<br>
The program calculates the frequency of characters in the message and constructs a Huffman tree.<br>
The message is encoded using the generated Huffman codes and saved to encryptedstring.txt.<br>
The encoded message is then decoded back to the original message and displayed.<br>


Decryption Without Encryption:<br>
Option 2 allows the user to decrypt a message without the original encryption.<br>
The program reads the necessary information from character.txt and reconstructs the Huffman tree.<br>
The encoded message is decoded back to the original message and displayed.<br>


Compression Process:<br>
The Huffman encoding process achieves compression by representing frequently occurring characters with shorter codes and less frequent characters with longer codes. This compression technique reduces the number of bits required to represent the data, resulting in smaller file sizes.


Compression is achieved in the following steps:<br>
Frequency Calculation:<br>
The program calculates the frequency of each character in the input message.<br>
Huffman Tree Construction:<br>
Based on the character frequencies, the program constructs a Huffman tree where each leaf node represents a character and its associated frequency.<br>
Code Assignment:<br>
Huffman codes are assigned to each character based on their position in the Huffman tree.
Characters occurring more frequently receive shorter codes, while less frequent characters receive longer codes.<br>
Encoding:<br>
The original message is encoded using the assigned Huffman codes.
Each character is replaced with its corresponding Huffman code, resulting in a compressed representation of the message.<br>
Decoding:<br>
During decoding, the encoded message is traversed through the Huffman tree to reconstruct the original message.
The shorter codes assigned to frequently occurring characters allow for efficient decoding, maintaining the integrity of the original data.


By following this compression process, the program achieves efficient data compression while preserving the original information, making Huffman encoding an essential technique in various applications, including file compression and data transmission.
