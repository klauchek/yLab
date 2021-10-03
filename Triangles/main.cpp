#include <iostream>
#include "triangles.hpp"

int main()
{

Vector v1(1.0, 2.0, 3.0);
Vector v2(1.0, 2.0, 3.0);
Vector v3(0.0, 0.0, 0.0);

Vector v4;
v4 = v1 + v2 + v3;

std::cout << v3;


return 0;
}
