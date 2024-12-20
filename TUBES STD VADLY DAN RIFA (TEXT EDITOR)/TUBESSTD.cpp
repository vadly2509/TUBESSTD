#include "TUBESSTD.h"

void cStack_103052300025_103052300087(Stack& S) {
    S.top = -1;
}

bool isEmpty_103052300025_103052300087(Stack S) {
    return S.top == -1;
}

bool isFull_103052300025_103052300087(Stack S) {
    return S.top == topMax;
}

void clearStack_103052300025_103052300087(Stack& S) {
    S.top = -1;
}

void cList_103052300025_103052300087(List& L) {
    L.first = nullptr;
    L.last = nullptr;
    L.cursorPos = 0;
    L.length = 0;
}

adr nelem_103052300025_103052300087(infotype data) {
    adr p = new elm;
    p->info = data;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void insL_103052300025_103052300087(List& L, infotype data) {
    adr p = nelem_103052300025_103052300087(data);
    adr current = L.first;
    int pos = 0;

    while (current != nullptr && pos < L.cursorPos) {
        current = current->next;
        pos++;
    }

    if (L.first == nullptr) {
        L.first = p;
        L.last = p;
    } else if (L.cursorPos == 0) {
        p->next = L.first;
        L.first->prev = p;
        L.first = p;
    } else if (L.cursorPos == L.length) {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    } else {
        p->prev = current->prev;
        p->next = current;
        current->prev->next = p;
        current->prev = p;
    }

    L.length++;
    L.cursorPos++;
}

void del_103052300025_103052300087(List& L, infotype& deletedChar) {
    if (L.cursorPos > 0) {
        adr current = L.first;
        int pos = 0;

        while (current != nullptr && pos < L.cursorPos - 1) {
            current = current->next;
            pos++;
        }

        if (current != nullptr) {
            adr temp = current;
            deletedChar = temp->info;

            if (temp == L.first && temp == L.last) {
                L.first = L.last = nullptr;
            } else if (temp == L.first) {
                L.first = temp->next;
                L.first->prev = nullptr;
            } else if (temp == L.last) {
                L.last = temp->prev;
                L.last->next = nullptr;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            delete temp;
            L.length--;
            L.cursorPos--;
        }
    }
}

void moveCursorLeft_103052300025_103052300087(List& L) {
    if (L.cursorPos > 0) {
        L.cursorPos--;
    }
}

void moveCursorRight_103052300025_103052300087(List& L) {
    if (L.cursorPos < L.length) {
        L.cursorPos++;
    }
}
int countWords(List L) {
    int wordCount = 0;
    bool inWord = false;
    adr p = L.first;

    while (p != nullptr) {
        if (isspace(p->info) || p->info == '\n') {
            if (inWord) {
                wordCount++;
                inWord = false;
            }
        } else {
            inWord = true;
        }
        p = p->next;
    }

    if (inWord) {
        wordCount++;
    }

    return wordCount;
}
void Print_103052300025_103052300087(List L) {
    system("cls");
    cout << "=== Editor Text Sederhana ===" << endl;
    cout << "Ctrl+Z: Undo | Ctrl+Y: Redo | Arrow (L or R): Move | ESC: Exit" << endl ;
    cout << "Enter: Add New Line | Backspace: Hapus | Ctrl+F: Cari Kata |  Ctrl+G: Pindah Baris" << endl << endl;
    adr p = L.first;
    int pos = 0;

    while (p != nullptr) {
        if (pos == L.cursorPos) {
            cout << "|";
        }
        cout << p->info;
        p = p->next;
        pos++;
    }

    if (pos == L.cursorPos) {
        cout << "|";
    }

    cout << endl;
    cout << "\nPanjang Character: " << L.length << " | Posisi kursor: " << L.cursorPos << " | Word Count: " << countWords(L) << endl;
}
void insertNewLine_103052300025_103052300087(List& L) {
    adr newLine = new elm;
    newLine->info = '\n';
    newLine->next = nullptr;
    newLine->prev = nullptr;

    adr current = L.first;
    int pos = 0;
    while (current != nullptr && pos < L.cursorPos) {
        current = current->next;
        pos++;
    }

    if (current == nullptr) {
        if (L.last != nullptr) {
            L.last->next = newLine;
            newLine->prev = L.last;
            L.last = newLine;
        } else {
            L.first = newLine;
            L.last = newLine;
        }
    } else {
        newLine->next = current;
        if (current->prev != nullptr) {
            current->prev->next = newLine;
            newLine->prev = current->prev;
        }
        current->prev = newLine;
    }
}
void push_undo(Stack& S, infotype x, bool isInsertion) {
    if (!isFull_103052300025_103052300087(S)) {
        S.top++;
        S.info[S.top].character = x;
        S.info[S.top].isInsertion = isInsertion;
    }
}

void pop_undo(Stack& S, UndoRedoOperation& operation) {
    if (!isEmpty_103052300025_103052300087(S)) {
        operation = S.info[S.top];
        S.top--;
    }
}

void push_redo(Stack& S, infotype x, bool isInsertion) {
    if (!isFull_103052300025_103052300087(S)) {
        S.top++;
        S.info[S.top].character = x;
        S.info[S.top].isInsertion = isInsertion;
    }
}

void pop_redo(Stack& S, UndoRedoOperation& operation) {
    if (!isEmpty_103052300025_103052300087(S)) {
        operation = S.info[S.top];
        S.top--;
    }
}
void undoOperation(List& L, Stack& undoStack, Stack& redoStack) {
    if (!isEmpty_103052300025_103052300087(undoStack)) {
        UndoRedoOperation undoOp;
        pop_undo(undoStack, undoOp);

        if (undoOp.isInsertion) {
            del_103052300025_103052300087(L, undoOp.character);
        } else {
            insL_103052300025_103052300087(L, undoOp.character);
        }
        push_redo(redoStack, undoOp.character, undoOp.isInsertion);
    }
}
void redoOperation(List& L, Stack& undoStack, Stack& redoStack) {
    if (!isEmpty_103052300025_103052300087(redoStack)) {
        UndoRedoOperation redoOp;
        pop_redo(redoStack, redoOp);

        if (redoOp.isInsertion) {
            insL_103052300025_103052300087(L, redoOp.character);
        } else {
            del_103052300025_103052300087(L, redoOp.character);
        }
        push_undo(undoStack, redoOp.character, redoOp.isInsertion);
    }
}
void handleBackspace(List& L, Stack& undoStack) {
    if (L.cursorPos > 0) {
        infotype deletedChar;
        del_103052300025_103052300087(L, deletedChar);
        push_undo(undoStack, deletedChar, false);
    } else if (L.cursorPos == 0 && L.first != nullptr) {
        adr prev = L.first;
        while (prev->next != nullptr) {
            prev = prev->next;
        }
        infotype deletedChar;
        del_103052300025_103052300087(L, deletedChar);
        push_undo(undoStack, deletedChar, false);
    }
}
void insertNewCharacter(List& L, Stack& undoStack, infotype newChar) {
    insL_103052300025_103052300087(L, newChar);
    push_undo(undoStack, newChar, true);
}
int findWord(List L, string word) {
    adr p = L.first;
    int pos = 0;
    string currentWord = "";

    while (p != nullptr) {
        if (isspace(p->info) || p->info == '\n') {
            if (!currentWord.empty()) {
                if (currentWord == word) {
                    return pos - currentWord.length();
                }
                currentWord = "";
            }
        } else {
            currentWord += p->info;
        }
        p = p->next;
        pos++;
    }
    return -1;
}

void moveToLine(List& L, int lineNumber) {
    adr p = L.first;
    int currentLine = 1;
    int currentPos = 0;

    while (p != nullptr) {
        if (p->info == '\n') {
            currentLine++;
        }
        if (currentLine == lineNumber) {
            L.cursorPos = currentPos;
            cout << "Baris telah di pindahkan di posisi yang di inginkan" << endl;
            return;
        }
        p = p->next;
        currentPos++;
    }

    cout << "Baris tidak ditemukan!" << endl;
}
void textEditor_103052300025_103052300087() {
    List L;
    Stack undoStack, redoStack;
    cList_103052300025_103052300087(L);
    cStack_103052300025_103052300087(undoStack);
    cStack_103052300025_103052300087(redoStack);

    char input;
    bool running = true;

    Print_103052300025_103052300087(L);
    while (running) {
        input = _getch();
        if ((input == -32) || (input == 0)) {
            input = _getch();
            switch (input) {
                case KEY_LEFT:
                    moveCursorLeft_103052300025_103052300087(L);
                    Print_103052300025_103052300087(L);
                    break;
                case KEY_RIGHT:
                    moveCursorRight_103052300025_103052300087(L);
                    Print_103052300025_103052300087(L);
                    break;
            }
        }
        else {
            switch (input) {
                case KEY_CTRL_Z:
                    undoOperation(L, undoStack, redoStack);
                    Print_103052300025_103052300087(L);
                    break;

                case KEY_CTRL_Y:
                    redoOperation(L, undoStack, redoStack);
                    Print_103052300025_103052300087(L);
                    break;

                case KEY_BACKSPACE:
                    handleBackspace(L, undoStack);
                    Print_103052300025_103052300087(L);
                    break;

                case '\r':
                    insertNewLine_103052300025_103052300087(L);
                    Print_103052300025_103052300087(L);
                    break;

                case 27:
                    running = false;
                    Print_103052300025_103052300087(L);
                    break;

                case 6:
                    {
                        cout << "Masukkan kata yang dicari: ";
                        string word;
                        cin >> word;
                        int pos = findWord(L, word);
                        Print_103052300025_103052300087(L);

                        if (pos != -1) {
                            cout << "Kata ditemukan di posisi character ke-" << pos << endl;
                        } else {
                            cout << "Kata tidak ditemukan" << endl;
                        }
                    }
                    break;

                case 7:
                    {
                        cout << "Masukkan nomor baris: ";
                        int lineNumber;
                        cin >> lineNumber;
                        Print_103052300025_103052300087(L);
                        moveToLine(L, lineNumber);
                    }
                    break;

                default:
                    if (input >= 32 && input <= 126) {
                        insertNewCharacter(L, undoStack, input);
                        clearStack_103052300025_103052300087(redoStack);
                        Print_103052300025_103052300087(L);
                    }
                    break;
            }
        }

    }
}
