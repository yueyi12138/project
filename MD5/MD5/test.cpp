#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"md5.h"

using std::cout;
using std::endl;

void testHex()
{
	MD5 md5;
	uint32 n = 0x23456789;  //89674523
	cout << md5.changeHex(n) << endl;
}
int main()
{
	testHex();
	return 0;
}