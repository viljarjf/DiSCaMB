#pragma once
#include "discamb/MathUtilities/Vector3.h"
#include <cstddef>
#include <vector>

namespace discamb{
    /**
    * \addtogroup MathUtilities MathUtilities
    * @{
    */

namespace lebedev_laikov{

    /* vector with sizes of available Lebedev-Laikov grids
                        6,   14,   26,   38,   50,   74,   86,  110, 
                      146,  170,  194,  230,  266,  302,  350,  434,
                      590,  770,  974, 1202, 1454, 1730, 2030, 2354,
                     2702, 3074, 3470, 3890, 4334, 4802, 5294, 5810
    */
    void grid_sizes(std::vector<int> &n);
    /* grid points and weights */
    void get_grid(int n, std::vector<std::vector<double> > &r, std::vector<double> &w);
	void get_grid(int n, std::vector<Vector3d> &r, std::vector<double> &w);
    /* half of grid points and weights, another half can be generated by taking negative
       values of vector components and the same weights,
       i.e. if there is a point (x,y,z) with weight w (returned by this function),
       the grid contains also point (-x,-y,-z) with weight w (not returned by this function)*/
    void get_grid_pairs(int n, std::vector<std::vector<double> > &r, std::vector<double> &w);
	void get_grid_pairs(int n, std::vector<Vector3d> &r, std::vector<double> &w);

}
/** @}*/
}
