#pragma once
#include <GameServerMessage/Dispatcher.h>


extern Dispatcher<TCPSession> gDispatcher;
void DispatcherRegistration();