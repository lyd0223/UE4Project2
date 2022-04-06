#pragma once
#include "GameServerDebug.h"
#include <typeinfo>
#include <thread>

// �뵵 : 
// �з� :
// ÷�� : 
class GameServerThread
{
private: // Member Var
	std::thread thread_;
	static thread_local std::string Name_;
	static thread_local unsigned int Order_;
	static thread_local const std::type_info* LocalDataTypeInfo_;
	static thread_local std::vector<char> LocalData_;

public:
	static void SetName(const std::string& _Name)
	{
		Name_ = _Name;
		
		std::wstring Str;
		Str.assign(_Name.begin(), _Name.end());

		HRESULT hr = SetThreadDescription(GetCurrentThread(), Str.c_str());
	}

	static std::string GetName()
	{
		return Name_;
	}

	inline std::thread::id ThreadId() 
	{
		return thread_.get_id();
	}

	inline void SetThreadOrder(unsigned int _Order)
	{
		Order_ = _Order;
	}

	template<typename LocalDataType>
	static LocalDataType* SetLocalData()
	{
		if (nullptr != LocalDataTypeInfo_)
		{
			GameServerDebug::AssertDebugMsg("LocalData is not nullptr");
			return nullptr;
		}

		LocalDataTypeInfo_ = &typeid(LocalDataType);

		// c�� ������ �׳� ���� �ʿ��� �޸𸮸� ũ�⸸ŭ �����Ҵ��ϴ� �༮.
		// �����Լ� ���̺��� �ִ� Ŭ������ 
		LocalData_.resize(sizeof(LocalDataType));

		return new (&LocalData_[0]) LocalDataType();
	}

	template<typename LocalDataType>
	static LocalDataType* GetLocalData()
	{
		// 0. �����帶�� �ٸ� �����͸� ��������.
		// 1. �ٸ� �ڷ������� �ڵ带 ġ�� ������� ���ƾ� // RTTI
		// DBConnecter�Ҵ��ߴµ�. NetworkManager�� �޶�� �ϴ� ���.
		// 2. �Ϲ����� Ŭ������ �Ҵ��� �� �ֵ��� �����ڸ� ����.
		// 3. �̷� �� �𸮾��̳� �ֱ� �޸�Ʈ����� 
		//    list���� vector�� ����� �޸𸮸� �Ҵ��ϴ°� ��õ�ǰ� �־��
		//    ���� ������ ������ �ϰ� �ʹ�
		//    for Ƚ���� ���̴°� �ƴ϶�. �޸𸮸� ����ȭ�ϸ�
		//    �ӷµ� �´�.

		if (LocalDataTypeInfo_ != &typeid(LocalDataType))
		{
			GameServerDebug::AssertDebugMsg("Local Data Type Is Not Equal");
		}

		return (LocalDataType*)&LocalData_[0];
	}

public: // Default
	template <class _Fn, class... _Args, std::enable_if_t<!std::is_same_v<std::_Remove_cvref_t<_Fn>, std::thread>, int> = 0>
	explicit GameServerThread(std::string _name, _Fn&& _Fx, _Args&&... _Ax)
	{
		thread_ = std::thread(_Fx, _Ax...);
	}


	template <class _Fn, class... _Args, std::enable_if_t<!std::is_same_v<std::_Remove_cvref_t<_Fn>, std::thread>, int> = 0>
	explicit GameServerThread(_Fn&& _Fx, _Args&&... _Ax) 
		: thread_(_Fx, _Ax...)
	{
		// _Start(_STD forward<_Fn>(_Fx), _STD forward<_Args>(_Ax)...);
	}

	GameServerThread(){}

	~GameServerThread();

	GameServerThread(const GameServerThread& _Other) = delete;
	GameServerThread(GameServerThread&& _Other) noexcept;

protected:
	GameServerThread& operator=(const GameServerThread& _Other) = delete;
	GameServerThread& operator=(GameServerThread&& _Other) = delete;

public: // Member Function
	void join();

	template <class _Fn, class... _Args, std::enable_if_t<!std::is_same_v<std::_Remove_cvref_t<_Fn>, std::thread>, int> = 0>
	void Start(_Fn&& _Fx, _Args&&... _Ax)
	{
		thread_ = std::thread(_Fx, _Ax...);
	}
};

