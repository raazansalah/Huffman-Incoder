#ifndef HUFFMAN
#define HUFFMAN
#include <bits/stdc++.h>
#include "freq.hpp"
struct Node
{
    int id;                       //grey value
    int freq;                     // freq. of greyvalue
    Node *left, *right;           // left &right pointers
    Node(int data, unsigned freq) //constructor
    {
        left = right = nullptr;  
        this->id = data;
        this->freq = freq;
    }
};
struct compare
{
    bool operator()(Node *l, Node *r)

    {
        return (l->freq > r->freq);
    }
};
void Generate_code(struct Node *parent, string code, unordered_map<int, string> &Pixel_Data) // recursive fnc to print code of each id 
{
    if (parent == nullptr)   // to exit the recurion  
    {
        return; 
    }
    if (parent->left != nullptr) // if parent not a leaf node 
        Generate_code(parent->left, code + "0", Pixel_Data);  // go left and add 0 to the code and call the function for this new parent 
    if (parent->right != nullptr) // if parent not a leaf node 
        Generate_code(parent->right, code + "1", Pixel_Data);  // go left and add 1 to the code and call the function for this new parent 
    if (parent->right == nullptr && parent->left == nullptr) // if it is a leaf node
        Pixel_Data[parent->id] = code;                       // push the codes to the vector
}
void Encode(vector<int> frequencyTable, unordered_map<int, string> &Pixel_Data) // func to build huffman tree  from the freq table "generated before"
{
    struct Node *left, *right, *top; 
    priority_queue<Node *, vector<Node *>, compare> pq;  // priority queue of freq
    for (int i = 0; i < frequencyTable.size(); ++i)     // loop to push  frequencies into priority queue
    {
        if (frequencyTable[i] == 0)   // if freq = 0 we dont need it
            continue;     // go fot next loop
        else    // freq not equal 0
            pq.push(new Node(i, frequencyTable[i])); // push this freq to the priority queue
    }
    while (pq.size() != 1)  // for priority queue is not empty
    {
        left = pq.top(); //  frist  min freqs. to left 
        pq.pop();  // remove this freq from queue
        right = pq.top(); // second element with min freq to the left chid
        pq.pop();  // remove it from the queue
        top = new Node('$', left->freq + right->freq); // internal node with any value and sum of freqs
        top->left = left;
        top->right = right;
        pq.push(top);  // push this node  to the priority queue
    }
    // Print Huffman codes using the Huffman tree built above
    Generate_code(pq.top(), "", Pixel_Data);
}
#endif