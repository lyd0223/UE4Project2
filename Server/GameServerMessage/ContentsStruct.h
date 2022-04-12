#pragma once
#include <GameServerBase/GameServerSerializer.h>

struct FCharacterInfo
{
	int m_Idx;
	int m_UserIdx;
	std::string m_Nickname;
	std::string m_ClassName;
	float m_HP;
	float m_MP;
	float m_ATK;

public:
	int GetDataSize()
	{
		return (4 * 8) + 4 + static_cast<int>(m_Nickname.size());
	}

	void Serialize(GameServerSerializer& _Ser)
	{
		_Ser << m_Idx;
		_Ser << m_UserIdx;
		_Ser << m_Nickname;
		_Ser << m_ClassName;
		_Ser << m_HP;
		_Ser << m_MP;
		_Ser << m_ATK;
	}

	void DeSerialize(GameServerSerializer& _Ser)
	{
		_Ser >> m_Idx;
		_Ser >> m_UserIdx;
		_Ser >> m_Nickname;
		_Ser >> m_ClassName;
		_Ser >> m_HP;
		_Ser >> m_MP;
		_Ser >> m_ATK;
	}
};