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
using std::vector;
using std::iostream;


#include "../SiftGPU/SiftGPU.h"


int main()
{
	SiftGPU sift;

    //Create a context for computation, and SiftGPU will be initialized automatically 
    //The same context can be used by SiftMatchGPU
    if(sift.CreateContextGL() != SiftGPU::SIFTGPU_FULL_SUPPORTED) 
		return 0;

    if(sift.RunSIFT("../data/800-1.jpg"))
    {
        //get feature count
        int num = sift.GetFeatureNum();
		std::cout << "feature number is : " << num;
    }


    return 1;
}

