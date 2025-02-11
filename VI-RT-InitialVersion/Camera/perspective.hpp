//
//  perspective.hpp
//  VI-RT
//
//  Created by Luis Paulo Santos on 10/02/2023.
//

#ifndef perspective_hpp
#define perspective_hpp

#include "camera.hpp"
#include "ray.hpp"
#include "vector.hpp"

class Perspective: public Camera {
    Vector Up;
    float fovW, fovH, tan_halfW, tan_halfH;
    int W, H;
    float c2w[3][3];  // camera 2 world transform
public:
    Point Eye, At;
    Perspective (const Point Eye, const Point At, const Vector _Up, const int W, const int H, const float fovW, const float fovH): Eye(Eye), At(At), W(W), H(H), fovW(fovW), fovH(fovH)  {
        // compute camera 2 world transform
        Vector forward (At.X-Eye.X, At.Y-Eye.Y, At.Z-Eye.Z);
        forward.normalize();
        Vector right = forward.cross(_Up);
        right.normalize();
        // now we compute UP exactly as the cross product  right X forward
        Up = right.cross(forward);
        Up.normalize();
        c2w[0][0] = right.X;
        c2w[0][1] = right.Y;
        c2w[0][2] = right.Z;
        c2w[1][0] = Up.X;
        c2w[1][1] = Up.Y;
        c2w[1][2] = Up.Z;
        c2w[2][0] = forward.X;
        c2w[2][1] = forward.Y;
        c2w[2][2] = forward.Z;
        // precompute the tangents
        tan_halfW = tanf(fovW/2.f);
        tan_halfH = tanf(fovH/2.f);

    }
    bool GenerateRay(const int x, const int y, Ray *r, const float *cam_jitter=NULL);
    void getResolution (int *_W, int *_H) {*_W=W; *_H=H;}
};

#endif /* perspective_hpp */
