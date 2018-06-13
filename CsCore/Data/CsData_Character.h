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
	virtual const int32& GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetRespawnTime();

#pragma endregion Stats

// Inventory
#pragma region

	virtual FCsInventoryLoadout* GetLoadout();

#pragma endregion Inventory

// Collision
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetCapsuleRadius();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetCapsuleHalfHeight();

private:

	FCollisionResponseContainer DefaultCollisionResponseContainer;

public:

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual FCollisionResponseContainer& GetCollisionResponseContainer();

	virtual FCsHeadCollision* GetHeadCollision();

#pragma endregion Collision

// Movement
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetMaxWalkSpeed();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetMaxAcceleration();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetJumpZVelocity();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetGravityScale();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const float& GetAirControl();

#pragma endregion Movement

// Weapon
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	virtual const FName& GetBoneToAttachWeaponTo();

#pragma endregion Weapon

// Animation
#pragma region
public:

	virtual bool IsAnimMemberAStruct(const FECsCharacterAnim &AnimType);

	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	// Sequence
#pragma region

	virtual UAnimSequence* GetAnimSequence(const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimSequence* GetAnimSequence(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimSequence* GetAnimSequence(const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimSequence* GetAnimSequence(const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	virtual FCsAnimSequence* GetFCsAnimSequence(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0);
	virtual FCsAnimSequence* GetFCsAnimSequence(const FECsCharacterAnim &AnimType, const int32 &Index = 0);
	virtual FCsFpvAnimSequence* GetFCsFpvAnimSequence(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0);
	virtual FCsFpvAnimSequence* GetFCsFpvAnimSequence(const FECsCharacterAnim &AnimType, const int32 &Index = 0);

#pragma endregion Sequence

	// Montage
#pragma region

	virtual UAnimMontage* GetAnimMontage(const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	
	virtual FCsAnimMontage* GetFCsAnimMontage(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0);
	virtual FCsAnimMontage* GetFCsAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index = 0);
	virtual FCsFpvAnimMontage* GetFCsFpvAnimMontage(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index = 0);
	virtual FCsFpvAnimMontage* GetFCsFpvAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index = 0);

#pragma endregion Montage

	// BlendSpace1D
#pragma region

	virtual UBlendSpace1D* GetBlendSpace1D(const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual UBlendSpace1D* GetBlendSpace1D(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual UBlendSpace1D* GetBlendSpace1D(const FECsCharacterBlendSpace &BlendType, const bool &IsLow = false);

	virtual FCsBlendSpace1D* GetFCsBlendSpace1D(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);
	virtual FCsBlendSpace1D* GetFCsBlendSpace1D(const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);
	virtual FCsFpvBlendSpace1D* GetFCsFpvBlendSpace1D(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);
	virtual FCsFpvBlendSpace1D* GetFCsFpvBlendSpace1D(const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);

#pragma endregion BlendSpace1D

	// BlendSpace
#pragma region

	virtual bool IsBlendMemberStruct(const FECsCharacterBlendSpace &BlendType);
	
	virtual UBlendSpace* GetBlendSpace(const TCsViewType &ViewType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual UBlendSpace* GetBlendSpace(const FECsCharacterBlendSpace &BlendType, const bool &IsLow = false);

	virtual FCsBlendSpace* GetFCsBlendSpace(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);
	virtual FCsBlendSpace* GetFCsBlendSpace(const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);
	virtual FCsFpvBlendSpace* GetFCsFpvBlendSpace(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);
	virtual FCsFpvBlendSpace* GetFCsFpvBlendSpace(const FECsCharacterBlendSpace &BlendType, const int32 &Index = 0);

#pragma endregion BlendSpace

	virtual USkeleton* GetSkeleton(const TCsViewType &ViewType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual USkeleton* GetSkeleton(const FECsCharacterBlendSpace &BlendType, const bool &IsLow = false);
	virtual USkeleton* GetSkeleton(const TCsViewType &ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual USkeleton* GetSkeleton(const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);

	// AnimBlueprint
#pragma region

	virtual bool IsAnimBlueprintMemberStruct(const FECsCharacterAnimBlueprint &BlueprintType);

	virtual UAnimBlueprintGeneratedClass* GetAnimBlueprint(const TCsViewType &ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual UAnimBlueprintGeneratedClass* GetAnimBlueprint(const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(UObject* InObject, const TCsViewType &ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(UObject* InObject, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow = false);

#pragma endregion AnimBlueprint

	// Play
#pragma region

	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(UObject* InObject, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);
	virtual void PlayAnimation(UObject* InObject, const FECsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate = 1.0f, const bool &IsLooping = false, const bool &IsLow = false);

#pragma endregion Play

	// JumpTo
#pragma region

	virtual void Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(USkeletalMeshComponent* InMesh, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(USkeletalMeshComponent* InMesh, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(class ASkeletalMeshActor* InActor, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(class ASkeletalMeshActor* InActor, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(UObject* InObject, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(UObject* InObject, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(UObject* InObject, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);
	virtual void Montage_JumpToSection(UObject* InObject, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index = 0, const bool &IsLow = false);

#pragma endregion JumpTo

	// Stop
#pragma region

	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class UObject* InObject, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class UObject* InObject, const FECsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime = 0.0f, const bool &IsLow = false);

#pragma endregion Stop

#pragma endregion Animation
};