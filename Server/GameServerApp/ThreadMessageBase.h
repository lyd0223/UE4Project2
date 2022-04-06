#pragma once
#include <memory>

/*
Usage		: BaseClass
Category	:   
Description : 메세지를 받았을때 일처리를 담아두는 class의 Base
*/

template<class T>
class ThreadMessageBase
{
	ThreadMessageBase(std::shared_ptr<T> _Request) {}
	virtual ~ThreadMessageBase() {}

protected:
	std::shared_ptr<T> m_Request;
};

