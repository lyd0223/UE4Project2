#pragma once

/*
Usage		:  DB에 날릴 Query들의 부모클래스.
Category	:  DB
Description :  DBQuery를 상속받은 모든 클래스는 무조건 DoQuery를 가져야함.
			   추상클래스
*/

class DBConnecter;
class DBQuery
{
public: //Default
	DBQuery();
	DBQuery(const char* _QueryText);
	virtual ~DBQuery();

	DBQuery(const DBQuery& _Other) = delete;
	DBQuery(DBQuery&& _Other)		noexcept = delete;
	DBQuery& operator=(const DBQuery& _Other) = delete;
	DBQuery& operator=(DBQuery&& _Other)		= delete;

protected: //Member Value
	DBConnecter* m_DBConnecter;
	const char* m_QueryText;
	
	
public:  //Member Function
	//쿼리 실행하는함수. DBQuery를 상속받은 모든 클래스는 무조건 DoQuery를 가져야함.
	virtual bool DoQuery() = 0;
};

