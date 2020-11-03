// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_SkeletalMesh.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Math.h"
// Components
#include "Components/SkeletalMeshComponent.h"

namespace NCsSkeletalMesh
{
	// Bone
	#pragma region

	FVector FLibrary::GetBoneLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone)
	{
		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		checkf(Bone != NAME_None, TEXT("%s: Bone: None is NOT Valid."), *Context);

		checkf(Component->GetBoneIndex(Bone) != INDEX_NONE, TEXT("%s: Bone: %s does NOT exist on SkeletalMesh: %s."), *Context, *(Bone.ToString()), *(Component->SkeletalMesh->GetName()));

		return Component->GetBoneLocation(Bone);
	}

	FRotator FLibrary::GetBoneRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		checkf(Bone != NAME_None, TEXT("%s: Bone: None is NOT Valid."), *Context);

		checkf(Component->GetBoneIndex(Bone) != INDEX_NONE, TEXT("%s: Bone: %s does NOT exist on SkeletalMesh: %s."), *Context, *(Bone.ToString()), *(Component->SkeletalMesh->GetName()));

		FRotator Rotation = Component->GetBoneQuaternion(Bone).Rotator();

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FVector FLibrary::GetBoneNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		return GetBoneRotationChecked(Context, Component, Bone, Rules).Vector();
	}

	#pragma endregion Bone

	// Socket
	#pragma region

	FVector FLibrary::GetSocketLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket)
	{
		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		checkf(Socket != NAME_None, TEXT("%s: Socket: None is NOT Valid."), *Context);

		checkf(Component->DoesSocketExist(Socket), TEXT("%s: Socket: %s does NOT exist on SkeletalMesh: %s."), *Context, *(Component->SkeletalMesh->GetName()));

		const FTransform Transform = Component->GetSocketTransform(Socket);

		return Transform.GetLocation();
	}

	FRotator FLibrary::GetSocketRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		checkf(Socket != NAME_None, TEXT("%s: Socket: None is NOT Valid."), *Context);

		checkf(Component->GetBoneIndex(Socket) != INDEX_NONE, TEXT("%s: Bone: %s Socket NOT exist on SkeletalMesh: %s."), *Context, *(Socket.ToString()), *(Component->SkeletalMesh->GetName()));

		const FTransform Transform = Component->GetSocketTransform(Socket);

		FRotator Rotation = Transform.GetRotation().Rotator();

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FVector FLibrary::GetSocketNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		return GetSocketRotationChecked(Context, Component, Socket, Rules).Vector();
	}

	#pragma endregion Socket
}