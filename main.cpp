#include <iostream>
#include "ray.h"//作成したヘッダーファイルの読み込み

using namespace std;

vec3 color(const ray&r){
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 200;
	int ny = 100;

	//この文がないとうまくppmに変換できない
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lover_left_corner(-2.0, -1.0, -1.0);


	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			float red = float(i) / float(nx);
			float green = float(j) / float(ny);
			float blue = 0.2;
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
