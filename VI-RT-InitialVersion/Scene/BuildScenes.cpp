//
//  BuildScenes.cpp
//  VI-RT-InitialVersion
//
//  Created by Luis Paulo Santos on 11/02/2025.
//

#include "BuildScenes.hpp"

static int AddDiffuseMat (Scene& scene, RGB const color);
static int AddPhongMat (Scene& scene, RGB const Ka, RGB const Kd, RGB const Ks, RGB const Kt, float const Ns);
static void AddSphere (Scene& scene, Point const C, float const radius,
                            int const mat_ndx);
static void AddTriangle (Scene& scene,
                        Point const v1, Point const v2, Point const v3,
                        int const mat_ndx);


static int AddDiffuseMat (Scene& scene, RGB const color) {
    Phong *brdf = new Phong;
    
    brdf->Ka = color;
    brdf->Kd = color;
    brdf->Ks = RGB(0., 0., 0.);
    brdf->Kt = RGB(0., 0., 0.);
    
    return (scene.AddMaterial(brdf));
}

static int AddPhongMat (Scene& scene, RGB const Ka, RGB const Kd, RGB const Ks, RGB const Kt, float const Ns) {
    Phong *brdf = new Phong;
    
    brdf->Ka = Ka;
    brdf->Kd = Kd;
    brdf->Ks = Ks;
    brdf->Kt = Kt;
    brdf->Ns = Ns;
    
    return (scene.AddMaterial(brdf));
}

static void AddSphere (Scene& scene, Point const C,
                             float const radius, int const mat_ndx) {
    Sphere *sphere = new Sphere(C, radius);
    Primitive *prim = new Primitive;
    prim->g = sphere;
    prim->material_ndx = mat_ndx;
    scene.AddPrimitive(prim);
}

static void AddTriangle (Scene& scene,
                         Point const v1, Point const v2, Point const v3,
                         int const mat_ndx) {
    
    Triangle *tri = new Triangle(v1, v2, v3);
    Primitive *prim = new Primitive;
    prim->g = tri;
    prim->material_ndx = mat_ndx;
    scene.AddPrimitive(prim);
}

// Scene with  spheres
void SpheresScene (Scene& scene, int const N_spheres){
    int const red_mat = AddDiffuseMat(scene, RGB (0.9, 0.1, 0.1));
    AddSphere(scene, Point(0., 0., 3.), 0.8, red_mat);
    // add an ambient light to the scene
    AmbientLight *ambient = new AmbientLight(RGB(0.7,0.7,0.7));
    scene.lights.push_back(ambient);
    scene.numLights++;
    return ;
}

// Scene with  sphere and 4 triangles
void SpheresTriScene (Scene& scene) {
    int const red_mat = AddDiffuseMat(scene, RGB (0.9, 0.1, 0.1));
    int const green_mat = AddDiffuseMat(scene, RGB (0.1, 0.9, 0.1));
    AddSphere(scene, Point(0., 0., 3.), 0.8, red_mat);
    AddTriangle(scene, Point(0., 0., 7.), Point(-2., 1.5, 4.), Point(-0.5, 1.5, 5.),green_mat);
    AddTriangle(scene, Point(0., 0., 7.), Point(0.5, 1.5, 5.), Point(2., 1.5, 4.),green_mat);
    AddTriangle(scene, Point(0., 0., 7.), Point(-0.5, -1.5, 5.), Point(-2., -1.5, 4.),green_mat);
    AddTriangle(scene, Point(0., 0., 7.), Point(0.5, -1.5, 5.), Point(2., -1.5, 4.), green_mat);
    // add an ambient light to the scene
    AmbientLight *ambient = new AmbientLight(RGB(0.7,0.7,0.7));
    scene.lights.push_back(ambient);
    scene.numLights++;
    return ;
}

// Cornell Box
void CornellBox (Scene& scene) {
    int const white_mat = AddPhongMat(scene, RGB (0.9, 0.9, 0.9), RGB (0.4, 0.4, 0.4), RGB (0., 0., 0.), RGB (0., 0., 0.), 1);
    int const red_mat = AddPhongMat(scene, RGB (0.9, 0., 0.), RGB (0.4, 0., 0.), RGB (0., 0., 0.), RGB (0., 0., 0.), 1);
    int const green_mat = AddPhongMat(scene, RGB (0., 0.9, 0.), RGB (0., 0.2, 0.), RGB (0., 0., 0.), RGB (0., 0., 0.), 1);
    int const blue_mat = AddPhongMat(scene, RGB (0., 0., 0.9), RGB (0., 0., 0.4), RGB (0., 0., 0.), RGB (0., 0., 0.), 1);
    int const orange_mat = AddPhongMat(scene, RGB (0.99, 0.65, 0.), RGB (0.37, 0.24, 0.), RGB (0., 0., 0.), RGB (0., 0., 0.), 1);
    // Floor
    AddTriangle(scene, Point(552.8, 0.0, 0.0), Point(0.0, 0.0, 0.0), Point(0.0, 0.0, 559.2), white_mat);
    AddTriangle(scene, Point(549.6, 0.0, 559.2), Point(552.8, 0.0, 0.0), Point(0.0, 0.0, 559.2), white_mat);
    // Ceiling
    AddTriangle(scene, Point(556.0, 548.8, 0.0), Point(0.0, 548.8, 0.0), Point(0.0, 548.8, 559.2), white_mat);
    AddTriangle(scene, Point(556.0, 548.8, 559.2), Point(556.0, 548.8, 0.0), Point(0., 548.8, 559.2), white_mat);
    // Back wall
    AddTriangle(scene, Point(0.0, 0.0, 559.2), Point(549.6, 0.0, 559.2), Point(556.0, 548.8, 559.2), white_mat);
    AddTriangle(scene, Point(0.0, 0.0, 559.2), Point(0.0, 548.8, 559.2), Point(556.0, 548.8, 559.2), white_mat);
    // Left Wall
    AddTriangle(scene, Point(0.0, 0.0, 0.), Point(0., 0., 559.2), Point(0., 548.8, 559.2), green_mat);
    AddTriangle(scene, Point(0.0, 0.0, 0.), Point(0., 548.8, 0.), Point(0., 548.8, 559.2), green_mat);
    // Right Wall
    AddTriangle(scene, Point(552.8, 0.0, 0.), Point(549.6, 0., 559.2), Point(549.6, 548.8, 559.2), red_mat);
    AddTriangle(scene, Point(552.8, 0.0, 0.), Point(552.8, 548.8, 0.), Point(549.6, 548.8, 559.2), red_mat);
    // short block
    // top
    AddTriangle(scene, Point(130.0, 165.0,  65.0), Point( 82.0, 165.0, 225.0), Point(240.0, 165.0, 272.0), orange_mat);
    AddTriangle(scene, Point(130.0, 165.0,  65.0), Point( 290.0, 165.0, 114.0), Point(240.0, 165.0, 272.0), orange_mat);
    // bottom
    AddTriangle(scene, Point(130.0, 0.01,  65.0), Point( 82.0, 0.01, 225.0), Point(240.0, 0.01, 272.0), orange_mat);
    AddTriangle(scene, Point(130.0, 0.01,  65.0), Point( 290.0, 0.01, 114.0), Point(240.0, 0.01, 272.0), orange_mat);
    // left
    AddTriangle(scene, Point(290.0,   0.0, 114.0), Point(  290.0, 165.0, 114.0), Point(240.0, 165.0, 272.0), orange_mat);
    AddTriangle(scene, Point(290.0,   0.0, 114.0), Point( 240.0,  0.0, 272.0), Point(240.0, 165.0, 272.0), orange_mat);
    // back
    AddTriangle(scene, Point(240.0, 0.0, 272.0), Point(240.0, 165.0, 272.0), Point(82.0, 165., 272.0), orange_mat);
    AddTriangle(scene, Point(240.0, 0.0, 272.0), Point(82.0, 0.0, 225.0), Point(82.0, 165.0, 272.0), orange_mat);
    // right
    AddTriangle(scene, Point(82.0, 0.0, 225.0), Point(82.0, 165.0, 225.0), Point(130.0, 165.0, 65.0), orange_mat);
    AddTriangle(scene, Point(82.0, 0.0, 225.0), Point(130.0, 0.0, 65.0), Point(130.0, 165.0, 65.0), orange_mat);
    // front
    AddTriangle(scene, Point( 130.0,   0.0,  65.0), Point(130.0, 165.0, 65.0), Point(290.0, 165.0, 114.0), orange_mat);
    AddTriangle(scene, Point( 130.0,   0.0,  65.0), Point(290.0, 0.0, 114.0), Point(290.0, 165.0, 114.0), orange_mat);

    // tall block
    // top
    AddTriangle(scene, Point(423.0, 330.0, 247.0), Point(265.0, 330.0, 296.0), Point(314.0, 330.0, 456.0), blue_mat);
    AddTriangle(scene, Point(423.0, 330.0, 247.0), Point(472.0, 330.0, 406.0), Point(314.0, 330.0, 456.0), blue_mat);
    // bottom
    AddTriangle(scene, Point(423.0, 0.1, 247.0), Point(265.0, 0.1, 296.0), Point(314.0, 0.1, 456.0), blue_mat);
    AddTriangle(scene, Point(423.0, 0.1, 247.0), Point(472.0, 0.1, 406.0), Point(314.0, 0.1, 456.0), blue_mat);
    // left
    AddTriangle(scene, Point(423.0, 0.0, 247.0), Point(423.0, 330.0, 247.0), Point(472.0, 330.0, 406.0), blue_mat);
    AddTriangle(scene, Point(423.0, 0.0, 247.0), Point(472.0, 0.0, 406.0), Point(472.0, 330.0, 406.0), blue_mat);
    // back
    AddTriangle(scene, Point(472.0, 0.0, 406.0), Point(472.0, 330.0, 406.0), Point(314.0, 330.0, 456.0), blue_mat);
    AddTriangle(scene, Point(472.0, 0.0, 406.0), Point(314.0, 0.0, 406.0), Point(314.0, 330.0, 456.0), blue_mat);
    // right
    AddTriangle(scene, Point(314.0, 0.0, 456.0), Point(314.0, 330.0, 456.0), Point(265.0, 330.0, 296.0), blue_mat);
    AddTriangle(scene, Point(314.0, 0.0, 456.0), Point(265.0, 0.0, 296.0), Point(265.0, 330.0, 296.0), blue_mat);
    // front
    AddTriangle(scene, Point(265.0, 0.0, 296.0), Point(265.0, 330.0, 296.0), Point(423.0, 330.0, 247.0), blue_mat);
    AddTriangle(scene, Point(265.0, 0.0, 296.0), Point(423.0, 0.0, 247.0), Point(423.0, 330.0, 247.0), blue_mat);
    // add an ambient light to the scene
    AmbientLight *ambient = new AmbientLight(RGB(0.7,0.7,0.7));
    scene.lights.push_back(ambient);
    scene.numLights++;
    return ;
}
