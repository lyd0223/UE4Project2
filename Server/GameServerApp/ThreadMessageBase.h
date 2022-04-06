#pragma once
#include <memory>

/*
Usage		: BaseClass
Category	:   
Description : �޼����� �޾����� ��ó���� ��Ƶδ� class�� Base
*/

template<class T>
class ThreadMessageBase
{
	ThreadMessageBase(std::shared_ptr<T> _Request) {}
	virtual ~ThreadMessageBase() {}

protected:
	std::shared_ptr<T> m_Request;
};

