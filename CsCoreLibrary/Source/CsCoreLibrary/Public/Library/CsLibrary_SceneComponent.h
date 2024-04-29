// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class USceneComponent;

namespace NCsSceneComponent
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORELIBRARY_API const FString GetScaleChecked;
				extern CSCORELIBRARY_API const FString SetScaleChecked;
				extern CSCORELIBRARY_API const FString SetRelativeScaleChecked;
				// Orientation
				extern CSCORELIBRARY_API const FString GetRotationChecked;
				extern CSCORELIBRARY_API const FString SetRotationChecked;
				extern CSCORELIBRARY_API const FString GetRelativeRotationChecked;
				extern CSCORELIBRARY_API const FString GetQuatChecked;
				extern CSCORELIBRARY_API const FString GetTransformChecked;
				// Movement
				extern CSCORELIBRARY_API const FString GetLocationChecked;
				extern CSCORELIBRARY_API const FString SetLocationChecked;
				extern CSCORELIBRARY_API const FString SetRelativeLocationChecked;
				extern CSCORELIBRARY_API const FString GetSocketLocationChecked;
				extern CSCORELIBRARY_API const FString GetUpChecked;
			}
		}
	}

	/**
	* Library of functions related to USceneComponent
	*/
	struct CSCORELIBRARY_API FLibrary final
	{
	#define USING_NS_CACHED using namespace NCsSceneComponent::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsSceneComponent::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName

	public:

		static FVector3f GetScaleChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetScaleChecked(const USceneComponent* Component)
		{
			SET_CONTEXT(GetScaleChecked);

			return GetScaleChecked(Context, Component);
		}
		
		static void SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale);
		FORCEINLINE static void SetScaleChecked(USceneComponent* Component, const FVector3f& Scale)
		{
			SET_CONTEXT(SetScaleChecked);

			return SetScaleChecked(Context, Component, Scale);
		}

		static void SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale);
		FORCEINLINE static void SetRelativeScaleChecked(USceneComponent* Component, const FVector3f& Scale)
		{
			SET_CONTEXT(SetRelativeScaleChecked);

			SetRelativeScaleChecked(Context, Component, Scale);
		}

	// Orientation
	#pragma region
	public:

		static FRotator3f GetRotationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator3f GetRotationChecked(const USceneComponent* Component)
		{
			SET_CONTEXT(GetRotationChecked);

			return GetRotationChecked(Context, Component);
		}

		static void SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator3f& Rotation);
		FORCEINLINE static void SetRotationChecked(USceneComponent* Component, const FRotator3f& Rotation)
		{
			SET_CONTEXT(SetRotationChecked);

			return SetRotationChecked(Context, Component, Rotation);
		}

		static FRotator3f GetRelativeRotationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator3f GetRelativeRotationChecked(const USceneComponent* Component)
		{
			SET_CONTEXT(GetRelativeRotationChecked);

			return GetRelativeRotationChecked(Context, Component);
		}

		static FQuat4f GetQuatChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FQuat4f GetQuatChecked(const USceneComponent* Component)
		{
			SET_CONTEXT(GetQuatChecked);

			return GetQuatChecked(Context, Component);
		}

		static FTransform3f GetTransformChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FTransform3f GetTransformChecked(const USceneComponent* Component)
		{
			SET_CONTEXT(GetTransformChecked);

			return GetTransformChecked(Context, Component);
		}

	#pragma endregion Orientation

	// Movement
	#pragma region
	public:

		static FVector3f GetLocationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetLocationChecked(const USceneComponent* Component)
		{
			SET_CONTEXT(GetLocationChecked);

			return GetLocationChecked(Context, Component);
		}

		static void SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location);
		FORCEINLINE static void SetLocationChecked(USceneComponent* Component, const FVector3f& Location)
		{
			SET_CONTEXT(SetLocationChecked);

			SetLocationChecked(Context, Component, Location);
		}

		static void SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location);
		FORCEINLINE static void SetRelativeLocationChecked(USceneComponent* Component, const FVector3f& Location)
		{
			SET_CONTEXT(SetRelativeLocationChecked);

			SetRelativeLocationChecked(Context, Component, Location);
		}

		static FVector3f GetSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName);
		FORCEINLINE static FVector3f GetSocketLocationChecked(const USceneComponent* Component, const FName& SocketName)
		{
			SET_CONTEXT(GetSocketLocationChecked);

			return GetSocketLocationChecked(Context, Component, SocketName);
		}

		static FVector3f GetUpChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetUpChecked(const USceneComponent* Component)
		{
			SET_CONTEXT(GetUpChecked);

			return GetUpChecked(Context, Component);
		}

	#pragma endregion Movement

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	};
}