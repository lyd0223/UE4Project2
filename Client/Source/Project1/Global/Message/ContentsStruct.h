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
		m_EXP = 0;
		m_HP = 0.f;
		m_SP = 0.f;
		m_ATK = 0.f;
		m_DEF = 0.f;
		m_AttackSpeed = 0.f;
		m_MoveSpeed = 0.f;
	}
	FCharacterInfo(int _Idx, int _UserIdx, std::string _Nickname, std::string _ClassName, 
		int _LV, int _EXP,
		float _HP, float _SP, float _ATK , float _DEF,
		float _AttackSpeed, float _MoveSpeed)
	{
		m_Idx = _Idx;
		m_UserIdx = _UserIdx;
		m_Nickname = _Nickname;
		m_ClassName = _ClassName;
		m_LV = _LV;
		m_EXP = _EXP;
		m_HP = _HP;
		m_SP = _SP;
		m_ATK = _ATK;
		m_DEF = _DEF;
		m_AttackSpeed = _AttackSpeed;
		m_MoveSpeed = _MoveSpeed;
	}

public:
	int m_Idx;
	int m_UserIdx;
	std::string m_Nickname;
	std::string m_ClassName;
	int m_LV;
	int m_EXP;
	float m_HP;
	float m_SP;
	float m_ATK;
	float m_DEF;
	float m_AttackSpeed;
	float m_MoveSpeed;

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
		_Ser << m_EXP;
		_Ser << m_HP;
		_Ser << m_SP;
		_Ser << m_ATK;
		_Ser << m_DEF;
		_Ser << m_AttackSpeed;
		_Ser << m_MoveSpeed;
	}

	void DeSerialize(GameServerSerializer& _Ser)
	{
		_Ser >> m_Idx;
		_Ser >> m_UserIdx;
		_Ser >> m_Nickname;
		_Ser >> m_ClassName;
		_Ser >> m_LV;
		_Ser >> m_EXP;
		_Ser >> m_HP;
		_Ser >> m_SP;
		_Ser >> m_ATK;
		_Ser >> m_DEF;
		_Ser >> m_AttackSpeed;
		_Ser >> m_MoveSpeed;
	}
};