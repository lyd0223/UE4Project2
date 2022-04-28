#include "PreCompile.h"
#include "DBCharacterInfoTable.h"

#include <GameServerNet/DBConnecter.h>
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>

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
		//						std::vector<unsigned char> _InventoryData)
		
		std::string InventoryDataString = MysqlRow[12];
		std::vector<unsigned char> InventoryData(InventoryDataString.begin(), InventoryDataString.end());
		for (int i = 0; i < InventoryData.size(); i++)
		{
			InventoryData[i]--;
		}
		
		m_RowDataList.push_back(std::make_shared<DBCharacterInfoTableRow>(
			std::stoi(MysqlRow[0]), std::stoi(MysqlRow[1]), MysqlRow[2], MysqlRow[3],
			std::stoi(MysqlRow[4]), std::stoi(MysqlRow[5]), 
			std::stof(MysqlRow[6]), std::stof(MysqlRow[7]), std::stof(MysqlRow[8]), std::stof(MysqlRow[9]),
			std::stof(MysqlRow[10]), std::stof(MysqlRow[11]), 
			InventoryData));
	}

	return true;
}


//InsertQuery

DBCharacterInfoTable_InsertCharacterInfoQuery::DBCharacterInfoTable_InsertCharacterInfoQuery(
	int _UserIdx, const FCharacterInfo& _CharacterInfo)
{
	std::string str = "INSERT INTO unrealserver.characterinfo (UserIdx,Nickname,ClassName,LV,EXP,HP,SP,ATK,DEF,AttackSpeed,MoveSpeed,InventoryData) VALUES ('"
		+ std::to_string(_CharacterInfo.m_UserIdx) + "','"
		+ _CharacterInfo.m_Nickname + "','"
		+ _CharacterInfo.m_ClassName + "','"
		+ std::to_string(_CharacterInfo.m_LV) + "','"
		+ std::to_string(_CharacterInfo.m_EXP) + "','"
		+ std::to_string(_CharacterInfo.m_HP) + "','"
		+ std::to_string(_CharacterInfo.m_SP) + "','"
		+ std::to_string(_CharacterInfo.m_ATK) + "','"
		+ std::to_string(_CharacterInfo.m_DEF) + "','"
		+ std::to_string(_CharacterInfo.m_AttackSpeed) + "','"
		+ std::to_string(_CharacterInfo.m_MoveSpeed) + "','";
	std::string InventoryDataString(_CharacterInfo.m_InventoryData.begin(), _CharacterInfo.m_InventoryData.end());
	for (int i = 0; i < InventoryDataString.size(); i++)
	{
		InventoryDataString[i]++;
	}
	str += InventoryDataString + "');";

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

//DeleteQuery

DBCharacterInfoTable_DeleteCharacterInfoQuery::DBCharacterInfoTable_DeleteCharacterInfoQuery(const FCharacterInfo& _CharacterInfo)
{
	std::string str = "DELETE FROM unrealserver.characterinfo WHERE Idx = ";
	str += std::to_string(_CharacterInfo.m_Idx);
	str += ";";

	m_QueryText = _strdup(str.c_str());
}

bool DBCharacterInfoTable_DeleteCharacterInfoQuery::DoQuery()
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



DBCharacterInfoTable_UpdateCharacterInfoQuery::DBCharacterInfoTable_UpdateCharacterInfoQuery(
	int _UserIdx, const FCharacterInfo& _CharacterInfo)
{
	std::string str = "UPDATE unrealserver.characterinfo SET ";
	str += "LV = " + std::to_string(_CharacterInfo.m_LV);
	str += ",EXP = " + std::to_string(_CharacterInfo.m_EXP);
	str += ",HP = " + std::to_string(_CharacterInfo.m_HP);
	str += ",SP = " + std::to_string(_CharacterInfo.m_SP);
	str += ",ATK = " + std::to_string(_CharacterInfo.m_ATK);
	str += ",DEF = " + std::to_string(_CharacterInfo.m_DEF);
	str += ",AttackSpeed = " + std::to_string(_CharacterInfo.m_AttackSpeed);
	str += ",MoveSpeed = " + std::to_string(_CharacterInfo.m_MoveSpeed);
	std::string InventoryDataString(_CharacterInfo.m_InventoryData.begin(), _CharacterInfo.m_InventoryData.end());
	for (int i = 0; i < InventoryDataString.size(); i++)
	{
		InventoryDataString[i]++;
	}
	str += ",InventoryData = \"" + InventoryDataString + "\"";
	//utf-8로 할시 인식이 안된다. 인코딩방식을 Ansi로 바꾼다.
	std::string Nickname = "";
	GameServerString::UTF8ToAnsi(_CharacterInfo.m_Nickname, Nickname);
	str += " WHERE Nickname = \"" +_CharacterInfo.m_Nickname + "\";";
	
	m_QueryText = _strdup(str.c_str());
}

bool DBCharacterInfoTable_UpdateCharacterInfoQuery::DoQuery()
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