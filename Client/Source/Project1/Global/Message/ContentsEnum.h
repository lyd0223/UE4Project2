#pragma once
#include <string>

enum class ESignInResultType
{
	OK,
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
