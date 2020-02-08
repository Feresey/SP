/* $b13 */
#include "code-gen.h"
using namespace std;
int tCG::p01(){ // S -> PROG
    string header = "/*  " + lex.Authentication() + "   */\n";
    header += "#include \"mlisp.h\"\n";
    header += declarations;
    header += "//________________ \n";
    S1->obj = header + S1->obj;
    return 0;}
int tCG::p02(){ //  PROG -> CALCS
    S1->obj = "int main(){\n " + S1->obj
        + " std::cin.get();\n return 0;\n}\n";
    return 0;}
int tCG::p03(){ //  PROG -> DEFS
    S1->obj += "int main(){\n"
               " display(\"No calculations!\");newline();\n"
               " std::cin.get();\n return 0;\n}\n";
    return 0;}
int tCG::p04(){ //  PROG -> DEFS CALCS
    //?????????
    S1->obj += "int main(){\n " + S2->obj
        + ";\n std::cin.get();\n return 0;\n}\n";
    return 0;}
int tCG::p05(){ // CALCS -> CALC
    return 0;}
int tCG::p06(){ // CALCS -> CALCS CALC
    S1->obj += ";\n " + S2->obj;
    return 0;}
int tCG::p07(){ //  CALC -> E
    S1->obj = "display(" + S1->obj + "); newline()";
    return 0;}

int tCG::p08(){ //   CALC -> BOOL
    return 0;}
int tCG::p09(){ //   CALC -> STR
    return 0;}
int tCG::p10(){ //   CALC -> DISPSET
    return 0;}
int tCG::p11(){ //      E -> $id
    S1->obj = decor(S1->name);
    return 0;}
int tCG::p12(){ //      E -> CONST
    return 0;}
int tCG::p13(){ //      E -> ADD
    return 0;}
int tCG::p14(){ //      E -> SUB
    return 0;}
int tCG::p15(){ //      E -> DIV
    return 0;}
int tCG::p16(){ //      E -> MUL
    return 0;}
int tCG::p17(){ //      E -> COND
    return 0;}
int tCG::p18(){ //      E -> IF
    return 0;}
int tCG::p19(){ //      E -> CPROC
    return 0;}
int tCG::p20(){ //  CONST -> $zero
    S1->obj = "0";
    return 0;}
int tCG::p21(){ //  CONST -> $dec
    S1->obj = S1->name;
    return 0;}
int tCG::p22(){ //    ADD -> HADD E )
    S1->obj += S2->obj + ")";
    return 0;}
int tCG::p23(){ //   HADD -> ( +
    S1->obj += "(";
    return 0;}
int tCG::p24(){ //   HADD -> HADD E
    S1->obj += S2->obj + " + ";
    ++S1->count;
    return 0;}
int tCG::p25(){ //    SUB -> HSUB E )
    S1->obj += S2->obj + ")";
    return 0;}
int tCG::p26(){ //   HSUB -> ( -
    S1->obj += "(";
    return 0;}
int tCG::p27(){ //   HSUB -> HSUB E
    S1->obj += S2->obj + " - ";
    ++S1->count;
    return 0;}
int tCG::p28(){ //    DIV -> ( / E )
    S1->obj = "(double(1) / " + S3->obj + ")";
    return 0;}
int tCG::p29(){ //    MUL -> HMUL E )
    if (S1->count == 0)
        S1->obj = S2->obj;
    else
        S1->obj += S2->obj;
    S1->count = 0;
    return 0;}
int tCG::p30(){ //   HMUL -> ( *
    return 0;}
int tCG::p31(){ //   HMUL -> HMUL E
    S1->obj += S2->obj + " * ";
    ++S1->count;
    return 0;}
int tCG::p32(){ //   COND -> ( cond CLAUS ELSE )
    S1->obj = S3->obj + S4->obj;
    return 0;}
int tCG::p33(){ //  CLAUS -> HCLAUS E )
    S1->obj += S2->obj + ") : (";
    return 0;}
int tCG::p34(){ // HCLAUS -> ( BOOL
    S1->obj = S2->obj + " ? (";
    return 0;}
int tCG::p35(){ // HCLAUS -> HCLAUS INTER
    S1->obj += S2->obj + ", ";
    return 0;}
int tCG::p36(){ //   ELSE -> HELSE E )
    S1->obj += S2->obj + ")";
    return 0;}
int tCG::p37(){ //  HELSE -> ( else
    S1->obj = "";
    return 0;}
int tCG::p38(){ //  HELSE -> HELSE INTER
    S1->obj += S2->obj + ", ";
    return 0;}
int tCG::p39(){ //     IF -> ( if BOOL E E )
    S1->obj = "((" + S3->obj + ") ? " + S4->obj + " : " + S5->obj + ")";
    S1->count = 0; // !!!
    return 0;}
int tCG::p40(){ //  CPROC -> HCPROC )
    S1->obj += ")";
    return 0;}
int tCG::p41(){ // HCPROC -> ( $id
    S1->obj = decor(S2->name) + "(";
    return 0;}
int tCG::p42(){ // HCPROC -> HCPROC E
    if (S1->count)
        S1->obj += ", ";
    S1->obj += S2->obj;
    ++(S1->count);
    return 0;}
int tCG::p43(){ //   BOOL -> $bool
    S1->obj = (S1->name == "#t" ? "true" : "false");
    return 0;}
int tCG::p44(){ //   BOOL -> $idq
    S1->obj = decor(S1->name);
    return 0;}
int tCG::p45(){ //   BOOL -> CPRED
    return 0;}
int tCG::p46(){ //   BOOL -> REL
    return 0;}
int tCG::p47(){ //   BOOL -> ( not BOOL )
    S1->obj = "( ! " + S3->obj + ")";
    return 0;}
int tCG::p48(){ //  CPRED -> HCPRED )
    S1->obj += ")";
    return 0;}
int tCG::p49(){ // HCPRED -> ( $idq
    S1->obj = decor(S2->name) + "(";
    return 0;}
int tCG::p50(){ // HCPRED -> HCPRED ARG
    S1->obj += S2->obj;
    return 0;}
int tCG::p51(){ //    ARG -> E
    return 0;}
int tCG::p52(){ //    ARG -> BOOL
    return 0;}
int tCG::p53(){ //    REL -> ( < E E )
    S1->obj = "(" + S3->obj + " < " + S4->obj + ")";
    return 0;}
int tCG::p54(){ //    REL -> ( = E E )
    S1->obj = "(" + S3->obj + " == " + S4->obj + ")";
    return 0;}
int tCG::p55(){ //    STR -> $str
    S1->obj = S1->name;
    return 0;}
int tCG::p56(){ //    SET -> ( set! $id E )
    S1->obj = decor(S3->name) + " = " + S4->obj;
    return 0;}
int tCG::p57(){ //DISPSET -> ( display E )
    S1->obj = "display(" + S3->obj + ")";
    return 0;}
int tCG::p58(){ //DISPSET -> ( display BOOL )
    S1->obj = "display(" + S3->obj + ")";
    return 0;}
int tCG::p59(){ //DISPSET -> ( display STR )
    S1->obj = "display(" + S3->obj + ")";
    return 0;}
int tCG::p60(){ //DISPSET -> ( newline )
    S1->obj = "newline()";
    return 0;}
int tCG::p61(){ //DISPSET -> SET
    return 0;}
int tCG::p62(){ //  INTER -> DISPSET
    return 0;}
int tCG::p63(){ //  INTER -> E
    return 0;}
int tCG::p64(){ //   DEFS -> DEF
    return 0;}
int tCG::p65(){ //   DEFS -> DEFS DEF
    S1->obj += S2->obj;
    return 0;}
int tCG::p66(){ //    DEF -> PRED
    return 0;}
int tCG::p67(){ //    DEF -> VAR
    return 0;}
int tCG::p68(){ //    DEF -> PROC
    return 0;}
int tCG::p69(){ //   PRED -> HPRED BOOL )
    S1->obj += S2->obj + ";\n}\n";
    return 0;}
int tCG::p70(){ //  HPRED -> PDPAR )
    S1->obj += ")";
    return 0;}
int tCG::p71(){ //  PDPAR -> ( define ( $idq
    S1->obj = "double " + decor(S4->name) + "(";
    S1->count = 0;
    return 0;}
int tCG::p72(){ //  PDPAR -> PDPAR $idq
    if (S1->count)
        S1->obj += ", ";
    S1->obj += "bool " + decor(S2->name);
    ++(S1->count);
    return 0;}
int tCG::p73(){ //  PDPAR -> PDPAR $id
    if (S1->count)
        S1->obj += ", ";
    S1->obj += "bool " + decor(S2->name);
    ++(S1->count);
    return 0;}
int tCG::p74(){ //    VAR -> ( define $id CONST )
    S1->obj = "double " + decor(S3->name) + " = " + S4->obj + ";\n";
    declarations += S1->obj;
    S1->obj = "";
    return 0;}
int tCG::p75(){ //   PROC -> HPROC LET )
    S1->obj += S2->obj;
    return 0;}
int tCG::p76(){ //   PROC -> HPROC E )
    S1->obj += "return " + S2->obj + ";\n}\n";
    return 0;}
int tCG::p77(){ //  HPROC -> PCPAR )
    declarations += S1->obj + ");//DECLARATION\n";
    S1->obj += "){//DEFINITION\n  ";
    return 0;}
int tCG::p78(){ //  HPROC -> HPROC INTER
    S1->obj += S2->obj + ";\n  ";
    return 0;}
int tCG::p79(){ //  PCPAR -> ( define ( $id
    S1->obj = "double " + decor(S4->name) + "(";
    S1->count = 0;
    return 0;}
int tCG::p80(){ //  PCPAR -> PCPAR $id
    if (S1->count)
        S1->obj += ", ";
    S1->obj += "double " + decor(S2->name);
    ++(S1->count);
    return 0;}
int tCG::p81(){ //    LET -> HLET E )
    S1->obj += "return " + S2->obj + ";\n  } //let\n}\n";
    return 0;}
int tCG::p82(){ //   HLET -> LETLOC )
    return 0;}
int tCG::p83(){ //   HLET -> HLET INTER
    S1->obj += S2->obj + ";\n    ";
    return 0;}
int tCG::p84(){ // LETLOC -> ( let (
    S1->obj += "{ //let\n    ";
    return 0;}
int tCG::p85(){ // LETLOC -> LETLOC LETVAR
    S1->obj += S2->obj;
    return 0;}
int tCG::p86(){ // LETVAR -> ( $id E )
    S1->obj = "double " + decor(S2->name) + " = " + S3->obj + ";\n    ";
    return 0;}
//_____________________
int tCG::p87()  { return 0; } int tCG::p88()  { return 0; }
int tCG::p89()  { return 0; } int tCG::p90()  { return 0; }
int tCG::p91()  { return 0; } int tCG::p92()  { return 0; }
int tCG::p93()  { return 0; } int tCG::p94()  { return 0; }
int tCG::p95()  { return 0; } int tCG::p96()  { return 0; }
int tCG::p97()  { return 0; } int tCG::p98()  { return 0; }
int tCG::p99()  { return 0; } int tCG::p100() { return 0; }
int tCG::p101() { return 0; } int tCG::p102() { return 0; }
int tCG::p103() { return 0; } int tCG::p104() { return 0; }
int tCG::p105() { return 0; } int tCG::p106() { return 0; }
int tCG::p107() { return 0; } int tCG::p108() { return 0; }
int tCG::p109() { return 0; } int tCG::p110() { return 0; }
