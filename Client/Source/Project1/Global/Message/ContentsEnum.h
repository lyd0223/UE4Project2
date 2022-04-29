#pragma once

enum class ESignInResultType
{
	OK,
	Failed_WrongPassword,
	Failed_NoUser,
	Error,
	MAX
};

enum class ESignUpResultType
{
	OK,
	Error_DuplicateID,
	Error_NonAvailableID,
	MAX
};

enum class ECreateCharacterInfoResultType
{
	OK,
	Error,
	MAX
};