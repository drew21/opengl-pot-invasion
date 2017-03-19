// Normal.h: interface for the Normal class.
//
//////////////////////////////////////////////////////////////////////
    
#ifndef  NORMAL_H
#define NORMAL_H 
 
#include "Vector3d.h"
 
class Normal  
{
public:
    Normal();
    virtual ~Normal();
 
    Vector3d norm;
    Vector3d pt;
 
};
 
#endif 