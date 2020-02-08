
#include "parser.h"
#include <iomanip>
#include <iostream>

#include "basegramma.cpp"
#include "baselexer.cpp"
#include "kngramma.cpp"
#include "parser.cpp"
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
    tParser parser(gramma_name.c_str());
    if (!parser) {
        cout << parser.getMessage() << endl;
        cout << "Good bye! >";
        cin.get();
        return 1;
    }

    if (print) {
        outgr(cout, parser.getGramma());
    }
    do {
        cout << "Source>";
        *buf = 0;
        cin.getline(buf, 1000);
        if (!*buf)
            break;
        char* name = buf;
        bool file = false;
        parser.PARSER_DEBUG = true;

        do {
            if (*name == '\'') {
                ++name;
                file = true;
                break;
            }

            if (*name == '/') {
                ++name;
                file = true;
                parser.PARSER_DEBUG = false;
                break;
            }

            string source_name = string(name) + ".ss";
            ifstream tmp(source_name.c_str());
            if (!tmp)
                break;

            file = true;
            parser.PARSER_DEBUG = false;
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

        int res = parser.parse(source_name.c_str());
        if (res == 0)
            cout << "Good sourse!\n";
        else
            cout << parser.getMessage() << endl;
        cout << "_________________________\n";
    } while (true);
    return 0;
}
