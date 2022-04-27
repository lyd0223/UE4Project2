#pragma once
#include <GameServerNet/DBQuery.h>
#include <GameServerMessage/ContentsStruct.h>
/*
Usage		:  DB CharacterInfo Table 쿼리용
Category	:  DB
Description :  CharacterInfo Table관련 DB쿼리 날리고 그에 관련된 일들을 하는 클래스들.
*/


class DBCharacterInfoTableRow
{
public:
	DBCharacterInfoTableRow()
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
		m_InventoryData.reserve(800);
	}
	DBCharacterInfoTableRow(int _Idx, int _UserIdx, std::string _Nickname, std::string _ClassName,
		int _LV, int _EXP,
		float _HP, float _SP, float _ATK, float _DEF,
		float _AttackSpeed, float _MoveSpeed, std::vector<unsigned char> _InventoryData)
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
		m_InventoryData = _InventoryData;
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
	std::vector<unsigned char> m_InventoryData;


};


class DBCharacterInfoTable
{
public: //Default
	DBCharacterInfoTable();
	~DBCharacterInfoTable();

	DBCharacterInfoTable(const DBCharacterInfoTable& _Other) = delete;
	DBCharacterInfoTable(DBCharacterInfoTable&& _Other)		noexcept = delete;
	DBCharacterInfoTable& operator=(const DBCharacterInfoTable& _Other) = delete;
	DBCharacterInfoTable& operator=(DBCharacterInfoTable&& _Other) = delete;

private: //Member Value
	static std::string m_TableName;

public:  //Member Function
};


class DBCharacterInfoTable_SelectCharacterInfoQuery : public DBQuery, DBCharacterInfoTable
{
public:
	int m_UserIdx;
	std::vector<std::shared_ptr<DBCharacterInfoTableRow>> m_RowDataList;

public:
	DBCharacterInfoTable_SelectCharacterInfoQuery(int _UserIdx);
	bool DoQuery() override;

};


class DBCharacterInfoTable_InsertCharacterInfoQuery : public DBQuery, DBCharacterInfoTable
{
public:

public:
	DBCharacterInfoTable_InsertCharacterInfoQuery(int _UserIdx, const FCharacterInfo& _CharacterInfo);
		//std::string _Nickname, std::string _ClassName,
		//int _LV, int _EXP, float _HP, float _SP, float _ATK, float _DEF, float _AttackSpeed, float _MoveSpeed,
		//std::vector<unsigned char> _InventoryData);
	bool DoQuery() override;

};

class DBCharacterInfoTable_UpdateCharacterInfoQuery : public DBQuery, DBCharacterInfoTable
{
public:

public:
	DBCharacterInfoTable_UpdateCharacterInfoQuery(int _UserIdx, const FCharacterInfo& _CharacterInfo);
	bool DoQuery() override;

};
