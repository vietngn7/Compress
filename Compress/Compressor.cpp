//
//  Compressor.cpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#include "Compressor.hpp"
#include <cmath>

Compressor::Compressor(string filename, string tofile, vector<wchar_t> symbols, vector<string> codes)
{
    fileSourse = filename;
    
    fileTo = tofile;
    
    for(int i = 0; i < symbols.size(); ++ i)
        map.insert(pair<wchar_t, string>(symbols[i], codes[i]));
}

vector<bool> Compressor::getBits(wchar_t c)
{
    string code = map[c];
    
    vector<bool> result  = *new vector<bool>;
    
    for(int i = 0 ; i < code.size(); ++i)
        result.push_back( code[i]=='1');
    
    return result;
}

void Compressor::CreateHeader(ofstream & comp)
{
    int size = (int)map.size(); //Write number of row in table
    
    comp.write((char*)&size,sizeof(size));
    
    for (auto i = map.begin() ; i != map.end(); ++i)
    {
        wchar_t c = (*i).first;
        comp.write((char*)&c,sizeof(c));
        
        int s = (int)(*i).second.size();
        comp.write((char*)&s,sizeof(s));
    }
    
    int count = 0;
    char buffer = 0;
    
    for(auto i = map.begin() ; i != map.end(); ++i)
    {
        wchar_t s = (*i).first;
        vector<bool> bits = getBits(s);
        for(int i = 0; i < bits.size(); ++i)
        {
            buffer = buffer | (bits[i]? 1: 0) << (7 - count);
            count++;
            
            if (count == 8)
            {
                count = 0;
                comp.put(buffer);
                //comp << buffer;
                buffer = 0;
            }
        }
    }
    if(buffer != 0)
        comp.put(buffer);

}

void Compressor::CompressText()
{
    //Open sourse text file to get text
    setlocale(LC_ALL, "en_US.UTF-8");
    ifstream input (fileSourse);
    
#ifdef PREFER_BOOST
    boost::locale::generator gen;
    std::locale loc = gen("en_US.UTF-8");
#else
    std::locale loc("en_US.UTF-8");
#endif
    input.imbue(loc);
    wcout.imbue(loc);
    
    //Create new file
    ofstream comp (fileTo, ofstream::binary);
    
    CreateHeader(comp);
    
    int count = 0;
    int buffer = 0;
    while (!input.eof())
    {
        unsigned wchar_t ch = input.get();
        
        vector<bool> bits = getBits(ch);
        
        for(int i = 0; i < bits.size(); ++i)
        {
            buffer = buffer | (bits[i]? 1: 0) << (7 - count);
            count++;
            
            if (count == 8)
            {
                comp.put(buffer);
                buffer = 0;
                count = 0;
            }
        }
    }
    //Adding pseudo EOF
    vector<bool> bits = getBits(-1);
    for(int i = 0; i < bits.size(); ++i)
    {
        buffer = buffer | (bits[i]? 1: 0) << (7 - count);
        count++;
        
        if (count == 8)
        {
            comp.put(buffer);
            buffer = 0;
            count = 0;
        }
    }
    
    if(buffer != 0)
        comp.put(buffer);
    input.close();
    comp.close();
}
