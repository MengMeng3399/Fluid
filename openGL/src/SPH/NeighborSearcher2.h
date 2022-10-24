#ifndef NEIGHBORSEARCHER2_H
#define NEIGHBORSEARCHER2_H

#include <iostream>
using namespace std;
#include<vector>

#include "vector2.h"
#include "Vector2Array.h"
#include"ConstVar.h"

//使用格子搜索法

//我们把0号格子也放到左下角
//粒子坐标范围（0.0，0.0）-（1.1，1.1）。
//网格范围（0.0，0.0）-（1.1，1.1）。
class NeighborSearcher2 {
public:
	NeighborSearcher2();
	~NeighborSearcher2();
	explicit NeighborSearcher2(int resolutionX, int resolutionY, int numberOfParticles);
	void setNeiborList(const Vector2ArrayPtr positions);
	vector<vector<size_t>>& neighBors();
	void directSearch(const Vector2ArrayPtr positions);

private:
	//注意这里的resolution只是封闭格子的resolution
	//暂且不考虑开放格子
	//X代表有几行，Y代表有几列

	//注意在绘制中的坐标系问题
	//这里采用的坐标系是以窗口左下角为原点，x、y轴的方向与opengl坐标系一致
	//所以在绘制的时候要转成opengl的坐标系
	int _resolutionX;
	int _resolutionY;
	int _numberOfParticles;

	//存放每个粒子的邻居
	vector<vector<size_t>> _data;
	void resetDataSize();
	void clearData();
	bool IsXoverBorder(size_t idx);
	bool IsYoverBorder(size_t idx);
	bool IsNeighbor(Vector2& pos1, Vector2& pos2, const double& r);
	void forEachNeighborGrid(Vector2& idx, size_t particleId, vector<vector<vector<size_t>>>& grids, const Vector2ArrayPtr positions);

};

using NeighborSearcher2Ptr = shared_ptr<NeighborSearcher2>;

#endif

