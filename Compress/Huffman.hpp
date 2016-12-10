//
//  Huffman.hpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#ifndef Huffman_hpp
#define Huffman_hpp

#include <stdio.h>
#include <vector>
#include "Node.hpp"
#include <queue>

using namespace std;

class Huffman{
    
public:
    
    Huffman(const vector<wchar_t> symbols, const vector<int> frequencie);
    
    vector<string> getCodes();
    
private:
    
    void BuldingTree();
    
    void GenerateCodes(Node* node);
    
    Node* root = nullptr;
    
    vector<wchar_t> symbols;
    
    vector<int> frequencies;
    
    vector<string> codes;
    
    size_t capacity;
};

#endif /* Huffman_hpp */
