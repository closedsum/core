// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CoreMinimal.h"
#include "CsMacro_Log.h"
// Log
#include "Utility/CsTypesLog.h"

class UObject;
class ICsObject_Orientation;

namespace NCsObject
{
	namespace NOrientation
	{
		/**
		* Library for an Object that implements the interface: ICsObject_Orientation
		*/
		class CSTYPES_API FLibrary final
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL

		public:

			FORCEINLINE static bool ImplementsChecked(const FString& Context, const UObject* Object)
			{
				return GetChecked(Context, Object) != nullptr;
			}

			FORCEINLINE static bool SafeImplements(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				return GetSafe(Context, Object, Log) != nullptr;
			}

			static const ICsObject_Orientation* GetChecked(const FString& Context, const UObject* Object);

			static const ICsObject_Orientation* GetSafe(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			static FRotator3d Orientation_GetRotation3dChecked(const FString& Context, const UObject* Object);
			static FRotator3d Orientation_GetSafeRotation3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FRotator3d Orientation_GetSafeRotation3d(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRotation3d(Context, Object, OutSuccess, Log);
			}

			static FRotator3f Orientation_GetRotation3fChecked(const FString& Context, const UObject* Object);
			static FRotator3f Orientation_GetSafeRotation3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FRotator3f Orientation_GetSafeRotation3f(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRotation3f(Context, Object, OutSuccess, Log);
			}

			static FVector3d Orientation_GetDirection3dChecked(const FString& Context, const UObject* Object);
			static FVector3d Orientation_GetSafeDirection3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FVector3d Orientation_GetSafeDirection3d(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeDirection3d(Context, Object, OutSuccess, Log);
			}

			static FVector3f Orientation_GetDirection3fChecked(const FString& Context, const UObject* Object);
			static FVector3f Orientation_GetSafeDirection3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FVector3f Orientation_GetSafeDirection3f(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeDirection3f(Context, Object, OutSuccess, Log);
			}

			static FVector3d Orientation_GetForward3dChecked(const FString& Context, const UObject* Object);
			static FVector3d Orientation_GetSafeForward3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FVector3d Orientation_GetSafeForward3d(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeForward3d(Context, Object, OutSuccess, Log);
			}

			static FVector3f Orientation_GetForward3fChecked(const FString& Context, const UObject* Object);
			static FVector3f Orientation_GetSafeForward3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FVector3f Orientation_GetSafeForward3f(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeForward3f(Context, Object, OutSuccess, Log);
			}

			static FVector3d Orientation_GetRight3dChecked(const FString& Context, const UObject* Object);
			static FVector3d Orientation_GetSafeRight3d(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FVector3d Orientation_GetSafeRight3d(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRight3d(Context, Object, OutSuccess, Log);
			}

			static FVector3f Orientation_GetRight3fChecked(const FString& Context, const UObject* Object);
			static FVector3f Orientation_GetSafeRight3f(const FString& Context, const UObject* Object, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static FVector3f Orientation_GetSafeRight3f(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRight3f(Context, Object, OutSuccess, Log);
			}
		};
	}
}