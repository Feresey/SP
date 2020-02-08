// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "fsm.h"
#include <iomanip>
#include <iostream>
using namespace std;
#define addran addrange

int main()
{
    tFSM Adec;
    addstr(Adec, 0, ".", 7);
    addstr(Adec, 0, "+-", 1);
    addstr(Adec, 1, "0", 4);
    addran(Adec, 1, '1', '9', 2);
    addstr(Adec, 1, ".", 7);

    addstr(Adec, 4, ".", 7);
    addstr(Adec, 0, "0", 4);

    addran(Adec, 0, '1', '9', 2);
    addran(Adec, 2, '0', '9', 2);
    
    addstr(Adec, 2, ".", 7);
    addran(Adec, 3, '0', '9', 3);
    addran(Adec, 7, '0', '9', 3);

    addstr(Adec, 2, "eE", 5);
    addstr(Adec, 3, "eE", 5);
    addstr(Adec, 5, "+-", 5);
    addran(Adec, 5, '0', '9', 6);
    addran(Adec, 6, '0', '9', 6);

    Adec.final(3);
    Adec.final(2);
    Adec.final(6);

    cout << "*** xxx Adec "
         << "size=" << Adec.size()
         << " ***\n";
    cout << endl;

    while (true) {
        char input[81];
        cout << ">";
        cin.getline(input, 81);
        if (!*input)
            break;
        int res = Adec.apply(input);
        cout << setw(res ? res + 1 : 0) << "^"
             << endl;
    }
    return 0;
}
