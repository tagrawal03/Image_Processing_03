/*
Problem2b_errDiffusion.cpp: Convert image to half toned image using error diffusion method.
Author: Taruna Agrawal
Date: 1st November 2015
email:tagrawal@usc.edu
ID: 7650184685
*/


#include "Image.cpp"
#include <math.h> 

//Global variables
Image inImage, outImage;

/*Error diffusion by Flyod Steinberg method*/
bool Image::diffusion_stein()
{
   
   /*Normalize data and invert values as per printing norms*/
   double *norm_data;
   norm_data = new double[width*height];
   double *out_data;
   out_data = new double[width*height];
   for (int i=0; i<width*height; i++)
   {
       norm_data[i] = (double)data[i]/(double)255;
       norm_data[i] = 1 - norm_data[i];
   }


   for (int x = 0; x <height; x++)
   {
      
      /*Serpentine: Even rows left-->right error diffusion*/
      if (x % 2 == 0)
      {
         for (int y=0; y < width; y++)
         {
            int pixel = x*width +y;
            int pixel1 = (x+1)*width +(y+1);
            int pixel2 = (x+1)*width +y;
            int pixel3 = (x+1)*width +(y-1);
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;
           
           double quant_err = norm_data[pixel] - out_data[pixel];
           if (y+1 < width)
           {
              norm_data[pixel +1] += quant_err*((double)7.0/(double)16.0);
           }
           if(x+1 < height && y+1 <width)
           {
              norm_data[pixel1] += quant_err*((double)1.0/(double)16.0);            
           }
           if(x+1 < height)
           {
              norm_data[pixel2] += quant_err*((double)5.0/(double)16.0);            
           }
           if(x+1 < height && y-1 >=0)
           {
              norm_data[pixel3] += quant_err*((double)3.0/(double)16.0);            
           }
        }
      }
      /*Serpentine: Odd rows right-->left error diffusion*/
      else
      {
         for (int y= width-1; y >=0; y--)
         {
            int pixel = x*width +y;
            int pixel1 = (x+1)*width +(y-1);
            int pixel2 = (x+1)*width +y;
            int pixel3 = (x+1)*width +(y+1);
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;
            double quant_err = norm_data[pixel] - out_data[pixel];
            if (y-1 >= 0)
            {
               norm_data[pixel -1] += quant_err*((double)7.0/(double)16.0);
            }
           if(x+1 < height && y-1 >=0)
           {
              norm_data[pixel1] += quant_err*((double)1.0/(double)16.0);            
           }
           if(x+1 < height)
           {
              norm_data[pixel2] += quant_err*((double)5.0/(double)16.0);            
           }
           if(x+1 < height && y+1 <=width)
           {
              norm_data[pixel3] += quant_err*((double)3.0/(double)16.0);            
           }
         }
      }
   }
   for (int i =0; i < height*width; i++)
   {
      data[i] = (1-out_data[i])*255;
   }
   delete out_data;
   delete norm_data;
   return true;
}

/*Error diffusion using jarvis method*/
bool Image::diffusion_jarvis()
{
   /*Normalize data and invert values as per printing norms*/
   double *norm_data;
   norm_data = new double[width*height];
   double *out_data;
   out_data = new double[width*height];
   for (int i=0; i<width*height; i++)
   {
       norm_data[i] = (double)data[i]/(double)255;
       norm_data[i] = 1 - norm_data[i];
   }


   for (int x = 0; x <height; x++)
   {
      
      /*Serpentine: Even rows left-->right error diffusion*/
      if (x % 2 == 0)
      {
         for (int y=0; y < width; y++)
         {
            int pixel = x*width +y;
            int pixel1 = (x+1)*width +y;
            int pixel2 = (x+2)*width +y;
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;

           double quant_err = norm_data[pixel] - out_data[pixel];

           if (y+2 < width)
           {
              norm_data[pixel +1] += quant_err*(7.0/48.0);
              norm_data[pixel +2] += quant_err*(5.0/48.0);
           }
           else if(x+2 < height && y+2 <width)
           {
              norm_data[pixel1+1] += quant_err*(5.0/48.0);            
              norm_data[pixel1+2] += quant_err*(3.0/48.0);            
              norm_data[pixel2+1] += quant_err*(3.0/48.0);            
              norm_data[pixel2+2] += quant_err*(1.0/48.0);            
           }
           else if(x+2 < height)
           {
              norm_data[pixel1] += quant_err*(7.0/48.0);            
              norm_data[pixel2] += quant_err*(5.0/48.0);            
           }
           else if(x+2 < height && y-2 >=0)
           {
              norm_data[pixel1-1] += quant_err*(5.0/48.0);            
              norm_data[pixel1-2] += quant_err*(3.0/48.0);            
              norm_data[pixel2-1] += quant_err*(3.0/48.0);            
              norm_data[pixel2-2] += quant_err*(1.0/48.0);            
           }
        }
      }
      /*Serpentine: Odd rows right-->left error diffusion*/
      else
      {
         for (int y= width-1; y >=0; y--)
         {
            int pixel = x*width +y;
            int pixel1 = (x+1)*width +y;
            int pixel2 = (x+2)*width +y;
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;
            double quant_err = norm_data[pixel] - out_data[pixel];
            if (y-2 >= 0)
            {
              norm_data[pixel -1] += quant_err*(7.0/48.0);
              norm_data[pixel -2] += quant_err*(5.0/48.0);
            }
           else if(x+2 < height && y+2 <width)
           {
              norm_data[pixel1+1] += quant_err*(5.0/48.0);            
              norm_data[pixel1+2] += quant_err*(3.0/48.0);            
              norm_data[pixel2+1] += quant_err*(3.0/48.0);            
              norm_data[pixel2+2] += quant_err*(1.0/48.0);            
           }
           else if(x+2 < height)
           {
              norm_data[pixel1] += quant_err*(7.0/48.0);            
              norm_data[pixel2] += quant_err*(5.0/48.0);            
           }
           else if(x+2 < height && y-2 >=0)
           {
              norm_data[pixel1-1] += quant_err*(5.0/48.0);            
              norm_data[pixel1-2] += quant_err*(3.0/48.0);            
              norm_data[pixel2-1] += quant_err*(3.0/48.0);            
              norm_data[pixel2-2] += quant_err*(1.0/48.0);            
           }
         }
      }
   }
   for (int i =0; i < height*width; i++)
   {
      data[i] = (1-out_data[i])*255;
   }
   delete out_data;
   delete norm_data;

  return true;
}

/*Error diffusion by stucki method*/
bool Image::diffusion_stucki()
{

   /*Normalize data and invert values as per printing norms*/
   double *norm_data;
   norm_data = new double[width*height];
   double *out_data;
   out_data = new double[width*height];
   for (int i=0; i<width*height; i++)
   {
       norm_data[i] = (double)data[i]/(double)255;
       norm_data[i] = 1 - norm_data[i];
   }


   for (int x = 0; x <height; x++)
   {
      
      /*Serpentine: Even rows left-->right error diffusion*/
      if (x % 2 == 0)
      {
         for (int y=0; y < width; y++)
         {
            int pixel = x*width +y;
            int pixel1 = (x+1)*width +y;
            int pixel2 = (x+2)*width +y;
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;

           double quant_err = norm_data[pixel] - out_data[pixel];

           if (y+2 < width)
           {
              norm_data[pixel +1] += quant_err*(8.0/42.0);
              norm_data[pixel +2] += quant_err*(4.0/42.0);
           }
           else if(x+2 < height && y+2 <width)
           {
              norm_data[pixel1+1] += quant_err*(4.0/42.0);            
              norm_data[pixel1+2] += quant_err*(2.0/42.0);            
              norm_data[pixel2+1] += quant_err*(2.0/42.0);            
              norm_data[pixel2+2] += quant_err*(1.0/42.0);            
           }
           else if(x+2 < height)
           {
              norm_data[pixel1] += quant_err*(2.0/42.0);            
              norm_data[pixel2] += quant_err*(4.0/42.0);            
           }
           else if(x+2 < height && y-2 >=0)
           {
              norm_data[pixel1-1] += quant_err*(4.0/42.0);            
              norm_data[pixel1-2] += quant_err*(2.0/42.0);            
              norm_data[pixel2-1] += quant_err*(2.0/42.0);            
              norm_data[pixel2-2] += quant_err*(1.0/42.0);            
           }
        }
      }
      /*Serpentine: Odd rows right-->left error diffusion*/
      else
      {
         for (int y= width-1; y >=0; y--)
         {
            int pixel = x*width +y;
            int pixel1 = (x+1)*width +y;
            int pixel2 = (x+2)*width +y;
            if (norm_data[pixel] >= 0.5)
               out_data[pixel] = 1;
            else
               out_data[pixel] = 0;
            double quant_err = norm_data[pixel] - out_data[pixel];
            if (y-2 >= 0)
            {
              norm_data[pixel -1] += quant_err*(8.0/42.0);
              norm_data[pixel -2] += quant_err*(4.0/42.0);
            }
           else if(x+2 < height && y+2 <width)
           {
              norm_data[pixel1+1] += quant_err*(4.0/42.0);            
              norm_data[pixel1+2] += quant_err*(2.0/42.0);            
              norm_data[pixel2+1] += quant_err*(2.0/42.0);            
              norm_data[pixel2+2] += quant_err*(1.0/42.0);            
           }
           else if(x+2 < height)
           {
              norm_data[pixel1] += quant_err*(8.0/42.0);            
              norm_data[pixel2] += quant_err*(4.0/42.0);            
           }
           else if(x+2 < height && y-2 >=0)
           {
              norm_data[pixel1-1] += quant_err*(4.0/42.0);            
              norm_data[pixel1-2] += quant_err*(2.0/42.0);            
              norm_data[pixel2-1] += quant_err*(2.0/42.0);            
              norm_data[pixel2-2] += quant_err*(1.0/42.0);            
           }
         }
      }
   }
   for (int i =0; i < height*width; i++)
   {
      data[i] = (1-out_data[i])*255;
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

   cout <<"Enter 1 - For Floyd-SteinBerg method "<<endl;
   cout <<"Enter 2 - For Jarvis et. al method "<<endl;
   cout <<"Enter 3 - For Stucki  method "<<endl;
   int index;
   cin >>index;
   //Read Image
   if (!inImage.readImage(argv[1]))
   {
      cout <<"Could not Read Image"<< endl;
   }
   else
   {
     cout << "Problem2b: Error Diffusion " <<endl;
     outImage = inImage;
     if (index == 1)
     {
        if (!outImage.diffusion_stein())
        {
           cout << "Error:Could not perform error diffusion"<<endl;
        }
     }
     else if (index == 2)
     {
        if (!outImage.diffusion_jarvis())
        {
           cout << "Error:Could not perform error diffusion"<<endl;
        }
     }
     else if (index == 3)
     {
        if (!outImage.diffusion_stucki())
        {
           cout << "Error:Could not perform error diffusion"<<endl;
        }
     }
     else
     {
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
