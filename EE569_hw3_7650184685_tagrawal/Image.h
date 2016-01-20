/*
***image_proc.h: Declares the class Image and its members
***Author: Taruna Agrawal
***Date: 31st August 2015
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <memory.h>

using namespace std;

//Image class

class Image
{

private:
        int width;  //image width
        int height; //image height
        int numbytes; //number of bytes per pixel
        unsigned char* data; //image data
        char ImagePath[1000];
public:
       //constructor()
       Image();
       //overloading constructor
       Image(Image *otherImage);
       //Destructor
       ~Image();

       //operator overloading
       Image& operator= (const Image& otherImage);

       //variable
       double feature[25];
       //functions
       void setWidth(int w) {width = w; };
       void setHeight(int h) {height = h; };
       void setNumbytes(int n) {numbytes = n; }; 
       void setImagePath(const char *path) { strcpy(ImagePath, path); }
       void setImageData( const char *img ) { data = (unsigned char *)img; };
       unsigned char* getImageData() { return data; };
       int getWidth() { return width; };
       int getHeight() { return height; };
       bool readImage();
       bool readImage(char* fileIn);
       bool writeImage(char* fileOut);
       bool swirlEffect();
       bool dithering_four(int intensity);
       bool dithering_eight(int intensity);
       bool diffusion_stein();
       bool diffusion_jarvis();
       bool diffusion_stucki();
       bool sch();
       bool vch();
       bool shrinking();
       bool preprocessing();
       bool thinning();
       bool  skeletonizing();
       bool transformation1(unsigned char* data1);
       bool transformation2(unsigned char* data1);
       bool transformation3(unsigned char* data1);
};
