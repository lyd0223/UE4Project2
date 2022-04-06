#pragma once
#include <vector>
#include <string>

class GameServerSerializer
{
public:
	GameServerSerializer();
	GameServerSerializer(const std::vector<unsigned char>& _Data);

private:
	unsigned int m_Offset;
	std::vector<unsigned char> m_Data;

public:
	const std::vector<unsigned char>& GetData() const
	{
		return m_Data;
	}

public:
	void Write(const void* _Data, unsigned int _Size);
	void Read(void* _Data, unsigned int _Size);

	void operator<<(const std::string& _Value);
	void operator<<(const int _Value);
	void operator<<(const unsigned int _Value);

	void operator>>(std::string& _Value);
	void operator>>(int& _Value);
	void operator>>(unsigned int& _Value);
};
