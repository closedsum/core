// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/CsTypes_Manager_Level.h"

// Library
#include "Library/CsLibrary_Valid.h"

bool FCsManagerLevel_ChangeMapParams::IsValidChecked(const FString& Context) const 
{
	CS_IS_STRING_EMPTY_CHECKED(Map)
	return true;
}

bool FCsManagerLevel_ChangeMapParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_STRING_EMPTY(Map)
	return true;
}

namespace NCsLevel
{
	namespace NManager
	{
		namespace NChangeMap
		{
			bool FParams::IsValidChecked(const FString& Context) const 
			{
				CS_IS_STRING_EMPTY_CHECKED(Map)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_STRING_EMPTY(Map)
				return true;
			}
		}
	}
}