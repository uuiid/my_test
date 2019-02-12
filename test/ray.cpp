// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <boost\algorithm\string.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>
//
//int main()
//{
//	std::string str;
//	std::vector<std::string> fields;
//	std::cout << "Input Conversion Folder\n";
//	std::cin >> str;
//	boost::split(fields, str, boost::is_any_of("\\"));
//
//	//boost::is_any_of
//	std::cout << fields[0];
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

//#define MY_RAY_SP_H
#include "my_ray_sp.h"

bool scene_intersect(
	const Vec3f &orig,
	const Vec3f &dir,
	const std::vector<sph::Sphere> &sphere,
	Vec3f &hit_point,
	Vec3f &N,
	sph::Material &material) //计算是否交叉光线
{
	float sphere_dir = std::numeric_limits<float>::max();
	for (size_t i = 0; i < sphere.size(); i++)
	{
		float dist_i;
		if (sphere[i].ray_intersect(orig,dir,dist_i) && dist_i<sphere_dir)
		{
			sphere_dir = dist_i;
			hit_point = orig + dir * dist_i;
			N = (hit_point - sphere[i].center).normalize(1.f);
			material = sphere[i].material;
		}		
	}
	return sphere_dir < 1000;
}

Vec3f cast_ray(const Vec3f &orig, 
	const Vec3f &dir, 
	const std::vector<sph::Sphere> &sphere,
	const std::vector<sph::light>  &light) {
	
	Vec3f point, N;
	sph::Material material;

	if (!scene_intersect(orig, dir,sphere, point, N, material))
	{
		return Vec3f(0.f, 0.f, 0.f);//背景颜色
	}

	float deffuse_light_intensity = 0, specular_light_intensity = 0;
	for (size_t i = 0; i < light.size(); i++)
	{
		Vec3f light_dir = (light[i].position - point).normalize(1.f);
		float light_distance = (light[i].position - point).norm();
		
		Vec3f shadow_orig = light_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3;//point - N * 1e-3;//
		Vec3f shadow_point, shadow_N;
		sph::Material temp_material;
		if (scene_intersect(shadow_orig, light_dir, sphere, shadow_point, shadow_N, temp_material) &&
			(shadow_point - shadow_orig).norm() < light_distance) {
			continue;
		}

		deffuse_light_intensity  += light[i].intensity * std::max(0.f, light_dir*N);
		specular_light_intensity += material.reflect(light_dir, dir, N) *light[i].intensity;
	}
	/*
	Vec3f specular_insiity = Vec3f(0.f, 0.f, 0.f);
	specular_insiity = (Vec3f(1.f, 1.f, 1.f)) * specular_light_intensity *material.albedo[1];*/
	return material.deffuse_color * deffuse_light_intensity*material.albedo[0] +
		(Vec3f(1.f, 1.f, 1.f)) * specular_light_intensity * material.albedo[1];
}

/*
struct Material
{


	//Material(const Vec3f &color) : diffuse_color() {}
	Material(const Vec3f &color) : deffuse_color(color) {}
	Vec3f deffuse_color;

}; */

void render(const std::vector<sph::Sphere> &sphere, const std::vector<sph::light> &light) {
	const int width = 1024;
	const int height = 768;
	int n = 4;
	const float fov = 45;

	//Vec3f cast_ray();

	std::vector<Vec3f> framebuffer(width*height);

	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			framebuffer[i + j * width] = Vec3f(j / float(height), i / float(width), 0);
		}
	}

	#pragma omp parallel for
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			float x = -width/2  + (j + 0.5);
			float y = height/2 - (i + 0.5);
			float z = -sqrtf((width / 2) * (width / 2) + (height / 2)*(height / 2)) / tanf(fov / 2);
			Vec3f dir = Vec3f(x, y, z).normalize(1.f);
			framebuffer[i * width + j] = cast_ray(Vec3f(0, 0, 0), dir, sphere,light);
		}
	}


	/*
	struct Sphere
	{
		Vec3f center;
		float radius;

		Sphere(const Vec3f &c, const float &r) :center(c), radius(r) {};

		bool ray_intersect(const Vec3f &orig, const Vec3f &dir)const {
			Vec3f L = orig - center;
			float tca = L * dir.normalize;
			float L_len = L.norm;
			float d2 = L_len * L_len + tca * tca;
			if (d2>(radius*radius))
			{
				return false;
			}
			float thc = sqrtf(radius*radius - d2);
			float t0 = thc - tca;
			float t1 = thc + tca;
			if (t0 < 0) t0 = t1;
			if (t0 < 0)return false;
			return true;
		}
	};	
	*/

	/*错误的方式
	unsigned char data[width*height*4];
	
	for (size_t i = 0; i < height*width; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			data[n*i+(j+1)] = (unsigned char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
		}
		data[i*n-1] = (unsigned char)255;
	}

	unsigned char *data_ip = data;

	stbi_write_png("./my_write1.png", width, height, n, data_ip, 0);

	stbi_image_free(data_ip);
	delete data_ip;
	 */
	
 	std::vector<unsigned char> pimap(width*height * 4);
	for (size_t i = 0; i < height*width; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			pimap[n*i + j] = (unsigned char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
		}
		pimap[i*n + 3] = (unsigned char)255;
	}

	stbi_write_png("./my_write_2.png", width, height, n, pimap.data(), 0);
	/*
	std::ofstream ofs; // save the framebuffer to file
	ofs.open("./out.png");
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (size_t i = 0; i < height*width; ++i) {
		for (size_t j = 0; j < 3; j++) {
			ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
		}
	}
	ofs.close();*/
}

int main() {
	
	
	sph::Material    blue(Vec2f(0.6, 0.3), Vec3f(0.3, 0.5,  0.8), 200);
	sph::Material  yellow(Vec2f(0.85, 0.05), Vec3f(0.7, 0.65, 0.3), 100);
	
	std::vector<sph::Sphere> spheres;
	spheres.push_back(sph::Sphere(Vec3f(-3,      0, -16), 2, blue  ));
	spheres.push_back(sph::Sphere(Vec3f(-1.0, -1.5, -12), 2, blue  ));
	spheres.push_back(sph::Sphere(Vec3f( 1.5, -0.5, -18), 3, yellow));
	spheres.push_back(sph::Sphere(Vec3f( 7  ,  5  , -18), 4, yellow));
	//sph::Sphere sphere1(Vec3f(0, 0, -16), 2);
	
	std::vector<sph::light> lights;
	lights.push_back(sph::light(Vec3f(-20, 20, 20), 1.5));
	lights.push_back(sph::light(Vec3f(30, 50, -15), 1.8));
	lights.push_back(sph::light(Vec3f(30, 20, 30), 1.1));
	render(spheres,lights);
	return 0;
}