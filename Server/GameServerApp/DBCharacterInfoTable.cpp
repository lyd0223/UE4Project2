#include "PreCompile.h"
#include "DBCharacterInfoTable.h"

#include <GameServerNet/DBConnecter.h>
#include <GameServerBase/GameServerDebug.h>

std::string DBCharacterInfoTable::m_TableName = "characterinfo";
DBCharacterInfoTable::DBCharacterInfoTable()
{

}

DBCharacterInfoTable::~DBCharacterInfoTable()
{

}


DBCharacterInfoTable_SelectCharacterInfoQuery::DBCharacterInfoTable_SelectCharacterInfoQuery(int _UserIdx)
{
	std::string str = "SELECT Idx,UserIdx,Nickname,ClassName,LV,HP,MP,ATK FROM unrealserver.characterinfo WHERE UserIdx = '" 
		+ std::to_string(_UserIdx) + "'";
	m_QueryText = _strdup(str.c_str());
	m_UserIdx = _UserIdx;
}

bool DBCharacterInfoTable_SelectCharacterInfoQuery::DoQuery()
{
	int __stdcall result = mysql_query(m_DBConnecter->GetMYSQL(), m_QueryText);
	if (result != 0)
	{
		std::string ErrorStr = mysql_error(m_DBConnecter->GetMYSQL());
		GameServerDebug::LogError("QueryError : " + ErrorStr);
		return false;
	}

	//DB에서 불러온 데이터 TableRow에 저장.
	MYSQL_RES* MysqlResult = mysql_store_result(m_DBConnecter->GetMYSQL());
	MYSQL_ROW MysqlRow;
	while ((MysqlRow = mysql_fetch_row(MysqlResult)) != NULL)
	{
		m_RowDataList.push_back(std::make_shared<DBCharacterInfoTableRow>(std::stoi(MysqlRow[0]), std::stoi(MysqlRow[1]),
			MysqlRow[2], MysqlRow[3], std::stoi(MysqlRow[4]), std::stof(MysqlRow[5]), std::stof(MysqlRow[6]), std::stof(MysqlRow[7])));

	}

	return true;
}




DBCharacterInfoTable_InsertCharacterInfoQuery::DBCharacterInfoTable_InsertCharacterInfoQuery(std::string _NickName)
{
	//std::string str = "INSERT INTO unrealserver.characterinfo (ID,PW) VALUES ('" + _ID + "','" + _PW + "');";
	//m_QueryText = _strdup(str.c_str());
	//m_ID = _ID;
	//m_PW = _PW;
}

bool DBCharacterInfoTable_InsertCharacterInfoQuery::DoQuery()
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