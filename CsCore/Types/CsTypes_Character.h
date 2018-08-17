// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Character.generated.h"
#pragma once

// CharacterAnim

USTRUCT(BlueprintType)
struct CSCORE_API FECsCharacterAnim : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsCharacterAnim() {}
	FECsCharacterAnim(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsCharacterAnim(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsCharacterAnim() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsCharacterAnim& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsCharacterAnim : public TCsEnumStructMap<FECsCharacterAnim, uint8>
{
protected:
	EMCsCharacterAnim() {}
	EMCsCharacterAnim(const EMCsCharacterAnim &) = delete;
	EMCsCharacterAnim(EMCsCharacterAnim &&) = delete;
public:
	~EMCsCharacterAnim() {}
private:
	static EMCsCharacterAnim* Instance;

public:
	static EMCsCharacterAnim& Get();
};

// CharacterBlendSpace

USTRUCT(BlueprintType)
struct CSCORE_API FECsCharacterBlendSpace : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsCharacterBlendSpace() {}
	FECsCharacterBlendSpace(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsCharacterBlendSpace(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsCharacterBlendSpace() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsCharacterBlendSpace& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsCharacterBlendSpace : public TCsEnumStructMap<FECsCharacterBlendSpace, uint8>
{
protected:
	EMCsCharacterBlendSpace() {}
	EMCsCharacterBlendSpace(const EMCsCharacterBlendSpace &) = delete;
	EMCsCharacterBlendSpace(EMCsCharacterBlendSpace &&) = delete;
public:
	~EMCsCharacterBlendSpace() {}
private:
	static EMCsCharacterBlendSpace* Instance;

public:
	static EMCsCharacterBlendSpace& Get();
};


// CharacterAnimBlueprint

USTRUCT(BlueprintType)
struct CSCORE_API FECsCharacterAnimBlueprint : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsCharacterAnimBlueprint() {}
	FECsCharacterAnimBlueprint(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsCharacterAnimBlueprint(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsCharacterAnimBlueprint() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsCharacterAnimBlueprint& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsCharacterAnimBlueprint : public TCsEnumStructMap<FECsCharacterAnimBlueprint, uint8>
{
protected:
	EMCsCharacterAnimBlueprint() {}
	EMCsCharacterAnimBlueprint(const EMCsCharacterAnimBlueprint &) = delete;
	EMCsCharacterAnimBlueprint(EMCsCharacterAnimBlueprint &&) = delete;
public:
	~EMCsCharacterAnimBlueprint() {}
private:
	static EMCsCharacterAnimBlueprint* Instance;

public:
	static EMCsCharacterAnimBlueprint& Get();
};

namespace ECsCharacterAnimVariation
{
	enum Type : uint8;
}

typedef ECsCharacterAnimVariation::Type TCsCharacterAnimVariation;

// CharacterAnimVariationToString
typedef const FString&(*TCsCharacterAnimVariationToString)(const TCsCharacterAnimVariation&);
// StringToCharacterAnim
typedef TCsCharacterAnimVariation(*TCsStringToCharacterAnimVariation)(const FString&);

#define CS_DECLARE_CHARACTER_ANIM_VARIATION	TCsCharacterAnimVariation CharacterAnimVariation_MAX; \
											uint8 CHARACTER_ANIM_VARIATION_MAX; \
											TCsCharacterAnimVariationToString CharacterAnimVariationToString; \
											TCsStringToCharacterAnimVariation StringToCharacterAnimVariation;

#define CS_DEFINE_CHARACTER_ANIM_VARIATION	CharacterAnimVariation_MAX = ECsCharacterAnimVariation::ECsCharacterAnimVariation_MAX;\
											CHARACTER_ANIM_VARIATION_MAX = (uint8)CharacterAnimVariation_MAX \
											CharacterAnimVariationToString = &ECsCharacterAnimVariation::ToString; \
											StringToCharacterAnimVariation = &ECsCharacterAnimVariation::ToType;

// CharacterAnimVariation

USTRUCT(BlueprintType)
struct CSCORE_API FECsCharacterAnimVariation : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsCharacterAnimVariation() {}
	FECsCharacterAnimVariation(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsCharacterAnimVariation(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsCharacterAnimVariation() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsCharacterAnimVariation& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsCharacterAnimVariation : public TCsEnumStructMap<FECsCharacterAnimVariation, uint8>
{
protected:
	EMCsCharacterAnimVariation() {}
	EMCsCharacterAnimVariation(const EMCsCharacterAnimVariation &) = delete;
	EMCsCharacterAnimVariation(EMCsCharacterAnimVariation &&) = delete;
public:
	~EMCsCharacterAnimVariation() {}
private:
	static EMCsCharacterAnimVariation* Instance;

public:
	static EMCsCharacterAnimVariation& Get();
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsHeadCollision
{
	GENERATED_USTRUCT_BODY()

	/** Radius of collision sphere around head. Used for in Big Head Mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius;

	/** Name of the bone / joint where the head collision will be checked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FName BoneName;

	/** Offset from BoneName from where the head collision will be checked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FVector Offset;

	FCsHeadCollision() {}
	~FCsHeadCollision() {}

	FORCEINLINE FCsHeadCollision& operator=(const FCsHeadCollision& B)
	{
		Radius = B.Radius;
		BoneName = B.BoneName;
		Offset = B.Offset;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsHeadCollision& B) const
	{
		return Radius != B.Radius && BoneName != BoneName && Offset == B.Offset;
	}

	FORCEINLINE bool operator!=(const FCsHeadCollision& B) const
	{
		return !(*this == B);		
	}
};

/*
UENUM(BlueprintType)
namespace ECsCharacterJumpMovementState
{
	enum Type
	{
		None								UMETA(DisplayName = "None"),
		Up									UMETA(DisplayName = "Up"),
		Down								UMETA(DisplayName = "Down"),
		ECsCharacterJumpMovementState_MAX	UMETA(Hidden),
	};
}

typedef ECsCharacterJumpMovementState::Type TCsCharacterJumpMovementState;

struct CSCORE_API EMCsFpvAnimMember : public TCsEnumMap<ECsFpvAnimMember::Type>
{
protected:
	EMCsFpvAnimMember() {}
	EMCsFpvAnimMember(const EMCsFpvAnimMember &) = delete;
	EMCsFpvAnimMember(EMCsFpvAnimMember &&) = delete;
public:
	~EMCsFpvAnimMember() {}
private:
	static EMCsFpvAnimMember* Instance;

public:
	static EMCsFpvAnimMember& Get();
};

namespace ECsFpvAnimMember
{
	namespace Ref
	{
		extern CSCORE_API const Type Anim1P;
		extern CSCORE_API const Type Anim3P;
		extern CSCORE_API const Type Anim3P_Low;
		extern CSCORE_API const Type AnimVR;
		extern CSCORE_API const Type ECsFpvAnimMember_MAX;
	}

	FORCEINLINE const FString& ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimMember::Get().ToString(Ref::AnimVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}
*/