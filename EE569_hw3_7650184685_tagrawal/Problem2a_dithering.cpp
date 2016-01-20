/*
Problem2a_dithering.cpp.cpp: Converts mandrill image to half toned image suing dithering matrix
Author: Taruna Agrawal
Date: 1st November 2015
email:tagrawal@usc.edu
ID: 7650184685
*/


#include "Image.cpp"
#include <math.h> 

//Global variables
Image inImage, outImage;


bool Image::dithering_eight(int intensity)
{
   /*Normalize image*/   
   double *norm_data;
   norm_data = new double[width*height];
   double *out_data;
   out_data = new double[width*height];
   for (int i=0; i<width*height; i++)
   {
       norm_data[i] = (double)data[i]/(double)255;
   }

   int index = 8;
     double I[8][8] = {{21,37,25, 41, 22, 38, 26,42},
          {33, 5, 57, 9, 34, 6, 58, 10},
          {29, 45, 17, 33, 30, 46, 18, 34},
          {61, 13, 49, 1, 62, 14, 50, 2},
          {23, 39, 27, 43, 20, 36, 24, 40 },
          {35, 7, 59, 11, 32, 4, 56, 8},
          {31, 47, 19, 35, 28, 44, 16, 32},
          {63, 15, 51, 3, 60, 12, 48, 0}};
#if 1
   for (int x = 0; x <height ; x+=index)
   {
      for (int y=0; y<width; y+=index)
      {
         //int pixel = 3*x*width +3*y;
         for (int xblock=x; xblock<(x+index); xblock++)
         {
            for (int yblock=y; yblock<(y+index); yblock++)
            {
               int pixel = (xblock*width) + yblock;
               double threshold = ((double)I[xblock % index][yblock % index] + 0.5)/(double)(index*index);
               
               if (intensity == 2)
               {
                  if (norm_data[pixel] > threshold)
                    out_data[pixel] = 1;
                  else
                    out_data[pixel] = 0;
               }
               else if (intensity == 4)
               {
                  if (norm_data[pixel] >= 1.5*threshold)
                    out_data[pixel] = 1;
                  else if ((norm_data[pixel] >= threshold))
                    out_data[pixel] = (double)170.0/(double)255.0;
                  else if ((norm_data[pixel] > 0.75*threshold))
                    out_data[pixel] = (double)85.0/(double)255.0;
                  else 
                    out_data[pixel] = 0;
                     
               }
               else
                 cout << "Enter valid intensity value"<<endl;

            }
         }
       }
    }   
  
   for (int i =0; i < height*width; i++)
   {
      data[i] = out_data[i]*255;
   }
   delete out_data;
   delete norm_data;
   //delete I;
#endif
   return true;
}


bool Image::dithering_four(int intensity)
{
   /*Normalize image*/   
   double *norm_data;
   norm_data = new double[width*height];
   double *out_data;
   out_data = new double[width*height];
   for (int i=0; i<width*height; i++)
   {
       norm_data[i] = (double)data[i]/(double)255;
   }
  int index =4;
  double I[4][4] = {{5, 9, 4, 6},
          {13, 1, 14,2},
          {7, 11, 4, 8},
          {15, 3, 12, 0}};
#if 1
   for (int x = 0; x <height; x+=index)
   {
      for (int y=0; y<width; y+=index)
      {
         //int pixel = 3*x*width +3*y;
         for (int xblock=x; xblock<(x+index); xblock++)
         {
            for (int yblock=y; yblock<(y+index); yblock++)
            {
               int pixel = (xblock*width) + yblock;
               double threshold = (double)(I[xblock % index][yblock % index] + 0.5)/(double)(index*index);
               if (intensity == 2)
               {
                  if (norm_data[pixel] > threshold)
                    out_data[pixel] = 1;
                  else
                    out_data[pixel] = 0;
               }
               else if (intensity == 4)
               {
                  if (norm_data[pixel] >= 1.5*threshold)
                    out_data[pixel] = 1;
                  else if ((norm_data[pixel] >= threshold))
                    out_data[pixel] = (double)170.0/(double)255.0;
                  else if ((norm_data[pixel] > 0.75*threshold))
                    out_data[pixel] = (double)85.0/(double)255.0;
                  else 
                    out_data[pixel] = 0;
               }
               else
                 cout << "Enter valid intensity value"<<endl;
            }
         }
      }
    }   
  
   for (int i =0; i < height*width; i++)
   {
      data[i] = out_data[i]*255;
   }
   delete out_data;
   delete norm_data;
   //delete I;
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
   cout <<"Enter Bayer index value either 4 or 8 "<<endl;
   int index;
   cin >>index;
   cout <<"Enter intensity value 2 or 4 "<<endl;
   int intensity;
   cin >>intensity;
   //Read Image
   if (!inImage.readImage(argv[1]))
   {
      cout <<"Could not Read Image"<< endl;
   }
   else
   {
     cout << "Problem2a: Dithering " <<endl;
     outImage = inImage;
     if (index == 4)
     {
        if (!outImage.dithering_four(intensity))
        {
           cout << "Error:Could not perform dithering image"<<endl;
        }
     }
     else if (index == 8)
     {
        if (!outImage.dithering_eight(intensity))
        {
           cout << "Error:Could not perform dithering image"<<endl;
        }
     }
     else{
       cout <<"Enter valid value"<<endl;
     }
   }
   //write final image to file
   if (!outImage.writeImage(argv[2]))
   {
      cout <<"Could not Write Image"<< endl;
   }

  return 0;
}


