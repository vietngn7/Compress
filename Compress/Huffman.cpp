//
//  Huffman.cpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#include "Huffman.hpp"

struct comparison
{
    bool operator() (Node*& i, Node*& j)
    {
        return (i->weight > j->weight);
    }
} comparer;

int findIndexChar(vector<wchar_t> symbols, wchar_t c)
{
    for(int i = 0; i < symbols.size(); ++i)
        if(symbols[i] == c)
            return i;
    return -1;
}

Huffman::Huffman(const vector<wchar_t> symbols, const vector<int> frequencies)
{
    capacity = (unsigned) symbols.size();
    
    for(unsigned i = 0; i < capacity; ++i)
    {
        this->symbols.push_back ( symbols[i]);
        this->frequencies.push_back( frequencies[i]);
    }
}

vector<string> Huffman::getCodes()
{
    BuldingTree();
    
    codes = *new vector<string>(capacity);
    
    GenerateCodes(root);
    
    vector<string> result = *new vector<string>();
    
    for(unsigned i = 0; i < capacity; ++i)
        result.push_back(codes[i]);
    
    return result;
}

void Huffman::GenerateCodes(Node* node)
{
    if(node->left == nullptr && node->right == nullptr) //Node with character
    {
        wchar_t c = node->c;
        string code = node->code;
        
        codes[findIndexChar(symbols, c)] = code; //Add code to vector
        
        return;
    }
    
    if(node->left != nullptr) //First internal node
    {
        node->left->code = node->code;  //Copy parent code
        node->left->code += '0';    //Add bit to child code
        GenerateCodes(node->left);
    }
    
    if(node->right != nullptr) //Second internal node
    {
        node->right->code = node->code;
        node->right->code += '1';
        GenerateCodes(node->right);
    }
}
void Huffman::BuldingTree()
{
    
    //Query to store elements
    priority_queue<Node*, vector<Node*>, comparison>* temp = new priority_queue<Node*, vector<Node*>, comparison>();
    
    for(int i = 0; i < capacity; ++i)
        temp->push(createNode(symbols[i], frequencies[i]) ); //Create a leaf node for each symbol and add it to query
  
    priority_queue<Node*, vector<Node*>, comparison>* query = new priority_queue<Node*, vector<Node*>, comparison>();
    
    for(int i = 0; i < capacity; ++i) //Sort query
    {
        query->push(temp->top());
        temp->pop();
    }
    delete  temp;
    
    while(query->size() != 1) //Remove all nodes to create a root node
    {

        Node* left = query->top(); //first child
        query->pop();
        
        Node* right = query->top();
        query->pop();
        
        Node* newNode = new Node;
        newNode->weight = left->weight + right->weight;
        newNode->left = left;
        newNode->right = right;
        query->push(newNode);
    }
    
    root = query->top(); //Remaing node is the root
    
    query->pop(); //Delete it from query
    delete query;
}

