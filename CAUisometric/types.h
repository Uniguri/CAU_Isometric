#pragma once
struct Coord
{
	int x, y;
};

// 0�� ���� �Ʒ�, 1�� ������ �Ʒ�, 2�� ������ ��, 3�� ���� ����.
struct Square
{
	Coord p0, p1, p2, p3;
};

// 0�� ���� �Ʒ�, 1�� ������ �Ʒ�, 2�� ������
struct Triangle
{
	Coord p0, p1, p2;
};

// 0�� ������, 1�� ������ ��, 2�� ���� ��
struct ReverseTriangle
{
	Coord p0, p1, p2;
};