/* $mlisp19 */
#include "semantics.h"
#include "semempty.cpp"
#include <sstream>

using namespace std;
void tSM::init()
{
    globals.clear();
    locals.clear();
    params.clear();
    scope = 0;

    globals["e"] =

        tgName(VAR | DEFINED | BUILT);
    globals["pi"] = tgName(VAR | DEFINED | BUILT);

    globals["remainder"] =

        tgName(PROC | DEFINED | BUILT, 2);
    globals["abs"] = tgName(PROC | DEFINED | BUILT, 1);

    return;
}
int tSM::p01()
{
    bool error = false;
    for (tGlobal::iterator it = globals.begin();
         it != globals.end();
         ++it) {
    }
    if (error)
        return 1;
    return 0;
}
int tSM::p11()
{
    return 0;
}
int tSM::p45()
{
    string name = S1->name;
    int count = S1->count;
    if (scope > 1) {
        if (locals.count(name)) {

            ferror_message = "[!]Procedure application:"
                             " local variable '"
                + name + "' shadows the procedure!";
            return 1;
        }
    }
    if (scope > 0) {
        if (params.count(name)) {

            ferror_message = "[!]Procedure application:"
                             " parameter '"
                + name + "' shadows the procedure!";
            return 1;
        }
    }
    do {

        tgName& ref = globals[name];
        if (ref.empty()) {

            ref = tgName(PROC | USED, count);
            break;
        }

        if (!ref.test(PROC)) {

            ferror_message = "[!]Procedure application:"
                             "  '"
                + name + "' is not a procedure!";
            return 1;
        }

        if (ref.arity != count) {

            std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' "

                << (ref.test(DEFINED) ? "expects "

                                      : "has been called already\n\t with ")
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        }

        ref.set(USED);
    } while (false);
    return 0;
}
int tSM::p46()
{
    S1->name = S2->name;
    S1->count = 0;
    return 0;
}
int tSM::p47()
{
    ++S1->count;
    return 0;
}
int tSM::p49()
{
    return 0;
}
int tSM::p55()
{
    return 0;
}
int tSM::p56()
{
    return 0;
}
int tSM::p57()
{
    return 0;
}
int tSM::p58()
{
    return 0;
}
int tSM::p59()
{
    return 0;
}
int tSM::p74()
{
    return 0;
}
int tSM::p87()
{
    return 0;
}
int tSM::p88()
{
    scope = 1;
    return 0;
}
int tSM::p89()
{
    return 0;
}
int tSM::p90()
{
    return 0;
}
int tSM::p91()
{
    return 0;
}
int tSM::p92()
{
    return 0;
}
int tSM::p93()
{
    params.clear();
    scope = 0;
    return 0;
}
int tSM::p94()
{
    params.clear();
    scope = 0;
    return 0;
}
int tSM::p95()
{
    scope = 1;
    return 0;
}
int tSM::p97()
{
    S1->name = S4->name;
    S1->count = 0;
    return 0;
}
int tSM::p98()
{
    if (params.count(S2->name)) {

        ferror_message = "[!]Procedure definition: in '"
            + S1->name + "' duplicate parameter identifier '"
            + S2->name + "'!";
        return 1;
    }
    params.insert(S2->name);
    ++S1->count;
    return 0;
}
int tSM::p99()
{
    locals.clear();
    return 0;
}
int tSM::p100()
{
    scope = 2;
    return 0;
}
int tSM::p102()
{
    return 0;
}
int tSM::p104()
{
    return 0;
}
