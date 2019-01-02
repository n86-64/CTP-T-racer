/** @file Projections.h
*  @brief A range of projection methods
*
*  Defines a set of functions for performing projections.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "Math_Trig.h"
#include "Math_Vector.h"

namespace T_racer_Math 
{
	// Implements Shirly-Chiu projection method (http://psgraphics.blogspot.com/2011/01/improved-code-for-concentric-map.html)
	Vector projToUnitDisk(Vector seed)
	{
		double phi, r;

		double a = 2 * seed.X - 1; /* (a,b) is now on [-1,1]^2 */
		double b = 2 * seed.Y - 1;

		if (a > -b) 
		{ /* region 1 or 2 */
			if (a > b) 
			{ /* region 1, also |a| > |b| */
				r = a;
				phi = (M_PI / 4) * (b / a);
			}
			else
			{ /* region 2, also |b| > |a| */
				phi = (M_PI / 4) * (2 - (a / b));
			}
		}
		else { /* region 3 or 4 */
			if (a < b) {
				/* region 3, also |a| >= |b|, a != 0 */
				r = -a;
				phi = (M_PI / 4) * (4 + (b / a));
			}
			else 
			{ /* region 4, |b| >= |a|, but a==0 and b==0 could occur. */
				r = -b;
				if (b != 0)
				{
					phi = (M_PI / 4) * (6 - (a / b));
				}
				else
				{
					phi = 0;
				}
			}
		}

		return Vector(r * cos(phi), r * sin(phi));
			//*x = r * cos(phi);
			//*y = r * sin(phi);
	}
}
