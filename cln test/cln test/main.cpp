//
//  main.cpp
//  cln test
//
//  Created by Philip Huffman on 3/15/18.
//  Copyright © 2018 Philip Huffman. All rights reserved.
//

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <time.h>
#include <cln/cln.h>

using namespace cln;
using namespace std;

int chkCenter(cl_I n);
cl_I makePalindromeOdd(cl_I n);
cl_I nextPalindrome(cl_I n);
cl_I nextPrimePalindrome(cl_I n);
string fmt(cl_I n);

int main(int argc, const char * argv[]) {
    set<int> cetenters;
    int j;
    cl_I n = 9;
    pair<std::set<int>::iterator, bool> ret;
    string s;
    s.insert(0, 153, '8');
    n = cl_I(s.c_str());
    long i = 0;
    cout.flags(ios::right);
    do {
        n = nextPrimePalindrome(n);
        cout << fmt(n) << endl;
        j = chkCenter(n);
        if (j >= 0) {
            ret = cetenters.insert(j);
            if (ret.second) {
                cout << setw(4) << cetenters.size() << setw(11) << fmt(i) << setw(3) << fmt(j).substr(0,1) << endl;
            }
        }
        i++;
    } while (cetenters.size() < 10);
    return 0;
}

int chkCenter(cl_I n) {
    stringstream ss;
    ss << n;
    string s = ss.str();
    long l = s.length() >> 1;
    int i0 = stoi(s.substr(l - 1, 3));
    int i1 = stoi(s.substr(l, 3));
    if (i0 == i1) {
        return i0;
    }
    return -1;
}

cl_I nextPrimePalindrome(cl_I n) {
    do {
        n = nextPalindrome(n);
    } while (!isprobprime(n));
    return n;
}

cl_I nextPalindrome(cl_I n) {
    if (n < 11) {
        return 11;
    }
    if (n < 101) {
        return 101;
    }
    if (!oddp(n)) {
        return makePalindromeOdd(n);
    }
    stringstream s0, s1;
    cl_I i;
    s0 << n;
    string s = s0.str(), u0;
    long l = s.length() >> 1;
    if (s.length() % 2 == 0) {
        s.insert(l, 1, '0');
        u0 = s;
    } else {
        u0 = s.substr(0, l + 1);
        i = cl_I(u0.c_str()) + 1;
        s1 << i;
        u0 = s1.str();
        string u1 = u0.substr(0, l);
        reverse(u1.begin(), u1.end());
        u0.append(u1);
    }
    i = cl_I(u0.c_str());
    if (oddp(i)) {
        return i;
    }
    return makePalindromeOdd(i);
}

string fmt(cl_I n) {
    stringstream ss;
    ss << n;
    string s = ss.str();

    for (long i = s.length() - 3; i > 0; i -= 3) {
        s.insert(i, 1, ',');
    }
    
    return s;
}

cl_I makePalindromeOdd(cl_I n) {
    n++;
    if (mod(n, 5) == 0) {
        n += 2;
    }
    stringstream s0;
    s0 << n;
    string s = s0.str();
    long l = s.length() >> 1;
    string u1 = s.substr(l + 1, l);
    string u0 = u1;
    reverse(u0.begin(), u0.end());
    string m = "0";
    u0.append(m.append(u1));
    return cl_I(u0.c_str());
}

//void lineOut(cl_I n, long i) {
//    time_t rawtime;
//    struct tm * timeinfo;
//    time (&rawtime);
//    timeinfo = localtime (&rawtime);
//    string s = asctime(timeinfo);
//    cout << fmt(i + 1) << " \t" << fmt(n) << endl;
//}
