// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <limits>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int main()
{
	float sphere_dist = std::numeric_limits<float>::max();

	std::cout << "max" << sphere_dist<<"\n";
	std::cout << &sphere_dist;


	/*
	char a = 'A';
	std::cout << a << "\n";
	std::string sdd = "sadsa";
	char *b = (char*)"sghjk";

	std::cout << "is *b \t" << *b << "\n";
	std::cout << "is &*b \t" << &*b << "\n";
	std::cout << "is &b \t" << &b << "\n";
	std::cout << "is b[0] \t" << b[0] << "\n";
	std::cout << "is &b[0] \t" << &b[0] << "\n\n";

	b = &a;
	
	std::cout << "is *b \t" << *b << "\n";
	std::cout << "is b[0] \t" << b[0] << "\n";
	*/

	/*
	int a, b, c;
	a = b = c = 1;
	unsigned char* data = stbi_load("rgba.png", &a, &b, &c, 0);

	printf("%d, %d, %d\n", a, b, c);

	for (size_t i = 0; i < a*b+300; i++)
	{
		printf("%d\t", data[i*c + 0]);
		printf("%d\t", data[i*c + 1]);
		printf("%d\t", data[i*c + 2]);
		printf("%d\n", data[i*c + 3]);
		if (i == a*b)
		{
			printf("\n\n\n");
		}
	}
	*/

	//printf("\n\n");

	////for (size_t i = 0; i < 10; i++)
	////{
	////	printf("%d\t", data[c * a * 10 + c * i + 0]);
	////	printf("%d\t", data[c * a * 10 + c * i + 1]);
	////	printf("%d\t", data[c * a * 10 + c * i + 2]);
	////	printf("%d\n", data[c * a * 10 + c * i + 3]);
	////}

	////for (size_t i = 0; i < 10; i++)
	////{
	////	data[c * a * 10 + c * i + 0] = 255;
	////	data[c * a * 10 + c * i + 1] = 0;
	////	data[c * a * 10 + c * i + 2] = 0;
	////	data[c * a * 10 + c * i + 3] = 255;
	////}

	//for (size_t i = 0; i < 10; i++)
	//{
	//	data[c * i + 0] = 255;
	//	data[c * i + 1] = 0;
	//	data[c * i + 2] = 0;
	//	data[c * i + 3] = 255;
	//}
	//stbi_write_png("write.png", a, b, c, data, a * 4);
	//stbi_image_free(data);
	/*const char *a = "string1";
	a = "bassss";
	std::cout << a;*/


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
