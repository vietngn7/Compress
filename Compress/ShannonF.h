//
// Created by Viet Nguyen on 12/5/16.
//

#ifndef UNTITLED_FOLDER_SHANNONF_H
#define UNTITLED_FOLDER_SHANNONF_H
#include <vector>
#include <string>
using namespace std;


class ShannonF {
public:

    ~ShannonF();
    ShannonF(const vector<wchar_t> symbols, const vector<int> frequencies);

    vector<string> getCodes();

private:

    int capacity;

    vector<int> frequencies;

    vector<wchar_t> symbols;

    vector<string> codes;

    void GenerateCodes(int left, int right);
};


#endif //UNTITLED_FOLDER_SHANNONF_H
