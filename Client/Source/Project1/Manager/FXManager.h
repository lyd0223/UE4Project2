#pragma once
#include <stack>

class FXManager
{
private:
	FXManager();
	~FXManager();

private:
	static FXManager* m_Instance;
	static std::stack<class NormalEffect*> m_FXPool;

public:
	static FXManager* GetInst() 
	{
		if(!m_Instance)
		{
			m_Instance = new FXManager();
		}
		return m_Instance;
	}
public:
	static NormalEffect* GetFX()
	{
		if(m_FXPool.empty())
		{
		}
	}
	static void ReturnObejct(NormalEffect* FX)
	{
		
	}
};
