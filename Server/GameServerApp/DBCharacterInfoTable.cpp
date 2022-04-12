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
	std::string str = "SELECT _Idx,_UserIndx,_Nickname,_ClassName,_HP,_MP,_ATK FROM unrealserver.characterinfo WHERE ID = '" 
		+ std::to_string(_UserIdx) + "' LIMIT 1";
	m_QueryText = _strdup(str.c_str());
	m_UserIdx = _UserIdx;
	m_RowData = nullptr;
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

	return true;
}




DBCharacterInfoTable_InsertCharacterInfoQuery::DBCharacterInfoTable_InsertCharacterInfoQuery(const std::string& _ID, const std::string& _PW)
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