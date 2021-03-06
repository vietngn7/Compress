//
//  Node.hpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <string>
using namespace std;

struct Node
{
    wchar_t c;
    int weight;
    string code;
    Node* left;
    Node* right;
};

Node* createNode(wchar_t c, int weight);

#endif /* Node_hpp */
