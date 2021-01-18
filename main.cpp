//
//  main.cpp
//  bresenhamlinealgorithm
//
//  Created by Hasan Eroglu on 11.08.2020.
//  Copyright © 2020 hasanheroglu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>

#define WIDTH 640
#define HEIGHT 480

struct Vec3f
{
    float x;
    float y;
    float z;
    
    Vec3f(): x(0.0f), y(0.0f), z(0.0f){}
    Vec3f(float x, float y, float z): x(x), y(y), z(z){}
    bool operator==(Vec3f v)
    {
        return x == v.x && y == v.y && z == v.z;
    }
    bool operator!=(Vec3f v)
    {
        return x != v.x || y != v.y || z != v.z;
    }
};

Vec3f *image = new Vec3f[WIDTH*HEIGHT];

int clamp(int n, int lo, int hi)
{
    if(n<=lo){ return lo; }
    if(n>=hi){ return hi; }
    
    return n;
}

void colorImage(unsigned int x, unsigned int y, Vec3f color)
{
    image[x+WIDTH*y] = color;
}

void bresenham(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;
    float deltaError = (float) abs(deltaY)/abs(deltaX);
    printf("error: %f\n", deltaError);
    
    float error = 0.0f;
    for(unsigned int x=x0, y=y0; x<=x1; x++)
    {
        printf("Point (%d, %d)\n", x, y);
        error += deltaError;
        colorImage(x, y, Vec3f(1.0f, 0.0f, 0.0f));
        if(error > 0.5f)
        {
            y += (int) abs(deltaY)/deltaY;
            error -= 1.0f;
        }
    }
}

void drawCircle(unsigned int x0, unsigned int y0, unsigned int r)
{
    for(unsigned int x=x0+r, y=y0; y<=y0+(r*sqrt(2)/2); y++)
    {
        colorImage(x, y, Vec3f(0.0f, 1.0f, 0.0f));
        colorImage(2*x0-x, y, Vec3f(0.0f, 1.0f, 0.0f));
        colorImage(2*x0-x, 2*y0-y, Vec3f(0.0f, 1.0f, 0.0f));
        colorImage(x, 2*y0-y, Vec3f(0.0f, 1.0f, 0.0f));

    
    if(abs(pow((x-x0)-1,2)+pow((y-y0)+1,2)-pow(r,2)) < abs(pow((x-x0),2)+pow((y-y0)+1,2)-pow(r,2)))
        {
            x--;
        }
    }
    
    for(unsigned int y=y0+r, x=x0; x<=x0+(r*sqrt(2)/2); x++)
    {
        colorImage(x, y, Vec3f(0.0f, 1.0f, 0.0f));
        colorImage(2*x0-x, y, Vec3f(0.0f, 1.0f, 0.0f));
        colorImage(2*x0-x, 2*y0-y, Vec3f(0.0f, 1.0f, 0.0f));
        colorImage(x, 2*y0-y, Vec3f(0.0f, 1.0f, 0.0f));

        if(abs(pow((x-x0)+1,2)+pow((y-y0)-1,2)-pow(r,2))<abs(pow((x-x0)+1,2)+pow((y-y0),2)-pow(r,2)))
        {
            y--;
        }
    }
}

void fill(unsigned int x, unsigned int y, Vec3f fillColor)
{
    Vec3f currentColor = image[x+WIDTH*y];
        
    colorImage(x, y, fillColor);
    
    if((x-1)+WIDTH*y >= 0 && image[(x-1)+WIDTH*y] == currentColor)
    {
        fill(x-1, y, fillColor);
    }
    
    if((x+1)+WIDTH*y < WIDTH*HEIGHT && image[(x+1)+WIDTH*y] == currentColor)
    {
        fill(x+1, y, fillColor);
    }
    
    if(x+WIDTH*(y-1) >= 0 && image[x+WIDTH*(y-1)] == currentColor)
    {
        fill(x, y-1, fillColor);
    }
    
    if(x+WIDTH*(y+1) < WIDTH*HEIGHT && image[x+WIDTH*(y+1)] == currentColor)
    {
        fill(x, y+1, fillColor);
    }
}

void generateImage(Vec3f *image)
{
    std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
    for (unsigned i = 0; i < WIDTH * HEIGHT; ++i) {
        ofs <<  (unsigned char)(std::min(float(1), image[i].x) * 255) <<
                (unsigned char)(std::min(float(1), image[i].y) * 255) <<
                (unsigned char)(std::min(float(1), image[i].z) * 255);
    }
    ofs.close();
}


int main(int argc, const char * argv[]) {
    // insert code here...
    bresenham(12, 400, 500, 23);
    drawCircle(150, 150, 5);
    drawCircle(300, 300, 50);
    drawCircle(399, 399, 80);
    drawCircle(320, 240, 100);
    fill(320, 240, Vec3f(1.0f, 0.0f, 1.0f));
    fill(300, 300, Vec3f(1.0f, 1.0f, 1.0f));
    fill(399, 399, Vec3f(0.0f, 0.0f, 1.0f));
    //fill(1, 1, Vec3f(0.0f, 0.0f, 1.0f));

    generateImage(image);
    return 0;
}

