#pragma once

/*
Usage		:  ��� Ŭ���� �⺻.  
Category	:  Object 
Description :  ������Ʈ ��ӿ�.
*/

class GameServerUser
{
public: //Default
	GameServerUser();
	~GameServerUser();

	GameServerUser(const GameServerUser& _Other) = delete;
	GameServerUser(GameServerUser&& _Other)		noexcept = delete;

protected:
	GameServerUser& operator=(const GameServerUser& _Other) = delete;
	GameServerUser& operator=(GameServerUser&& _Other)		= delete;

private: //Member Value
	std::string m_ID;
	
public: // GetSet Function
	inline void SetID(const std::string& _ID)
	{
		m_ID = _ID;
	}
	inline std::string GetID()
	{
		return m_ID;
	}

public:  //Member Function
	
};

