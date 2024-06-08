// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Object/CsLibrary_GetCreatedObjects.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Object/CsGetCreatedObjects.h"

namespace NCsObject
{
	namespace NCreate
	{
		// Get
		#pragma region

		ICsGetCreatedObjects* FLibrary::GetChecked(const FString& Context, UObject* Object)
		{
			return CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsGetCreatedObjects);
		}
			
		ICsGetCreatedObjects* FLibrary::GetChecked(const FString& Context)
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
			CS_IMPLEMENTS_INTERFACE_CHECKED(Object, UObject, ICsGetCreatedObjects);
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IMPLEMENTS_INTERFACE(Object, UObject, ICsGetCreatedObjects)
			return true;
		}

		#pragma endregion Implements

		#define CreatedObjectsType NCsObject::NCreate::FCreated
		CreatedObjectsType* FLibrary::GetCreatedObjectsChecked(const FString& Context)
		{
			return GetChecked(Context)->GetCreatedObjects();
		}
		#undef CreatedObjectsType

		void FLibrary::AddChecked(const FString& Context, UObject* Object, UObject* Owner)
		{
			GetCreatedObjectsChecked(Context)->Add(Object, Owner);
		}

		void FLibrary::DestroyAndRemoveNullPendingKillOrOrphanedChecked(const FString& Context)
		{
			GetCreatedObjectsChecked(Context)->DestroyAndRemoveNullPendingKillOrOrphaned();
		}
	}
}