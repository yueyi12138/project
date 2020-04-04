#define  _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<iostream>
#include "md5.h"
//��ʼ��static��Ա
int MD5::_leftShift[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 
12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9,14, 20, 5, 9, 
14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 
16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10,
15, 21, 6, 10, 15, 21};

MD5::MD5()
{
	init();
}
void MD5::init()
{
	//��ʼ��k[i]
	for (int i = 0; i < 64; ++i)
	{
		_k[i] = static_cast<uint32>(abs(sin(i + 1.0))*pow(2.0, 32));
	}
}

void MD5::reset()
{
	_a = 0x67452301; 
	_b = 0xefcdab89; 
	_c = 0x98badcfe; 
	_d = 0x10325476;
	//��ʼ��chunk
	memset(_chunk, 0, CHUNK_BYTE);
	_lastByte = _totalByte = 0;


}

void MD5::calMD5(uint32* chunk)
{
	//if (0 <= i < 16) g = i; 
	//if (16 <= i < 32) g = (5 * i + 1) % 16;
	//if (32 <= i < 48) g = (3 * i + 5) % 16; 
	//if(48 <= i < 63) g = (7 * i) % 16;
	//4byteΪһ������Ԫ
	//��ִ��64�β���
	int a = _a, b = _b, c = _c, d=_d ;
	int f, g;
	for (int i = 0; i < 64; i++)
	{
		//λ���� F G H I
		// 0~15 F
		if (0 <= i&&i <= 15)
		{
			f = F(b, c, d);
			g = i;
		}
		//16~31 G
		else if (16 <= i&&i <= 31)
		{
			f = G(b, c, d);
			(5 * i + 1) % 16;
		}
		//32~47 H
		else if (32<= i&&i <= 47)
		{
			f = H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		//48~63 I
		else 
		{
			f = I(b, c, d);
			g = (7 * i) % 16;
		}
		//���� �ӷ� ѭ������
		int tmp = d;
		d = c;
		c = b;
		b = b + leftShift(a + f + chunk[g] + _k[i], _leftShift[i]);
		a = tmp;
	}
	//����A,B,C,D
	_a += a;
	_b += b;
	_c += c;
	_d += d;
}

//������䣬�ٽ���MD5����
void MD5::calFinalMD5()
{
	//���������Ϣ����һ��bitλ��1��ʣ����0
	//�κ��������Ҫ�������1byte��������Ϣ
	//��ȡ��һ��������λ��
	char*p = _chunk + _lastByte;
	//�������1byte��������Ϣ��1000 0000
	*p++ = 0x80;
	int remainByte = CHUNK_BYTE - _lastByte - 1;
	//���ʣ���ֽ�������8byte->64bit��������䳤����Ϣ
	//�ȴ���һ�����ݣ���ȥ����һ���µ����ݿ飬ǰ448λ��0�����64λ�����Ϣ
	if (remainByte < 8)
	{
		//ʣ��λȫ�����㣬����һ��
		memset(p, 0, remainByte);
		calMD5((uint32*)_chunk);
		//����һ���µ����ݿ�
		memset(_chunk, 0, CHUNK_BYTE);
	}
	else
	{
		//ʣ��λȫ������
		memset(p, 0, remainByte);
	}
	//�����ݿ�����64λ���ԭʼ������Ϣ
	unsigned long long totalBits = _totalByte;
	totalBits *= 8;
	((unsigned long long*)_chunk)[7] = totalBits;
	calMD5((uint32*)_chunk);
}

std::string MD5::changeHex(uint32 n)
{
	static std::string strMap = "0123456789abcdef";
	std::string ret;
	//��ȡÿһ���ֽ�����
	for (int i = 0; i < 4; i++)
	{
		//��ȡһ���ֽ�����
		int curByte = (n >> (i * 8)) & 0xff;
		//����ת��16�����ַ�
		std::string curRet;
		//��16����λ  ģ16����λ   �ֽ��ڲ�����
		curRet += strMap[curByte / 16];
		curRet += strMap[curByte %16];
		//�ֽ�֮������
		ret += curRet;
	}
	return ret;
}

std::string getStringMD5(const std::string& str)
{
	return "";
}

std::string getFileMD5(const char* filePath)
{
	return "";
}