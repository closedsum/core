// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class ICsObject_Orientation;

namespace NCsObject
{
	namespace NOrientation
	{
		/**
		* Library for an Object that implements the interface: ICsObject_Orientation
		*/
		class CSCORE_API FLibrary final
		{
		#define LogWarning void(*Log)(const FString&) = &FCsLog::Warning

		public:

			FORCEINLINE static bool ImplementsChecked(const FString& Context, const UObject* Object)
			{
				return GetChecked(Context, Object) != nullptr;
			}

			FORCEINLINE static bool SafeImplements(const FString& Context, const UObject* Object, LogWarning)
			{
				return GetSafe(Context, Object, Log) != nullptr;
			}

			static const ICsObject_Orientation* GetChecked(const FString& Context, const UObject* Object);

			static const ICsObject_Orientation* GetSafe(const FString& Context, const UObject* Object, LogWarning);

			static FRotator3d Orientation_GetRotation3dChecked(const FString& Context, const UObject* Object);
			static FRotator3d Orientation_GetSafeRotation3d(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FRotator3d Orientation_GetSafeRotation3d(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRotation3d(Context, Object, OutSuccess, Log);
			}

			static FRotator3f Orientation_GetRotation3fChecked(const FString& Context, const UObject* Object);
			static FRotator3f Orientation_GetSafeRotation3f(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FRotator3f Orientation_GetSafeRotation3f(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRotation3f(Context, Object, OutSuccess, Log);
			}

			static FVector3d Orientation_GetDirection3dChecked(const FString& Context, const UObject* Object);
			static FVector3d Orientation_GetSafeDirection3d(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FVector3d Orientation_GetSafeDirection3d(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeDirection3d(Context, Object, OutSuccess, Log);
			}

			static FVector3f Orientation_GetDirection3fChecked(const FString& Context, const UObject* Object);
			static FVector3f Orientation_GetSafeDirection3f(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FVector3f Orientation_GetSafeDirection3f(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeDirection3f(Context, Object, OutSuccess, Log);
			}

			static FVector3d Orientation_GetForward3dChecked(const FString& Context, const UObject* Object);
			static FVector3d Orientation_GetSafeForward3d(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FVector3d Orientation_GetSafeForward3d(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeForward3d(Context, Object, OutSuccess, Log);
			}

			static FVector3f Orientation_GetForward3fChecked(const FString& Context, const UObject* Object);
			static FVector3f Orientation_GetSafeForward3f(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FVector3f Orientation_GetSafeForward3f(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeForward3f(Context, Object, OutSuccess, Log);
			}

			static FVector3d Orientation_GetRight3dChecked(const FString& Context, const UObject* Object);
			static FVector3d Orientation_GetSafeRight3d(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FVector3d Orientation_GetSafeRight3d(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRight3d(Context, Object, OutSuccess, Log);
			}

			static FVector3f Orientation_GetRight3fChecked(const FString& Context, const UObject* Object);
			static FVector3f Orientation_GetSafeRight3f(const FString& Context, const UObject* Object, bool& OutSuccess, LogWarning);
			FORCEINLINE static FVector3f Orientation_GetSafeRight3f(const FString& Context, const UObject* Object, LogWarning)
			{
				bool OutSuccess = false;
				return Orientation_GetSafeRight3f(Context, Object, OutSuccess, Log);
			}

		#undef LogWarning
		};
	}
}