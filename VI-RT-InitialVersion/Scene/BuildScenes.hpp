//
//  BuildScenes.hpp
//  VI-RT-InitialVersion
//
//  Created by Luis Paulo Santos on 11/02/2025.
//

#ifndef BuildScenes_hpp
#define BuildScenes_hpp

#include "scene.hpp"
#include "AmbientLight.hpp"
#include "Sphere.hpp"
#include "triangle.hpp"
#include "Phong.hpp"

 void SpheresScene (Scene& scene, int const N_spheres);
 void SpheresTriScene (Scene& scene);
 void CornellBox (Scene& scene);


#endif /* BuildScenes_hpp */
