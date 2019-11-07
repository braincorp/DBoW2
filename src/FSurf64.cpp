/**
 * File: FSurf64.cpp
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: functions for Surf64 descriptors
 * License: see the LICENSE.txt file
 *
 */
 
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "DBoW2/FClass.h"
#include "DBoW2/FSurf64.h"

using namespace std;

namespace DBoW2 {

// --------------------------------------------------------------------------

void FSurf64::meanValue(const std::vector<FSurf64::pDescriptor> &descriptors, 
  FSurf64::TDescriptor &mean)
{
//    if(descriptors.empty())
//    {
//        mean.release();
//        return;
//    }
//    else if(descriptors.size() == 1)
//    {
//        mean = descriptors[0]->clone();
//    }
//    else
//    {
        mean = cv::Mat::zeros(1, FSurf64::L, CV_32F);
        float *meanPtr = mean.ptr<float>();
        
        float s = descriptors.size();
        
        for(size_t i = 0; i < descriptors.size(); ++i)
        {
            const cv::Mat &d = *descriptors[i];
            const float *p = d.ptr<float>(0); // descriptors size: (1, 64) --> point to first row (0) and iterate thru
            
            for (int j = 0; j < FSurf64::L; j++) {
                meanPtr[j] += p[j] / s;
            }
        }
//    }
    
//    mean.resize(0);
//    mean.resize(FSurf64::L, 0);
//
//    float s = descriptors.size();
//
//  vector<FSurf64::pDescriptor>::const_iterator it;
//  for(it = descriptors.begin(); it != descriptors.end(); ++it)
//  {
//    const FSurf64::TDescriptor &desc = **it;
//    for(int i = 0; i < FSurf64::L; i += 4)
//    {
//      mean[i  ] += desc[i  ] / s;
//      mean[i+1] += desc[i+1] / s;
//      mean[i+2] += desc[i+2] / s;
//      mean[i+3] += desc[i+3] / s;
//    }
//  }
}

// --------------------------------------------------------------------------
  
double FSurf64::distance(const FSurf64::TDescriptor &a, const FSurf64::TDescriptor &b)
{
    double sqd = 0.;
    
    const float* aPtr = a.ptr<float>(0);
    const float* bPtr = b.ptr<float>(0);
    
    for(int i = 0; i < FSurf64::L; i++) {
        sqd += (aPtr[i] - bPtr[i])*(aPtr[i] - bPtr[i]);
    }
    
    return sqd;
    
    
//  double sqd = 0.;
//  for(int i = 0; i < FSurf64::L; i += 4)
//  {
//    sqd += (a[i  ] - b[i  ])*(a[i  ] - b[i  ]);
//    sqd += (a[i+1] - b[i+1])*(a[i+1] - b[i+1]);
//    sqd += (a[i+2] - b[i+2])*(a[i+2] - b[i+2]);
//    sqd += (a[i+3] - b[i+3])*(a[i+3] - b[i+3]);
//  }
//  return sqd;
}

// --------------------------------------------------------------------------

std::string FSurf64::toString(const FSurf64::TDescriptor &a)
{
  stringstream ss;
  for(int i = 0; i < FSurf64::L; ++i)
  {
    //ss << a[i] << " ";
      ss << a.at<float>(i) << " ";
  }
  return ss.str();
}

// --------------------------------------------------------------------------
  
void FSurf64::fromString(FSurf64::TDescriptor &a, const std::string &s)
{
//  a.create(1, FSurf64::L, CV_32F);
//
//  stringstream ss(s);
//  for(int i = 0; i < FSurf64::L; ++i)
//  {
//    //ss >> a[i];
//      ss >> a.at<float>(i);
//  }
    a.create(1, FSurf64::L, CV_32F);
    auto p = a.ptr<float>();
    
    stringstream ss(s);
    for(int i = 0; i < FSurf64::L; ++i, ++p)
    {
        float n;
        ss >> n;
        
        if(!ss.fail())
            *p = n;
    }
}

// --------------------------------------------------------------------------

void FSurf64::toMat32F(const std::vector<TDescriptor> &descriptors, cv::Mat &mat)
{
    if(descriptors.empty())
    {
        mat.release();
        return;
    }
  
    const int N = descriptors.size();
    const int L = FSurf64::L;

    mat.create(N, L, CV_32F);
  
    for(int i = 0; i < N; ++i)
    {
        const TDescriptor& desc = descriptors[i];
        const float *descPtr = desc.ptr<float>(0);
        float *p = mat.ptr<float>(i);
        for(int j = 0; j < L; ++j, ++p)
        {
            //*p = desc[j];
            *p = descPtr[j];
        }
    }
}

// --------------------------------------------------------------------------

} // namespace DBoW2
