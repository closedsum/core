// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Character.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Anim.h"
#include "Types/CsTypes_Item.h"
#include "CsData_Character.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Character : public ACsData
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual int32 GetHealth();

#pragma endregion Stats

// Inventory
#pragma region

	virtual FCsInventoryLoadout* GetLoadout();

#pragma endregion Inventory

// Collision
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual float GetCapsuleRadius();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual float GetCapsuleHalfHeight();

#pragma endregion Collision

// Movement
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual float GetMaxWalkSpeed();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual float GetMaxAcceleration();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual float GetJumpZVelocity();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual float GetGravityScale();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual float GetAirControl();

#pragma endregion Movement

// Weapon
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual FName GetBoneToAttachWeaponTo();

#pragma endregion Weapon

// Animation
#pragma region
public:

	CS_DECLARE_CHARACTER_ANIM
	CS_DECLARE_CHARACTER_BLEND_SPACE
	CS_DECLARE_CHARACTER_ANIM_BLUEPRINT

	virtual bool IsAnimMemberAStruct(const TCsCharacterAnim &AnimType);

	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	virtual UAnimSequence* GetAnimSequence(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const bool &IsLow = false);
	virtual UAnimSequence* GetAnimSequence(const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const bool &IsLow = false);
	virtual UAnimSequence* GetAnimSequence(const TCsCharacterAnim &AnimType, const bool &IsLow = false);

	virtual UAnimMontage* GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const TCsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	
	virtual bool IsBlendMemberStruct(const TCsCharacterBlendSpace &BlendType);
	
	virtual UBlendSpace* GetBlendSpace(const TCsViewType &ViewType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual UBlendSpace* GetBlendSpace(const TCsCharacterBlendSpace &BlendType, const bool &IsLow = false);

	virtual USkeleton* GetSkeleton(const TCsViewType &ViewType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual USkeleton* GetSkeleton(const TCsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual USkeleton* GetSkeleton(const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual USkeleton* GetSkeleton(const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);

	virtual bool IsAnimBlueprintMemberStruct(const TCsCharacterAnimBlueprint &BlueprintType);

	virtual UAnimBlueprintGeneratedClass* GetAnimBlueprint(const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual UAnimBlueprintGeneratedClass* GetAnimBlueprint(const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(UObject* InObject, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);

	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(UObject* InObject, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);

	virtual void Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(UObject* InObject, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);

	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class UObject* InObject, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);

	virtual FCsAnimSequence* GetFCsAnimSequence(const TCsCharacterAnim &AnimType);
	virtual FCsAnimMontage* GetFCsAnimMontage(const TCsCharacterAnim &AnimType);

	virtual FCsFpsAnimSequence* GetFCsFpsAnimSequence(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType);
	virtual FCsFpsAnimSequence* GetFCsFpsAnimSequence(const TCsCharacterAnim &AnimType);
	virtual FCsFpsAnimMontage* GetFCsFpsAnimMontage(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType);
	virtual FCsFpsAnimMontage* GetFCsFpsAnimMontage(const TCsCharacterAnim &AnimType);

#pragma endregion Animation
};