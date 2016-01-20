/*
Problem2d_VCH.cpp: Convert color image to half toned image using scalar halftoning method.
Author: Taruna Agrawal
Date: 1st November 2015
email:tagrawal@usc.edu
ID: 7650184685
*/


#include "Image.cpp"
#include <math.h> 

//Global variables
Image inImage, outImage;


void mbvq_func(double R, double G, double B, int (&index)[4])
{

   R = (double)R/(double)255;
   G = (double)G/(double)255;
   B = (double)B/(double)255;
   if ((R+G) > 1)
   {
      if ((G+B) > 1)
      {
          if ((R+G+B) > 2)
           {
               index[0] = 3;
               index[1] = 5;
               index[2] = 6;
               index[3] = 7;
           }
           else
           {
               index[0] = 5;
               index[1] = 6;
               index[2] = 2;
               index[3] = 3;
           }
       }
       else
       {
               index[0] = 2;
               index[1] = 4;
               index[2] = 5;
               index[3] = 6;
       }
   }
   else
   {
      if (!((G+B) > 1))
      {
          if (!((R+G+B) > 1))
           {
               index[0] = 0;
               index[1] = 1;
               index[2] = 2;
               index[3] = 4;
           }
           else
           {
               index[0] = 1;
               index[1] = 2;
               index[2] = 4;
               index[3] = 5;
           }
       }
       else
       {
               index[0] = 1;
               index[1] = 2;
               index[2] = 3;
               index[3] = 5;
       }
   }

}

/*Function to perform scalar half toning on Image*/
bool Image::vch()
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
       //norm_data[pixel] = 1 - norm_data[pixel];
       norm_data[pixel+1] = (double)data[pixel+1]/(double)255;
       //norm_data[pixel+1] = 1 - norm_data[pixel+1];
       norm_data[pixel+2] = (double)data[pixel+2]/(double)255;
       //norm_data[pixel+2] = 1 - norm_data[pixel+2];
   }
#if 1
   int color_quadrants[8][3] = {{0, 0, 0}, //black-0
                                {0, 0, 1}, //blue-1
                                {0, 1, 0}, //green-2
                                {0, 1, 1}, //cyan-3
                                {1, 0, 0}, //red-4
                                {1, 0, 1}, //magenta-5
                                {1, 1, 0}, //yellow-6
                                {1, 1, 1}}; //white-7

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


            int quad[4];
            mbvq_func(data[pixel], data[pixel +1],data[pixel+2], quad);   
            //cout <<quad[0] << " "<<quad[1]<<" "<<quad[2]<<" "<<quad[3]<<endl;
#if 0           
            double dist[4] = {0};

            for (int iDist=0; iDist < 4; iDist++)
            {
                dist[iDist] = pow((norm_data[pixel] - color_quadrants[quad[iDist]][0]), 2) +
                         pow((norm_data[pixel+1] - color_quadrants[quad[iDist]][1]), 2) +
                         pow((norm_data[pixel+2] - color_quadrants[quad[iDist]][2]), 2);
 //               dist[iDist] = sqrt(dist[iDist]); 
            }
            /*Find the minimum distance*/
            double min = dist[0];
            int index = 0;
            for (int iMin=0; iMin<4; iMin++)
            {
               if (min > dist[iMin])
               {
                  min = dist[iMin]; 
                  index = iMin;
               }
            }
#endif
#if 1
            /*Find distance of pixel from each quadrant*/
            double dist[8] = {0};
            for (int iDist=0; iDist < 8; iDist++)
            {
               //  dist[iDist] = pow((((double)data[pixel]/(double)255) - color_quadrants[iDist][0]), 2) +
                 //       pow((((double)data[pixel+1]/(double)255) - color_quadrants[iDist][1]), 2) +
                   //      pow((((double)data[pixel +2]/(double)255) - color_quadrants[iDist][2]), 2);
                dist[iDist] = pow((norm_data[pixel] - color_quadrants[iDist][0]), 2) +
                         pow((norm_data[pixel+1] - color_quadrants[iDist][1]), 2) +
                        pow((norm_data[pixel+2] - color_quadrants[iDist][2]), 2);
            }

            /*Find the minimum distance*/
            double min = dist[0];
            int index = 0;
            for (int iMin=0; iMin<8; iMin++)
            {
               if (min > dist[iMin])
               {
                  min = dist[iMin]; 
                  index = iMin;
               }
            }
#endif
#if 1
           /*Calculate error*/
           double quant_errC = norm_data[pixel] - color_quadrants[index][0];
           double quant_errM = norm_data[pixel+1] - color_quadrants[index][1];
           double quant_errY = norm_data[pixel+2] - color_quadrants[index][2];
           //quant_errC = -1*quant_errC;
           //quant_errM = -1*quant_errM;
         // quant_errY = -1*quant_errY;
#endif    
#if 1 
           out_data[pixel] = color_quadrants[index][0];
           out_data[pixel+1] = color_quadrants[index][1];
           out_data[pixel+2] = color_quadrants[index][2];
#endif

#if 1
           /*Distribute error to future pixels*/
           if (y+1 < width)
           {
              norm_data[pixel +3] += quant_errC*((double)7.0/(double)16.0);
              norm_data[pixel +4] += quant_errM*((double)7.0/(double)16.0);
              norm_data[pixel +5] += quant_errY*((double)7.0/(double)16.0);
           }
           if(x+1 < height && y+1 <width)
           {
              norm_data[pixel1] += quant_errC*((double)1.0/(double)16.0);            
              norm_data[pixel1+1] += quant_errM*((double)1.0/(double)16.0);            
              norm_data[pixel1+2] += quant_errY*((double)1.0/(double)16.0);            
           }
           if(x+1 < height)
           {
              	norm_data[pixel2] += quant_errC*((double)5.0/(double)16.0);            
              norm_data[pixel2+1] += quant_errM*((double)5.0/(double)16.0);            
              norm_data[pixel2+2] += quant_errY*((double)5.0/(double)16.0);            
           }
           if(x+1 < height && y-1 >=0)
           {
              norm_data[pixel3] += quant_errC*((double)3.0/(double)16.0);            
              norm_data[pixel3+1] += quant_errM*((double)3.0/(double)16.0);            
              norm_data[pixel3+2] += quant_errY*((double)3.0/(double)16.0);            
           }
#endif
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
         
            int quad[4];
            mbvq_func(data[pixel], data[pixel +1],data[pixel+2], quad);   
          //  cout <<quad[0] << " "<<quad[1]<<" "<<quad[2]<<" "<<quad[3]<<endl;
#if 0           
            double dist[4] = {0};

            for (int iDist=0; iDist < 4; iDist++)
            {
                dist[iDist] = pow((norm_data[pixel] - color_quadrants[quad[iDist]][0]), 2) +
                         pow((norm_data[pixel+1] - color_quadrants[quad[iDist]][1]), 2) +
                         pow((norm_data[pixel+2] - color_quadrants[quad[iDist]][2]), 2);
     //           dist[iDist] = sqrt(dist[iDist]); 
            }
            /*Find the minimum distance*/
            double min = dist[0];
            int index = 0;
            for (int iMin=0; iMin<4; iMin++)
            {
               if (min > dist[iMin])
               {
                  min = dist[iMin]; 
                  index = iMin;
               }
            }
#endif
#if 1
            /*Find distance of pixel from each quadrant*/
            double dist[8] = {0};
            for (int iDist=0; iDist < 8; iDist++)
            {
            //   dist[iDist] = pow((((double)data[pixel]/(double)255) - color_quadrants[iDist][0]), 2) +
              //           pow((((double)data[pixel+1]/(double)255) - color_quadrants[iDist][1]), 2) +
                //         pow((((double)data[pixel +2]/(double)255) - color_quadrants[iDist][2]), 2);
                dist[iDist] = pow((norm_data[pixel] - color_quadrants[iDist][0]), 2) +
                         pow((norm_data[pixel+1] - color_quadrants[iDist][1]), 2) +
                         pow((norm_data[pixel+2] - color_quadrants[iDist][2]), 2);
            }
            /*Find the minimum distance*/
            double min = dist[0];
            int index = 0;
            for (int iMin=0; iMin<8; iMin++)
            {
               if (min > dist[iMin])
               {
                  min = dist[iMin]; 
                  index = iMin;
               }
            }
#endif
#if 1
           /*Calculate error*/
           double quant_errC = norm_data[pixel] - color_quadrants[index][0];
           double quant_errM = norm_data[pixel+1] - color_quadrants[index][1];
           double quant_errY = norm_data[pixel+2] - color_quadrants[index][2];
     //      quant_errC = -1*quant_errC;
       //    quant_errM = -1*quant_errM;
         //  quant_errY = -1*quant_errY;
#endif 
#if 1          
           out_data[pixel] = color_quadrants[index][0];
           out_data[pixel+1] = color_quadrants[index][1];
           out_data[pixel+2] = color_quadrants[index][2];
#endif

#if 1           
           if (y-1 >= 0)
           {
               norm_data[pixel -3] += quant_errC*((double)7.0/(double)16.0);
               norm_data[pixel -4] += quant_errM*((double)7.0/(double)16.0);
               norm_data[pixel -5] += quant_errY*((double)7.0/(double)16.0);
           }
           if(x+1 < height && y-1>=0)
           {
              norm_data[pixel1] += quant_errC*((double)1.0/(double)16.0);            
              norm_data[pixel1+1] += quant_errM*((double)1.0/(double)16.0);            
              norm_data[pixel1+2] += quant_errY*((double)1.0/(double)16.0);            
           }
           if(x+1 < height)
           {
              norm_data[pixel2] += quant_errC*((double)5.0/(double)16.0);            
              norm_data[pixel2+1] += quant_errM*((double)5.0/(double)16.0);            
              norm_data[pixel2+2] += quant_errY*((double)5.0/(double)16.0);            
           }
           if(x+1 < height && y+1<=width)
           {
              norm_data[pixel3] += quant_errC*((double)3.0/(double)16.0);            
              norm_data[pixel3+1] += quant_errM*((double)3.0/(double)16.0);            
              norm_data[pixel3+2] += quant_errY*((double)3.0/(double)16.0);            
           }
#endif
         }

      }
   }

#endif

#endif
   for (int i =0; i < height*width*3; i++)
   {
      data[i] = (out_data[i])*255;
      //data[i] = norm_data[i]*255;
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
     cout << "Problem2d: Vector Error Diffusion " <<endl;
     outImage = inImage;
     if (!outImage.vch())
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
