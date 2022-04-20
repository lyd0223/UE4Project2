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
	std::string str = "SELECT * FROM unrealserver.characterinfo WHERE UserIdx = '" 
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
		//DBCharacterInfoTableRow(int _Idx, int _UserIdx, std::string _Nickname, std::string _ClassName,
		//						int _LV, int _EXP,
		//						float _HP, float _SP, float _ATK, float _DEF,
		//						float _AttackSpeed, float _MoveSpeed, 
		//						std::vector<char> _InventoryData)
		m_RowDataList.push_back(std::make_shared<DBCharacterInfoTableRow>(
			std::stoi(MysqlRow[0]), std::stoi(MysqlRow[1]), MysqlRow[2], MysqlRow[3],
			std::stoi(MysqlRow[4]), std::stoi(MysqlRow[5]), 
			std::stof(MysqlRow[6]), std::stof(MysqlRow[7]), std::stof(MysqlRow[8]), std::stof(MysqlRow[9]),
			std::stof(MysqlRow[10]), std::stof(MysqlRow[11]), 
			MysqlRow[12]));
	}

	return true;
}




DBCharacterInfoTable_InsertCharacterInfoQuery::DBCharacterInfoTable_InsertCharacterInfoQuery(
	int _UserIdx, std::string _Nickname, std::string _ClassName,
	int _LV, int _EXP, float _HP, float _SP, float _ATK, float _DEF, float _AttackSpeed, float _MoveSpeed,
	std::vector<char> _InventoryData)
{
	std::string InventoryDataStr(_InventoryData.begin(), _InventoryData.end());
	std::string str = "INSERT INTO unrealserver.characterinfo (UserIdx,Nickname,ClassName,LV,EXP,HP,SP,ATK,DEF,AttackSpeed,MoveSpeed,InventoryData) VALUES ('"
		+ std::to_string(_UserIdx) + "','" 
		+ _Nickname + "','"
		+ _ClassName + "','"
		+ std::to_string(_LV) + "','"
		+ std::to_string(_EXP) + "','"
		+ std::to_string(_HP) + "','"
		+ std::to_string(_SP) + "','"
		+ std::to_string(_ATK) + "','"
		+ std::to_string(_DEF) + "','"
		+ std::to_string(_AttackSpeed) + "','"
		+ std::to_string(_MoveSpeed) + "',"
		+ InventoryDataStr + "');";
	m_QueryText = _strdup(str.c_str());
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