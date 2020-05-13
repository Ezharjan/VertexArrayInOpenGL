//
//  sphere.hpp
//  openGL-sphere
//
//  Created by Lax Zhang on 2019/3/2.
//  Copyright © 2019 Lax Zhang. All rights reserved.
//

#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <math.h>
#include <vector>

#define PI 3.1415926

class Sphere{
public:
    
    Sphere(float radius=1.0f, int sectorCount=60, int stackCount=60, bool smooth=true);
    ~Sphere() {};
    
    void set(float radius, int sectorCount, int stackCount, bool smooth=true);
    void buildVertices();
    void buildIndices();
    
    std::vector<float> getVertices();
    std::vector<unsigned int> getIndices();
    
private:
    // memeber vars
    float radius;
    int sectorCount;                        // longitude, # of slices
    int stackCount;                         // latitude, # of stacks
    bool smooth;
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;
};

#endif /* sphere_hpp */
