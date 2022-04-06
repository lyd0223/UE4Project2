#pragma once
#include <GameServerNet/DBQuery.h>

/*
Usage		:  모든 클래스 기본.  
Category	:  Object 
Description :  오브젝트 상속용.
*/


//User라 봐도 무방하지만, DBTable관련해서만 쓰인다.
class DBUserInfoTableRow
{
public:
	DBUserInfoTableRow()
	{
		m_Index = NULL;
		m_ID = "";
		m_PW = "";
	}
	DBUserInfoTableRow(int _Index, const std::string& _ID, const std::string& _PW)
	{
		m_Index = _Index;
		m_ID = _ID;
		m_PW = _PW;
	}
public:
	int m_Index;
	std::string m_ID;
	std::string m_PW;
	
public:
	
};


class DBUserInfoTable
{
public: //Default
	DBUserInfoTable();
	~DBUserInfoTable();

	DBUserInfoTable(const DBUserInfoTable& _Other) = delete;
	DBUserInfoTable(DBUserInfoTable&& _Other)		noexcept = delete;
	DBUserInfoTable& operator=(const DBUserInfoTable& _Other) = delete;
	DBUserInfoTable& operator=(DBUserInfoTable&& _Other)		= delete;

private: //Member Value
	static std::string m_TableName;
	
public:  //Member Function
};


class UserInfoTable_SelectIDQuery : public DBQuery, DBUserInfoTable
{
public:
	std::string m_ID;
	std::shared_ptr<DBUserInfoTableRow> m_RowData;

public:
	UserInfoTable_SelectIDQuery(const std::string& _ID);
	bool DoQuery() override;
	
};


class UserInfoTable_InsertUserInfoQuery : public DBQuery, DBUserInfoTable
{
public:
	std::string m_ID;
	std::string m_PW;

public:
	UserInfoTable_InsertUserInfoQuery(const std::string& _ID, const std::string& _PW);
	bool DoQuery() override;

};
