#include <iostream>
#include "ray.h"//rayクラスの読み込み
#include <stdlib.h>

using namespace std;//

bool hit_sphere(const vec3&center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;//光源座標-球の中心座標(今回は(0,0,0)-(0,0,-1)=(0,0,-1))
	float a = dot(r.direction(), r.direction());//(光線の向かう座標(B),光線の向かう座標(B))
	float b = 2.0*dot(oc, r.direction()); //((0,0,-1),B(lower_left_corner + u*horizontal + v*vertical))
	float c = dot(oc, oc) - radius*radius;//((0,0,-1),(0,0,-1)-半径(0.5)*半径(0.5)
	float discriminant = b*b - 4 * a*c;
	return (discriminant > 0);
}

vec3 color(const ray&r)
{
	if (hit_sphere(vec3(0, 0, 1), 0.5, r))//球の中心座標、半径、光線の原点と方向を渡す
		return vec3(1, 0, 0);

	vec3 unit_direction = unit_vector(r.direction());// 単位方向=単位ベクトル
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.3, 0.7, 1.0);
}

int main()
{
	int nx = 400;
	int ny = 200;

	//この文がないとうまくppmに変換できない
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);// 左下端
	vec3 horizontal(4.0, 0.0, 0.0);//水平
	vec3 vertical(0.0, 2.0, 0.0);//垂直
	vec3 origin(0.0, 0.0, 0.0);//原点

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);//0.005刻み
			float v = float(j) / float(ny);//0.01刻み

			ray r(origin, lower_left_corner + u*horizontal + v*vertical);//原点と今表示するピクセルの座標をrayに渡す
			vec3 col = color(r);//vec3型変数colに、関数colorで出した値を入れる

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
