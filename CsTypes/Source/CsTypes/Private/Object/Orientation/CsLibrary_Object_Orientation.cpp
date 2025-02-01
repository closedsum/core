// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Object/Orientation/CsLibrary_Object_Orientation.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Object
#include "Object/Orientation/CsObject_Orientation.h"

namespace NCsObject
{
	namespace NOrientation
	{
		using LogClassType = NCsTypes::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		const ICsObject_Orientation* FLibrary::GetChecked(const FString& Context, const UObject* Object)
		{
			return CS_CONST_INTERFACE_CAST_CHECKED(Object, UObject, ICsObject_Orientation);
		}

		const ICsObject_Orientation* FLibrary::GetSafe(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			return CS_CONST_INTERFACE_CAST(Object, UObject, ICsObject_Orientation);
		}

		FRotator3d FLibrary::Orientation_GetRotation3dChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetRotation3d();
		}

		FRotator3d FLibrary::Orientation_GetSafeRotation3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetRotation3d();
			}
			return FRotator3d::ZeroRotator;
		}

		FRotator3f FLibrary::Orientation_GetRotation3fChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetRotation3f();
		}

		FRotator3f FLibrary::Orientation_GetSafeRotation3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetRotation3f();
			}
			return FRotator3f::ZeroRotator;
		}

		FVector3d FLibrary::Orientation_GetDirection3dChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetDirection3d();
		}

		FVector3d FLibrary::Orientation_GetSafeDirection3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetDirection3d();
			}
			return FVector3d::ZeroVector;
		}

		FVector3f FLibrary::Orientation_GetDirection3fChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetDirection3f();
		}

		FVector3f FLibrary::Orientation_GetSafeDirection3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetDirection3f();
			}
			return FVector3f::ZeroVector;
		}

		FVector3d FLibrary::Orientation_GetForward3dChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetForward3d();
		}

		FVector3d FLibrary::Orientation_GetSafeForward3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetForward3d();
			}
			return FVector3d::ZeroVector;
		}

		FVector3f FLibrary::Orientation_GetForward3fChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetForward3f();
		}

		FVector3f FLibrary::Orientation_GetSafeForward3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetForward3f();
			}
			return FVector3f::ZeroVector;
		}

		FVector3d FLibrary::Orientation_GetRight3dChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetRight3d();
		}

		FVector3d FLibrary::Orientation_GetSafeRight3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetRight3d();
			}
			return FVector3d::ZeroVector;
		}

		FVector3f FLibrary::Orientation_GetRight3fChecked(const FString& Context, const UObject* Object)
		{
			return GetChecked(Context, Object)->Orientation_GetRight3f();
		}

		FVector3f FLibrary::Orientation_GetSafeRight3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (const ICsObject_Orientation* Interface = GetSafe(Context, Object))
			{
				OutSuccess = true;
				return Interface->Orientation_GetRight3f();
			}
			return FVector3f::ZeroVector;
		}
	}
}