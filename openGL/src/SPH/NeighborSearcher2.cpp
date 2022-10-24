#include "NeighborSearcher2.h"

NeighborSearcher2::NeighborSearcher2() :_resolutionX(0.0), _resolutionY(0.0), _numberOfParticles(0) {}

NeighborSearcher2::~NeighborSearcher2() {

}

void NeighborSearcher2::resetDataSize() {

	_data.resize(_numberOfParticles);

}

NeighborSearcher2::NeighborSearcher2(int resolutionX, int resolutionY, int numberOfParticles)
	:_resolutionX(resolutionX), _resolutionY(resolutionY), _numberOfParticles(numberOfParticles) {
	resetDataSize();
}

void NeighborSearcher2::clearData() {
	_data.clear();
}

bool NeighborSearcher2::IsXoverBorder(size_t idx) {
	if (idx < 0 || idx >= _resolutionX) {
		return true;
	}
	return false;
}

bool NeighborSearcher2::IsYoverBorder(size_t idx) {
	if (idx < 0 || idx >= _resolutionY) {
		return true;
	}
	return false;
}

bool NeighborSearcher2::IsNeighbor(Vector2& pos1, Vector2& pos2, const double& r) {
	auto dis = sqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()));
	if (dis < r) {
		return true;
	}
	return false;
}

void NeighborSearcher2::forEachNeighborGrid(Vector2& idx, size_t particleId, vector<vector<vector<size_t>>>& grids, const Vector2ArrayPtr positions) {

	//idx是待求格子的坐标
	size_t x = idx.x();
	size_t y = idx.y();

	if (!IsYoverBorder(y) && !IsXoverBorder(x)) {
		//如果该待求格子存在，那么取该格子里面的所有粒子，即currentParticles
		auto currentParticles = grids[x][y];
		for (auto iter = currentParticles.begin(); iter != currentParticles.end(); iter++) {
			auto pos1 = positions->lookAt(*iter);
			auto pos2 = positions->lookAt(particleId);
			if (*iter != particleId) {
				if (IsNeighbor(pos1, pos2, neighbor_radius) == true) {
					//保存的是相邻邻居的序号 
					_data[particleId].push_back(*iter);
				}
			}

		}
	}

}

void NeighborSearcher2::directSearch(const Vector2ArrayPtr positions) {
	size_t i = 0;
	size_t j = 0;
	for (auto iter1 = positions->iterBegin(); iter1 != positions->iterEnd(); iter1++) {
		j = i + 1;
		for (auto iter2 = iter1 + 1; iter2 != positions->iterEnd(); iter2++) {
			auto p1 = *iter1;
			auto p2 = *iter2;
			auto dis = p1.dis(p2);
			double r = 0.01;
			if (dis < r) {
				_data[i].push_back(j);
			}
			j++;
		}
		++i;


	}
}

void NeighborSearcher2::setNeiborList(const Vector2ArrayPtr positions) {
	clearData();
	resetDataSize();

	//grids里保存粒子映射后的编号
	vector<vector<vector<size_t>>> grids;

	//gridPositions保存了粒子的映射坐标，粒子在网格中的位置
	vector<Vector2> gridPositons;
	//对格子进行初始化
	grids.resize(_resolutionX);
	for (auto iter = grids.begin(); iter != grids.end(); iter++) {
		iter->resize(_resolutionY);
	}

	int particleIdx = 0;

	for (auto iter = positions->iterBegin(); iter != positions->iterEnd(); iter++) {
		//-----------------------------------！！！------------------------------
		double maxWidth = 2;
		double maxHeight = 2;
		double tempX = iter->x();
		double tempY = iter->y();
		//---------------------------------单元网格的大小------------------------
		double scaleX = maxWidth / _resolutionX;
		double scaleY = maxHeight / _resolutionY;
		//---------------------------------粒子位置位于那个网格------------------
		size_t gridX = floor(tempX / scaleX);
		size_t gridY = floor(tempY / scaleY);

		size_t k = 1;

		if (gridX >= _resolutionX) {
			gridX = _resolutionX - k;
		}

		if (gridX < 0) {
			gridX = 0;
		}

		if (gridY >= _resolutionY) {
			gridY = _resolutionY - k;
		}

		if (gridY < 0) {
			gridY = 0;
		}
		Vector2 pos(gridX, gridY);
		gridPositons.push_back(pos);

		grids[gridX][gridY].push_back(particleIdx);

		particleIdx++;
	}

	particleIdx = 0;
	for (auto iter = positions->iterBegin(); iter != positions->iterEnd(); iter++) {

		auto current = gridPositons[particleIdx];
		Vector2 top(current.x(), current.y() + 1);
		Vector2 down(current.x(), current.y() - 1);
		Vector2 left(current.x() - 1, current.y());
		Vector2 right(current.x() + 1, current.y());
		Vector2 leftTop(current.x() - 1, current.y() + 1);
		Vector2 rightTop(current.x() + 1, current.y() + 1);
		Vector2 leftDown(current.x() - 1, current.y() - 1);
		Vector2 rightDown(current.x() + 1, current.y() - 1);

		forEachNeighborGrid(current, particleIdx, grids, positions);
		forEachNeighborGrid(top, particleIdx, grids, positions);
		forEachNeighborGrid(down, particleIdx, grids, positions);
		forEachNeighborGrid(left, particleIdx, grids, positions);
		forEachNeighborGrid(right, particleIdx, grids, positions);
		forEachNeighborGrid(leftTop, particleIdx, grids, positions);
		forEachNeighborGrid(rightTop, particleIdx, grids, positions);
		forEachNeighborGrid(leftDown, particleIdx, grids, positions);
		forEachNeighborGrid(rightDown, particleIdx, grids, positions);

		particleIdx++;
	}
}

vector<vector<size_t>>& NeighborSearcher2::neighBors() {
	return _data;
}


