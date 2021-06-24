#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <bits/stdc++.h>

struct MinHeapNode
{
    char data;			 // One of the input characters
    int freq;			 // Frequency of the character
    MinHeapNode *left, *right; // Left and right child

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// utility function for the priority queue
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

class Huffman {
public:
    // to map each character its huffman value
    map<char, string> codes;

    // to store the frequency of character of the input data
    map<char, int> freq;

    // STL priority queue to store heap tree, with respect
    // to their heap root node value
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    void printCodes(struct MinHeapNode* root, string str);
    void storeCodes(struct MinHeapNode* root, string str);
    void HuffmanCodes(int size);
    void calcFreq(string str, int n);
    string decode_file(struct MinHeapNode* root, string s);
    string decodeHuffman(string s, vector<string> symbol, vector<string> code_num);
    string prepare_dictionary();
    string compressed_message(string str);
    string start_huffman(string str);
    string decompress(string map_str, string encodedString);
};


#endif //HUFFMAN_H
