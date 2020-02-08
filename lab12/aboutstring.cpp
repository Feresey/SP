#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void print(const string& s)
{
    cout << (void*)s.data()
         << " : " << setw(6) << s.capacity()
         << " : " << setw(2) << s.size()
         << " : " << s << endl;
}

string decor(const string& id);

int main()
{
    string s;
    print(s);
    //----------------- PART 1 -------------------
    cout << "PART 1\n";
    for (int i = 0; i < 20; ++i) {
        s += "*";
        print(s);
    }
    cout << "\n\n";
    //----------------- PART 2 -------------------
    cout << "PART 2\n";
    string a(s);
    print(a);
    a += "!";
    print(a);
    a += "!";
    print(a);
    print(s);

    cout << "\n\n";
    //----------------- PART 3 -------------------
    cout << "PART 3\n";
    s.clear();
    print(s);

    s.reserve(s.size());
    print(s);

    cout << "\n\n";
    //----------------- PART 4 -------------------
    cout << "PART 4\n";
    s = decor(a);
    print(s);

    cin.get();
    return 0;
}

string decor(const string& id)
{
    // '-','!','?'
    string tmp;
    for (size_t i = 0; i < id.size(); ++i) {
        switch (id[i]) {
        case '?':
            tmp += "_Q";
            break;
        case '!':
            tmp += "_E";
            break;
        case '-':
            tmp += "__";
            break;
        default:
            tmp += id[i];
        }
    }
    print(tmp);
    return tmp;
}
