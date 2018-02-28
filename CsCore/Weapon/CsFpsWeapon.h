// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Weapon/CsWeapon.h"
#include "CsFpsWeapon.generated.h"

// Enums
#pragma region

namespace ECsFpsWeaponCacheMultiValueMember
{
	enum Type
	{
		// Spread
		MovingSpreadBonus = ECsWeaponCacheMultiValueMember::ECsWeaponCacheMultiValueMember_MAX,
		JumpSpreadImpulse,
		ScopeAccuracyBonus,
		// Scope
		DoScopePower,
		MaxScopePower,
		ScopePowerGrowthRate,
		CurrentScopePower,
		LastScopePower,
		// Movement
		DoSlowWhileFiring,
		SlowWhileFiringRate,
		DoKickback,
		DoKickbackOnGround,
		KickbackStrength,

		ECsFpsWeaponCacheMultiValueMember_MAX,
	};
}

namespace ECsFpsWeaponCacheMultiValueMember
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		// Spread
		const TCsString MovingSpreadBonus = TCsString(TEXT("MovingSpreadBonus"), TEXT("movingspreadbonus"), TEXT("moving spread bonus"));
		const TCsString JumpSpreadImpulse = TCsString(TEXT("JumpSpreadImpulse"), TEXT("jumpspreadimpulse"), TEXT("jump spread impulse"));
		const TCsString ScopeAccuracyBonus = TCsString(TEXT("ScopeAccuracyBonus"), TEXT("scopeaccuracybonus"), TEXT("scope accuracy bonus"));
		// Scope
		const TCsString DoScopePower = TCsString(TEXT("DoScopePower"), TEXT("doscopepower"), TEXT("do scope power"));
		const TCsString MaxScopePower = TCsString(TEXT("MaxScopePower"), TEXT("maxscopepower"), TEXT("max scope power"));
		const TCsString ScopePowerGrowthRate = TCsString(TEXT("ScopePowerGrowthRate"), TEXT("scopepowergrowthrate"), TEXT("scope power growth rate"));
		const TCsString CurrentScopePower = TCsString(TEXT("CurrentScopePower"), TEXT("currentscopepower"), TEXT("current scope power"));
		const TCsString LastScopePower = TCsString(TEXT("LastScopePower"), TEXT("lastscopepower"), TEXT("last scope power"));
		// Movement
		const TCsString DoSlowWhileFiring = TCsString(TEXT("DoSlowWhileFiring"), TEXT("doslowwhilefiring"), TEXT("do slow whilefiring"));
		const TCsString SlowWhileFiringRate = TCsString(TEXT("SlowWhileFiringRate"), TEXT("SlowWhileFiringRate"), TEXT("slow while firing rate"));
		const TCsString DoKickback = TCsString(TEXT("DoKickback"), TEXT("dokickback"), TEXT("do kickback"));
		const TCsString DoKickbackOnGround = TCsString(TEXT("DoKickbackOnGround"), TEXT("dokickbackonground"), TEXT("do kickback on ground"));
		const TCsString KickbackStrength = TCsString(TEXT("KickbackStrength"), TEXT("kickbackstrength"), TEXT("kickback strength"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		// Spread
		if (EType == Type::MovingSpreadBonus) { return Str::MovingSpreadBonus.Value; }
		if (EType == Type::JumpSpreadImpulse) { return Str::JumpSpreadImpulse.Value; }
		if (EType == Type::ScopeAccuracyBonus) { return Str::ScopeAccuracyBonus.Value; }
		// Scope
		if (EType == Type::DoScopePower) { return Str::DoScopePower.Value; }
		if (EType == Type::MaxScopePower) { return Str::MaxScopePower.Value; }
		if (EType == Type::ScopePowerGrowthRate) { return Str::ScopePowerGrowthRate.Value; }
		if (EType == Type::CurrentScopePower) { return Str::CurrentScopePower.Value; }
		if (EType == Type::LastScopePower) { return Str::LastScopePower.Value; }
		// Movement
		if (EType == Type::DoSlowWhileFiring) { return Str::DoSlowWhileFiring.Value; }
		if (EType == Type::SlowWhileFiringRate) { return Str::SlowWhileFiringRate.Value; }
		if (EType == Type::DoKickback) { return Str::DoKickback.Value; }
		if (EType == Type::DoKickbackOnGround) { return Str::DoKickbackOnGround.Value; }
		if (EType == Type::KickbackStrength) { return Str::KickbackStrength.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		// Spread
		if (String == Str::MovingSpreadBonus) { return Type::MovingSpreadBonus; }
		if (String == Str::JumpSpreadImpulse) { return Type::JumpSpreadImpulse; }
		if (String == Str::ScopeAccuracyBonus) { return Type::ScopeAccuracyBonus; }
		// Scope
		if (String == Str::DoScopePower) { return Type::DoScopePower; }
		if (String == Str::MaxScopePower) { return Type::MaxScopePower; }
		if (String == Str::ScopePowerGrowthRate) { return Type::ScopePowerGrowthRate; }
		if (String == Str::CurrentScopePower) { return Type::CurrentScopePower; }
		if (String == Str::LastScopePower) { return Type::LastScopePower; }
		// Movement
		if (String == Str::DoSlowWhileFiring) { return Type::DoSlowWhileFiring; }
		if (String == Str::SlowWhileFiringRate) { return Type::SlowWhileFiringRate; }
		if (String == Str::DoKickback) { return Type::DoKickback; }
		if (String == Str::DoKickbackOnGround) { return Type::DoKickbackOnGround; }
		if (String == Str::KickbackStrength) { return Type::KickbackStrength; }
		return Type::ECsFpsWeaponCacheMultiValueMember_MAX;
	}
}

#define ECS_FPS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX (uint8)ECsFpsWeaponCacheMultiValueMember::ECsFpsWeaponCacheMultiValueMember_MAX
typedef ECsFpsWeaponCacheMultiValueMember::Type TCsFpsWeaponCacheMultiValueMember;

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsFpsWeapon : public ACsWeapon
{
	GENERATED_UCLASS_BODY()

// Members
#pragma region

	virtual void InitMultiValueMembers() override;

	// Set
#pragma region

	virtual void SetMemberValue_float(const uint8 &Member, const int32 &Index, const float &Value) override;
	virtual void SetMemberValue_Script_float(const FString &MemberName, const int32 &Index, const float &Value) override;

	virtual void SetMultiValueMembers() override;

#pragma endregion Set

	// Get
#pragma region

	virtual bool GetMemberValue_bool(const uint8 &Member, const int32 &Index) override;
	virtual bool GetMemberValue_Script_bool(const FString &MemberName, const int32 &Index) override;

	virtual float GetMemberValue_float(const uint8 &Member, const int32 &Index) override;
	virtual float GetMemberValue_Script_float(const FString &MemberName, const int32 &Index) override;

#pragma endregion Get

#pragma endregion Members

// Data
#pragma region
public:

	TWeakObjectPtr<class ACsData_WeaponMaterialSkin> MyData_WeaponMaterialSkin;

	UFUNCTION(BlueprintCallable, Category = "Data")
	class ACsData_WeaponMaterialSkin* GetMyData_WeaponMaterialSkin();

	template<typename T>
	T* GetMyData_WeaponMaterialSkin()
	{
		return Cast<T>(GetMyData_WeaponMaterialSkin());
	}

#pragma endregion Data

// State
#pragma region

	virtual void OnTick(const float &DeltaSeconds) override;
	virtual void Disable() override;
	virtual void Show() override;
	virtual void Hide() override;

#pragma endregion State

// Mesh
#pragma region
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh1P;

	void SetMesh1P();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh3P;

	void SetMesh3P();

	USkeletalMeshComponent* GetMesh(const TCsViewType &ViewType);
	USkeletalMeshComponent* GetCurrentMesh();

	bool UseMesh3PLow;
	bool UseMeleeAttachment;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeleeAttachment1P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeleeAttachment3P;

protected:

	TArray<class UMaterialInstanceDynamic*> MeshMIDs1P;
	TArray<class UMaterialInstanceDynamic*> MeshMIDs3P;

#pragma endregion Mesh

// Firing
#pragma region

	virtual FVector GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode) override;

	// Spread

	FCsWeapon_TArrayRef_float MovingSpreadBonus;
	virtual float GetMovingSpreadBonus(const TCsWeaponFireMode &FireMode);
	FCsWeapon_TArrayRef_float JumpSpreadImpulse;
	virtual float GetJumpSpreadImpulse(const TCsWeaponFireMode &FireMode);
	FCsWeapon_TArrayRef_float ScopeAccuracyBonus;
	virtual float GetScopeAccuracyBonus(const TCsWeaponFireMode &FireMode);

	UPROPERTY()
	bool Last_OwnerIsFalling;

	// Scope

	TCsData_Weapon_FireMode ScopeDataFireMode;

	bool IsScopeActive;
	bool Last_IsScopeActive;
	bool IsScopeActive_Toggle;
	float ScopeActiveStartTime;

	FCsWeapon_TArrayRef_bool DoScopePower;
	FCsWeapon_TArrayRef_float MaxScopePower;
	virtual float GetMaxScopePower(const TCsWeaponFireMode &FireMode);
	FCsWeapon_TArrayRef_float ScopePowerGrowthRate;
	virtual float GetScopePowerGrowthRate(const TCsWeaponFireMode &FireMode);

	FCsWeapon_TArray_float CurrentScopePower;
	FCsWeapon_TArray_float LastScopePower;

	virtual void FireProjectile_Internal(const TCsWeaponFireMode &FireMode, FCsProjectileFireCache* Cache) override;

#pragma endregion Firing

// Movement
#pragma region

	TCsData_Weapon_FireMode MovementDataFireMode;

	FCsWeapon_TArrayRef_bool DoSlowWhileFiring;
	FCsWeapon_TArrayRef_float SlowWhileFiringRate;
	FCsWeapon_TArrayRef_bool DoKickback;
	FCsWeapon_TArrayRef_bool DoKickbackOnGround;
	FCsWeapon_TArrayRef_float KickbackStrength;

#pragma endregion Movement
};
