/* $mlisp18 */
#include "semantics.h"
#include "semempty.cpp"
using namespace std;
void tSM::init()
{
    globals.clear();
    locals.clear();
    params.clear();
    scope = 0; // глобальная область
    //константы:
    globals["e"] =
        //
        properties
            tgName(VAR | DEFINED | BUILT);
    globals["pi"] = tgName(VAR | DEFINED | BUILT);
    //
    // элементарные процедуры:
    globals["remainder"] =
        //
        properties
            arity
                tgName(PROC | DEFINED | BUILT, 2);
    globals["abs"] = tgName(PROC | DEFINED | BUILT, 1);
    globals["expt"] = tgName(PROC | DEFINED | BUILT, 2);
    globals["display"] = tgName(PROC | DEFINED | BUILT, 1);
    globals["newline"] = tgName(PROC | DEFINED | BUILT, 0);
    globals["quotient"] = tgName(PROC | DEFINED | BUILT, 2);
    // ...
    // только те процедуры, которые использованы
    // в СВОИХ контрольных задачах
    return;
}
// +++ пункт 1
int tSM::p01()
{ //S->PROG
    bool error = false;
    for (tGlobal::iterator it = globals.begin(); it != globals.end(); ++it) {
        if ((it->second.test(USED))
            && !(it - > second.test(DEFINED))
            && (it->second.test(PROC))) { //процедура вызвана, но не определена
            ferror_message += "[!]Procedure application: procedure '"
                + it->first + "' used, but not defined!\n";
            error = true;
        }
        if ((it->second.test(USED))
            && !(it - > second.test(DEFINED))
            && (it->second.test(VAR))) { //переменная использована, но не определена
            ferror_message += "[!]Variable application: variable '"
                + it->first + "' used, but not defined!\n";
            error = true;
        }
        if (!(it->second.test(USED))
            && (it - > second.test(DEFINED))
            && !(it->second.test(BUILT))
            && (it->second.test(PROC))) {
            ferror_message += "[?]Procedure application: procedure '"
                + it->first + "' defined, but not used!\n";
        }
        if (!(it->second.test(USED))
            && (it - > second.test(DEFINED))
            && !(it->second.test(BUILT))
            && (it->second.test(VAR))) {
            ferror_message += "[?]Variable application:"
                              "variable '"
                + it->first + "' defined, but not used!\n";
        }
        // Просмотреть таблицу глобальных имен
        // и в сообщении об ошибках указать имена
        // ВСЕХ вызванных, но не определенных процедур,
        // а также использованных, но не определенных
        // глобальных переменных. Сообщения отметить [!].
        // Кроме того, ПРЕДУПРЕДИТЬ обо ВСЕХ определенных,
        // но не использованных процедурах и переменных,
        // за исключением встроенных. Сообщения отметить [?].
        // it->first имя
        // it->second учетная запись
        // ...
    } //for...
    if (error)
        return 1;
    return 0;
}
// идентификаторы переменных
int tSM::p13()
{ //E->$id
        string name
        = S1->name;
    if (scope > 1) { // локальная область
        if (locals.count(name)) { // имя локальное
            return 0;
        }
    }
    if (scope > 0) { // область параметров
        if (params.count(name)) { // имя параметра
            return 0;
        }
    }
    //найти имя в глобальной таблице
    tgName& ref = globals[name];
    if (ref.empty()) { // неизвестное имя
        ref.set(VAR);
        ref.set(USED); // новая запись
        return 0;
    }
    if (ref.test(PROC)) { // правило 13
        ferror_message = "[!]Procedure application:"
                         "name of procedure '"
            + name + "' cann't be
            passed as parameter ";
            return 1;
    }
}
ref.set(USED);
return 0;
int tSM::p21()
{ //E->CPROC
        string name
        = S1->name;
    int count = S1->count;
    if (scope > 1) { // локальная область
        if (locals.count(name)) { // локальное имя
            //p21-1.ss
            ferror_message = "[!]Procedure application:"
                             " local variable '"
                + name + "' shadows the procedure!";
            return 1;
        } // if locals ...
    } // if scope ...
    if (scope > 0) { // область параметров
        if (params.count(name)) { // имя параметра
            //p21-2.ss
            ferror_message = "[!]Procedure application:"
                             " parameter '"
                + name + "' shadows the procedure!";
            return 1;
        } // if params...
    } // if scope...
    do {
        // найти имя в глобальной таблице
        tgName& ref = globals[name];
        if (ref.empty()) { //неизвестное имя
            //
            создать новую учетную запись
                ref
                = tgName(PROC | USED, count);
            break;
        }
        // имя найдено
        if (!ref.test(PROC)) { //не процедура
            //p21-3.ss
            ferror_message = "[!]Procedure application:"
                             " '"
                + name + "' is not a procedure!";
            return 1;
        }
        if (ref.arity != count) { //число аргументов
            //
            не равно числу параметров
                std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' "
                //p21-4.ss
                << (ref.test(DEFINED) ? "expects " // процедура
                           //
                           уже определена
                               //p21-5.ss
                               // процедура еще не определена, но уже вызывалась
                               ранее
                                      : "has been called already\n\t with ")
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        }
        // ошибок нет
        ref.set(USED); //имя использовано
    } while (false);
}
return 0;
// вызов процедуры
int tSM::p50()
{ // HCPROC -> ( $id
    S1->name = S2->name;
    S1->count = 0;
    return 0;
}
int tSM::p51()
{ // HCPROC -> HCPROC E
    ++S1->count;
    return 0;
}
// имя предиката содержит ?, имена переменных и имена
параметров не могут его содержать, потому что это $id int tSM::p58()
{ // CPRED -> HCPRED )
    string name = S1->name;
    int count = S1->count;
    do {
        // найти имя в глобальной таблице
        tgName& ref = globals[name];
        if (ref.empty()) { // неизвестное имя
            ref = tgName(PROC | USED, count); // создать новую
            учетную запись return 0;
        }
        if (ref.arity != count) { //число аргументов не равно
            числу параметров
                std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' "
                << (ref.test(DEFINED) ? "expects " // процедура
                           //
                           уже определена
                               // процедура еще не определена, но уже вызывалась
                               ранее
                                      : "has been called already\n\t with ")
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        }
        // ошибок нет
        ref.set(USED); //имя использовано
    } while (false);
}
return 0;
// вызов предиката
int tSM::p59()
{ // HCPRED -> ( $idq
    S1->name = S2->name;
    S1->count = 0;
    return 0;
}
int tSM::p60()
{ // HCPRED -> HCPRED E
    ++S1->count;
    return 0;
}
// присваивание
int tSM::p78()
{ // HSET -> ( set! $id
    string name = S3->name;
    if (scope > 1) { // локальная область
        if (locals.count(name)) { // имя локальное
            return 0;
        }
    }
    if (scope > 0) { // область параметров
        if (params.count(name)) { // имя параметра
            return 0;
        }
    }
    // найти имя в глобальной таблице
    tgName& ref = globals[name];
    if (ref.empty()) { //неизвестное имя
        ref = tgName(VAR | USED); // создать новую учетную
        запись
        return 0;
    }
    if (ref.test(PROC)) { //
        ferror_message = "[!]Procedure application:"
                         " procedure '"
            + name + "' cann't be redefined";
        return 1;
    }
    if (ref.test(VAR) && ref.test(BUILT)) {
        ferror_message = "[!]Procedure application:"
                         " constant '"
            + name + "' cann't be redefined";
        return 1;
    }
    ref.set(USED); // имя использовано
    return 0;
}
// определение предиката
int tSM::p89()
{ // PRED -> HPRED BOOL )
    string name = S1->name;
    int count = S1->count;
    tgName& ref = globals[name]; // найти имя в
    глобальной таблице if (ref.empty())
    { //неизвестное имя
        ref = tgName(PROC | DEFINED, count); // создать
        новую учетную запись
            params.clear();
        scope = 0;
        return 0;
    }
    if (ref.test(DEFINED)) { // p6
        ferror_message = "[!]Procedure defenition:"
                         " procedure '"
            + name + "' was defined";
        return 1;
    }
    if (ref.arity != count) { //число аргументов не равно
        числу параметров p4
            std::ostringstream buf;
        buf << "[!]Procedure application: '" << name << "' "
            << (ref.test(DEFINED) ? "expects " // процедура
                       уже определена
                                  : "has been called already\n\t with ") //
            процедура еще не определена,
            но уже вызывалась ранее
            << ref.arity << " argument"
            << (ref.arity != 1 ? "s" : "")
            << ", given: " << count << " !";
        ferror_message = buf.str();
        return 1;
    }
    ref.set(DEFINED);
    params.clear();
    scope = 0;
    return 0;
}
int tSM::p90()
{ //
    scope = 1;
    return 0;
}
HPRED -> PDPAR )
int tSM::p91()
{ // PDPAR -> ( define ( $idq
    S1->name = S4->name;
    S1->count = 0;
    return 0;
}
// параметры
int tSM::p92()
{ // PDPAR -> PDPAR $id
    if (params.count(S2->name)) { // p8
        ferror_message = "[!]Predicate definition:"
                         "in '"
                + S1->name + "' duplicate parameter identifier '" + S2 -
            > name + "'!";
        return 1;
    }
    params.insert(S2->name);
    ++S1->count;
    return 0;
}
// определение глобальной переменной
int tSM::p95()
{ // HVAR -> ( define $id
    string name = S3->name;
    tgName& ref = globals[name];
    if (ref.empty()) { //неизвестное имя
        //создать новую учетную запись
        ref = tgName(VAR | DEFINED);
        return 0;
    }
    if (ref.test(DEFINED)) { //p6
        ferror_message = "[!]Global variable init:"
                         " redefinition '"
            + name + "'";
        return 1;
    }
    if (ref.test(PROC) && ref.test(USED)) { //p2
        ferror_message = "[!]Global variable init:"
                         " procedure '"
            + name + "' was used";
        return 1;
    }
}
ref.set(DEFINED);
return 0;
// определение процедуры
int tSM::p96()
{ // PROC -> HPROC LETLOC )
    string name = S1->name;
    int count = S1->count;
    tgName& ref = globals[name];
    if (ref.empty()) {
        //не было упоминаний
        ref = tgName(PROC | DEFINED, count);
        params.clear();
        scope = 0;
        return 0;
    }
    if (ref.test(VAR)) { //p6
        ferror_message = "[!]Procedure init:"
                         " variable '"
            + name + "' was initializated";
        return 1;
    }
    if (ref.test(DEFINED)) { //p6
        ferror_message = "[!]Procedure init:"
                         " procedure '"
            + name + "' was initializated";
        return 1;
    }
    if (ref.arity != count) {
        std::ostringstream buf;
        buf << "[!]Procedure application: '" << name << "' "
            << "has been called already\n\t with "
            << ref.arity << " argument"
            << (ref.arity != 1 ? "s" : "")
            << ", given: " << count << " !";
        ferror_message = buf.str();
        return 1;
    }
    ref.set(DEFINED);
    params.clear();
    scope = 0;
    return 0;
}
// определение процедуры
int tSM::p97()
{ // PROC -> HPROC E1 )
    string name = S1->name;
    int count = S1->count;
    tgName& ref = globals[name];
    if (ref.empty()) {
        //не было упоминаний
        ref = tgName(PROC | DEFINED, count);
        params.clear();
        scope = 0;
        return 0;
    }
    if (ref.test(VAR)) {
        ferror_message = "[!]Procedure init:"
                         " variable '"
            + name + "' was initialized";
        return 1;
    }
    if (ref.test(DEFINED)) {
        ferror_message = "[!]Procedure init:"
                         " '"
            + name + "' was initialized";
        return 1;
    }
    if (ref.arity != count) {
        std::ostringstream buf;
        buf << "[!]Procedure application: '" << name << "' "
            << "has been called already\n\t with "
            << ref.arity << " argument"
            << (ref.arity != 1 ? "s" : "")
            << ", given: " << count << " !";
        ferror_message = buf.str();
        return 1;
    }
    ref.set(DEFINED);
    params.clear();
    scope = 0;
    return 0;
}
int tSM::p98()
{ //
    scope = 1;
    return 0;
}
HPROC -> PCPAR )
int tSM::p100()
{ //
 PCPAR -> ( define ( $id
S1->name = S4->name;
S1->count = 0;
return 0;
}
// параметры
int tSM::p101()
{ // PCPAR -> PCPAR $id
    if (params.count(S2->name)) {
        //p101-1.ss
        ferror_message = "[!]Procedure definition: in '"
            + S1->name + "' duplicate parameter identifier '"
            + S2->name + "'!";
        return 1;
    }
    params.insert(S2->name);
    ++S1->count;
    return 0;
}
int tSM::p102()
{ // LETLOC -> HLETLOC E1 )
    locals.clear();
    return 0;
}
int tSM::p103()
{ // HLETLOC -> LTVAR )
    scope = 2;
    return 0;
}
// определение локальной переменной
int tSM::p105()
{ // LTVAR -> ( let ( CPROC
    S1->name = S4->name;
    S1->count = 1;
    locals.insert(S4->name);
    return 0;
}
// определение локальных переменных
int tSM::p106()
{ // LTVAR -> LTVAR CPROC
    if (locals.count(S2->name)) {
        ferror_message = "[!]Local variables definition: in '"
            + S1->name + "' duplicate variable initialization'"
            + S2->name + "'!";
        return 1;
    }
    locals.insert(S2->name);
    ++S1->count;
    return 0;
}
//_____________________
