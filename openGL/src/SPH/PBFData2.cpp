#include"PBFDATA2.h"


PBFData2::PBFData2()
{

}

PBFData2::~PBFData2()
{

}
Vector2ArrayPtr& PBFData2::x_delta()
{
	return _x_delta;
}

Vector2ArrayPtr& PBFData2::predict_position()
{
	return _predict_position;
}

DoubleArrayPtr& PBFData2::lambda()
{
	return _lambda;
}