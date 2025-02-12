//
//  StandardRenderer.cpp
//  VI-RT-LPS
//
//  Created by Luis Paulo Santos on 14/03/2023.
//

#include "StandardRenderer.hpp"

void StandardRenderer::Render () {
    int W=0,H=0;  // resolution
    int x,y;

    // get resolution from the camera
    //...

    // main rendering loop: get primary rays from the camera until done
    for (y=0 ; y< H ; y++) {  // loop over rows
        printf ("%d\r",y);
        for (x=0 ; x< W ; x++) { // loop over columns
            Ray primary;
            Intersection isect;
            bool intersected;
            RGB color(0.,0.,0.);

            // Generate Ray (camera)
            //...
 
            // trace ray (scene)
            //...

            // shade this intersection (shader) - remember: depth=0
            //...
            
            // write the result into the image frame buffer (image)
            //...
            
        } // loop over columns
    }   // loop over rows
}
