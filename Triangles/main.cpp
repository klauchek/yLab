#include <iostream>
#include "vector.hpp"
#include "triangle.hpp"
#include "plane.hpp"


/*
Формат ввода: n - кол-во треугольников
n наборов из 3(?) чисел - координаты

Формат вывода: номера всех треугольников, которые пересекаются с каким-либо другим
*/


/*
проверять принадлежность треугольника плоскости? чтобы сразу отмести те, которые не могут пересекаться


*/



int main()
{

Vector v1(1.0, 2.0, 3.0);
Vector v2(1.0, 2.0, 3.0);
Vector v3(0.0, 0.0, 0.0);

Vector v4;
v4 = v1 * 2;
Vector v5 = v1/2;
Vector v6 = v1 + v2;
v6 -= v2;
//std::cout << v4 << ", " << v5 << "," << v6;

Triangle t1(v1, v2, v3);
Triangle t2(v4, v2, v3);
Triangle t3;
//std:: cout << "Triangle 1 " << t1 << " ," << "Triangle 2 " << t2 << " ," << std::endl;
//std:: cin >> t3;
//std:: cout << t3;

Vector r0(2, 1, 3);
Vector r1(-1, 2, 5);
Vector r2(3, 0, 1);

Plane p1(r0, r1, r2);
Vector norm = p1.getNorma();
float d = p1.getD();

std::cout << "Norm vec: " << norm << " ," << "D coef: " << d;


return 0;
}
