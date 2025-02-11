//
//  perspective.cpp
//  VI-RT
//
//  Created by Luis Paulo Santos on 10/02/2023.
//

#include "perspective.hpp"

bool Perspective::GenerateRay(const int x, const int y, Ray *r, const float *cam_jitter) {
    float xc, yc;
    
    // to screen space
    if (cam_jitter==NULL) {
        xc = 2.f * ((float)x + .5f)/W - 1.f;
        yc = 2.f * ((float)(H-y-1) + .5f)/H - 1.f;
    } else {
        // assume that cam_jitter contains 2 floats in (0.0 .. 1.0(
        xc = 2.f * ((float)x + cam_jitter[0])/W - 1.f;
        yc = 2.f * ((float)(H-y-1) + cam_jitter[1])/H - 1.f;
    }
    
    // to camera space
    xc *= tan_halfW;
    yc *= tan_halfH;
    
    // compute ray direction using c2w
    r->dir.X = c2w[0][0] * xc + c2w[0][1] * yc + c2w[0][2];
    r->dir.Y = c2w[1][0] * xc + c2w[1][1] * yc + c2w[1][2];
    r->dir.Z = c2w[2][0] * xc + c2w[2][1] * yc + c2w[2][2];
    r->dir.normalize();
    r->invertDir();
    
    r->o = Eye;
    
    r->pix_x = x;
    r->pix_y = y;
    
    r->FaceID = -1;
    
    return true;
}
