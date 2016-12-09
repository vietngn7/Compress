//
//  Decompressor.hpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/5/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#ifndef Decompressor_hpp
#define Decompressor_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Decompressor
{
private:
    
    map<string, wchar_t> getMap(ifstream&);
    
    void getBody(ifstream&, map<string, wchar_t> codes);
    
    string filename;
    
    string tofile;
    
public:
    
    Decompressor(string filename, string outFile);
    
    ~Decompressor();
    
    void decompressText();
    
};


#endif /* Decompressor_hpp */
