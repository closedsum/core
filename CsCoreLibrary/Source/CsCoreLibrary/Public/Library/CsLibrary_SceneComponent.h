// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Cached.h"
#include "CsMacro_Log.h"
#include "CoreMinimal.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class USceneComponent;

CS_START_CACHED_FUNCTION_NAME_NESTED_1(NCsSceneComponent, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetScaleChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetScale3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, SetScaleChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, SetRelativeScaleChecked)
	// Orientation
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetRotationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetRotation3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, SetRotationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetRelativeRotationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetRelativeRotation3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetQuatChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetQuat4fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetTransformChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetTransform3fChecked)
	// Movement
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetLocationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetLocation3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, SetLocationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, SetRelativeLocationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetSocketLocationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetSocketLocation3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetUpChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsSceneComponent::FLibrary, GetUp3fChecked)
CS_END_CACHED_FUNCTION_NAME_NESTED_1

namespace NCsSceneComponent
{
	/**
	* Library of functions related to USceneComponent
	*/
	struct CSCORELIBRARY_API FLibrary final
	{
	private:

		CS_USING_CACHED_FUNCTION_NAME_NESTED_1(NCsSceneComponent, Library);

		CS_DECLARE_STATIC_LOG_LEVEL

	public:

		static FVector GetScaleChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector GetScaleChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetScaleChecked);

			return GetScaleChecked(Context, Component);
		}
		static FVector3f GetScale3fChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetScale3fChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetScale3fChecked);

			return GetScale3fChecked(Context, Component);
		}
		
		static void SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector& Scale);
		FORCEINLINE static void SetScaleChecked(USceneComponent* Component, const FVector& Scale)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetScaleChecked);

			return SetScaleChecked(Context, Component, Scale);
		}
		static void SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale);
		FORCEINLINE static void SetScaleChecked(USceneComponent* Component, const FVector3f& Scale)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetScaleChecked);

			return SetScaleChecked(Context, Component, Scale);
		}

		static void SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector& Scale);
		FORCEINLINE static void SetRelativeScaleChecked(USceneComponent* Component, const FVector& Scale)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetRelativeScaleChecked);

			SetRelativeScaleChecked(Context, Component, Scale);
		}
		static void SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale);
		FORCEINLINE static void SetRelativeScaleChecked(USceneComponent* Component, const FVector3f& Scale)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetRelativeScaleChecked);

			SetRelativeScaleChecked(Context, Component, Scale);
		}

	// Orientation
	#pragma region
	public:

		static FRotator GetRotationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator GetRotationChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotationChecked);

			return GetRotationChecked(Context, Component);
		}
		static FRotator3f GetRotation3fChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator3f GetRotation3fChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotation3fChecked);

			return GetRotation3fChecked(Context, Component);
		}

		static void SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator& Rotation);
		FORCEINLINE static void SetRotationChecked(USceneComponent* Component, const FRotator& Rotation)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetRotationChecked);

			return SetRotationChecked(Context, Component, Rotation);
		}

		static void SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator3f& Rotation);
		FORCEINLINE static void SetRotationChecked(USceneComponent* Component, const FRotator3f& Rotation)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetRotationChecked);

			return SetRotationChecked(Context, Component, Rotation);
		}

		static FRotator GetRelativeRotationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator GetRelativeRotationChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRelativeRotationChecked);

			return GetRelativeRotationChecked(Context, Component);
		}

		static FRotator3f GetRelativeRotation3fChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator3f GetRelativeRotation3fChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRelativeRotation3fChecked);

			return GetRelativeRotation3fChecked(Context, Component);
		}

		static FQuat GetQuatChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FQuat GetQuatChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetQuatChecked);

			return GetQuatChecked(Context, Component);
		}

		static FQuat4f GetQuat4fChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FQuat4f GetQuat4fChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetQuat4fChecked);

			return GetQuat4fChecked(Context, Component);
		}

		static FTransform GetTransformChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FTransform GetTransformChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetTransformChecked);

			return GetTransformChecked(Context, Component);
		}

		static FTransform3f GetTransform3fChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FTransform3f GetTransform3fChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetTransform3fChecked);

			return GetTransform3fChecked(Context, Component);
		}

	#pragma endregion Orientation

	// Movement
	#pragma region
	public:

		static FVector GetLocationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector GetLocationChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLocationChecked);

			return GetLocationChecked(Context, Component);
		}

		static FVector3f GetLocation3fChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetLocation3fChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLocation3fChecked);

			return GetLocation3fChecked(Context, Component);
		}

		static void SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector& Location);
		FORCEINLINE static void SetLocationChecked(USceneComponent* Component, const FVector& Location)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetLocationChecked);

			SetLocationChecked(Context, Component, Location);
		}

		static void SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location);
		FORCEINLINE static void SetLocationChecked(USceneComponent* Component, const FVector3f& Location)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetLocationChecked);

			SetLocationChecked(Context, Component, Location);
		}

		static void SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector& Location);
		FORCEINLINE static void SetRelativeLocationChecked(USceneComponent* Component, const FVector& Location)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetRelativeLocationChecked);

			SetRelativeLocationChecked(Context, Component, Location);
		}

		static void SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location);
		FORCEINLINE static void SetRelativeLocationChecked(USceneComponent* Component, const FVector3f& Location)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(SetRelativeLocationChecked);

			SetRelativeLocationChecked(Context, Component, Location);
		}

		static FVector GetSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName);
		FORCEINLINE static FVector GetSocketLocationChecked(const USceneComponent* Component, const FName& SocketName)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSocketLocationChecked);

			return GetSocketLocationChecked(Context, Component, SocketName);
		}

		static FVector3f GetSocketLocation3fChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName);
		FORCEINLINE static FVector3f GetSocketLocation3fChecked(const USceneComponent* Component, const FName& SocketName)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSocketLocation3fChecked);

			return GetSocketLocation3fChecked(Context, Component, SocketName);
		}

		static FVector GetUpChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector GetUpChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetUpChecked);

			return GetUpChecked(Context, Component);
		}

		static FVector3f GetUp3fChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetUp3fChecked(const USceneComponent* Component)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetUp3fChecked);

			return GetUp3fChecked(Context, Component);
		}

	#pragma endregion Movement

	// Attach / Detach
	#pragma region
	public:

		static bool DoesSocketExistChecked(const FString& Context, USceneComponent* Component, const FName& Socket);

		static bool SafeDoesSocketExist(const FString& Context, USceneComponent* Component, const FName& Socket, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		// Attach
	#pragma region
	public:

		static bool AttachChecked_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

		static bool SafeAttach_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static bool SafeAttach_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, bool& OutSuccess, const FName& Socket = NAME_None, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			OutSuccess = SafeAttach_KeepRelativeTransform(Context, Child, Parent, Socket, Log);
			return OutSuccess;
		}

		static bool AttachChecked_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

		static bool SafeAttach_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static bool SafeAttach_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, bool& OutSuccess, const FName& Socket = NAME_None, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			OutSuccess = SafeAttach_KeepWorldTransform(Context, Child, Parent, Socket, Log);
			return OutSuccess;
		}

		static bool AttachChecked_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

		static bool SafeAttach_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static bool SafeAttach_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, bool& OutSuccess, const FName& Socket = NAME_None, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			OutSuccess = SafeAttach_SnapToTargetNotIncludingScale(Context, Child, Parent, Socket, Log);
			return OutSuccess;
		}

		static bool AttachChecked_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

		static bool SafeAttach_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static bool SafeAttach_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, bool& OutSuccess, const FName& Socket = NAME_None,  CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			OutSuccess = SafeAttach_SnapToTargetIncludingScale(Context, Child, Parent, Socket, Log);
			return OutSuccess;
		}

	#pragma endregion Attach

		// Detach
	#pragma region
	public:

		static void DetachChecked_KeepRelativeTransform(const FString& Context, USceneComponent* Component);

		static bool SafeDetach_KeepRelativeTransform(const FString& Context, USceneComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static bool SafeDetach_KeepRelativeTransform(const FString& Context, USceneComponent* Component, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			OutSuccess = SafeDetach_KeepRelativeTransform(Context, Component, Log);
			return OutSuccess;
		}

		static void DetachChecked_KeepWorldTransform(const FString& Context, USceneComponent* Component);

		static bool SafeDetach_KeepWorldTransform(const FString& Context, USceneComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static bool SafeDetach_KeepWorldTransform(const FString& Context, USceneComponent* Component, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			OutSuccess = SafeDetach_KeepWorldTransform(Context, Component, Log);
			return OutSuccess;
		}

	#pragma endregion Detach

	#pragma endregion Attach / Detach
	};
}

using CsSceneComponentLibrary = NCsSceneComponent::FLibrary;