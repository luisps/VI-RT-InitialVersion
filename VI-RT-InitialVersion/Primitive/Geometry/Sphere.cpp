//
//  Sphere.cpp
//  VI-RT
//
//  Created by Luis Paulo Santos on 08/02/2025.
//

#include <stdio.h>
#include "Sphere.hpp"

bool Sphere::intersect(Ray r, Intersection *isect) {
    
    if (!bb.intersect(r)) {
        return false;
    }
    
    // from https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/simplifyingtheray-sphereintersectioncode
    
    return false;
}
 
