#pragma once
#include "GameServerSerializer.h"

struct FCharacterInfo
{
public:
	FCharacterInfo()
	{
		m_Idx = -1;
		m_UserIdx = -1;
		m_Nickname = "";
		m_ClassName = "";
		m_LV = 0;
		m_HP = 0;
		m_MP = 0;
		m_ATK = 0;
	}
	FCharacterInfo(int _Idx, int _UserIdx, std::string _Nickname, std::string _ClassName, int _LV,
		float _HP, float _MP, float _ATK)
	{
		m_Idx = _Idx;
		m_UserIdx = _UserIdx;
		m_Nickname = _Nickname;
		m_ClassName = _ClassName;
		m_LV = _LV;
		m_HP = _HP;
		m_MP = _MP;
		m_ATK = _ATK;
	}

public:
	int m_Idx;
	int m_UserIdx;
	std::string m_Nickname;
	std::string m_ClassName;
	int m_LV;
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
		_Ser << m_LV;
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
		_Ser >> m_LV;
		_Ser >> m_HP;
		_Ser >> m_MP;
		_Ser >> m_ATK;
	}
};