# Huffman Coding Algorithm for Text Compression and Decompression in C++
This repository contains an implementation of Huffman Coding, a lossless data compression algorithm. Huffman Coding is used to compress data by assigning variable-length codes to input characters based on their frequencies. Characters that occur more frequently are assigned shorter codes, while those that occur less frequently receive longer codes. This implementation reads input text, constructs a Huffman tree, encodes the text into binary, and then decodes the encoded text back to its original form.

# Files
- input.txt: The input file containing the text to be encoded.
- codes.txt: File where the Huffman codes are saved.
- encoded.txt: File containing the encoded binary text.
- decoded.txt: File containing the decoded text.

# Features
- Frequency Analysis: Analyze the frequency of each character in the input file to construct the Huffman Tree.
- Tree Construction: Builds the Huffman Tree based on character frequencies.
- Code Assignment: Assigns binary codes to characters and saves them to a file.
- Encoding: Converts input text into a binary representation using the assigned codes.
- Decoding: Reads encoded text and reconstructs the original text using the Huffman codes.

  # Implementation Details
The implementation consists of a few key components:
- Node Structure: Represents each node in the Huffman Tree with a character, its frequency, and pointers to its left and right children.
- Queue: A custom queue implementation to manage nodes during the Huffman Tree construction.
- Huffman Tree: The core structure that constructs the tree, assigns codes, encodes, and decodes text.

  # Usage
  #### 1.Input Preparation= 
  Create an input text file (input.txt) containing the text you wish to compress.
  ```bash
  frequencies frequencies frequencies
#### 2.Building and Assigning Codes
The build_and_assign_codes method reads the input file, builds the Huffman Tree, and assigns binary codes to each character. It also writes these codes to a file (codes.txt).
#### 3.Encoding
To encode the text in the input file, use the encode_text method. The encoded binary text will be saved to encoded.txt.
#### 4.Decoding
To decode the encoded text, use the decode_text_and_show method. This method will display the decoded text and save it to decoded.txt.




