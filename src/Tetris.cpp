// April, 27 2021
// Main tetris file

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

#include <stdio.h>
#include <Windows.h>

wstring blocks[7];
int screenWidth = 80;
int screenHeight = 30;
int fieldWidth = 12;   // width of playing field
int fieldHeight = 18;  // Height of playing field
unsigned char *pField = nullptr;

int rotateBlock(int positionX, int positionY, int rotation);

bool pieceFits(int block, int rotation, int positionX, int positionY);

int main()
{
    // Code to create the screen buffer
    int screenArea = screenWidth*screenHeight;
    wchar_t *screen = new wchar_t[];
    for (int i = 0; i < screenArea; i++){
        screen[i] = L' ';
    }
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

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

    pField = new unsigned char[screenArea];
    for (int x = 0; x < fieldWidth; x++){
        for (int y = 0; y < fieldHeight; y++){
            pField[y*fieldWidth + x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 9 : 0;
        }
    }

    bool bKey[4];
    int currentPiece = 0;
    int currentRotation = 0;
    int currentX = fieldWidth / 2;
    int currentY = 0;
    int speed = 20;
    int speedCount = 0;
    int pieceCount = 0;
    int score = 0;
    bool bForceDown = false;
    bool bRotateHold = true;
    bool bGameOver = false;
    vector<int> vLines;

    while (!bGameOver){
        this_thread::sleep_for(50ms);
        speedCount++;
        bForceDown = (speedCount == speed);

        for (int k = 0; k < 4; k++){
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
        }

        currentX += (bKey[0] && pieceFits(currentPiece, currentRotation, currentX + 1, currentY)) ? 1 : 0;
        currentX -= (bKey[1] && pieceFits(currentPiece, currentRotation, currentX - 1, currentY)) ? 1 : 0;
        currentY += (bKey[2] && pieceFits(currentPiece, currentRotation, currentX, currentY + 1)) ? 1 : 0;
        
        if (bKey[3]){
            currentRotation += (bRotateHold && pieceFits(currentPiece, currentRotation, currentX + 1, currentY)) ? 1 : 0;
            bRotateHold = false;
        }
        else{
            bRotateHold = true;
        }

        if (bForceDown){
            speedCount = 0;
            pieceCount++;
            if (pieceCount % 50 == 0){
                if (speed >= 10){
                    speed--;
                }
            }

            if (pieceFits(currentPiece, currentRotation, currentX, currentY + 1)){
                currentY++;
            }
            else{
                for (int x = 0; x < 4; x++){
                    for (int y = 0; y < 4; y++){
                        if (blocks[currentPiece][rotateBlock(x, y, currentRotation)] != L'.'){
                            pField[(currentY + y) * fieldWidth + (currentX + x)] = currentPiece + 1;
                        }
                    }
                }

                for (int y = 0; y < 4; y++){

                }
            }
        }
    }

    return 0;
}

// Math function to determine rotation of blocks
int rotateBlock(int positionX, int positionY, int rotation){
    switch (rotation % 4){
        case 0: return positionY * 4 + positionX;           // 0 degree rotation
        case 1: return 12 + positionY - (positionX * 4);    // 90 degree rotation
        case 2: return 15 - (positionY * 4) - positionX;    // 180 degree rotation
        case 3: return 3 - positionY + (positionX *4);      // 270 degree rotation
    }

    return 0;
}

bool pieceFits(int block, int rotation, int positionX, int positionY){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int pieceIndex = rotateBlock(i, j, rotation);

            int fieldIndex = (positionY + j) * fieldWidth + (positionX + i);

            if (positionX + i >= 0 && positionX + i < fieldWidth){
                if (positionY + j >= 0 && positionY + j < fieldHeight){
                    if (blocks[block][pieceIndex] != L'.' && pField[fieldIndex] != 0){
                        return false;
                    }
                }
            }
        }
    }

    return true;
}