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
	case EMessageType::SignIn:
		m_Message = std::make_shared<SignInMessage>();
		break;
	case EMessageType::SignUp:
		m_Message = std::make_shared<SignUpMessage>();
		break;
	case EMessageType::CreateCharacterInfo:
		m_Message = std::make_shared<CreateCharacterInfoMessage>();
		break;
	case EMessageType::DeleteCharacterInfo:
		m_Message = std::make_shared<DeleteCharacterInfoMessage>();
		break;
	case EMessageType::RequestCharacterInfo:
		m_Message = std::make_shared<RequestCharacterInfoMessage>();
		break;
	case EMessageType::SaveCharacterInfo:
		m_Message = std::make_shared<SaveCharacterInfoMessage>();
		break;
	case EMessageType::SignInResult:
		m_Message = std::make_shared<SignInResultMessage>();
		break;
	case EMessageType::ServerDestroy:
		m_Message = std::make_shared<ServerDestroyMessage>();
		break;
	case EMessageType::SignUpResult:
		m_Message = std::make_shared<SignUpResultMessage>();
		break;
	case EMessageType::CreateCharacterInfoResult:
		m_Message = std::make_shared<CreateCharacterInfoResultMessage>();
		break;
	case EMessageType::DeleteCharacterInfoResult:
		m_Message = std::make_shared<DeleteCharacterInfoResultMessage>();
		break;
	case EMessageType::ReplyCharacterInfo:
		m_Message = std::make_shared<ReplyCharacterInfoMessage>();
		break;
	case EMessageType::Chat:
		m_Message = std::make_shared<ChatMessage>();
		break;
	case EMessageType::CharacterMove:
		m_Message = std::make_shared<CharacterMoveMessage>();
		break;
	default:
		return;
	}
	m_Message->DeSerialize(Sr);
}