#pragma once
#include <memory>
#include <vector>
using std::unique_ptr;
using std::vector;

class Map {
	private:
		int mode;
		int width;
		int height;
		int mineCnt;		//��ġ�� ������ ����
		int openCnt;		//�÷��̾ �� ĭ�� ����
		int allCnt;			//��ü ĭ�� ����
		unique_ptr<unique_ptr<int[]>[]> map;
		//-1 ~ 9 �̸� ����ڿ��� ������ �����̰�, 10 ~ 20 �̸� ������ �����̴�.
		//������ ���¿��� 11�� ���ָ� �������� �ǰ�, ������ ���°� -1 �̸� �����̴�.
		vector<Map> replayMap;
		const int mv_x[8] = { 0, 0, -2, -2, -2, 2, 2, 2 };
		const int mv_y[8] = { -1, 1, -1, 0, 1, -1, 0, 1 };
		int checkMine(const int& x, const int& y);
		void end();
		int unfold(const int& x, const int& y);
	public:
		Map() = default;
		Map(const int& mode, const int& width, const int& height);
		~Map() = default;
		Map(const Map& m);
		int click(const int& x, const int& y);
		unique_ptr<int[]>& operator[](const int& idx) const;
		Map& operator=(const Map& myMap) noexcept;
		Map& operator=(Map&& myMap) noexcept;
		double getAchiveRate() const;
		int getWidth();
		int getHeight();
		int getMode();
		int getWidth() const;
		int getHeight() const;
		int getMode() const;
		vector<Map> getReplayMap() const;
};