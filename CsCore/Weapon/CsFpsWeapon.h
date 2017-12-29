// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Weapon/CsWeapon.h"
#include "CsFpsWeapon.generated.h"

// Enums
#pragma region

namespace ECsFpsWeaponCacheMultiValueMember
{
	enum Type
	{
		// Scope
		DoScopePower = ECsWeaponCacheMultiValueMember::ECsWeaponCacheMultiValueMember_MAX,
		MaxScopePower,
		ScopePowerGrowthRate,
		CurrentScopePower,
		LastScopePower,

		ECsFpsWeaponCacheMultiValueMember_MAX,
	};
}

namespace ECsFpsWeaponCacheMultiValueMember
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		// Scope
		const TCsString DoScopePower = TCsString(TEXT("DoScopePower"), TEXT("doscopepower"), TEXT("do scope power"));
		const TCsString MaxScopePower = TCsString(TEXT("MaxScopePower"), TEXT("maxscopepower"), TEXT("maxscopepower"));
		const TCsString ScopePowerGrowthRate = TCsString(TEXT("ScopePowerGrowthRate"), TEXT("scopepowergrowthrate"), TEXT("scopepowergrowthrate"));
		const TCsString CurrentScopePower = TCsString(TEXT("CurrentScopePower"), TEXT("currentscopepower"), TEXT("currentscopepower"));
		const TCsString LastScopePower = TCsString(TEXT("LastScopePower"), TEXT("lastscopepower"), TEXT("lastscopepower"));
	}

	inline FString ToString(const Type &EType)
	{
		// Scope
		if (EType == Type::DoScopePower) { return Str::DoScopePower.Value; }
		if (EType == Type::MaxScopePower) { return Str::MaxScopePower.Value; }
		if (EType == Type::ScopePowerGrowthRate) { return Str::ScopePowerGrowthRate.Value; }
		if (EType == Type::CurrentScopePower) { return Str::CurrentScopePower.Value; }
		if (EType == Type::LastScopePower) { return Str::LastScopePower.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	inline Type ToType(const FString &String)
	{
		// Scope
		if (String == Str::DoScopePower) { return Type::DoScopePower; }
		if (String == Str::MaxScopePower) { return Type::MaxScopePower; }
		if (String == Str::ScopePowerGrowthRate) { return Type::ScopePowerGrowthRate; }
		if (String == Str::CurrentScopePower) { return Type::CurrentScopePower; }
		if (String == Str::LastScopePower) { return Type::LastScopePower; }
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

// Data
#pragma region
public:

	TWeakObjectPtr<class ACsData_WeaponMaterialSkin> MyData_WeaponMaterialSkin;

	UFUNCTION(BlueprintCallable, Category = "Data")
	class ACsData_WeaponMaterialSkin* GetMyData_WeaponMaterialSkin();

#pragma endregion Data

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
};
