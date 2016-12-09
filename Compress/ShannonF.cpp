//
// Created by Viet Nguyen on 12/5/16.
//

#include "ShannonF.h"
void ShannonF::GenerateCodes(int left, int right)
{
    if(left == right)
        return;
    else if (right-left == 1)
    {
        codes[left] += '0';
        codes[right] += '1';
    }
    else
    {
        int high = left;
        int low = right;

        int h = frequencies[high];
        int l = frequencies[low];

        while (low - high != 1)
        {
            if(h>l)
                l += frequencies[--low];
            else
                h += frequencies[++high];
        }

        for(int i = left ; i <= high; ++i )
            codes[i] += '0';

        for(int i = low ; i <= right; ++i )
            codes[i] += '1';

        GenerateCodes(left, high);
        GenerateCodes(low, right);
    }
}
ShannonF::ShannonF(const vector<wchar_t> symbols, const vector<int> frequencies)
{
    capacity = (int)symbols.size();

    codes = *new vector<string>();

    this->symbols = *new vector<wchar_t>();
    this->frequencies = *new vector<int>();
    
    for(int i = 0; i < capacity; i++)
    {
        this->symbols.push_back(symbols[i]);
        this->frequencies.push_back(frequencies[i]);
        codes.push_back("");
    }
}
ShannonF::~ShannonF()
{
    codes.clear();
}
vector<string> ShannonF::getCodes()
{
    
    GenerateCodes(0, capacity-1);

    vector<string> res = *new vector<string>();

    for(int i = 0; i < codes.size(); ++i)
        res.push_back(codes[i]);

    return res;
}
