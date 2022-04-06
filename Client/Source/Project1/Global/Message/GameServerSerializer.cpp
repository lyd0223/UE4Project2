#include "GameServerSerializer.h"

GameServerSerializer::GameServerSerializer()
{
	m_Offset = 0;
	m_Data.resize(1024);
}

GameServerSerializer::GameServerSerializer(const std::vector<unsigned char>& _Data)
{
	m_Offset = 0;
	m_Data = _Data;
}

void GameServerSerializer::Write(const void* _Data, unsigned int _Size)
{
	memcpy_s( &m_Data[m_Offset], _Size, _Data, _Size);
	m_Offset += _Size;
	
}

void GameServerSerializer::Read(void* _Data, unsigned int _Size)
{
	memcpy_s(_Data, _Size, &m_Data[m_Offset], _Size);
	m_Offset += _Size;
}

void GameServerSerializer::operator<<(const std::string& _Value)
{
	operator<<(static_cast<int>(_Value.size()));
	Write(reinterpret_cast<const void*>(&_Value[0]), static_cast<unsigned int>(_Value.size()));
	
}
void GameServerSerializer::operator<<(const int _Value)
{
	Write(&_Value, sizeof(int));
}
void GameServerSerializer::operator<<(const unsigned int _Value)
{
	Write(&_Value, sizeof(unsigned int));
}

void GameServerSerializer::operator>>(std::string& _Value)
{
	int size = 0;
	operator>>(size);
	_Value.resize(size);
	Read(&_Value[0], size);
}
void GameServerSerializer::operator>>(int& _Value)
{
	Read(&_Value, sizeof(int));
}
void GameServerSerializer::operator>>(unsigned int& _Value)
{
	Read(&_Value, sizeof(unsigned int));
}
