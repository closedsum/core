// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_SkeletalMesh.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Math.h"
// Library
#include "Library/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/SkeletalMeshComponent.h"

namespace NCsSkeletalMesh
{
	// Load
	#pragma region

	USkeletalMesh* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::LoadChecked<USkeletalMesh>(Context, Path);
	}

	USkeletalMesh* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<USkeletalMesh>(Context, Path, Log);
	}

	USkeletalMesh* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::LoadChecked<USkeletalMesh>(Context, Path);
	}

	USkeletalMesh* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<USkeletalMesh>(Context, Path, Log);
	}

	#pragma endregion Load

	// Bone
	#pragma region

	bool FLibrary::IsBoneValidChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		CS_IS_NAME_NONE_CHECKED(Bone)

		USkeletalMesh* Mesh = Component->SkeletalMesh;

		checkf(Mesh, TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName()));

		checkf(Component->GetBoneIndex(Bone) != INDEX_NONE, TEXT("%s: Bone: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(Bone.ToString()), *(Component->GetName()), *(Mesh->GetName()));

		return true;
	}

	FVector FLibrary::GetBoneLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone)
	{
		check(IsBoneValidChecked(Context, Component, Bone));

		return Component->GetBoneLocation(Bone);
	}

	FRotator FLibrary::GetBoneRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		check(IsBoneValidChecked(Context, Component, Bone));

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

	bool FLibrary::IsSocketValidChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		CS_IS_NAME_NONE_CHECKED(Socket)

		USkeletalMesh* Mesh = Component->SkeletalMesh;

		checkf(Mesh, TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName()));

		checkf(Component->DoesSocketExist(Socket), TEXT("%s: Socket: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(Socket.ToString()), *(Component->GetName()), *(Mesh->GetName()));

		return true;
	}

	FVector FLibrary::GetSocketLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket)
	{
		check(IsSocketValidChecked(Context, Component, Socket));

		const FTransform Transform = Component->GetSocketTransform(Socket);

		return Transform.GetLocation();
	}

	FRotator FLibrary::GetSocketRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		check(IsSocketValidChecked(Context, Component, Socket));

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