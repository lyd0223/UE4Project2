#include "MessageConverter.h"
#include <memory>
MessageConverter::MessageConverter(const std::vector<unsigned char>&_Buffer)
	: m_Buffer(_Buffer)
{
	GameServerSerializer Sr = GameServerSerializer(m_Buffer);

	EMessageType Type;
	memcpy_s(&Type, sizeof(EMessageType), &m_Buffer[0], sizeof(EMessageType));
	switch (Type)
	{
	case EMessageType::Login:
		m_Message = std::make_shared<LoginMessage>();
		break;
	case EMessageType::SignIn:
		m_Message = std::make_shared<SignInMessage>();
		break;
	case EMessageType::LoginResult:
		m_Message = std::make_shared<LoginResultMessage>();
		break;
	case EMessageType::ServerDestroy:
		m_Message = std::make_shared<ServerDestroyMessage>();
		break;
	case EMessageType::SignInResult:
		m_Message = std::make_shared<SignInResultMessage>();
		break;
	case EMessageType::Chat:
		m_Message = std::make_shared<ChatMessage>();
		break;
	default:
		return;
	}
	m_Message->DeSerialize(Sr);
}