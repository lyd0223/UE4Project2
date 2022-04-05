#pragma once

class ObjectPoolManager
{
	
private:
	ObjectPoolManager();
	~ObjectPoolManager();

private:
	static ObjectPoolManager* m_Instance;

public:
	static ObjectPoolManager* GetInst()
	{
		if(m_Instance == nullptr)
		{
			m_Instance = new ObjectPoolManager();
		}
		return m_Instance;
	}

private:
};
