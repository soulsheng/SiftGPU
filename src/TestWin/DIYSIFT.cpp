////////////////////////////////////////////////////////////////////////////
//    File:        SimpleSIFT.cpp
//    Author:      Changchang Wu
//    Description : A simple example shows how to use SiftGPU and SiftMatchGPU
//
//
//
//    Copyright (c) 2007 University of North Carolina at Chapel Hill
//    All Rights Reserved
//
//    Permission to use, copy, modify and distribute this software and its
//    documentation for educational, research and non-profit purposes, without
//    fee, and without a written agreement is hereby granted, provided that the
//    above copyright notice and the following paragraph appear in all copies.
//    
//    The University of North Carolina at Chapel Hill make no representations
//    about the suitability of this software for any purpose. It is provided
//    'as is' without express or implied warranty. 
//
//    Please send BUG REPORTS to ccwu@cs.unc.edu
//
////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using std::vector;
using std::iostream;


#include "../SiftGPU/SiftGPU.h"

#define		MULTI_THREAD_ENABLE		0	// 开启多线程 

int main()
{
	SiftGPU sift;

    //Create a context for computation, and SiftGPU will be initialized automatically 
    //The same context can be used by SiftMatchGPU
    if(sift.CreateContextGL() != SiftGPU::SIFTGPU_FULL_SUPPORTED) 
		return 0;

	char * argv[] = {"-v", "0"};
	int argc = sizeof(argv)/sizeof(char*);
	sift.ParseParam(argc, argv);

	std::ostringstream os;
	std::string filenameBase("../data/640-");

	std::cout  << std::endl << "get features: " << std::endl;

#if MULTI_THREAD_ENABLE
#pragma omp parallel for
#endif
	for(int i=0; i<3; i++)
	{

		vector<float > descriptors;
		vector<SiftGPU::SiftKeypoint> keys;    

		os.str("");
		os << filenameBase << i+1 << ".jpg";
		std::string filename( os.str().c_str() );
		if(sift.RunSIFT( filename.c_str() ))
		{
			//get feature count
			int num = sift.GetFeatureNum();
			std::cout << std::endl << std::endl 
				<< "image " << i << " " 
				<< filename << " : " 
				<< num << " features" 
				<< std::endl;
		
			keys.resize(num);    descriptors.resize(128*num);
			sift.GetFeatureVector(&keys[0], &descriptors[0]);
			
			std::cout << "descriptors: " << std::endl;
			for(int ii=0; ii<num/100; ii++)
				std::cout << descriptors[ii] << " ";
		}
	}

    return 1;
}

