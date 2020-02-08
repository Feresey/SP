
#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"
#define addran addrange

class tLexer : public tBaseLexer {
public:
    std::string Authentication() const
    {
        return "CAA" + std::string("2019");
    }

    tLexer()
        : tBaseLexer()
    {
        addstr(Azero, 0, "+-", 2);
        addstr(Azero, 0, "0", 1);
        addstr(Azero, 2, "0", 1);
        Azero.final(1);

        addstr(Adec, 0, "+-", 1);
        addstr(Adec, 0, "0", 3);
        addstr(Adec, 0, ".", 4);
        addran(Adec, 0, '1', '9', 2);

        addstr(Adec, 1, "0", 3);
        addstr(Adec, 1, ".", 4);
        addran(Adec, 1, '1','9',2);

        addran(Adec, 2, '0', '9', 2);
        addstr(Adec, 2, ".", 4);
        addstr(Adec, 2, "eE", 5);

        addstr(Adec, 3, ".", 4);
        addstr(Adec, 3, "eE", 5);

        addran(Adec, 4, '0','9', 8);

        addran(Adec, 8, '0', '9', 8);
        addstr(Adec, 8, "eE", 5);

        addstr(Adec, 5, "+-", 6);

        addran(Adec, 6, '0', '9', 7);
        addran(Adec, 7, '0', '9', 7);

        Adec.final(2);
        Adec.final(7);
        Adec.final(8);

        addran(Aid, 0, 'a', 'z', 1);
        addran(Aid, 0, 'A', 'Z', 1);
        addstr(Aid, 0, "!", 1);
        addstr(Aid, 0, "?", 2);

        addran(Aid, 1, 'a', 'z', 1);
        addran(Aid, 1, 'A', 'Z', 1);
        addran(Aid, 1, '0', '9', 1);
        addstr(Aid, 1, "-!", 1);
        addstr(Aid, 1, "?", 2);

        addran(Aid, 2, 'a', 'z', 1);
        addran(Aid, 2, 'A', 'Z', 1);
        addran(Aid, 2, '0', '9', 1);
        addstr(Aid, 2, "-!", 1);
        addstr(Aid, 2, "?", 3);

        addran(Aid, 3, 'a', 'z', 1);
        addran(Aid, 3, 'A', 'Z', 1);
        addran(Aid, 3, '0', '9', 1);
        addstr(Aid, 3, "!", 1);
        addstr(Aid, 3, "?", 3);

        Aid.final(1);

        addran(Aidq, 0, 'a', 'z', 1);
        addran(Aidq, 0, 'A', 'Z', 1);
        addstr(Aidq, 0, "!", 1);
        addstr(Aidq, 0, "-", 3);
        addstr(Aidq, 0, "?", 2);

        addran(Aidq, 1, 'a', 'z', 1);
        addran(Aidq, 1, 'A', 'Z', 1);
        addran(Aidq, 1, '0', '9', 1);
        addstr(Aidq, 1, "-", 3);
        addstr(Aidq, 1, "!", 1);
        addstr(Aidq, 1, "?", 2);

        addran(Aidq, 2, 'a', 'z', 1);
        addran(Aidq, 2, 'A', 'Z', 1);
        addran(Aidq, 2, '0', '9', 1);
        addstr(Aidq, 2, "!", 1);
        addstr(Aidq, 2, "-", 3);
        addstr(Aidq, 2, "?", 2);

        addran(Aidq, 3, 'a', 'z', 1);
        addran(Aidq, 3, 'A', 'Z', 1);
        addran(Aidq, 3, '0', '9', 1);
        addstr(Aidq, 3, "!", 1);
        addstr(Aidq, 3, "?", 2);

        Aidq.final(2);
    }
};
#endif
