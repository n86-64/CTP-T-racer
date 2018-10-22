#include <stdio.h>

#include "helpers/Math_Vector.h"
#include "helpers/Image.h"

// The application entry point.
int main(int argc, char* argv[]) 
{
	printf("Hello world, Today Im going to calculate a vector.");
	T_racer_Math::Vector3   vec1;
	T_racer_Math::Vector3   vec2(1.0f);
	T_racer_Math::Vector3   vec3(1.0f, 10.0f);
	T_racer_Math::Vector3   vec4(100.0f, 100.0f, 100.0f);
	T_racer_Math::Vector3   vec5;
	vec5 += vec2;
	vec3 = vec5 * 10.0f;
	vec2 = vec3 * 2;

	T_racer_Math::Vector3   vec6(2.0f, 2.0f, 2.0f);

	vec1 = vec4.normalise();

	// float test = vec4.normaliseSelfWithMagnitude();

	float dotval = dot(vec4, vec6);

	auto test = vec4 / vec6;
	vec4 /= vec6;

	Image  testImage(100, 100);


	getchar();


	return 0;
}