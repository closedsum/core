// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_SceneComponent.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/SceneComponent.h"

namespace NCsSceneComponent
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetScaleChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetScaleChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetRelativeScaleChecked);
				// Orientation
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetRotationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetRotationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetRelativeRotationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetQuatChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetTransformChecked);
				// Movement
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetLocationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetLocationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetRelativeLocationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetSocketLocationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetUpChecked);
			}
		}
	}

	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
	#define MathLibrary NCsMath::FLibrary

	FVector3f FLibrary::GetScaleChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetComponentScale());
	}

	void FLibrary::SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldScale3D(MathLibrary::Convert(Scale));
	}

	void FLibrary::SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetRelativeScale3D(MathLibrary::Convert(Scale));

	}

	// Orientation
	#pragma region

	FRotator3f FLibrary::GetRotationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetComponentRotation());
	}

	void FLibrary::SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator3f& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldRotation(MathLibrary::Convert(Rotation));
	}

	FRotator3f FLibrary::GetRelativeRotationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetRelativeRotation());
	}

	FQuat4f FLibrary::GetQuatChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetComponentQuat());
	}

	FTransform3f FLibrary::GetTransformChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetComponentTransform());
	}

	#pragma endregion Orientation

	// Movement
	#pragma region
	
	FVector3f FLibrary::GetLocationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetComponentLocation());
	}

	void FLibrary::SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldLocation(MathLibrary::Convert(Location));
	}

	void FLibrary::SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetRelativeLocation(MathLibrary::Convert(Location));
	}

	FVector3f FLibrary::GetSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(SocketName)

		return MathLibrary::Convert(Component->GetSocketLocation(SocketName));
	}

	FVector3f FLibrary::GetUpChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetUpVector());
	}

	#pragma endregion Movement

	// Attach / Detach
	#pragma region

	bool FLibrary::DoesSocketExistChecked(const FString& Context, USceneComponent* Component, const FName& Socket)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(Socket)

		checkf(Component->DoesSocketExist(Socket), TEXT("%s: Component: %s does NOT have Socket: %s."), *Context, *(Component->GetName()), *(Socket.ToString()));
		return true;
	}

	bool FLibrary::SafeDoesSocketExist(const FString& Context, USceneComponent* Component, const FName& Socket, LogLevel)
	{
		CS_IS_PENDING_KILL(Component)
		CS_IS_NAME_NONE(Socket)

		if (Component->DoesSocketExist(Socket))
			return true;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component: %s does NOT have Socket: %s."), *Context, *(Component->GetName()), *(Socket.ToString())));
		return false;
	}

		// Attach
	#pragma region

	bool FLibrary::AttachChecked_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
	{
		CS_IS_PENDING_KILL_CHECKED(Child)
		CS_IS_PENDING_KILL_CHECKED(Parent)

		if (Socket != NAME_None)
		{
			check(DoesSocketExistChecked(Context, Parent, Socket));
		}

		const bool Success = Child->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform, Socket);
			
		checkf(Success, TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString()));
		return Success;
	}

	bool FLibrary::SafeAttach_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, LogLevel)
	{
		CS_IS_PENDING_KILL(Child)
		CS_IS_PENDING_KILL(Parent)

		if (Socket != NAME_None)
		{
			if (!SafeDoesSocketExist(Context, Parent, Socket, Log))
				return false;
		}
		
		if (Child->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform, Socket))
			return true;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString())));
		return false;
	}

	bool FLibrary::AttachChecked_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
	{
		CS_IS_PENDING_KILL_CHECKED(Child)
		CS_IS_PENDING_KILL_CHECKED(Parent)

		if (Socket != NAME_None)
		{
			check(DoesSocketExistChecked(Context, Parent, Socket));
		}

		const bool Success = Child->AttachToComponent(Parent, FAttachmentTransformRules::KeepWorldTransform, Socket);
			
		checkf(Success, TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString()));
		return Success;
	}

	bool FLibrary::SafeAttach_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, LogLevel)
	{
		CS_IS_PENDING_KILL(Child)
		CS_IS_PENDING_KILL(Parent)

		if (Socket != NAME_None)
		{
			if (!SafeDoesSocketExist(Context, Parent, Socket, Log))
				return false;
		}
		
		if (Child->AttachToComponent(Parent, FAttachmentTransformRules::KeepWorldTransform, Socket))
			return true;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString())));
		return false;
	}

	bool FLibrary::AttachChecked_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
	{
		CS_IS_PENDING_KILL_CHECKED(Child)
		CS_IS_PENDING_KILL_CHECKED(Parent)

		if (Socket != NAME_None)
		{
			check(DoesSocketExistChecked(Context, Parent, Socket));
		}

		const bool Success = Child->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
			
		checkf(Success, TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString()));
		return Success;
	}

	bool FLibrary::SafeAttach_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, LogLevel)
	{
		CS_IS_PENDING_KILL(Child)
		CS_IS_PENDING_KILL(Parent)

		if (Socket != NAME_None)
		{
			if (!SafeDoesSocketExist(Context, Parent, Socket, Log))
				return false;
		}
		
		if (Child->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket))
			return true;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString())));
		return false;
	}

	bool FLibrary::AttachChecked_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/)
	{
		CS_IS_PENDING_KILL_CHECKED(Child)
		CS_IS_PENDING_KILL_CHECKED(Parent)

		if (Socket != NAME_None)
		{
			check(DoesSocketExistChecked(Context, Parent, Socket));
		}

		const bool Success = Child->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
			
		checkf(Success, TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString()));
		return Success;
	}

	bool FLibrary::SafeAttach_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, LogLevel)
	{
		CS_IS_PENDING_KILL(Child)
		CS_IS_PENDING_KILL(Parent)

		if (Socket != NAME_None)
		{
			if (!SafeDoesSocketExist(Context, Parent, Socket, Log))
				return false;
		}
		
		if (Child->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket))
			return true;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Child: %s Failed to Attach to Parent: %s at Socket: %s."), *Context, *(Child->GetName()), *(Parent->GetName()), *(Socket.ToString())));
		return false;
	}

	#pragma endregion Attach

		// Detach
	#pragma region

	void FLibrary::DetachChecked_KeepRelativeTransform(const FString& Context, USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}

	bool FLibrary::SafeDetach_KeepRelativeTransform(const FString& Context, USceneComponent* Component, LogLevel)
	{
		CS_IS_PENDING_KILL(Component)

		Component->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		return true;
	}

	void FLibrary::DetachChecked_KeepWorldTransform(const FString& Context, USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}

	bool FLibrary::SafeDetach_KeepWorldTransform(const FString& Context, USceneComponent* Component, LogLevel)
	{
		CS_IS_PENDING_KILL(Component)

		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		return true;
	}

	#pragma endregion Detach

	#pragma endregion Attach / Detach

	#undef LogLevel
	#undef MathLibrary
}