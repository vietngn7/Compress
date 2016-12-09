//
//  Compressor.hpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#ifndef Compressor_hpp
#define Compressor_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>


using namespace std;


class Compressor
{
public:
    
    Compressor(string filename, string tofile, vector<wchar_t> symbols, vector<string> codes);
    
    void CompressText();
    
private:
    
    void CreateHeader(ofstream&);
    
    vector<bool> getBits(wchar_t c);
    
    string fileSourse;
    
    string fileTo;
    
    map<wchar_t, string> map;
};


#endif /* Compressor_hpp */
