#ifndef NEIGHBORSEARCHER2_H
#define NEIGHBORSEARCHER2_H

#include <iostream>
using namespace std;
#include<vector>

#include "vector2.h"
#include "Vector2Array.h"
#include"ConstVar.h"

//ʹ�ø���������

//���ǰ�0�Ÿ���Ҳ�ŵ����½�
//�������귶Χ��0.0��0.0��-��1.1��1.1����
//����Χ��0.0��0.0��-��1.1��1.1����
class NeighborSearcher2 {
public:
	NeighborSearcher2();
	~NeighborSearcher2();
	explicit NeighborSearcher2(int resolutionX, int resolutionY, int numberOfParticles);
	void setNeiborList(const Vector2ArrayPtr positions);
	vector<vector<size_t>>& neighBors();
	void directSearch(const Vector2ArrayPtr positions);

private:
	//ע�������resolutionֻ�Ƿ�ո��ӵ�resolution
	//���Ҳ����ǿ��Ÿ���
	//X�����м��У�Y�����м���

	//ע���ڻ����е�����ϵ����
	//������õ�����ϵ���Դ������½�Ϊԭ�㣬x��y��ķ�����opengl����ϵһ��
	//�����ڻ��Ƶ�ʱ��Ҫת��opengl������ϵ
	int _resolutionX;
	int _resolutionY;
	int _numberOfParticles;

	//���ÿ�����ӵ��ھ�
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

