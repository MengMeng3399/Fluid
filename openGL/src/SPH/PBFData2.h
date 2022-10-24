#ifndef PBFDATA2_H
#define PBFDATA2_H

#include <iostream>
#include"Vector2Array.h"
#include"DoubleArray.h"
#include"SphSpikyKernel2.h"
#include"SphStdKernel2.h"
#include"SphSystemData2.h"

using namespace std;

class PBFData2 :public SphSystemData2
{
public:
	PBFData2();
	~PBFData2();
	Vector2ArrayPtr& x_delta();
	Vector2ArrayPtr& predict_position();
	DoubleArrayPtr& lambda();

private:

	Vector2ArrayPtr _x_delta;
	Vector2ArrayPtr _predict_position;
	DoubleArrayPtr  _lambda;


};

using PBFData2Ptr = shared_ptr<PBFData2>;




#endif