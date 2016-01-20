/*
Problem2c_SCH.cpp: Convert color image to half toned image using scalar halftoning method.
Author: Taruna Agrawal
Date: 1st November 2015
email:tagrawal@usc.edu
ID: 7650184685
*/


#include "Image.cpp"
#include <math.h> 

//Global variables
Image inImage, outImage;

/*Function to perform scalar half toning on Image*/
bool Image::sch()
{

   /*Normalize data and invert values as per printing norms*/
   double *norm_data;
   norm_data = new double[width*height*3];
   double *out_data;
   out_data = new double[width*height*3];
   for (int i=0; i<height*width; i++)
   {
       int pixel = 3*i;
       norm_data[pixel] = (double)data[pixel]/(double)255;
     //  norm_data[pixel] = 1 - norm_data[pixel];
       norm_data[pixel+1] = (double)data[pixel+1]/(double)255;
       //norm_data[pixel+1] = 1 - norm_data[pixel+1];
       norm_data[pixel+2] = (double)data[pixel+2]/(double)255;
       //norm_data[pixel+2] = 1 - norm_data[pixel+2];
   }
#if 1 
   for (int x = 0; x <height; x++)
   {
      
      /*Serpentine: Even rows left-->right error diffusion*/
      if (x % 2 == 0)
      {
         for (int y=0; y < width; y++)
         {
            int pixel = 3*x*width +3*y;
            int pixel1 = 3*(x+1)*width +3*(y+1);
            int pixel2 = 3*(x+1)*width +3*y;
            int pixel3 = 3*(x+1)*width +3*(y-1);
            /*Quamtize cyan*/
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;
            /*Quamtize Magenta*/
            if (norm_data[pixel+1] >= 0.5)
               out_data[pixel+1] = 1;
            else
               out_data[pixel+1] = 0;
            /*Quamtize blue*/
            if (norm_data[pixel+2] >= 0.5)
               out_data[pixel+2] = 1;
            else
               out_data[pixel+2] = 0;
           
           double quant_errC = norm_data[pixel] - out_data[pixel];
           double quant_errM = norm_data[pixel+1] - out_data[pixel+1];
           double quant_errY = norm_data[pixel+2] - out_data[pixel+2];
           if (y+1 < width)
           {
              norm_data[pixel +3] += quant_errC*(7.0/16.0);
              norm_data[pixel +4] += quant_errM*(7.0/16.0);
              norm_data[pixel +5] += quant_errY*(7.0/16.0);
           }
           if(x+1 < height && y+1 <width)
           {
              norm_data[pixel1] += quant_errC*(1.0/16.0);            
              norm_data[pixel1+1] += quant_errM*(1.0/16.0);            
              norm_data[pixel1+2] += quant_errY*(1.0/16.0);            
           }
           if(x+1 < height)
           {
              norm_data[pixel2] += quant_errC*(5.0/16.0);            
              norm_data[pixel2+1] += quant_errM*(5.0/16.0);            
              norm_data[pixel2+2] += quant_errY*(5.0/16.0);            
           }
           if(x+1 < height && y-1 >=0)
           {
              norm_data[pixel3] += quant_errC*(3.0/16.0);            
              norm_data[pixel3+1] += quant_errM*(3.0/16.0);            
              norm_data[pixel3+2] += quant_errY*(3.0/16.0);            
           }
        }
      }
      /*Serpentine: Odd rows right-->left error diffusion*/
      else
      {
         for (int y= width-1; y >=0; y--)
         {

            int pixel = 3*x*width +3*y;
            int pixel1 = 3*(x+1)*width +3*(y-1);
            int pixel2 = 3*(x+1)*width +3*y;
            int pixel3 = 3*(x+1)*width +3*(y+1);
            /*Quamtize cyan*/
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;
            /*Quamtize Magenta*/
            if (norm_data[pixel+1] >= 0.5)
               out_data[pixel+1] = 1;
            else
               out_data[pixel+1] = 0;
            /*Quamtize blue*/
            if (norm_data[pixel+2] >= 0.5)
               out_data[pixel+2] = 1;
            else
               out_data[pixel+2] = 0;
            
            double quant_errC = norm_data[pixel] - out_data[pixel];
            double quant_errM = norm_data[pixel+1] - out_data[pixel+1];
            double quant_errY = norm_data[pixel+2] - out_data[pixel+2];
           
           if (y-1 >= 0)
           {
               norm_data[pixel -3] += quant_errC*(7.0/16.0);
               norm_data[pixel -4] += quant_errM*(7.0/16.0);
               norm_data[pixel -5] += quant_errY*(7.0/16.0);
           }
           if(x+1 < height && y-1 >=0)
           {
              norm_data[pixel1] += quant_errC*(1.0/16.0);            
              norm_data[pixel1+1] += quant_errM*(1.0/16.0);            
              norm_data[pixel1+2] += quant_errY*(1.0/16.0);            
           }
           if(x+1 < height)
           {
              norm_data[pixel2] += quant_errC*(5.0/16.0);            
              norm_data[pixel2+1] += quant_errM*(5.0/16.0);            
              norm_data[pixel2+2] += quant_errY*(5.0/16.0);            
           }
           if(x+1 < height && y+1 <=width)
           {
              norm_data[pixel3] += quant_errC*(3.0/16.0);            
              norm_data[pixel3+1] += quant_errM*(3.0/16.0);            
              norm_data[pixel3+2] += quant_errY*(3.0/16.0);            
           }
         }
      }
   }
#endif
   for (int i =0; i < height*width*3; i++)
   {
      data[i] = (out_data[i])*255;
     // data[i] = norm_data[i]*255;
   }
   delete out_data;
   delete norm_data;

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
     cout << "Problem2c: Scalar Error Diffusion " <<endl;
     outImage = inImage;
     if (!outImage.sch())
     {
        cout << "Error:Could not perform scalar half toning"<<endl;
     }
   }
   //write final image to file
   if (!outImage.writeImage(argv[2]))
   {
      cout <<"Could not Write Image"<< endl;
   }

  return 0;
}
