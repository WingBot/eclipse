//============================================================================
// Name        : datatype.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<string>
#include <limits>
#include <climits>
using namespace std;

int main()
{
    cout << "bool: \t\t" << "所占字节数：" << sizeof(bool);
    cout << "\t取值范围：" << (numeric_limits<bool>::min)();
    cout << " ~ " <<(numeric_limits<bool>::max)()<< endl;
    cout << "char: \t\t" << "所占字节数：" << sizeof(char);
    cout << "\t取值范围：" << (signed int)(numeric_limits<char>::min)();
    cout << " ~ " <<(signed int)(numeric_limits<char>::max)()<< endl;
    cout << "signed char: \t" << "所占字节数：" << sizeof(signed char);
    cout << "\t取值范围：" << (signed int)(numeric_limits<signed char>::min)();
    cout << " ~ " <<(signed int)(numeric_limits<signed char>::max)()<< endl;
    cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char);
    cout << "\t取值范围：" << (unsigned int)(numeric_limits<unsigned char>::min)();
    cout << " ~ " <<(unsigned int)(numeric_limits<unsigned char>::max)()<< endl;
    cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t);
    cout << "\t取值范围：" << (numeric_limits<wchar_t>::min)();
    cout << " ~ " <<(numeric_limits<wchar_t>::max)()<< endl;
    cout << "short(int): \t" << "所占字节数：" << sizeof(short);
    cout << "\t取值范围：" << (numeric_limits<short>::min)();
    cout << " ~ " <<(numeric_limits<short>::max)()<< endl;
    cout << "unsigned short(int):" << "所占字节数：" << sizeof(short);
    cout << "\t取值范围：" << (numeric_limits<unsigned short>::min)();
    cout << " ~ " <<(numeric_limits<unsigned short>::max)()<< endl;
    cout << "int: \t\t" << "所占字节数：" << sizeof(int);
    cout << "\t取值范围：" << (numeric_limits<int>::min)();
    cout << " ~ " <<(numeric_limits<int>::max)()<< endl;
    cout << "unsigned (int): " << "所占字节数：" << sizeof(unsigned);
    cout << "\t取值范围：" << (numeric_limits<unsigned>::min)();
    cout << " ~ " <<(numeric_limits<unsigned>::max)()<< endl;
    cout << "long (int): \t" << "所占字节数：" << sizeof(long);
    cout << "\t取值范围：" << (numeric_limits<long>::min)();
    cout << " ~ " <<(numeric_limits<long>::max)()<< endl;
    cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long);
    cout << "\t取值范围：" << (numeric_limits<unsigned long>::min)();
    cout << " ~ " <<(numeric_limits<unsigned long>::max)()<< endl;
    cout << "double: \t" << "所占字节数：" << sizeof(double);
    cout << "\t取值范围：" << (numeric_limits<double>::min)();
    cout << " ~ " <<(numeric_limits<double>::max)()<< endl;
    cout << "long double: \t" << "所占字节数：" << sizeof(long double);
    cout << "\t取值范围：" << (numeric_limits<long double>::min)();
    cout << " ~ " <<(numeric_limits<long double>::max)()<< endl;
    cout << "float: \t\t" << "所占字节数：" << sizeof(float);
    cout << "\t取值范围：" << (numeric_limits<float>::min)();
    cout << " ~ " <<(numeric_limits<float>::max)()<< endl;
    cout << "size_t: \t" << "所占字节数：" << sizeof(size_t);
    cout << "\t取值范围：" << (numeric_limits<size_t>::min)();
    cout << " ~ " <<(numeric_limits<size_t>::max)()<< endl;
    cout << "string: \t" << "所占字节数：" << sizeof(string);
    cout << "\t取值范围：" << (numeric_limits<string>::min)();
    cout << " ~ " <<(numeric_limits<string>::max)()<< endl;
    cout << "long long: \t" << "所占字节数：" << sizeof(long long);
    cout << "\t取值范围：" << (numeric_limits<long long>::min)();
    cout << " ~ " <<(numeric_limits<long long>::max)()<< endl;
    return 0;
}
