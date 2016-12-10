//
//  Node.cpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#include "Node.hpp"
Node* createNode(wchar_t c, int weight)
{
    Node* newNode = new Node;
    
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->code = "";
    newNode->c = c;
    newNode->weight = weight;
    
    return newNode;
}
