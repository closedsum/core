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
	using LogClassType = NCsCore::NLibrary::FLog;

	CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);
	CS_DEFINE_STATIC_LOG_WARNING(FLibrary, LogClassType::Warning);

	// Load
	#pragma region

	USkeletalMesh* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		return CsObjectLibrary::LoadChecked<USkeletalMesh>(Context, Path);
	}

	USkeletalMesh* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<USkeletalMesh>(Context, Path, Log);
	}

	USkeletalMesh* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		return CsObjectLibrary::LoadChecked<USkeletalMesh>(Context, Path);
	}

	USkeletalMesh* FLibrary::SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<USkeletalMesh>(Context, Path, Log);
	}

	#pragma endregion Load

	// Get
	#pragma region

	USkeletalMesh* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsPropertyLibrary::GetObjectPropertyValueByPath<USkeletalMesh>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	#pragma endregion Get

	// Asset
	#pragma region 
	
	bool FLibrary::HasAssetChecked(const FString& Context, const USkeletalMeshComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		checkf(IsValid(Component->GetSkeletalMeshAsset()), TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName()));
		return true;
	}

	bool FLibrary::SafeHasAsset(const FString& Context, const USkeletalMeshComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_PENDING_KILL(Component)

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

		if (!Mesh)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: SkeletalMesh is NULL for Component: %s."), *Context, *(Component->GetName())));
			return false;
		}
		return true;
	}

	#pragma endregion Asset

	// Bone
	#pragma region

	bool FLibrary::IsBoneValidChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(Bone)
		check(HasAssetChecked(Context, Component));

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

		checkf(Component->GetBoneIndex(Bone) != INDEX_NONE, TEXT("%s: Bone: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(Bone.ToString()), *(Component->GetName()), *(Mesh->GetName()));
		return true;
	}

	FVector FLibrary::GetBoneLocationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone)
	{
		check(IsBoneValidChecked(Context, Component, Bone));
		return Component->GetBoneLocation(Bone);
	}

	FVector3f FLibrary::GetBoneLocation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone)
	{
		check(IsBoneValidChecked(Context, Component, Bone));
		return CsMathLibrary::Convert(Component->GetBoneLocation(Bone));
	}

	FRotator FLibrary::GetBoneRotationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		check(IsBoneValidChecked(Context, Component, Bone));

		FRotator Rotation = Component->GetBoneQuaternion(Bone).Rotator();

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FRotator3f FLibrary::GetBoneRotation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		check(IsBoneValidChecked(Context, Component, Bone));

		FRotator3f Rotation = CsMathLibrary::Convert(Component->GetBoneQuaternion(Bone).Rotator());

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FVector FLibrary::GetBoneNormalChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		return GetBoneRotationChecked(Context, Component, Bone, Rules).Vector();
	}

	FVector3f FLibrary::GetBoneNormal3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules)
	{
		return GetBoneRotation3fChecked(Context, Component, Bone, Rules).Vector();
	}

	#pragma endregion Bone

	// Socket
	#pragma region

	bool FLibrary::IsSocketValidChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket)
	{
		CS_IS_PTR_NULL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(Socket)
		check(HasAssetChecked(Context, Component));

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

		checkf(Component->DoesSocketExist(Socket), TEXT("%s: Socket: %s does NOT exist on Component: %s with SkeletalMesh: %s."), *Context, *(Socket.ToString()), *(Component->GetName()), *(Mesh->GetName()));
		return true;
	}

	FVector FLibrary::GetSocketLocationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket)
	{
		check(IsSocketValidChecked(Context, Component, Socket));
		return Component->GetSocketTransform(Socket).GetLocation();
	}

	FVector3f FLibrary::GetSocketLocation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket)
	{
		check(IsSocketValidChecked(Context, Component, Socket));

		const FTransform3f Transform = CsMathLibrary::Convert(Component->GetSocketTransform(Socket));

		return Transform.GetLocation();
	}

	FRotator FLibrary::GetSocketRotationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		check(IsSocketValidChecked(Context, Component, Socket));

		const FTransform Transform = Component->GetSocketTransform(Socket);
		FRotator Rotation		   = Transform.GetRotation().Rotator();

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FRotator3f FLibrary::GetSocketRotation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		check(IsSocketValidChecked(Context, Component, Socket));

		const FTransform3f Transform = CsMathLibrary::Convert(Component->GetSocketTransform(Socket));
		FRotator3f Rotation			 = Transform.GetRotation().Rotator();

		return NCsRotationRules::GetRotationChecked(Context, Rotation, Rules);
	}

	FVector FLibrary::GetSocketNormalChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		return GetSocketRotationChecked(Context, Component, Socket, Rules).Vector();
	}

	FVector3f FLibrary::GetSocketNormal3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules)
	{
		return GetSocketRotation3fChecked(Context, Component, Socket, Rules).Vector();
	}

	#pragma endregion Socket

	bool FLibrary::IsBoneOrSocketValidChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(BoneOrSocket)
		check(HasAssetChecked(Context, Component));

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

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

	bool FLibrary::SafeIsBoneOrSocketValid(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_PENDING_KILL(Component)
		CS_IS_NAME_NONE(BoneOrSocket)

		if (!SafeHasAsset(Context, Component, Log))
			return false;

		USkeletalMesh* Mesh = Component->GetSkeletalMeshAsset();

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

	bool FLibrary::ConditionalIsBoneOrSocketValidChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		void(*Log)(const FString&) = LogWarning;

		if (const USkeletalMeshComponent* C = CS_CONST_CAST(Component, USceneComponent, USkeletalMeshComponent))
			return IsBoneOrSocketValidChecked(Context, C, BoneOrSocket);
		return true;
	}

	bool FLibrary::ConditionalSafeIsBoneOrSocketValid(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_PENDING_KILL(Component)

		if (const  USkeletalMeshComponent* C = CS_CONST_CAST(Component, USceneComponent, USkeletalMeshComponent))
			return SafeIsBoneOrSocketValid(Context, C, BoneOrSocket, Log);
		return true;
	}

	FRotator FLibrary::GetBoneOrSocketRotationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return Component->GetBoneQuaternion(BoneOrSocket).Rotator();
	}

	FRotator FLibrary::GetSafeBoneOrSocketRotation(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		OutSuccess = false;

		if (!SafeIsBoneOrSocketValid(Context, Component, BoneOrSocket, Log))
			return FRotator::ZeroRotator;

		OutSuccess = true;
		return Component->GetBoneQuaternion(BoneOrSocket).Rotator();
	}

	FRotator3f FLibrary::GetBoneOrSocketRotation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return CsMathLibrary::Convert(Component->GetBoneQuaternion(BoneOrSocket).Rotator());
	}

	FRotator3f FLibrary::GetSafeBoneOrSocketRotation3f(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		OutSuccess = false;

		if (!SafeIsBoneOrSocketValid(Context, Component, BoneOrSocket, Log))
			return FRotator3f::ZeroRotator;

		OutSuccess = true;
		return CsMathLibrary::Convert(Component->GetBoneQuaternion(BoneOrSocket).Rotator());
	}

	FVector FLibrary::GetBoneOrSocketDirectionChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return Component->GetBoneQuaternion(BoneOrSocket).Vector();
	}

	FVector3f FLibrary::GetBoneOrSocketDirection3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return CsMathLibrary::Convert(Component->GetBoneQuaternion(BoneOrSocket).Vector());
	}

	FVector FLibrary::GetBoneOrSocketDirectionChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket)
	{
		const USkeletalMeshComponent* C = CS_CONST_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

		return GetBoneOrSocketDirectionChecked(Context, C, BoneOrSocket);
	}

	FVector3f FLibrary::GetBoneOrSocketDirection3fChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket)
	{
		const USkeletalMeshComponent* C = CS_CONST_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

		return GetBoneOrSocketDirection3fChecked(Context, C, BoneOrSocket);
	}

	FVector FLibrary::GetBoneOrSocketLocationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return Component->GetBoneLocation(BoneOrSocket);
	}

	FVector3f FLibrary::GetBoneOrSocketLocation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket)
	{
		check(IsBoneOrSocketValidChecked(Context, Component, BoneOrSocket));
		return CsMathLibrary::Convert(Component->GetBoneLocation(BoneOrSocket));
	}

	FVector FLibrary::GetSafeBoneOrSocketLocation(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		OutSuccess = false;

		if (!SafeIsBoneOrSocketValid(Context, Component, BoneOrSocket))
			return FVector::ZeroVector;

		OutSuccess = true;
		return Component->GetBoneLocation(BoneOrSocket);
	}

	FVector FLibrary::GetBoneOrSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket)
	{
		const USkeletalMeshComponent* C = CS_CONST_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

		return GetBoneOrSocketLocationChecked(Context, C, BoneOrSocket);
	}

	FVector3f FLibrary::GetBoneOrSocketLocation3fChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket)
	{
		const USkeletalMeshComponent* C = CS_CONST_CAST_CHECKED(Component, USceneComponent, USkeletalMeshComponent);

		return GetBoneOrSocketLocation3fChecked(Context, C, BoneOrSocket);
	}
}