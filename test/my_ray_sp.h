#pragma once
#ifndef MY_RAY_SP_H
//#define MY_RAY_SP_H
#include "geometry.h"

#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>


namespace sph {

	struct light {
		light(const Vec3f &p, const float &i) :position(p), intensity(i){}
		Vec3f position;
		float intensity;
	};

	struct Material
	{

		Material(const Vec2f &albedo, const Vec3f &color, const float specular) 
			: albedo(albedo), deffuse_color(color),specular_exponent(specular) {}
		Material() : albedo(1,0), deffuse_color(),specular_exponent() {}
		Vec2f albedo;
		Vec3f deffuse_color;
		float specular_exponent;
		
		float reflect(const Vec3f &light_direction,const Vec3f &dir ,const Vec3f &N) {
			Vec3f half_light_view = (light_direction - dir).normalize(1.f);
			return powf(std::max(half_light_view*N,0.f), specular_exponent);
		}
	};


	struct Sphere
	{
		Vec3f center;
		float radius;
		Material material;

		Sphere(const Vec3f &c, const float &r, const Material &m) 
			:center(c), radius(r), material(m) {};

		bool ray_intersect(const Vec3f &orig, 
			const Vec3f &dir, 
			float &t0/*传入后返回击中点距离*/
			)const {
			Vec3f L = center - orig;
			float tca = L * dir;
			float d2 = L * L - tca * tca;
			if (d2 > radius*radius) return false;
			
			float thc = sqrtf(radius*radius - d2);
			t0 = tca - thc;
			float t1 = tca + thc;
			if (t0 < 0) t0 = t1;
			if (t0 < 0) return false;
			
			return true;
		}
	};
}



#endif // !MY_RAY_SP_H
