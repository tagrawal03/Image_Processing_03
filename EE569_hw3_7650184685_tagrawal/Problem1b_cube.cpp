/*
Problem1b_cube.cpp: Perspective transformation and Imaging goemetry
Author: Taruna Agrawal
Date: 1st November 2015
email:tagrawal@usc.edu
ID: 7650184685
*/


#include "Image.cpp"
#include <math.h> 

//Global variables
Image inImage1, inImage2, inImage3, outImage;



/*Perform goemetric transformation on Image1*/
bool Image::transformation1(unsigned char* data1)
{
   for (int ipix=0; ipix<width*height*3; ipix++)
       data[ipix] = 0;

   double x_baby[200][200];
   double y_baby[200][200];
   double z_baby[200][200];

   double R[3][4] = {{(double)-1/(double)sqrt(2), (double)1/(double)sqrt(2), 0, 0},
                     {(double)1/(double)sqrt(6), (double)1/(double)sqrt(6), (double)-2/(double)sqrt(6), 0},
                     {(double)-1/(double)sqrt(3), (double)-1/(double)sqrt(3), (double)-1/(double)sqrt(3), (double)15/(double)sqrt(3)}};
#if 0
   for(int i=0; i<3; i++)
   {
      for(int j=0; j<4; j++)
      {
          cout<<R[i][j]<<" ,";
      }
      cout<<endl;
   }
#endif

   //ofstream myfile;
   //myfile.open ("x.txt");
   for(int i=0; i<height; i++)
   {
      for(int j=0; j<width; j++)
      {
         x_baby[i][j] = -1 + ((double)2/(double)width)*i;
         y_baby[i][j] = -1 + ((double)2/(double)width)*j;
         z_baby[i][j] = 1;
         /*From world coordinates to camera coordinates*/
         double xC = R[0][0]*x_baby[i][j] + R[0][1]*y_baby[i][j] + R[0][2]*z_baby[i][j] + R[0][3]*1;   
         double yC = R[1][0]*x_baby[i][j] + R[1][1]*y_baby[i][j] + R[1][2]*z_baby[i][j] + R[1][3]*1;   
         double zC = R[2][0]*x_baby[i][j] + R[2][1]*y_baby[i][j] + R[2][2]*z_baby[i][j] + R[2][3]*1;   
         /*Camera coordinates to image plane coordinates*/
         double x = (double)(sqrt(3)*xC)/(double)zC;
         double y = (double)(sqrt(3)*yC)/(double)zC;
         /*Multiply by pixel density and add width to adjust negative pixels*/         
         unsigned int newx = x*255 + (width/2);
         unsigned int newy = y*255 + (width/2);
         int pixel = 3*newx*width +3*newy;
         int pix =3*i*width +3*j;
         data[pixel] = data1[pix];  
         data[pixel+1] = data1[pix+1];  
         data[pixel+2] = data1[pix+2];  
   //      data[pixel] = 0;  
     //    myfile <<newy<< " ";
      }
  //    myfile <<endl;
   }
  // myfile.close();
   cout<<endl;
   cout <<"Mapping for baby"<<endl;
   cout <<x_baby[0][0]<<"->"<<(int)data1[(3*0*width)+(3*0)]<<endl;
   cout <<y_baby[0][0]<<"->"<<(int)data1[((3*0*width)+(3*0))+1]<<endl;
   cout <<z_baby[0][0]<<"->"<<(int)data1[((3*0*width)+(3*0))+2]<<endl;
   cout <<x_baby[0][199]<<"->"<<(int)data1[(3*0*width)+(3*199)]<<endl;
   cout <<y_baby[0][199]<<"->"<<(int)data1[((3*0*width)+(3*199))+1]<<endl;
   cout <<z_baby[0][199]<<"->"<<(int)data1[((3*0*width)+(3*199))+2]<<endl;
   cout <<x_baby[199][0]<<"->"<<(int)data1[(3*199*width)+(3*0)]<<endl;
   cout <<y_baby[199][0]<<"->"<<(int)data1[((3*199*width)+(3*0))+1]<<endl;
   cout <<z_baby[199][0]<<"->"<<(int)data1[((3*199*width)+(3*0))+2]<<endl;
   cout <<x_baby[199][199]<<"->"<<(int)data1[(3*199*width)+(3*199)]<<endl;
   cout <<y_baby[199][199]<<"->"<<(int)data1[((3*199*width)+(3*199))+1]<<endl;
   cout <<z_baby[199][199]<<"->"<<(int)data1[((3*199*width)+(3*199))+2]<<endl;

   /*Calculating image plane coordinates*/
      

   return true;
}

bool Image::transformation2(unsigned char* data1)
{

   double x_dog[200][200];
   double y_dog[200][200];
   double z_dog[200][200];
   double R[3][4] = {{(double)-1/(double)sqrt(2), (double)1/(double)sqrt(2), 0, 0},
                     {(double)1/(double)sqrt(6), (double)1/(double)sqrt(6), (double)-2/(double)sqrt(6), 0},
                     {(double)-1/(double)sqrt(3), (double)-1/(double)sqrt(3), (double)-1/(double)sqrt(3), (double)15/(double)sqrt(3)}};

   for(int i=0; i<height; i++)
   {
      for(int j=0; j<width; j++)
      {
         x_dog[i][j] = 1;
         y_dog[i][j] = -1 + ((double)2/(double)width)*j;
         z_dog[i][j] = 1 - ((double)2/(double)width)*i;
         /*From world coordinates to camera coordinates*/
         double xC = R[0][0]*x_dog[i][j] + R[0][1]*y_dog[i][j] + R[0][2]*z_dog[i][j] + R[0][3]*1;   
         double yC = R[1][0]*x_dog[i][j] + R[1][1]*y_dog[i][j] + R[1][2]*z_dog[i][j] + R[1][3]*1;   
         double zC = R[2][0]*x_dog[i][j] + R[2][1]*y_dog[i][j] + R[2][2]*z_dog[i][j] + R[2][3]*1;   
         /*Camera coordinates to image plane coordinates*/
         double x = (double)(sqrt(3)*xC)/(double)zC;
         double y = (double)(sqrt(3)*yC)/(double)zC;
         
         unsigned int newx = x*255 + (width/2);
         unsigned int newy = y*255 + (width/2);
         int pixel = 3*newx*width +3*newy;
         int pix =3*i*width +3*j;
         data[pixel] = data1[pix];  
         data[pixel+1] = data1[pix+1];  
         data[pixel+2] = data1[pix+2];  
      }
   }
   cout<<endl;
   cout <<"Mapping for dog"<<endl;
   cout <<x_dog[0][0]<<"->"<<(int)data1[(3*0*width)+(3*0)]<<endl;
   cout <<y_dog[0][0]<<"->"<<(int)data1[((3*0*width)+(3*0))+1]<<endl;
   cout <<z_dog[0][0]<<"->"<<(int)data1[((3*0*width)+(3*0))+2]<<endl;
   cout <<x_dog[0][199]<<"->"<<(int)data1[(3*0*width)+(3*199)]<<endl;
   cout <<y_dog[0][199]<<"->"<<(int)data1[((3*0*width)+(3*199))+1]<<endl;
   cout <<z_dog[0][199]<<"->"<<(int)data1[((3*0*width)+(3*199))+2]<<endl;
   cout <<x_dog[199][0]<<"->"<<(int)data1[(3*199*width)+(3*0)]<<endl;
   cout <<y_dog[199][0]<<"->"<<(int)data1[((3*199*width)+(3*0))+1]<<endl;
   cout <<z_dog[199][0]<<"->"<<(int)data1[((3*199*width)+(3*0))+2]<<endl;
   cout <<x_dog[199][199]<<"->"<<(int)data1[(3*199*width)+(3*199)]<<endl;
   cout <<y_dog[199][199]<<"->"<<(int)data1[((3*199*width)+(3*199))+1]<<endl;
   cout <<z_dog[199][199]<<"->"<<(int)data1[((3*199*width)+(3*199))+2]<<endl;

   return true;
}

bool Image::transformation3(unsigned char* data1)
{

   double x_panda[200][200];
   double y_panda[200][200];
   double z_panda[200][200];
   double R[3][4] = {{(double)-1/(double)sqrt(2), (double)1/(double)sqrt(2), 0, 0},
                     {(double)1/(double)sqrt(6), (double)1/(double)sqrt(6), (double)-2/(double)sqrt(6), 0},
                     {(double)-1/(double)sqrt(3), (double)-1/(double)sqrt(3), (double)-1/(double)sqrt(3), (double)15/(double)sqrt(3)}};

   for(int i=0; i<height; i++)
   {
      for(int j=0; j<width; j++)
      {
         x_panda[i][j] = 1 - ((double)2/(double)width)*j;
         y_panda[i][j] = 1;
         z_panda[i][j] = 1 - ((double)2/(double)width)*i;
         /*From world coordinates to camera coordinates*/
         double xC = R[0][0]*x_panda[i][j] + R[0][1]*y_panda[i][j] + R[0][2]*z_panda[i][j] + R[0][3]*1;   
         double yC = R[1][0]*x_panda[i][j] + R[1][1]*y_panda[i][j] + R[1][2]*z_panda[i][j] + R[1][3]*1;   
         double zC = R[2][0]*x_panda[i][j] + R[2][1]*y_panda[i][j] + R[2][2]*z_panda[i][j] + R[2][3]*1;   
         /*Camera coordinates to image plane coordinates*/
         double x = (double)(sqrt(3)*xC)/(double)zC;
         double y = (double)(sqrt(3)*yC)/(double)zC;
         unsigned int newx = x*255 + (width/2);
         unsigned int newy = y*255 + (width/2);
      
         int pixel = 3*newx*width +3*newy;
         int pix =3*i*width +3*j;
         data[pixel] = data1[pix];  
         data[pixel+1] = data1[pix+1];  
         data[pixel+2] = data1[pix+2];  
      }
   }
   cout<<endl;
   cout <<"Mapping for panda"<<endl;
   cout <<x_panda[0][0]<<"->"<<(int)data1[(3*0*width)+(3*0)]<<endl;
   cout <<y_panda[0][0]<<"->"<<(int)data1[((3*0*width)+(3*0))+1]<<endl;
   cout <<z_panda[0][0]<<"->"<<(int)data1[((3*0*width)+(3*0))+2]<<endl;
   cout <<x_panda[0][199]<<"->"<<(int)data1[(3*0*width)+(3*199)]<<endl;
   cout <<y_panda[0][199]<<"->"<<(int)data1[((3*0*width)+(3*199))+1]<<endl;
   cout <<z_panda[0][199]<<"->"<<(int)data1[((3*0*width)+(3*199))+2]<<endl;
   cout <<x_panda[199][0]<<"->"<<(int)data1[(3*199*width)+(3*0)]<<endl;
   cout <<y_panda[199][0]<<"->"<<(int)data1[((3*199*width)+(3*0))+1]<<endl;
   cout <<z_panda[199][0]<<"->"<<(int)data1[((3*199*width)+(3*0))+2]<<endl;
   cout <<x_panda[199][199]<<"->"<<(int)data1[(3*199*width)+(3*199)]<<endl;
   cout <<y_panda[199][199]<<"->"<<(int)data1[((3*199*width)+(3*199))+1]<<endl;
   cout <<z_panda[199][199]<<"->"<<(int)data1[((3*199*width)+(3*199))+2]<<endl;
   return true;
}

int main(int argc, char* argv[])
{

   int BytesPerPixel = 3;
   int Width = 200;
   int Height = 200;
   int outWidth, outHeight;

   if (argc < 4)
   {
      cout << "Error - Incorrect Parameter Usage:" << endl;
      cout << "program_name input_image1 input_image2 input_image3 output_image" << endl;
      return 0;
   }	
   //BytesPerPixel = atoi(argv[3]);
   inImage1.setNumbytes(BytesPerPixel);
   inImage2.setNumbytes(BytesPerPixel);
   inImage3.setNumbytes(BytesPerPixel);

      // Check if size is specified
   if (argc >= 4){
	// Width = atoi(argv[4]);
	 //Height = atoi(argv[5]);
         inImage1.setWidth(Width);
         inImage1.setHeight(Height);
         inImage2.setWidth(Width);
         inImage2.setHeight(Height);
         inImage3.setWidth(Width);
         inImage3.setHeight(Height);
    }

   unsigned char* data1;
   data1 = new unsigned char[Width*Height];
   //Read Image1
   if ((!inImage1.readImage(argv[1])) || (!inImage2.readImage(argv[2])) || (!inImage3.readImage(argv[3])))
   {
      cout <<"Could not Read Image"<< endl;
   }
   else
   {
     cout << "Problem1b: Goemetric Transformation" <<endl;
     outImage = inImage1;
   //   outImage.setWidth(Width*2);
     // outImage.setHeight(Height*2);
      // outImage.setNumbytes(BytesPerPixel);
       //for (int ipix =0; ipix < Width*Height*BytesPerPixel; ipix++)
        //  outImage.setImageData(0);
     
     data1 = inImage1.getImageData();
     if (!outImage.transformation1(data1))
     {
         cout << "Error:Could not perform goemetrical modification in Image1"<<endl;
     }
#if 1
     //outImage = inImage2;
     data1 = inImage2.getImageData();
     if (!outImage.transformation2(data1))
     {
         cout << "Error:Could not perform goemetrical modification in Image2"<<endl;
     }
     //outImage = inImage3;
     data1 = inImage3.getImageData();
     if (!outImage.transformation3(data1))
     {
         cout << "Error:Could not perform goemetrical modification in Image3"<<endl;
     }
#endif
   }
   //write final image to file
   if (!outImage.writeImage(argv[4]))
   {
      cout <<"Could not Write Image"<< endl;
   }

  return 0;
}
