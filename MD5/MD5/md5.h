#include<string>
#define CHUNK_BYTE 64
typedef unsigned int uint32;

class MD5
{
public:
	/*
	F(x,y,z) = (x & y) | ((~x) & z) 
	G(x,y,z) = (x & z) | ( y & (~z)) 
	H(x,y,z) = x ^ y ^ z
	I(x,y,z) = y ^ (x | (~z))
	*/
	//位运算函数
	uint32 F(uint32 b, uint32 c, uint32 d)
	{
		return (b & c) | ((~b) & d);
	}
	uint32 G(uint32 b, uint32 c, uint32 d)
	{
		return (b & d) | (c & (~d));
	}
	uint32 H(uint32 b, uint32 c, uint32 d)
	{
		return  b ^ c ^ d;
	}
	uint32 I(uint32 b, uint32 c, uint32 d)
	{
		return c ^ (b | (~d));
	}
	//循环左移
	uint32 leftShift(uint32 number, int shiftnumber)
	{
		return (number << shiftnumber) | (number >> (32 - shiftnumber));
	}
	MD5();//构造函数

	void init();

	void reset();

	//一个chunk的MD5运算
	void calMD5(uint32* chunk);

	//进行填充，再进行MD5计算
	void calFinalMD5();

	//把一个整数数据换成对应的16进制字符串
	std::string changeHex(uint32 n);
	std::string getStringMD5(const std::string& str);
	std::string getFileMD5(const char* filePath);
	
private:
	//循环移位的位数
	static int _leftShift[64];
	//K[i]:    K[i] = floor(2^(32) * abs(sin(i + 1)))
	unsigned int _k[64];
	//数据块 64byte
	char _chunk[CHUNK_BYTE];
	//填充相关变量
	//最后一块数据的字节数
	uint32 _lastByte;
	//总字节数
	uint32 _totalByte;
	//MD5信息
	uint32 _a;
	uint32 _b;
	uint32 _c;
	uint32 _d;
};

//多个cc cpp文件包含次头文件会导致static成员的重定义
//int MD5::_leftShift[64]={初始化}；