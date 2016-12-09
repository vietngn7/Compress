//
//  Counting.hpp
//  TextCompression
//
//  Created by Viet Nguyen on 12/4/16.
//  Copyright © 2016 Viet Nguyen. All rights reserved.
//

#ifndef Counting_hpp
#define Counting_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class Counting
{
private:
    
    vector<wchar_t> letters;
    
    vector<int> frequency;
    
public:
    
    Counting(string filename);
    
    ~Counting();
    
    vector<int> getFrequencies();
    
    vector<wchar_t> getSymbols();
};


#endif /* Counting_hpp */
