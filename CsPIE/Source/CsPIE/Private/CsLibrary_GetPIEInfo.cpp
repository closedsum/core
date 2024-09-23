// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_GetPIEInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsPIE
{
	namespace NGetInfo
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsPIE::FLog::Warning*/

		// Get
		#pragma region

		const ICsGetPIEInfo* FLibrary::GetChecked(const FString& Context, const UObject* Object)
		{
			return CS_CONST_INTERFACE_CAST_CHECKED(Object, UObject, ICsGetPIEInfo);
		}
			
		const ICsGetPIEInfo* FLibrary::GetChecked(const FString& Context)
		{
		#if WITH_EDITOR
			return GetChecked(Context, GEngine);
		#else
			check(0);
			return nullptr;
		#endif // #if WITH_EDITOR
		}

		#pragma endregion Get

		// Implements
		#pragma region

		bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
		{
			CS_IMPLEMENTS_INTERFACE_CHECKED(Object, UObject, ICsGetPIEInfo);
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, LogLevel)
		{
			CS_IMPLEMENTS_INTERFACE(Object, UObject, ICsGetPIEInfo)
			return true;
		}

		#pragma endregion Implements

		const CsPIEInfoType& FLibrary::GetInfoChecked(const FString& Context)
		{
			return GetChecked(Context)->GetPIEInfo();
		}

		#undef LogLevel
	}
}