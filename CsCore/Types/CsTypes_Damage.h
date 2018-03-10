// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Damage.generated.h"
#pragma once

namespace ECsDamageType
{
	enum Type : uint8;
}

typedef ECsDamageType::Type TCsDamageType;

// DamageTypeToString
typedef FString(*TCsDamageTypeToString)(const TCsDamageType&);
// StringToDamageType
typedef TCsDamageType(*TCsStringToDamageType)(const FString&);

#define CS_DECLARE_DAMAGE_TYPE	TCsDamageType DamageType_MAX; \
								uint8 DAMAGE_TYPE_MAX; \
								TCsDamageTypeToString DamageTypeToString; \
								TCsStringToDamageType StringToDamageType;

#define CS_DEFINE_DAMAGE_TYPE	DamageType_MAX = ECsDamageType::ECsDamageType_MAX;\
								DAMAGE_TYPE_MAX = (uint8)DamageType_MAX \
								DamageTypeToString = &ECsDamageType::ToString; \
								StringToDamageType = &ECsDamageType::ToType;

namespace ECsHitType
{
	enum Type : uint8;
}

typedef ECsHitType::Type TCsHitType;

// HitTypeToString
typedef FString(*TCsHitTypeToString)(const TCsHitType&);
// StringToHitType
typedef TCsHitType(*TCsStringToHitType)(const FString&);

#define CS_DECLARE_HIT_TYPE	TCsHitType HitType_MAX; \
							uint8 HIT_TYPE_MAX; \
							TCsHitTypeToString HitTypeToString; \
							TCsStringToHitType StringToHitType;

#define CS_DEFINE_HIT_TYPE	HitType_MAX = ECsHitType::ECsHitType_MAX;\
							HIT_TYPE_MAX = (uint8)HitType_MAX \
							HitTypeToString = &ECsHitType::ToString; \
							StringToHitType = &ECsHitType::ToType

#define CS_INVALID_DAMAGE_TYPE 255
#define CS_INVALID_HIT_TYPE 255

USTRUCT(BlueprintType)
struct FCsDamageEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool IsAllocated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<UObject> Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<UObject> Causer;

	TCsDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 DamageType_Script;

	TCsHitType HitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	uint8 HitType_Script;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	//TEnumAsByte<EProjectileType::Type> ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool HasImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FHitResult HitInfo;

	FCsDamageEvent()
	{
		Reset();
	}
	virtual ~FCsDamageEvent(){}

	FCsDamageEvent& operator=(const FCsDamageEvent& B)
	{
		Damage = B.Damage;
		Instigator = B.Instigator;
		Causer = B.Causer;
		DamageType = B.DamageType;
		DamageType_Script = B.DamageType_Script;
		HitType = B.HitType;
		HitType_Script = B.HitType_Script;
		HasImpulse = B.HasImpulse;
		HitInfo = B.HitInfo;
		return *this;
	}

	bool operator==(const FCsDamageEvent& B) const
	{
		return Damage == B.Damage &&
			   Instigator == B.Instigator &&
			   Causer == B.Causer &&
			   DamageType == B.DamageType &&
			   DamageType_Script == B.DamageType_Script &&
		 	   HitType == B.HitType &&
			   HitType_Script == B.HitType_Script &&
			   HasImpulse == B.HasImpulse;
	}

	bool operator!=(const FCsDamageEvent& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8 &InIndex)
	{
		Index = InIndex;
	}

	void Reset()
	{
		Damage = 0.0f;
		Instigator.Reset();
		Instigator = nullptr;
		Causer.Reset();
		Causer = nullptr;
		DamageType = (TCsDamageType)0;
		DamageType_Script = CS_INVALID_DAMAGE_TYPE;
		HitType = (TCsHitType)0;
		HitType_Script = CS_INVALID_HIT_TYPE;
		HasImpulse = false;
		HitInfo.Reset(0.0f, false);
	}

	void SetDamageType(const TCsDamageType &InDamageType)
	{
		DamageType		  = InDamageType;
		DamageType_Script = (uint8)DamageType;
	}

	void SetHitType(const TCsHitType &InHitType)
	{
		HitType		   = InHitType;
		HitType_Script = (uint8)HitType;
	}

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	T* GetInstigator() { return Cast<T>(GetInstigator()); }

	UObject* GetCauser() { return Causer.IsValid() ? Causer.Get() : nullptr; }
	template<typename T>
	T* GetCauser() { return Cast<T>(GetCauser()); }
};