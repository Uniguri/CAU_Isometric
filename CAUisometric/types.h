#pragma once
struct Coord
{
	int x, y;
};

// 0이 왼쪽 아래, 1이 오른쪽 아래, 2가 오른쪽 위, 3은 왼쪽 위임.
struct Square
{
	Coord p0, p1, p2, p3;
};

// 0이 왼쪽 아래, 1이 오른쪽 아래, 2가 꼭짓점
struct Triangle
{
	Coord p0, p1, p2;
};

// 0이 꼭짓점, 1이 오른쪽 위, 2가 왼쪽 위
struct ReverseTriangle
{
	Coord p0, p1, p2;
};