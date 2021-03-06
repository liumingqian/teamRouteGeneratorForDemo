// teamGenerator.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include<string>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<iomanip>
using namespace std;
using std::ofstream;

struct Point {
	float x;
	float y;
	float z;
	Point(float _x, float _y, float  _z)
	{
		x = _x;
		y = _y; 
		z = _z;
	}
};
void Clamp(float x, float range)
{
	if (x <0 && x> -range)
	{
		x = -range;
	}
	if (x > 0 && x < range)
	{
		x = range;
	}
}
int main()
{
	string file_name;
	int numOfMember;//编队成员数量
	float minDis, maxDis;//编队中成员间距
	int numOfRow;
	cout << "原始文件名(不带txt） 编队成员数量 一排几个" << endl;
	while (cin >> file_name>>numOfMember>> numOfRow)
	{
		ifstream file_stream(file_name+".txt");
		if (!file_stream)
		{
			cout << "wrong filename" << endl;
			continue;
		}
		vector<Point>origin_points;
		while (!file_stream.eof())
		{
			double x,y,z;
			file_stream >> x >> y >> z;
			origin_points.push_back(Point(x,y,z));
		}
		file_stream.close();
		float xOffsetBase = 0;
		float yOffsetBase = 0;
		float xNegOffsetBase = 0;
		float yNegOffsetBase = 0;
		for (int i = 0,k=1; i < numOfMember; i++,k=-k)
		{
			ofstream o_stream(file_name + "_" + to_string(i) + ".txt");

			float xOffset = -k * (rand() % 100)*0.0000022;
			float yOffset = -k * (rand() % 100)*0.0000022;
			Clamp(xOffset, 0.0003);
			Clamp(yOffset, 0.0003);
			for (int j = 0; j < origin_points.size(); j++)
			{
				if (j == origin_points.size() - 1)
				{
					o_stream << setprecision(14) << origin_points[j].x + xOffset + xOffsetBase << " " << origin_points[j].y + yOffset + yOffsetBase << " " << origin_points[j].z;
				}
				else
				{
					o_stream << setprecision(14) << origin_points[j].x + xOffset + xOffsetBase << " " << origin_points[j].y + yOffset + yOffsetBase << " " << origin_points[j].z << endl;
				}
			}
			if (k == 1)
			{
				xOffsetBase += xOffset;
				yOffsetBase += yOffset;
			}
			else {
				xNegOffsetBase += xOffset;
				yNegOffsetBase += yOffset;
			}

			if (i%numOfRow == 0)
			{
				xOffsetBase += 0.000001;
				yOffsetBase = 0;
				xNegOffsetBase += 0.000001;
				yNegOffsetBase = 0;
			}

			o_stream.close();
		}
		cout << "原始文件名 编队成员数量 一排几个" << endl;
	}
	
	return 0;
}

