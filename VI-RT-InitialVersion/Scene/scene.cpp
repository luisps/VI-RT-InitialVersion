//
//  Scene.cpp
//  VI-RT
//
//  Created by Luis Paulo Santos on 30/01/2023.
//

#include "scene.hpp"

#include "primitive.hpp"
#include "Phong.hpp"

#include <iostream>
#include <set>
#include <vector>


bool Scene::trace (Ray r, Intersection *isect) {
    Intersection curr_isect;
    bool intersection = false;    
    
    /*if (r.pix_x==320 && r.pix_y==240) {
        fprintf (stderr, "This is a pixel. There are %d primitives!\n", numPrimitives);
        fflush(stderr);
    }*/
        
    
    if (numPrimitives==0) return false;
    
    // iterate over all primitives
    for (auto prim_itr = prims.begin() ; prim_itr != prims.end() ; prim_itr++) {
       /* if (r.pix_x==320 && r.pix_y==240) {
            fprintf (stderr, "Testing intersection\n");
            fflush(stderr);
        }*/
        if ((*prim_itr)->g->intersect(r, &curr_isect)) {
            if (!intersection) { // first intersection
                intersection = true;
                *isect = curr_isect;
                isect->f = BRDFs[(*prim_itr)->material_ndx];
            }
            else if (curr_isect.depth < isect->depth) {
                *isect = curr_isect;
                isect->f = BRDFs[(*prim_itr)->material_ndx];
            }
        }
    }
    isect->isLight = false;

    /*if (r.pix_x==320 && r.pix_y==240) {
        fprintf (stderr, "It intersects %s \n", (intersection ? "a thing" : " notihng"));
        fflush(stderr);
    }*/
    return intersection;
}

// checks whether a point on a light source (distance maxL) is visible
bool Scene::visibility (Ray s, const float maxL) {
    bool visible = true;
    Intersection curr_isect;
    
    if (numPrimitives==0) return true;
    
    // iterate over all primitives while visible
    for (auto prim_itr = prims.begin() ; prim_itr != prims.end() && visible ; prim_itr++) {
        if ((*prim_itr)->g->intersect(s, &curr_isect)) {
            if (curr_isect.depth < maxL) {
                visible = false;
            }
        }
    }
    return visible;
}
