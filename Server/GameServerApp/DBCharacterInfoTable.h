#pragma once
#include <GameServerNet/DBQuery.h>

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
		m_UserIndx = -1;
		m_Nickname = "";
		m_ClassName = "";
		m_HP = 0;
		m_MP = 0;
		m_ATK = 0;
	}
	DBCharacterInfoTableRow(int _Idx,
		int _UserIndx,
		std::string _Nickname,
		std::string _ClassName,
		float _HP,
		float _MP,
		float _ATK)
	{
		m_Idx = _Idx;
		m_UserIndx = _UserIndx;
		m_Nickname = _UserIndx;
		m_ClassName = _ClassName;
		m_HP = _HP;
		m_MP = _HP;
		m_ATK = _ATK;
	}
public:
	int m_Idx;
	int m_UserIndx;
	std::string m_Nickname;
	std::string m_ClassName;
	float m_HP;
	float m_MP;
	float m_ATK;


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
	std::shared_ptr<DBCharacterInfoTableRow> m_RowData;

public:
	DBCharacterInfoTable_SelectCharacterInfoQuery(int _UserIdx);
	bool DoQuery() override;

};


class DBCharacterInfoTable_InsertCharacterInfoQuery : public DBQuery, DBCharacterInfoTable
{
public:

public:
	DBCharacterInfoTable_InsertCharacterInfoQuery(const std::string& _ID, const std::string& _PW);
	bool DoQuery() override;

};
