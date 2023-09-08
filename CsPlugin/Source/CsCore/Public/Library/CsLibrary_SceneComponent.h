// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class USceneComponent;

namespace NCsSceneComponent
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetScaleChecked;
				extern CSCORE_API const FString SetScaleChecked;
				extern CSCORE_API const FString SetRelativeScaleChecked;
				// Orientation
				extern CSCORE_API const FString GetRotationChecked;
				extern CSCORE_API const FString SetRotationChecked;
				extern CSCORE_API const FString GetRelativeRotationChecked;
				extern CSCORE_API const FString GetQuatChecked;
				extern CSCORE_API const FString GetTransformChecked;
				// Movement
				extern CSCORE_API const FString GetLocationChecked;
				extern CSCORE_API const FString SetLocationChecked;
				extern CSCORE_API const FString SetRelativeLocationChecked;
				extern CSCORE_API const FString GetSocketLocationChecked;
				extern CSCORE_API const FString GetUpChecked;
			}
		}
	}

	/**
	* Library of functions related to USceneComponent
	*/
	struct CSCORE_API FLibrary final
	{
	public:

		static FVector3f GetScaleChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetScaleChecked(const USceneComponent* Component)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetScaleChecked;

			return GetScaleChecked(Context, Component);
		}
		
		static void SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale);
		FORCEINLINE static void SetScaleChecked(USceneComponent* Component, const FVector3f& Scale)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::SetScaleChecked;

			return SetScaleChecked(Context, Component, Scale);
		}

		static void SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale);
		FORCEINLINE static void SetRelativeScaleChecked(USceneComponent* Component, const FVector3f& Scale)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::SetRelativeScaleChecked;

			SetRelativeScaleChecked(Context, Component, Scale);
		}

	// Orientation
	#pragma region
	public:

		static FRotator3f GetRotationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator3f GetRotationChecked(const USceneComponent* Component)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetRotationChecked;

			return GetRotationChecked(Context, Component);
		}

		static void SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator3f& Rotation);
		FORCEINLINE static void SetRotationChecked(USceneComponent* Component, const FRotator3f& Rotation)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::SetRotationChecked;

			return SetRotationChecked(Context, Component, Rotation);
		}

		static FRotator3f GetRelativeRotationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FRotator3f GetRelativeRotationChecked(const USceneComponent* Component)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetRelativeRotationChecked;

			return GetRelativeRotationChecked(Context, Component);
		}

		static FQuat4f GetQuatChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FQuat4f GetQuatChecked(const USceneComponent* Component)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetQuatChecked;

			return GetQuatChecked(Context, Component);
		}

		static FTransform3f GetTransformChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FTransform3f GetTransformChecked(const USceneComponent* Component)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetTransformChecked;

			return GetTransformChecked(Context, Component);
		}

	#pragma endregion Orientation

	// Movement
	#pragma region
	public:

		static FVector3f GetLocationChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetLocationChecked(const USceneComponent* Component)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetLocationChecked;

			return GetLocationChecked(Context, Component);
		}

		static void SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location);
		FORCEINLINE static void SetLocationChecked(USceneComponent* Component, const FVector3f& Location)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::SetLocationChecked;

			SetLocationChecked(Context, Component, Location);
		}

		static void SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location);
		FORCEINLINE static void SetRelativeLocationChecked(USceneComponent* Component, const FVector3f& Location)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::SetRelativeLocationChecked;

			SetRelativeLocationChecked(Context, Component, Location);
		}

		static FVector3f GetSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName);
		FORCEINLINE static FVector3f GetSocketLocationChecked(const USceneComponent* Component, const FName& SocketName)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetSocketLocationChecked;

			return GetSocketLocationChecked(Context, Component, SocketName);
		}

		static FVector3f GetUpChecked(const FString& Context, const USceneComponent* Component);
		FORCEINLINE static FVector3f GetUpChecked(const USceneComponent* Component)
		{
			using namespace NCsSceneComponent::NLibrary::NCached;

			const FString& Context = Str::GetUpChecked;

			return GetUpChecked(Context, Component);
		}

	#pragma endregion Movement
	};
}