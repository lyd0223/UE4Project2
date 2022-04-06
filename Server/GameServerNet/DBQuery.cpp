#include "PreCompile.h"
#include "DBQuery.h"
#include "DBConnecter.h"

DBQuery::DBQuery()
{
	m_DBConnecter = GameServerThread::GetLocalData<DBConnecter>();
	m_QueryText = "";
}

DBQuery::DBQuery(const char* _QueryText)
{
	m_DBConnecter = GameServerThread::GetLocalData<DBConnecter>();
	m_QueryText = _QueryText;
}

DBQuery::~DBQuery()
{

}
