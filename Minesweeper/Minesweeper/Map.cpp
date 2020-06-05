#include "Map.h"
#include <memory.h>
using std::make_unique;

Map::Map(const int& mode, const int& width, const int& height)
    :mode(mode), width(width), height(height), mineCnt((double)(width* height)* ((double)mode / 10)), openCnt(0), allCnt(width* height), map(make_unique<unique_ptr<int[]>[]>(height))
{
    for (int i = 0; i < height; i++)
    {
        map[i] = make_unique<int[]>(width * 2);
        for (int j = 0; j < width * 2; j++)
        {
            map[i][j] = 0;
        }
    }

    for (int i = 0; i < mineCnt; i++)
    {
        int x = rand() % (width * 2);
        int y = rand() % height;

        if (map[y][x] == 10 || x % 2 == 1) {
            //���δ� �� ĭ�� 2byte�̹Ƿ� ¦�� ĭ�� �Ǵ�, ���ڰ� �̹� ������ �ٽ� ����
            i--;
            continue;
        }

        map[y][x] = 10;
        map[y][x + 1] = 10;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width * 2; j += 2)
        {
            if (map[i][j] != 10)
                map[i][j] = checkMine(j, i);
        }
    }
}

int Map::checkMine(const int& x, const int& y)
//�� ĭ�� �������� �ֺ��� ���ڰ� �� ������ üũ.
{
    int cnt = 0;

    for (int i = 0; i < 8; i++)
    {
        int nx = x + mv_x[i];
        int ny = y + mv_y[i];

        if (nx < 0 || ny < 0 || nx >= width * 2 || ny >= height) continue;

        if (map[ny][nx] == 10)
            cnt++;
    }

    return cnt + 11;
}

void Map::end()
//������ ������ �� ��� ���ڸ� ������.
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width * 2; j++)
        {
            if (map[i][j] == 10) {
                map[i][j] = -1;
                map[i][j + 1] = -1;
            }
        }
    }
}

Map::Map(const Map& m)
    :mode(m.mode), width(m.width), height(m.height), mineCnt(m.mineCnt), openCnt(m.openCnt), allCnt(m.allCnt), map(make_unique<unique_ptr<int[]>[]>(height))
{
    for (int i = 0; i < height; i++)
    {
        map[i] = make_unique<int[]>(width * 2);
        for (int j = 0; j < width * 2; j++)
        {
            map[i][j] = m[i][j];
        }
    }
}

int Map::click(const int& x, const int& y)
{
    if (map[y][x] == 10 || map[y][x + 1] == 10) {       //���ڸ� ������ ��
        end();
        return 3;
    }
    if (map[y][x] < 11)  return 0;  //�̹� ������ ���̶��
    map[y][x] -= 11;                //Ŭ���� ���� ������.
    map[y][x + 1] -= 11;
    openCnt++;

    if (allCnt - openCnt == mineCnt) {
        // Ŭ������ ���
        end();
        return 2;
    }

    if (map[y][x] == 0) {
        for (int i = 0; i < 8; i++)
        {
            int nx = x + mv_x[i];
            int ny = y + mv_y[i];

            if (nx < 0 || ny < 0 || nx >= width * 2 || ny >= height) continue;      //���� ���� ������ ������ �ʰ�
            if (map[ny][nx] == 10)   continue;          //���ڰ� �ִ� ���� Ž��x
            click(nx, ny);
        }
    }
    return 1;   //�ϳ��� �����ٸ�
}

unique_ptr<int[]>& Map::operator[](const int& idx) const
{
    if(idx >= 0 && idx < width)
        return map[idx];
    else {
        exit(0);
    }
}

Map& Map::operator=(const Map& myMap) noexcept
{
    if (this == &myMap)  return *this;

    mode = myMap.mode;
    width = myMap.width;
    height = myMap.height;
    mineCnt = myMap.mineCnt;
    openCnt = myMap.openCnt;
    allCnt = myMap.allCnt;

    map = make_unique<unique_ptr<int[]>[]>(height);
    for (int i = 0; i < height; i++)
    {
        map[i] = make_unique<int[]>(width * 2);
        for (int j = 0; j < width * 2; j++)
        {
            map[i][j] = myMap[i][j];
        }
    }

    return *this;
}

double Map::getAchiveRate() const
{
    //������� ��ȯ
    return ((double)(openCnt) / (double)(allCnt - mineCnt)) * 100.0;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}
