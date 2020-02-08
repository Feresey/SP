//                 mlispsem.cpp 2019
#include "semantics.h"
#include <iomanip>
#include <iostream>

#include "base-compiler.cpp"
#include "basegramma.cpp"
#include "baselexer.cpp"
#include "kngramma.cpp"
#include "semantics.cpp"
#include "slr.cpp"
using namespace std;

int main()
{
    char buf[1000];
    cout << "Input gramma name>";
    *buf = 0;
    cin.getline(buf, 1000);

    char* name = buf;
    bool print = false;
    if (*name == '+') {
        ++name;
        print = true;
    }
    string gramma_name = string(name) + ".txt";
    cout << "Gramma:" << gramma_name << endl;
    //____________________________________
    tSM sm(gramma_name.c_str());
    tBC& bc = sm;
    if (print) {
        outgr(cout, bc.getGramma());
    }
    if (!bc) {
        cout << "Good bye!\n";
        cin.get();
        return 1;
    }

    do {
        cout << "Source>";
        *buf = 0;
        cin.getline(buf, 1000);
        if (!*buf)
            break;
        char* name = buf;
        bool file = false;
        bc.PARSER_DEBUG = true;
        //****************************************
        do { //16.04.2016
            if (*name == '\'') {
                ++name;
                file = true;
                break;
            }

            if (*name == '/') {
                ++name;
                file = true;
                bc.PARSER_DEBUG = false;
                break;
            }

            string source_name = string(name) + ".ss";
            ifstream tmp(source_name.c_str());
            if (!tmp)
                break;
            // ������ ����� ������ �� ��� �����
            file = true;
            bc.PARSER_DEBUG = false;
        } while (false);
        //****************************************

        string source = (file ? name : "temp");
        string source_name = source + ".ss";
        if (!file) {
            ofstream tmp(source_name.c_str());
            tmp << buf << endl;
        }

        cout << "Source:" << source_name << endl;
        { // ������ ����� ���������� �����
            ifstream fsource(source_name.c_str());
            int linecount = 0;
            while (fsource) {
                *buf = 0;
                fsource.getline(buf, 1000);
                cout << setw(4) << ++linecount << "|" << buf << endl;
            } //while(fsource)...
            cout << "_________________\n";
        } // ����� �����

        int res = bc.rewrite(source_name.c_str());
        cout << bc.getMessage() << endl;
        if (res == 0) {
            cout << "Accepted!\n";
        } else
            cout << "Rejected!\n";
        cout << "_________________________\n";
    } while (true);
    return 0;
}