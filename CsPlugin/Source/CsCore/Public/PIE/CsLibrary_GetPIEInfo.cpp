// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "PIE/CsLibrary_GetPIEInfo.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Engine
#include "Engine/Engine.h"

namespace NCsPIE
{
	namespace NGetInfo
	{
		// Get
		#pragma region

		const ICsGetPIEInfo* FLibrary::GetChecked(const FString& Context, const UObject* Object)
		{
			return CS_CONST_INTERFACE_CAST_CHECKED(Object, UObject, ICsGetPIEInfo);
		}
			
		const ICsGetPIEInfo* FLibrary::GetChecked(const FString& Context)
		{
			return GetChecked(Context, GEngine);
		}

		#pragma endregion Get

		// Implements
		#pragma region

		bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
		{
			CS_IMPLEMENTS_INTERFACE_CHECKED(Object, UObject, ICsGetPIEInfo);
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IMPLEMENTS_INTERFACE(Object, UObject, ICsGetPIEInfo)
			return true;
		}

		#pragma endregion Implements

		#define InfoType NCsPIE::FInfo
		const InfoType& FLibrary::GetInfoChecked(const FString& Context)
		{
			return GetChecked(Context)->GetPIEInfo();
		}
		#undef InfoType
	}
}