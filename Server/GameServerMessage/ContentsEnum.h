#pragma once

enum class ELoginResultType
{
	OK,
	Error,
	MAX
};

enum class ESignInResultType
{
	OK,
	Error_DuplicateID,
	Error_NonAvailableID,
	MAX
};

struct CharacterInfo
{
	std::string Idx;
	std::string Name;
};