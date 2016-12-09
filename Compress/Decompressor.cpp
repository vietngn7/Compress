//
//  Decompressor.cpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/5/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#include "Decompressor.hpp"

map<string, wchar_t> Decompressor::getMap(ifstream& file)
{
    int mapSize = 0; //Get size of table with codes
    file.read((char*)&mapSize,sizeof(mapSize));
    
    //Get characters in the table
    vector<char> chars = *new vector<char>();
    //Get their length
    vector<int> codeSizes = *new vector<int>();

    for(int i = 0; i < mapSize; ++i)
    {
        wchar_t c = 0;
        file.read((char*)&c,sizeof(c));
        chars.push_back(c);
        
        int size = 0;
        file.read((char*)&size,sizeof(size));
        codeSizes.push_back(size);

    }
    
    
    //Get its code
    vector<string> code = *new vector<string>();

    for(int i = 0; i < mapSize; ++i)
        code.push_back("");
    
    int count = 0;
    unsigned char byte = file.get();
    
    for(int i = 0; i < mapSize; ++i)
    {
        for(int j = 0; j < codeSizes[i]; ++j)
        {
            bool b = byte & (1 << (7-count));
            
            code[i] += b? '1': '0';
            
            ++count;
            
            if(count == 8)
            {
                count = 0;
                byte = file.get();
            }
        }
    }
    
    
    map<string, wchar_t> codes = *new map<string, wchar_t>();
    for(int i = 0; i < mapSize; ++i)
    {
        wchar_t c = chars[i];
        string s  = code[i];
        codes.insert(pair<string, wchar_t>(s, c));
    }
    
    return codes;
}

void Decompressor::getBody(ifstream& in, map<string, wchar_t> codes)
{
    wofstream out(tofile);
    
    int count = 0;
    
    unsigned char byte = in.get();
    string code = "";
    while (!in.eof())
    {
        bool b = byte & (1 << (7-count));
        
        code += b? '1': '0';
        
        if(codes.find(code) != codes.end())
        {
            wchar_t c = codes[code];
            out << c;
            code = "";
        }
        
        ++count;
        
        if(count == 8)
        {
            count = 0;
            byte = in.get();
        }
    }
    
    if(code!="")
    {
        return;
    }
    
    in.close();
    out.close();
}

void Decompressor::decompressText()
{
    ifstream in(filename, ios::binary);
    
    map<string, wchar_t> codes =  getMap(in);
    
    getBody(in, codes );
}

Decompressor::~Decompressor()
{
}

Decompressor::Decompressor(string filename, string outFile)
{
    this->filename = filename;
    tofile = outFile;
}




