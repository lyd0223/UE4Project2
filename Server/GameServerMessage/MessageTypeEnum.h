#pragma once

enum class EMessageType 
{
	SignIn,
	SignUp,
	CreateCharacterInfo,
	DeleteCharacterInfo,
	RequestCharacterInfo,
	SaveCharacterInfo,
	SignInResult,
	ServerDestroy,
	SignUpResult,
	CreateCharacterInfoResult,
	DeleteCharacterInfoResult,
	ReplyCharacterInfo,
	Chat,
	CharacterMove,
	MAX
};