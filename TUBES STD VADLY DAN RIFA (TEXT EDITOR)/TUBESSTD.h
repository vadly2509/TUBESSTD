#ifndef TUBESSTD_H_INCLUDED
#define TUBESSTD_H_INCLUDED
#include <iostream>
#include <conio.h>

using namespace std;

typedef char infotype;

struct elm {
    infotype info;
    elm* next;
    elm* prev;
};

typedef elm* adr;

struct List {
    adr first;
    adr last;
    int cursorPos;
    int length;
};
struct UndoRedoOperation {
    infotype character;
    bool isInsertion;
    };

struct Stack {
    UndoRedoOperation info[98];
    int top;
};


const int topMax = 98;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_BACKSPACE = 8;
const int KEY_CTRL_Z = 26;
const int KEY_CTRL_Y = 25;

void cStack_103052300025_103052300087(Stack& S);
bool isEmpty_103052300025_103052300087(Stack S);
bool isFull_103052300025_103052300087(Stack S);
void push_undo(Stack& S, infotype x, bool isInsertion);
void pop_undo(Stack& S, UndoRedoOperation& operation);
void push_redo(Stack& S, infotype x, bool isInsertion);
void pop_redo(Stack& S, UndoRedoOperation& operation);
void clearStack_103052300025_103052300087(Stack& S);
void cList_103052300025_103052300087(List& L);
adr nelem_103052300025_103052300087(infotype data);
void insL_103052300025_103052300087(List& L, infotype data);
void del_103052300025_103052300087(List& L, infotype& deletedChar);
void moveCursorLeft_103052300025_103052300087(List& L);
void moveCursorRight_103052300025_103052300087(List& L);
void Print_103052300025_103052300087(List L);
void insertNewLine_103052300025_103052300087(List& L);
void undoOperation(List& L, Stack& undoStack, Stack& redoStack);
void redoOperation(List& L, Stack& undoStack, Stack& redoStack);
void handleBackspace(List& L, Stack& undoStack);
int countWords(List L);
void moveToLine(List& L, int lineNumber);
int findWord(List L, string word);
void insertNewCharacter(List& L, Stack& undoStack, infotype newChar);
void textEditor_103052300025_103052300087();

#endif // TUBESSTD_H_INCLUDED
