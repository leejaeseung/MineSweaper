#include "MineSweeper.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
using std::make_unique;

MineSweeper::MineSweeper()
    :started(false), saved(false), end(false), map(nullptr), saveIdx(0)
{
    srand(time(NULL));
}

void MineSweeper::play()
{
    while (1)
    {
        auto clk_pos = clk.getPos();

        if (started) {
            switch (UM.gameProcess(clk_pos.first, clk_pos.second, end, &saveIdx)) {
            case 0:
                //��ȿ���� ���� �� Ŭ�� �� or ������ ����ǰ� �� Ŭ�� ��
                break;
            case 1:
                //�� Ŭ��
                UM.tightXY(&clk_pos.first, &clk_pos.second);
                //Ŀ���� ��ǥ�� �������� ������.

                switch (map->click(clk_pos.first, clk_pos.second)) {
                    //Ŭ��
                case 0:
                    break;
                case -1:
                    //������ �����.
                    UM.printMap(const_cast<Map&>(*map));
                    end = true;
                    replayMap.push_back(*map);
                    replay();
                    //���÷���
                    break;
                case 1:
                    UM.printMap(const_cast<Map&>(*map));
                    replayMap.push_back(*map);
                    break;
                
                }
                break;
            case -1:
                //�޴��� ���ư�.
                started = false;
                UM.reset();
                UM.printMenu(saved);
                break;
            case 2:

                break;
            default:
                break;
           }
        }
        else {
            switch (UM.menuProcess(clk_pos.first, clk_pos.second, saved)) {
            case 0:
                break;
            case 1:
                map.reset((new Map(UM.getMode(), UM.getWidth(), UM.getHeight())));
                //���� ���� ����.
                gameStart();
                break;
            case 2:
                gameStart();
                break;
            default:
                break;
            }
        }
    }
}

void MineSweeper::replay()
{
    for (auto nowMap : replayMap) {
        Sleep(1000);
        UM.printMap(nowMap);
    }
}

void MineSweeper::gameStart()
{
    started = true;
    end = false;
    UM.printMap(const_cast<Map&>(*map));
    replayMap.clear();
    replayMap.push_back(*map);
}
