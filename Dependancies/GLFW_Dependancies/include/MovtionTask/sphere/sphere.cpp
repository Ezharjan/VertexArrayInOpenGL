//
//  sphere.cpp
//  openGL-sphere
//
//  Created by Lax Zhang on 2019/3/2.
//  Copyright © 2019 Lax Zhang. All rights reserved.
//

#include "sphere.hpp"

Sphere::Sphere(float radius, int sectorCount, int stackCount, bool smooth){
    set(radius, sectorCount, stackCount, smooth);
}

void Sphere::set(float radius, int sectorCount, int stackCount, bool smooth){
    this->radius = radius;
    this->sectorCount = sectorCount;
    this->stackCount = stackCount;
    this->smooth = smooth; // Not achive it.
    buildVertices();
    buildIndices();
}

std::vector<float> Sphere::getVertices(){
    return this->vertices;
}

std::vector<unsigned int> Sphere::getIndices(){
    return this->indices;
}


void Sphere::buildVertices(){
    float sectorStep = (2*PI)/sectorCount; // 横向每份的角度 算出弧度值
    float stackStep = PI/stackCount;    // 纵向每份的角度        算出弧度值
    float sectorAngle, stackAngle;    // 当前横向, 纵向角度
    float s, t;
    float nx, ny, nz, lenInv = radius / 1.0f; // vertex normal
    
    for (float i = 0; i <= stackCount; i++ )
    {
        stackAngle = PI/2 - i*stackStep;
        float z = radius * sin(stackAngle);
        float xy = radius * cos(stackAngle);
        for (float j = 0; j <= sectorCount; j++)
        {
            sectorAngle = sectorStep * j;
            float x = xy * cos(sectorAngle);
            float y = xy * sin(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            
            nx = x * lenInv;
            ny = y * lenInv;
            nz = z * lenInv;
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
            
            // texture coordinate range between [0,0]->[1,1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back(s);
            texCoords.push_back(t);
        }
    }
}


void Sphere::buildIndices(){
    int k1, k2;
    //    vector<float> vbo = drawglobeVBO();
    for (int i = 0; i < stackCount; i++)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;
        for (int j = 0;j < sectorCount; j++, k1++, k2++)
        {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1+1);
            }
            if (i != (stackCount - 1)) {
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2+1);
            }
        }
    }
}
