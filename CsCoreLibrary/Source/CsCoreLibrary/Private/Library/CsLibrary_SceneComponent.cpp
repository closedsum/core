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
	using LogLevelType = NCsCore::NLibrary::FLog;

	CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogLevelType::Warning);

	FVector FLibrary::GetScaleChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return Component->GetComponentScale();
	}

	FVector3f FLibrary::GetScale3fChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return CsMathLibrary::Convert(Component->GetComponentScale());
	}

	void FLibrary::SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldScale3D(Scale);
	}

	void FLibrary::SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldScale3D(CsMathLibrary::Convert(Scale));
	}

	void FLibrary::SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetRelativeScale3D(Scale);
	}

	void FLibrary::SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetRelativeScale3D(CsMathLibrary::Convert(Scale));
	}

	// Orientation
	#pragma region

	FRotator FLibrary::GetRotationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return Component->GetComponentRotation();
	}

	FRotator3f FLibrary::GetRotation3fChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return CsMathLibrary::Convert(Component->GetComponentRotation());
	}
	
	void FLibrary::SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldRotation(Rotation);
	}

	void FLibrary::SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator3f& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldRotation(CsMathLibrary::Convert(Rotation));
	}

	FRotator FLibrary::GetRelativeRotationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return Component->GetRelativeRotation();
	}


	FRotator3f FLibrary::GetRelativeRotation3fChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return CsMathLibrary::Convert(Component->GetRelativeRotation());
	}

	FQuat FLibrary::GetQuatChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return Component->GetComponentQuat();
	}

	FQuat4f FLibrary::GetQuat4fChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return CsMathLibrary::Convert(Component->GetComponentQuat());
	}

	FTransform FLibrary::GetTransformChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return Component->GetComponentTransform();
	}

	FTransform3f FLibrary::GetTransform3fChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return CsMathLibrary::Convert(Component->GetComponentTransform());
	}

	#pragma endregion Orientation

	// Movement
	#pragma region
	
	FVector FLibrary::GetLocationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return Component->GetComponentLocation();
	}

	FVector3f FLibrary::GetLocation3fChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return CsMathLibrary::Convert(Component->GetComponentLocation());
	}

	void FLibrary::SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldLocation(Location);
	}

	void FLibrary::SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetWorldLocation(CsMathLibrary::Convert(Location));
	}

	void FLibrary::SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetRelativeLocation(Location);
	}

	void FLibrary::SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetRelativeLocation(CsMathLibrary::Convert(Location));
	}

	FVector FLibrary::GetSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(SocketName)

		return Component->GetSocketLocation(SocketName);
	}

	FVector3f FLibrary::GetSocketLocation3fChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(SocketName)

		return CsMathLibrary::Convert(Component->GetSocketLocation(SocketName));
	}

	FVector FLibrary::GetUpChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return Component->GetUpVector();
	}

	FVector3f FLibrary::GetUp3fChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return CsMathLibrary::Convert(Component->GetUpVector());
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

	bool FLibrary::SafeDoesSocketExist(const FString& Context, USceneComponent* Component, const FName& Socket, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SafeAttach_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SafeAttach_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SafeAttach_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SafeAttach_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket /*=NAME_None*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SafeDetach_KeepRelativeTransform(const FString& Context, USceneComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SafeDetach_KeepWorldTransform(const FString& Context, USceneComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_PENDING_KILL(Component)

		Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		return true;
	}

	#pragma endregion Detach

	#pragma endregion Attach / Detach
}