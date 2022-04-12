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

	template<typename T>
	void WriteUserData(const T _Value)
	{
		Write(reinterpret_cast<const void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}


	template<typename T>
	void WriteVector(std::vector<T>& _Value)
	{
		operator<<(static_cast<int>(_Value.size()));
		for (size_t i = 0; i < _Value.size(); i++)
		{
			_Value[i].Serialize(*this);
			// Write(reinterpret_cast<const void*>(&_Value[i]), static_cast<unsigned int>(sizeof(T)));
		}
	}

	void Read(void* _Data, unsigned int _Size);

	template<typename T>
	void ReadUserData(T& _Value)
	{
		Read(reinterpret_cast<void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	template<typename T>
	void ReadVector(std::vector<T>& _Value)
	{
		int Size;
		operator>>(Size);
		_Value.resize(Size);
		for (size_t i = 0; i < _Value.size(); i++)
		{
			_Value[i].DeSerialize(*this);
		}
	}

	void operator<<(const std::string& _Value);
	void operator<<(const int _Value);
	void operator<<(const unsigned int _Value);
	void operator<<(const float _Value);

	void operator>>(std::string& _Value);
	void operator>>(int& _Value);
	void operator>>(unsigned int& _Value);
	void operator>>(float& _Value);
};
