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

void testStringMD5()
{
	MD5 md5;
	std::string str = "123456789abcdefgh";
	cout << md5.getStringMD5(str) << endl;
}
int main()
{
	//testHex();
	testStringMD5();
	return 0;
}