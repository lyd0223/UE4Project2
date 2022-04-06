#pragma once

/*
Usage		:  DB연결담당
Category	:  
Description :  DB연결
*/



class DBStmt
{

};

class DBStmtResult
{

};

class DBConnecter
{
public: //Default
	DBConnecter();
	~DBConnecter();

	DBConnecter(const DBConnecter& _Other) = delete;
	DBConnecter(DBConnecter&& _Other)		noexcept = delete;
	DBConnecter& operator=(const DBConnecter& _Other) = delete;
	DBConnecter& operator=(DBConnecter&& _Other)		= delete;

private: //Member Value
	MYSQL* m_MYSQL;

	std::string m_Host;
	std::string m_ID;
	std::string m_PW;
	std::string m_SchemaName;
	unsigned int m_Port;
	
public: //Get,Set function
	inline bool IsConnected()
	{
		return m_MYSQL != nullptr;
	}

	inline MYSQL* GetMYSQL()
	{
		return m_MYSQL;
	}

public:  //Member Function
	//std::unique_ptr<DBStmt> CreateDBStmt(std::string_view _DBQuery);
	
	bool Connect();
	bool Connect(const std::string& _Host, const std::string& _ID, 
		const std::string& _PW, const std::string& _SchemaName, unsigned int _Port);

	std::string GetLastErrorStr();
	
};
