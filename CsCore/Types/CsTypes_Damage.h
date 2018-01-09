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
	AActor* Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	AActor* Causer;

	TCsDamageType DamageType;

	TCsHitType HitType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	//TEnumAsByte<EProjectileType::Type> ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool HasImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FHitResult HitInfo;

	FCsDamageEvent(){}
	virtual ~FCsDamageEvent(){}

	FCsDamageEvent& operator=(const FCsDamageEvent& B)
	{
		Damage = B.Damage;
		Instigator = B.Instigator;
		Causer = B.Causer;
		DamageType = B.DamageType;
		HitType = B.HitType;
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
		 	   HitType == B.HitType &&
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
		Instigator = nullptr;
		Causer = nullptr;
		//DamageType = B.DamageType;
		//HitType = B.HitType;
		HasImpulse = false;
		HitInfo.Reset(0.0f, false);
	}
};