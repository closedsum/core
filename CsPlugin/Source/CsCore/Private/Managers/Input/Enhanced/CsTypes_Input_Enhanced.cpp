// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Enhanced/CsTypes_Input_Enhanced.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Input
#include "InputMappingContext.h"

// FCsInputMappingContextInfo
#pragma region

bool FCsInputMappingContextInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_PENDING_KILL_CHECKED(MappingContext)
	return true;
}

bool FCsInputMappingContextInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PENDING_KILL(MappingContext)
	return true;
}

bool FCsInputMappingContextInfo::IsTopValidChecked(const FString& Context) const
{
	return true;
}

bool FCsInputMappingContextInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsInputMappingContextInfo