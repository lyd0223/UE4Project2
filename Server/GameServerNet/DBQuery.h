#pragma once

/*
Usage		:  DB�� ���� Query���� �θ�Ŭ����.
Category	:  DB
Description :  DBQuery�� ��ӹ��� ��� Ŭ������ ������ DoQuery�� ��������.
			   �߻�Ŭ����
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
	//���� �����ϴ��Լ�. DBQuery�� ��ӹ��� ��� Ŭ������ ������ DoQuery�� ��������.
	virtual bool DoQuery() = 0;
};

