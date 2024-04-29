// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_SkeletalMesh.h"

// Types
#include "CsMacro_Misc.h"
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Math_Library.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Skeletal Mesh
#include "Engine/SkeletalMesh.h"
// Components
#include "Components/SkeletalMeshComponent.h"

namespace NCsSkeletalMesh
{
	#define LogWarning void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
	#define MathLibrary NCsMath::FLibrary

	// Load
	#pragma region

	#define ObjectLibrary NCsObject::FLibrary

	USkeletalMesh* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		return ObjectLibrary::LoadChecked<USkeletalMesh>(Context, Path);
	}

	USkeletalMesh* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogWarning)
	{
		return ObjectLibrary::SafeLoad<USkeletalMesh>(Context, Path, Log);
	}

	USkeletalMesh* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		return ObjectLibrary::LoadChecked<USkeletalMesh>(Context, Path);
	}

	USkeletalMesh* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogWarning)
	{
		return ObjectLibrary::SafeLoad<USkeletalMesh>(Context, Path, Log);
	}

	#undef ObjectLibrary

	#pragma endregion Load

	// Get
	#pragma region

	USkeletalMesh* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogWarning)
	{
		typedef NCsProperty::FLibrary PropertyLibrary;

		return PropertyLibrary::GetObjectPropertyValueByPath<USkeletalMesh>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	// Bone
	#pragma region

	bool FLibrary::IsBoneValidChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone)
	{
		CS_IS_PTR_NULL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(Bone)

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

		checkf(Mesh, TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName()));
		checkf(Component->GetBoneIndex(Bone) != INDEX_NONE, TEXT("%s: Bone: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(Bone.ToString()), *(Component->GetName()), *(Mesh->GetName()));

		return true;
	}

	FVector3f FLibrary::GetBoneLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone)
	{
		check(IsBoneValidChecked(Context, Component, Bone));
		return MathLibrary::Convert(Component->GetBoneLocation(Bone));
	}

	FRotator3f FLibrary::GetBoneRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		check(IsBoneValidChecked(Context, Component, Bone));

		FRotator3f Rotation = MathLibrary::Convert(Component->GetBoneQuaternion(Bone).Rotator());

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FVector3f FLibrary::GetBoneNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
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

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

		checkf(Mesh, TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName()));
		checkf(Component->DoesSocketExist(Socket), TEXT("%s: Socket: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(Socket.ToString()), *(Component->GetName()), *(Mesh->GetName()));
		return true;
	}

	FVector3f FLibrary::GetSocketLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket)
	{
		check(IsSocketValidChecked(Context, Component, Socket));

		const FTransform3f Transform = MathLibrary::Convert(Component->GetSocketTransform(Socket));

		return Transform.GetLocation();
	}

	FRotator3f FLibrary::GetSocketRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		check(IsSocketValidChecked(Context, Component, Socket));

		const FTransform3f Transform = MathLibrary::Convert(Component->GetSocketTransform(Socket));
		FRotator3f Rotation			 = Transform.GetRotation().Rotator();

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FVector3f FLibrary::GetSocketNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		return GetSocketRotationChecked(Context, Component, Socket, Rules).Vector();
	}

	#pragma endregion Socket

	bool FLibrary::IsBoneOrSocketValidChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		CS_IS_PTR_NULL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(BoneOrSocket)

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

		checkf(Mesh, TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName()));

		bool Exists = false;

		Exists = Component->DoesSocketExist(BoneOrSocket);

		if (Exists)
			return true;

		Exists = Component->GetBoneIndex(BoneOrSocket) != INDEX_NONE;

		if (Exists)	
			return true;
		checkf(0, TEXT("%s: BoneOrSocket: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(BoneOrSocket.ToString()), *(Component->GetName()), *(Mesh->GetName()));
		return false;
	}

	bool FLibrary::SafeIsBoneOrSocketValid(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket, LogWarning)
	{
		CS_IS_PTR_NULL(Component)
		CS_IS_NAME_NONE(BoneOrSocket)

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

		if (!Mesh)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName())));
			return false;
		}

		bool Exists = false;

		Exists = Component->DoesSocketExist(BoneOrSocket);

		if (Exists)
			return true;

		Exists = Component->GetBoneIndex(BoneOrSocket) != INDEX_NONE;

		if (Exists)
			return true;
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: BoneOrSocket: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(BoneOrSocket.ToString()), *(Component->GetName()), *(Mesh->GetName())));
		return false;
	}

	bool FLibrary::ConditionalIsBoneOrSocketValidChecked(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		if (USkeletalMeshComponent* C = Cast<USkeletalMeshComponent>(Component))
			return IsBoneOrSocketValidChecked(Context, C, BoneOrSocket);
		return true;
	}

	bool FLibrary::ConditionalSafeIsBoneOrSocketValid(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket, LogWarning)
	{
		CS_IS_PTR_NULL(Component)

		if (USkeletalMeshComponent* C = Cast<USkeletalMeshComponent>(Component))
			return SafeIsBoneOrSocketValid(Context, C, BoneOrSocket, Log);
		return true;
	}

	FVector3f FLibrary::GetBoneOrSocketDirectionChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return MathLibrary::Convert(Component->GetBoneQuaternion(BoneOrSocket).Vector());
	}

	FVector3f FLibrary::GetBoneOrSocketDirectionChecked(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket)
	{
		USkeletalMeshComponent* C = CS_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

		return GetBoneOrSocketDirectionChecked(Context, C, BoneOrSocket);
	}

	FVector3f FLibrary::GetBoneOrSocketLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return MathLibrary::Convert(Component->GetBoneLocation(BoneOrSocket));
	}

	FVector3f FLibrary::GetBoneOrSocketLocationChecked(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket)
	{
		USkeletalMeshComponent* C = CS_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

		return GetBoneOrSocketLocationChecked(Context, C, BoneOrSocket);
	}

	#undef LogWarning
	#undef MathLibrary
}