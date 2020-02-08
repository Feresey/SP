
#include "code-gen.h"
#include <iomanip>
#include <iostream>

#include "base-compiler.cpp"
#include "basegramma.cpp"
#include "baselexer.cpp"
#include "code-gen.cpp"
#include "kngramma.cpp"
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

    tCG cg(gramma_name.c_str());
    tBC& bc = cg;
    if (!bc) {
        cout << bc.getMessage() << endl;
        cout << "Good bye!>";
        cin.get();
        return 1;
    }

    if (print) {
        outgr(cout, bc.getGramma());
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

        do {
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

            file = true;
            bc.PARSER_DEBUG = false;
        } while (false);

        string source = (file ? name : "temp");
        string source_name = source + ".ss";
        if (!file) {
            ofstream tmp(source_name.c_str());
            tmp << buf << endl;
        }

        cout << "Source:" << source_name << endl;
        {
            ifstream fsource(source_name.c_str());
            int linecount = 0;
            while (fsource) {
                *buf = 0;
                fsource.getline(buf, 1000);
                cout << setw(4) << ++linecount << "|" << buf << endl;
            }
            cout << "_________________\n";
        }

        int res = bc.rewrite(source_name.c_str());
        if (res == 0) {
            cout << "Code:\n"
                 << bc.getObject() << endl;
            string obj_name = source + ".cpp";
            ofstream tmp(obj_name.c_str());
            tmp << bc.getObject() << endl;
        } else
            cout << bc.getMessage() << endl;
        cout << "_________________________\n";
    } while (true);
    return 0;
}
