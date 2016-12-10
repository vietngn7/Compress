//
//  main.cpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#include <iostream>
#include "Node.hpp"
#include "Compressor.hpp"
#include "Huffman.hpp"
#include "Counting.hpp"
#include "Decompressor.hpp"
#include "ShannonF.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    string filename = "/Users/Shadow/Desktop/warandpeace.txt";
    
    Counting* count = new Counting(filename);
    
    vector<wchar_t> symbols = count->getSymbols();
    
    vector<int> frequencies = count->getFrequencies();
    
    delete count;

    Huffman* h = new Huffman(symbols, frequencies);
    
    vector<string> code = h->getCodes();
    
    delete h;
    
    Compressor* c = new Compressor(filename, filename+".haff", symbols, code);
    
    c->CompressText();
    
    delete c;
    
    Decompressor* d =new Decompressor(filename+".haff", filename+".haff.txt");
    
    d->decompressText();
    
    delete d;
    
    
}
