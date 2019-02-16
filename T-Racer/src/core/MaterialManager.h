/** @file MaterialManager.h
*  @brief A material collection system.
*
*  A storage class which stores refrences to all materials.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <vector>

#include  "core/Materials.h"

class T_racer_MaterialManager
{
public:
	T_racer_MaterialManager();

	T_racer_Material*   retrieveMaterial(int matID);
	T_racer_Material*   retrieveMaterial(std::string name);

private:
	std::vector<std::unique_ptr<T_racer_Material>>  materials;
	int matSize = 0;
};