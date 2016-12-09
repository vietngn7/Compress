//
//  Counting.cpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#include "Counting.hpp"
#include <fstream>
#include <iostream>

struct Element
{
    wchar_t c;
    int f;
};
bool compareByf(const Element &a, const Element &b)
{
    return a.f < b.f;
}

Counting::Counting(string filename)
{
    setlocale(LC_ALL, "en_US.UTF-8");
    wifstream input (filename);
    
#ifdef PREFER_BOOST
    boost::locale::generator gen;
    std::locale loc = gen("en_US.UTF-8");
#else
    std::locale loc("en_US.UTF-8");
#endif
    input.imbue(loc);
    wcout.imbue(loc);
    
    wstring str;
    
    istreambuf_iterator<wchar_t> start(input), end;
    
    frequency = *new vector<int>();
    letters = *new vector<wchar_t>();
    
    for( ;start != end; ++start)
    {
        wchar_t item = (*start);
        bool t = false;
        for (size_t i = 0; i < letters.size(); ++i)
        {
            if(letters[i]  == item)
            {
                ++frequency[i];
                t = true;
                break;
            }
        }
        if(!t)
        {
            letters.push_back(item);
            frequency.push_back(1);
        }
    }
    
    vector<Element> el = *new vector<Element>();
    for(int i = 0; i < letters.size(); ++i)
        el.push_back(*new Element{letters[i], frequency[i]});
    sort(el.begin(), el.end(), compareByf);
    
    letters.clear();
    frequency.clear();

    for(int i = 0; i < el.size(); ++i)
    {
        letters.push_back(el[i].c);
        frequency.push_back(el[i].f);
    }
    
    el.clear();
    
    return;
}
Counting::~Counting()
{
    letters.clear();
    frequency.clear();
}


vector<int> Counting::getFrequencies()
{
    vector<int> result = *new vector<int>;
    for(unsigned i = 0 ; i < frequency.size(); ++i)
        result.push_back(frequency[i]);
    
    return result;
}


vector<wchar_t> Counting::getSymbols()
{
    vector<wchar_t> result = *new vector<wchar_t>;
    
    
    for(unsigned i = 0 ; i < letters.size(); ++i)
        result.push_back(letters[i]);
    
    
    return result;
}
