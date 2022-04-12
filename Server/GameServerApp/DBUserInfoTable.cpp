#include "PreCompile.h"
#include "DBUserInfoTable.h"
#include <GameServerNet/DBConnecter.h>
#include <GameServerBase/GameServerDebug.h>

std::string DBUserInfoTable::m_TableName = "userinfo";
DBUserInfoTable::DBUserInfoTable()
{

}

DBUserInfoTable::~DBUserInfoTable()
{

}


UserInfoTable_SelectIDQuery::UserInfoTable_SelectIDQuery(const std::string& _ID, const std::string& _PW)
{
	std::string str = "SELECT Idx, ID, PW FROM unrealserver.userinfo WHERE ID = '" + _ID + "' LIMIT 1";
	m_QueryText = _strdup(str.c_str());
	m_ID = _ID;
	m_PW = _PW;
	m_RowData = nullptr;
}

bool UserInfoTable_SelectIDQuery::DoQuery()
{
	int __stdcall result = mysql_query(m_DBConnecter->GetMYSQL(), m_QueryText);
	if (result != 0)
	{
		std::string ErrorStr = mysql_error(m_DBConnecter->GetMYSQL());
		GameServerDebug::LogError("QueryError : " + ErrorStr);
		return false;
	}
	
	return true;
}


bool UserInfoTable_SelectIDQuery::CheckPW()
{
	MYSQL_RES* MysqlResult = mysql_store_result(m_DBConnecter->GetMYSQL());
	MYSQL_ROW MysqlRow;
	while ((MysqlRow = mysql_fetch_row(MysqlResult)) != NULL)
	{
		if (m_PW != MysqlRow[2])
			return false;

		m_RowData = std::make_shared<DBUserInfoTableRow>(std::stoi(MysqlRow[0]), MysqlRow[1], MysqlRow[2]);
	}

	return true;
}


UserInfoTable_InsertUserInfoQuery::UserInfoTable_InsertUserInfoQuery(const std::string& _ID, const std::string& _PW)
{
	std::string str = "INSERT INTO unrealserver.userinfo (ID,PW) VALUES ('" + _ID + "','" + _PW + "');";
	m_QueryText = _strdup(str.c_str());
	m_ID = _ID;
	m_PW = _PW;
}

bool UserInfoTable_InsertUserInfoQuery::DoQuery()
{
	int __stdcall result = mysql_query(m_DBConnecter->GetMYSQL(), m_QueryText);
	if (result != 0)
	{
		std::string ErrorStr = mysql_error(m_DBConnecter->GetMYSQL());
		GameServerDebug::LogError("QueryError : " + ErrorStr);
		return false;
	}
	return true;
}