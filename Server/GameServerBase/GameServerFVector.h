#pragma once

struct FVector
{
public:
	float m_X;
	float m_Y;
	float m_Z;

public:
	int GetDataSize()
	{
		return (sizeof(float) * 3);
	}
};