#EE569 Homework Assignment #3
#Submission Date: 1st November, 2015
#Name: Taruna Agrawal
#Email: tagrawal@usc.edu

#Compiled on UBUNTU 14.04 with g++
#g++ version: g++ (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4

all : prob1a  prob1b prob2a prob2b prob2c prob2d prob3a prob3b 
prob1a:
	@echo " "
	@echo "Problem 1a of Swirl effect"
	@echo "Compiling Problem1a_swirl.cpp"
	@echo " "
	g++ -o swirl Problem1a_swirl.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	./swirl kate.raw kate_output.raw 3 512 512

prob1b:
	@echo " "
	@echo "Problem 1b of Gowmetric transformation"
	@echo "Compiling Problem1b_cube.cpp"
	@echo " "
	g++ -o cube Problem1b_cube.cpp
	@echo "Usage: program_name image1 image2 image3 output_image"
	@echo " "
	./cube baby.raw baby_dog.raw baby_panda.raw cube.raw

prob2a:
	@echo " "
	@echo "Problem 2a of Dithering"
	@echo "Compiling Problem2a_dithering.cpp"
	@echo " "
	g++ -o dithering Problem2a_dithering.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	./dithering mandrill.raw mandrill_output.raw 1 512 512

prob2b:
	@echo " "
	@echo "Problem 2b of error diffusion"
	@echo "Compiling Problem2b_errDiffusion.cpp"
	@echo " "
	g++ -o errDiff Problem2b_errDiffusion.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	./errDiff mandrill.raw mandrill_outputErr.raw 1 512 512

prob2c:
	@echo " "
	@echo "Problem 2c of scalar error diffusion"
	@echo "Compiling Problem2c_SCH.cpp"
	@echo " "
	g++ -o sch Problem2c_SCH.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	./sch Sailboat.raw Sailboat_sch.raw 3 512 512

prob2d:
	@echo " "
	@echo "Problem 2d of vector error diffusion"
	@echo "Compiling Problem2d_VCH.cpp"
	@echo " "
	g++ -o vch Problem2d_VCH.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	./vch Sailboat.raw Sailboat_vch.raw 3 512 512

prob3a:
	@echo " "
	@echo "Problem 3a of Morphological Processing"
	@echo "Compiling Problem3a_shrink.cpp"
	@echo "Compiling Problem3a_numWhiteObj.cpp"
	@echo "Compiling Problem3a_Nholes.cpp.cpp"
	@echo " "
	g++ -o shrink Problem3a_shrink.cpp
	g++ -o shrinkNobj Problem3a_numWhiteObj.cpp
	g++ -o Nholes Problem3a_Nholes.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	./shrink Horseshoe.raw Horseshoe_output.raw 1 91 108
	./shrinkNobj Horseshoe.raw HorseshoeNwhite_output.raw 1 91 108
	./Nholes Horseshoe.raw HorseshoeNhole_output.raw 1 91 108

prob3b:
	@echo " "
	@echo "Problem 3b of Morphological Processing"
	@echo "Compiling Problem3b_preprocessing.cpp"
	@echo "Compiling Problem3b_thin.cpp"
	@echo " "
	g++ -o thinSk Problem3b_thin.cpp
	g++ -o preproc Problem3b_preprocessing.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	@echo "Output with preprocessing and output without preprocessing "
	./preproc Horse1.raw Horse1_preproc.raw 1 360 275
	./thinSk HorseSm.raw Horse1_thinoutput1.raw 1 360 275
	./thinSk Horse1_preproc.raw Horse1_thinoutput2.raw 1 360 275
	./thinSk Horse1.raw Horse1_outputNopre.raw 1 360 275
	@echo "Compiling Problem3b_skel.cpp"
	@echo " "
	g++ -o skel Problem3b_skel.cpp
	@echo "Usage: program_name original_image output_image BytesPerPixel width height"
	@echo " "
	@echo "Output with preprocessing and output without preprocessing(comment out preprocessing function) "
	./skel HorseSm.raw Horse1_skeloutput1.raw 1 360 275
	./skel Horse1_preproc.raw Horse1_skeloutput2.raw 1 360 275
clean :
	rm -rf  swirl dithering errDiff sch vch shrink shrinkNobj Nholes preproc thinSk skel
