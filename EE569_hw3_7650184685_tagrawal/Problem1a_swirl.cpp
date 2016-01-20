/*
Problem1_swirl.cpp: Modifies the input image to give swirl effect
Author: Taruna Agrawal
Date: 1st November 2015
email:tagrawal@usc.edu
ID: 7650184685
*/


#include "Image.cpp"
#include <math.h> 

//Global variables
Image inImage, outImage;


/*Function to perform bilinear interpolation*/
unsigned char* bilinearInter(int u, int v, unsigned char* origdata)
{
   int width = 512;
   int height = 512;
   unsigned char* temp;
   temp = new unsigned char[3];
  
   double ynew = v;
   double xnew = u;
   if (ynew >=0 && ynew <width && xnew>=0 && xnew <height)
   {

   int yold = floor(ynew);
   int xold = floor(xnew);
#if 0
   if (ynew < 0)
       ynew = 0;
   else if (ynew > height-1)
      ynew = height - 1;
   if (xnew < 0)
       xnew = 0;
   else if (xnew > height-1)
       xnew = height - 1;

   if (yold < 0)
       yold = 0;
   else if (yold > height-1)
       yold = height - 1;
   if (xold < 0)
       xold = 0;
   else if (xold > height-1)
       xold = height - 1;
#endif
   int a = ynew - yold;
   int b = xnew - xold;
       //int pixel = (y*(width*3)) + (x*3);
   int data_co1 = yold*(width*3) + xold*3;
   int data_co2 = (yold+1)*(width*3) + xold*3;
   int data_co3 = (yold*(width*3)) + (xold+1)*3;
   int data_co4 = (yold+1)*(width*3) + (xold+1)*3;
   //Interpolation
          
    temp[0] = (1-a)*(1-b)*origdata[data_co1] + a*(1-b)*origdata[data_co2] + \
                   (1-a)*b*origdata[data_co3] + a*b*origdata[data_co4];
    temp[1] = (1-a)*(1-b)*origdata[data_co1 + 1] + a*(1-b)*origdata[data_co2 + 1] + \
                   (1-a)*b*origdata[data_co3 + 1] + a*b*origdata[data_co4 +1];
    temp[2] = (1-a)*(1-b)*origdata[data_co1 + 2] + a*(1-b)*origdata[data_co2 +2] + \
                   (1-a)*b*origdata[data_co3 + 2] + a*b*origdata[data_co4 + 2];
    }
    else
    {
          temp[0] = 0;
          temp[1] = 0;
          temp[2] = 0;

    }
    for (int i=0; i<3;i++)
    {
       if (temp[i] < 0)
          temp[i] = 0;
       else if (temp[i] > 255)
          temp[i] =0;
    } 
         
  /* data = new unsigned char[newwidth*newheight*3];
   for (int i =0; i < newheight*newwidth; i++)
   {
      data[3*i] =  temp[3*i];
      data[3*i+1] =  temp[3*i+1];
      data[3*i+2] =  temp[3*i+2];      
   }*/
  // delete temp;
   return temp;
} 


/*Perform swirl effect on input image*/
bool Image::swirlEffect()
{
   unsigned char **origImage = new unsigned char*[height*width];
   for (int i = 0; i < height*width; i++)
   {
       origImage[i] = new unsigned char[2];
   }
   unsigned char* outData;
   outData = new unsigned char[width*height*3];


   /*Change from image coordinate to cartesian cordinate with (0,0) in center of image
     After finding x, y find image coordinate after peforming rotation
     Perform bilinear interpolation to find original image coordinates*/
   double transMat[3][3] = {{1, 0, -255}, {0, -1, 255}, {0, 0, 1}};
   double invtransMat[3][3] = {{1, 0, 255}, {0, -1, 255}, {0, 0, 1}};
   double amtOfrotation = 0.0059;
   //double b =1;

   for (int i=0; i<height; i++)
   {
      for (int j=0; j<width; j++)
      {  
          int pixel = 3*i*width +3*j;
          unsigned char* swirlData;
          swirlData = new unsigned char[3];
          int x = transMat[0][0]*j + transMat[0][1]*i + transMat[0][2]*1;
          int y = transMat[1][0]*j + transMat[1][1]*i + transMat[1][2]*1;
     //     origImage[pixel][0] = x;
       //   origImage[pixel][1] = y;
#if 0
      }
   }
   
#endif
#if 1
          double angle = amtOfrotation*sqrt(x*x+y*y);
          //double angle = ((double)3.14/(double)256)*sqrt(x*x+y*y);
          //double angle =0.5;
          double u = cos(angle)*x + sin(angle)*y;
          double v = -sin(angle)*x + cos(angle)*y;
          u = invtransMat[0][0]*u + invtransMat[0][1]*v + invtransMat[0][2]*1;
          v = invtransMat[1][0]*u + invtransMat[1][1]*v + invtransMat[1][2]*1;
          swirlData = bilinearInter(u,v, data);
          outData[pixel] = swirlData[0];
          outData[pixel+1] = swirlData[1];
          outData[pixel+2] = swirlData[2];
          delete swirlData;
         // ignedout <<x<<","<<y << "  ";
      }
//      cout <<endl;
   }
   for (int i =0; i < height*width; i++)
   {
      data[3*i] =  outData[3*i];
      data[3*i+1] =  outData[3*i+1];
      data[3*i+2] =  outData[3*i+2];      
   }
   delete outData;
#endif
   return true;
}



int main(int argc, char* argv[])
{

   int BytesPerPixel = 1;
   int Width = 424;
   int Height = 636;
   int outWidth, outHeight;

   if (argc < 5)
   {
      cout << "Error - Incorrect Parameter Usage:" << endl;
      cout << "program_name input_image.raw output_image.raw BytesPerPixel width height" << endl;
      return 0;
   }	
   BytesPerPixel = atoi(argv[3]);
   inImage.setNumbytes(BytesPerPixel);

      // Check if size is specified
   if (argc >= 5){
	 Width = atoi(argv[4]);
	 Height = atoi(argv[5]);
         inImage.setWidth(Width);
         inImage.setHeight(Height);
    }

   //Read Image
   if (!inImage.readImage(argv[1]))
   {
      cout <<"Could not Read Image"<< endl;
   }
   else
   {
     cout << "Problem1a: Swirl Effect" <<endl;
     outImage = inImage;

     if (!outImage.swirlEffect())
     {
         cout << "Error:Could not perform goemetrical modification in Image"<<endl;
     }
   }
   //write final image to file
   if (!outImage.writeImage(argv[2]))
   {
      cout <<"Could not Write Image"<< endl;
   }

  return 0;
}
