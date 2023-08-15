// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsLibrary_Skeleton.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Mesh
#include "Engine/SkeletalMesh.h"
// Animation
#include "Animation/AnimationAsset.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimClassInterface.h"

namespace NCsSkeleton
{
	bool FLibrary::IsValidChecked(const FString& Context, USkeletalMesh* Mesh, UAnimationAsset* Anim)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)
		// Check Anim is Valid
		CS_IS_PTR_NULL_CHECKED(Anim)
		// Check Anim's Skeleton is Valid
		const USkeleton* AnimSkeleton = Anim->GetSkeleton();

		checkf(AnimSkeleton, TEXT("%s: Failed to get Skeleton from Anim: %s."), *Context, *(Anim->GetName()));
		// Check Mesh's Skeleton is compatible with Anim's Skeleton
		checkf(Mesh->GetSkeleton()->IsCompatible(AnimSkeleton), TEXT("%s: Mesh: %s Skeleton is NOT compatible with Anim: %s Skeleton."), *Context, *(Mesh->GetName()), *(Anim->GetName()));
		// Check Mesh is compatible with Anim's Skeleton
		checkf(AnimSkeleton->IsCompatibleMesh(Mesh), TEXT("%s: Mesh: %s is NOT compatible with Anim: %s Skeleton."), *Context, *(Mesh->GetName()), *(Anim->GetName()));
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, USkeletalMesh* Mesh, UAnimationAsset* Anim, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL(Mesh)
		// Check Anim is Valid
		CS_IS_PTR_NULL(Anim)
		// Check Anim's Skeleton is Valid
		const USkeleton* AnimSkeleton = Anim->GetSkeleton();

		if (!AnimSkeleton)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Skeleton from Anim: %s."), *Context, *(Anim->GetName())));
			return false;
		}
		// Check Mesh's Skeleton is compatible with Anim's Skeleton
		if (!Mesh->GetSkeleton()->IsCompatible(AnimSkeleton))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mesh: %s Skeleton is NOT compatible with Anim: %s Skeleton."), *Context, *(Mesh->GetName()), *(Anim->GetName())));
			return false;
		}
		// Check Mesh is compatible with Anim's Skeleton
		if (!AnimSkeleton->IsCompatibleMesh(Mesh))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mesh: %s is NOT compatible with Anim: %s Skeleton."), *Context, *(Mesh->GetName()), *(Anim->GetName())));
			return false;
		}
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, USkeletalMesh* Mesh, UClass* AnimClass)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)
		// Check AnimClass is Valid
		CS_IS_PTR_NULL_CHECKED(AnimClass)
		// Check AnimClass implements the interface: IAnimClassInterface
		IAnimClassInterface* AnimClassInterface = IAnimClassInterface::GetFromClass(AnimClass);

		checkf(AnimClassInterface, TEXT("%s: AnimClass: %s does NOT implement the interface: IAnimClassInterface."), *Context, *(AnimClass->GetName()));

		// Check AnimClass's Skeleton is Valid
		const USkeleton* AnimSkeleton = AnimClassInterface->GetTargetSkeleton();

		checkf(AnimSkeleton, TEXT("%s: Failed to get Skeleton from AnimClass: %s."), *Context, *(AnimClass->GetName()));
		// Check Mesh's Skeleton is compatible with AnimClass's Skeleton
		checkf(Mesh->GetSkeleton()->IsCompatible(AnimSkeleton), TEXT("%s: Mesh: %s Skeleton is NOT compatible with AnimClass: %s Skeleton."), *Context, *(Mesh->GetName()), *(AnimClass->GetName()));
		// Check Mesh is compatible with AnimClass's Skeleton
		checkf(AnimSkeleton->IsCompatibleMesh(Mesh), TEXT("%s: Mesh: %s is NOT compatible with AnimClass: %s Skeleton."), *Context, *(Mesh->GetName()), *(AnimClass->GetName()));
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, USkeletalMesh* Mesh, UClass* AnimClass, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL(Mesh)
		// Check AnimClass is Valid
		CS_IS_PTR_NULL(AnimClass)
		// Check AnimClass implements the interface: IAnimClassInterface
		IAnimClassInterface* AnimClassInterface = IAnimClassInterface::GetFromClass(AnimClass);

		if (!AnimClassInterface)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: AnimClass: %s does NOT implement the interface: IAnimClassInterface."), *Context, *(AnimClass->GetName())));
			return false;
		}
		// Check AnimClass's Skeleton is Valid
		const USkeleton* AnimSkeleton = AnimClassInterface->GetTargetSkeleton();

		if (!AnimSkeleton)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Skeleton from AnimClass: %s."), *Context, *(AnimClass->GetName())));
			return false;
		}
		// Check Mesh's Skeleton is compatible with AnimClass's Skeleton
		if (!Mesh->GetSkeleton()->IsCompatible(AnimSkeleton))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mesh: %s Skeleton is NOT compatible with AnimClass: %s Skeleton."), *Context, *(Mesh->GetName()), *(AnimClass->GetName())));
			return false;
		}
		// Check Mesh is compatible with AnimClass's Skeleton
		if (!AnimSkeleton->IsCompatibleMesh(Mesh))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mesh: %s is NOT compatible with AnimClass: %s Skeleton."), *Context, *(Mesh->GetName()), *(AnimClass->GetName())));
			return false;
		}
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, UClass* AnimClass, UAnimationAsset* Anim)
	{
		// Check AnimClass is Valid
		CS_IS_PTR_NULL_CHECKED(AnimClass)
		// Check Anim is Valid
		CS_IS_PTR_NULL_CHECKED(Anim)
		// Check AnimClass implements the interface: IAnimClassInterface
		IAnimClassInterface* AnimClassInterface = IAnimClassInterface::GetFromClass(AnimClass);

		checkf(AnimClassInterface, TEXT("%s: AnimClass: %s does NOT implement the interface: IAnimClassInterface."), *Context, *(AnimClass->GetName()));

		// Check AnimClass's Skeleton is Valid
		const USkeleton* AnimClassSkeleton = AnimClassInterface->GetTargetSkeleton();

		checkf(AnimClassSkeleton, TEXT("%s: Failed to get Skeleton from AnimClass: %s."), *Context, *(AnimClass->GetName()));
		// Check Anim's Skeleton is Valid
		const USkeleton* AnimSkeleton = Anim->GetSkeleton();

		checkf(AnimSkeleton, TEXT("%s: Failed to get Skeleton from Anim: %s."), *Context, *(Anim->GetName()));

		// Check AnimClass's Skeleton is compatible with Anim's Skeleton
		checkf(AnimClassSkeleton->IsCompatible(AnimSkeleton), TEXT("%s: AnimClass: %s Skeleton is NOT compatible with Anim: %s Skeleton."), *Context, *(AnimClass->GetName()), *(Anim->GetName()));
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, UClass* AnimClass, UAnimationAsset* Anim, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check AnimClass is Valid
		CS_IS_PTR_NULL(AnimClass)
		// Check Anim is Valid
		CS_IS_PTR_NULL(Anim)
		// Check AnimClass implements the interface: IAnimClassInterface
		IAnimClassInterface* AnimClassInterface = IAnimClassInterface::GetFromClass(AnimClass);

		if (!AnimClassInterface)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: AnimClass: %s does NOT implement the interface: IAnimClassInterface."), *Context, *(AnimClass->GetName())));
			return false;
		}
		// Check AnimClass's Skeleton is Valid
		const USkeleton* AnimClassSkeleton = AnimClassInterface->GetTargetSkeleton();

		if (!AnimClassSkeleton)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Skeleton from AnimClass: %s."), *Context, *(AnimClass->GetName())));
			return false;
		}
		// Check Anim's Skeleton is Valid
		const USkeleton* AnimSkeleton = Anim->GetSkeleton();

		if (!AnimSkeleton)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Skeleton from Anim: %s."), *Context, *(Anim->GetName())));
			return false;
		}
		// Check AnimClass's Skeleton is compatible with Anim's Skeleton
		if (!AnimClassSkeleton->IsCompatible(AnimSkeleton))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: AnimClass: %s Skeleton is NOT compatible with Anim: %s Skeleton."), *Context, *(AnimClass->GetName()), *(Anim->GetName())));
			return false;
		}
		return true;
	}
}