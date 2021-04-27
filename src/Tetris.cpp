// April, 27 2021
// Main tetris file

#include <iostream>
using namespace std;

wstring blocks[7];

int main()
{
    // Game assets i.e. blocks
    blocks[0].append(L"..X.");
    blocks[0].append(L"..X.");
    blocks[0].append(L"..X.");
    blocks[0].append(L"..X.");

    blocks[1].append(L".X..");
    blocks[1].append(L".XX.");
    blocks[1].append(L".X..");
    blocks[1].append(L"....");
    
    blocks[2].append(L".X..");
    blocks[2].append(L".XX.");
    blocks[2].append(L"..X.");
    blocks[2].append(L"....");
    
    blocks[3].append(L"..X.");
    blocks[3].append(L".XX.");
    blocks[3].append(L".XX.");
    blocks[3].append(L"....");

    blocks[4].append(L"..X.");
    blocks[4].append(L".XX.");
    blocks[4].append(L"..X.");
    blocks[4].append(L"....");

    blocks[5].append(L"....");
    blocks[5].append(L".XX.");
    blocks[5].append(L"..X.");
    blocks[5].append(L"..X.");

    blocks[6].append(L"....");
    blocks[6].append(L".XX.");
    blocks[6].append(L".X..");
    blocks[6].append(L".X..");



    return 0;
}