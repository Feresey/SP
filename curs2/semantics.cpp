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
    globals["e"] = tgName(VAR | DEFINED | BUILT);
    globals["pi"] = tgName(VAR | DEFINED | BUILT);
    globals["remainder"] = tgName(PROC | DEFINED | BUILT, 2);
    globals["abs"] = tgName(PROC | DEFINED | BUILT, 1);
    globals["cos"] = tgName(PROC | DEFINED | BUILT, 1);
    globals["sin"] = tgName(PROC | DEFINED | BUILT, 1);
    globals["sqrt"] = tgName(PROC | DEFINED | BUILT, 1);
    globals["expt"] = tgName(PROC | DEFINED | BUILT, 2);
    globals["display"] = tgName(PROC | DEFINED | BUILT, 1);
    globals["newline"] = tgName(PROC | DEFINED | BUILT, 0);
    globals["quotient"] = tgName(PROC | DEFINED | BUILT, 2);
}
int tSM::p01()
{ //       S -> PROG
    for (auto it : globals) {
        if (it.second.test(USED) && !(it.second.test(DEFINED))) {
            if (it.second.test(PROC)) { //процедура вызвана, но не определена
                ferror_message += "[!]Procedure application: procedure '"
                    + it.first + "' used, but not defined!\n";
                return 1;
            }
            if (it.second.test(VAR)) { //переменная использована, но не определена
                ferror_message += "[!]Variable application: variable '"
                    + it.first + "' used, but not defined!\n";
                return 1;
            }
        }
    }
    return 0;
}
int tSM::p11()
{ //       E -> $id
    if (scope > 1 && locals.count(S1->name))
        return 0;
    if (scope > 0 && params.count(S1->name))
        return 0;
    tgName& ref = globals[S1->name];
    if (ref.empty()) {
        ref.set(VAR | USED);
        return 0;
    }
    if (ref.test(PROC)) { // правило 13
        ferror_message = "[!]Use procedure: "
            + S1->name + " as a parameter ";
        return 1;
    }
    return 0;
}
int tSM::p45()
{ //   CPROC -> HCPROC )
    string name = S1->name;
    int count = S1->count;
    if (scope > 1) { //   let
        if (locals.count(name)) { //
            //p45-1.ss
            ferror_message = "[!]Procedure application: local variable '" + name + "' shadows the procedure!";
            return 1;
        } // if locals ...
    } // if scope ...
    if (scope > 0) { //
        if (params.count(name)) { //
            ferror_message = "[!]Procedure application: parameter '" + name + "' shadows the procedure!";
            return 1;
        } // if params...
    } // if scope...
    tgName& ref = globals[name];
    if (ref.empty()) { //
        ref = tgName(PROC | USED, count);
        return 0;
    }
    if (!ref.test(PROC)) { //
        ferror_message = "[!]Procedure application:  '"
            + name + "' is not a procedure!";
        return 1;
    }
    if (ref.arity != count) { //
        std::ostringstream buf;
        buf << "[!]Procedure application: '" << name << "' "
            //p45-4.ss
            << (ref.test(DEFINED) ? "expects " //p45-5.ss
                                  : "has been called already\n\t with ")
            << ref.arity << " argument"
            << (ref.arity != 1 ? "s" : "")
            << ", given: " << count << " !";
        ferror_message = buf.str();
        return 1;
    }
    ref.set(USED);
    return 0;
}
int tSM::p46()
{ //  HCPROC -> ( $id
    S1->name = S2->name;
    S1->count = 0;
    return 0;
}

int tSM::p49()
{ //    BOOL -> $idq
    if (scope > 1 && locals.count(S1->name))
        return 0;
    if (scope > 0 && params.count(S1->name))
        return 0;
    tgName& ref = globals[S1->name];
    if (ref.empty()) {
        ref.set(VAR | USED);
        return 0;
    }
    if (ref.test(PROC)) { // правило 13
        ferror_message = "[!]Used procedure: "
            + S1->name + " as a parameter ";
        return 1;
    }
    return 0;
}
int tSM::p55()
{ //   CPRED -> HCPRED )
    string name = S1->name;
    int count = S1->count;
    if (scope > 0) { //
        if (params.count(name)) { //
            //p45-2.ss
            ferror_message = "[!]Procedure application: parameter '"
                + name + "' shadows the procedure!";
            return 1;
        } // if params...
    } // if scope...
    tgName& ref = globals[name];
    if (ref.empty()) { //
        ref = tgName(PROC | USED, count);
        ref.set(USED);
        return 0;
    }
    if (!ref.test(PROC)) { //
        ferror_message = "[!]Procedure application:  '"
            + name + "' is not a procedure!";
        return 1;
    }
    if (ref.arity != count) { //
        std::ostringstream buf;
        buf << "[!]Procedure application: '" << name << "' "
            //p45-4.ss
            << (ref.test(DEFINED) ? "expects " //p45-5.ss
                                  : "has been called already\n\t with ")
            << ref.arity << " argument"
            << (ref.arity != 1 ? "s" : "")
            << ", given: " << count << " !";
        ferror_message = buf.str();
        return 1;
    }
    if (ref.types != S1->types) { //
        std::ostringstream buf;
        buf << "[!]Procedure application: '" << name << "' "
            << (ref.test(DEFINED) ? "expects " //p45-5.ss
                                  : "has been called already\n\t with ")
            << "other types of parameters";
        ferror_message = buf.str();
        return 1;
    }
    ref.set(USED);
    return 0;
}
int tSM::p56()
{ //  HCPRED -> ( $idq
    S1->name = S2->name;
    S1->count = 0;
    S1->types = 0;
    return 0;
}
int tSM::p57()
{ //  HCPRED -> HCPRED ARG
    S1->count++;
    S1->types <<= 1;
    if (!S2->types)
        S1->types++;
    // S2->count = S1->count;
    return 0;
}
int tSM::p58()
{ //     ARG -> E
    S1->types = 1;
    return 0;
}
int tSM::p59()
{ //     ARG -> BOOL
    S1->types = 0;
    return 0;
}
int tSM::p74()
{ //     SET -> ( set! $id E )
    if (scope > 1 && locals.count(S3->name))
        return 0;
    if (scope > 0 && params.count(S3->name))
        return 0;
    auto& ref = globals[S3->name];
    if (ref.empty()) { //неизвестное имя
        ref = tgName(VAR | USED);
        return 0;
    }
    if (ref.test(PROC)) { //
        ferror_message = "[!]Procedure application: '"
            + S3->name + "' can't be redefined";
        return 1;
    }
    if (ref.test(VAR) && ref.test(BUILT)) {
        ferror_message = "[!]Variable application: '"
            + S3->name + "' can't be redefined";
        return 1;
    }
    ref.set(USED); // имя использовано
    return 0;
}
int tSM::p87()
{ //    PRED -> HPRED BOOL )
    return 0;
}
int tSM::p88()
{ //   HPRED -> PDPAR )
    scope = 1;
    auto& ref = globals[S1->name];
    if (!ref.empty()) {
        if (ref.test(DEFINED)) {
            ferror_message = "[!]Redefinition global variable!";
            return 1;
        }
        if (ref.test(USED)) {
            if (ref.arity != S1->count) {
                ferror_message = "[!]Was called with another count of parameters!";
                return 1;
            }
            if (ref.types != S1->types) {
                ferror_message = "[!]Was called with another count of parameters!";
                return 1;
            }
        }
    }
    ref.arity = S1->count;
    ref.set(DEFINED | PROC);
    return 0;
}
int tSM::p89()
{ //   PDPAR -> ( define ( $idq
    S1->name = S4->name;
    S1->count = 0;
    return 0;
}
int tSM::p90()
{ //   PDPAR -> PDPAR $idq
    if (params.count(S2->name)) { // p8
        ferror_message = "[!]Predicate definition: in '"
            + S1->name + "' duplicate parameter identifier '" + S2->name + "'!";
        return 1;
    }
    params.insert(S2->name);
    globals[S1->name].types <<= 1;
    globals[S1->name].types++;
    ++S1->count;
    return 0;
}
int tSM::p91()
{ //   PDPAR -> PDPAR $id
    if (params.count(S2->name)) { // p8
        ferror_message = "[!]Predicate definition: in '"
            + S1->name + "' duplicate parameter identifier '" + S2->name + "'!";
        return 1;
    }
    params.insert(S2->name);
    globals[S1->name].types <<= 1;
    ++S1->count;
    return 0;
}
int tSM::p92()
{ //     VAR -> ( define $id CONST )
    if (globals.count(S3->name) && globals[S3->name].test(DEFINED)) {
        ferror_message = "[!]Redefinition global variable: '"
            + S3->name + "'!";
        S1->count = 0;
        return 1;
    }
    globals[S3->name] = tSM::tgName(VAR | DEFINED);
    return 0;
}
int tSM::p93()
{ //    PROC -> HPROC LET )
    params.clear();
    scope = 0;
    return 0;
}
int tSM::p94()
{ //    PROC -> HPROC E )
    params.clear();
    scope = 0;
    return 0;
}
int tSM::p95()
{ //   HPROC -> PCPAR )
    scope = 1;
    auto& ref = globals[S1->name];
    if (!ref.empty()) {
        if (ref.test(DEFINED)) {
            ferror_message = "[!]Redefinition global variable!";
            return 1;
        }
        if (ref.test(USED)) {
            if (ref.arity != S1->count) {
                ferror_message = "[!]Was called with another count of parameters!";
                return 1;
            }
        }
    }
    globals[S1->name].arity = S1->count;
    globals[S1->name].set(DEFINED | PROC);
    return 0;
}
int tSM::p96()
{ //   HPROC -> HPROC INTER
    S1->count++;
    return 0;
}
int tSM::p97()
{ //   PCPAR -> ( define ( $id
    S1->name = S4->name;
    S1->count = 0;
    return 0;
}
int tSM::p98()
{ //   PCPAR -> PCPAR $id
    if (params.count(S2->name)) {
        //p98-1.ss
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
{ //     LET -> HLET E )
    locals.clear();
    return 0;
}
int tSM::p100()
{ //    HLET -> LETLOC )
    scope = 2;
    return 0;
}

int tSM::p102()
{ //  LETLOC -> ( let (
    return 0;
}
int tSM::p104()
{ //  LETVAR -> ( $id E )
    if (globals.count(S2->name)) {
        //p104-1
        ferror_message = "[!]Let shadows global name: '"
            + S2->name + "'!";
        return 1;
    }
    if (locals.count(S2->name)) {
        //p104-2
        ferror_message = "[!]Let redefines local variable: '"
            + S2->name + "'!";
        return 1;
    }
    locals.insert(S2->name);
    S1->count = 0;
    return 0;
}
