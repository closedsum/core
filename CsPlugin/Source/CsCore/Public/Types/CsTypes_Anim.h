// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"

#include "CsTypes_Anim.generated.h"
#pragma once

namespace NCsAnimCached
{
	namespace Str
	{
		extern CSCORE_API const FString Empty;// = TEXT("");

		extern CSCORE_API const FString AnimSequence;// = TEXT("AnimSequence");
		extern CSCORE_API const FString Anim_Sequence;// = TEXT("Anim Sequence");
		extern CSCORE_API const FString AnimMontage;// = TEXT("AnimMontage");
		extern CSCORE_API const FString Anim_Montage;// = TEXT("Anim Montage");
		extern CSCORE_API const FString BlendSpace1D;// = TEXT("BlendSpace1D");
		extern CSCORE_API const FString Blend_Space_1D;// = TEXT("Blend Space 1D");
		extern CSCORE_API const FString BlendSpace;// = TEXT("BlendSpace");
		extern CSCORE_API const FString Blend_Space;// = TEXT("Blend Space");
		extern CSCORE_API const FString AimOffsetBlendSpace;// = TEXT("AimOffsetBlendSpace");
		extern CSCORE_API const FString Aim_Offset_Blend_Space;// = TEXT("Aim Offset Blend Space");
	}
}

// FpvAnimMember
#pragma region

UENUM(BlueprintType)
enum class ECsFpvAnimMember : uint8
{
	Anim1P					UMETA(DisplayName = "Anim1P"),
	Anim3P					UMETA(DisplayName = "Anim3P"),
	Anim3P_Low				UMETA(DisplayName = "Anim3P_Low"),
	AnimVR					UMETA(DisplayName = "AnimVR"),
	ECsFpvAnimMember_MAX	UMETA(Hidden),
};


struct CSCORE_API EMCsFpvAnimMember: public TCsEnumMap<ECsFpvAnimMember>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFpvAnimMember, ECsFpvAnimMember)
};

namespace NCsFpvAnimMember
{
	typedef ECsFpvAnimMember Type;

	namespace Ref
	{
		extern CSCORE_API const Type Anim1P;
		extern CSCORE_API const Type Anim3P;
		extern CSCORE_API const Type Anim3P_Low;
		extern CSCORE_API const Type AnimVR;
		extern CSCORE_API const Type ECsFpvAnimMember_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FString& ToStringFromViewType(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimMember::Get().ToString(Ref::AnimVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#pragma endregion FpvAnimMember

// FCsAnimSequence
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimSequence> Anim;


	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

	UPROPERTY(Transient)
	UAnimSequence* Anim_Internal;

public:

	FCsAnimSequence() :
		Anim(nullptr),
		Anim_LoadFlags(0),
		Anim_Internal(nullptr)
	{
	}

	FORCEINLINE UAnimSequence* Get()
	{
		return Anim_Internal;
	}

	FORCEINLINE FCsAnimSequence& operator=(const FCsAnimSequence& B)
	{
		Anim = B.Anim;
		Anim_LoadFlags = B.Anim_LoadFlags;
		Anim_Internal = B.Anim_Internal;
		return *this;
	}
};

#pragma endregion FCsAnimSequence

// FCsFpvAnimSequence
#pragma region

class UAnimSequence;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimSequence> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimSequence> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimSequence> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimSequence> AnimVR;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

	UPROPERTY(Transient)
	UAnimSequence* Anim1P_Internal;

	UPROPERTY(Transient)
	UAnimSequence* Anim3P_Internal;

	UPROPERTY(Transient)
	UAnimSequence* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	UAnimSequence* AnimVR_Internal;

public:

	FCsFpvAnimSequence() :
		Anim1P(nullptr),
		Anim3P(nullptr),
		Anim3P_Low(nullptr),
		AnimVR(nullptr),
		Anim1P_LoadFlags(0),
		Anim3P_LoadFlags(0),
		Anim3P_Low_LoadFlags(0),
		AnimVR_LoadFlags(0),
		Anim1P_Internal(nullptr),
		Anim3P_Internal(nullptr),
		Anim3P_Low_Internal(nullptr),
		AnimVR_Internal(nullptr)
	{
	}

	FORCEINLINE TSoftObjectPtr<UAnimSequence> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	FORCEINLINE UAnimSequence* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}
};

#pragma endregion FCsFpvAnimSequence

// FCsAnimMontage
#pragma region

class UAnimMontage;

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimMontage> Anim;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

	UPROPERTY(Transient)
	UAnimMontage* Anim_Internal;

public:

	FCsAnimMontage() :
		Anim(nullptr),
		Anim_LoadFlags(0),
		Anim_Internal(nullptr)
	{
	}

	FORCEINLINE UAnimMontage* Get()
	{
		return Anim_Internal;
	}
};

#pragma endregion FCsAnimMontage

// FCsFpvAnimMontage
#pragma region

class UAnimMontage;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimMontage> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimMontage> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimMontage> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAnimMontage> AnimVR;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

	UPROPERTY(Transient)
	UAnimMontage* Anim1P_Internal;

	UPROPERTY(Transient)
	UAnimMontage* Anim3P_Internal;

	UPROPERTY(Transient)
	UAnimMontage* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	UAnimMontage* AnimVR_Internal;

public:

	FCsFpvAnimMontage() :
		Anim1P(nullptr),
		Anim3P(nullptr),
		Anim3P_Low(nullptr),
		AnimVR(nullptr),
		Anim1P_LoadFlags(0),
		Anim3P_LoadFlags(0),
		Anim3P_Low_LoadFlags(0),
		AnimVR_LoadFlags(0),
		Anim1P_Internal(nullptr),
		Anim3P_Internal(nullptr),
		Anim3P_Low_Internal(nullptr),
		AnimVR_Internal(nullptr)
	{
	}

	FORCEINLINE TSoftObjectPtr<UAnimMontage> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	FORCEINLINE UAnimMontage* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}
};

#pragma endregion FCsFpvAnimMontage

// FCsTArrayAnimMontage
#pragma region

class UAnimMontage;

USTRUCT()
struct CSCORE_API FCsTArrayAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UAnimMontage>> Anims;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anims_LoadFlags;

	UPROPERTY(Transient)
	TArray<UAnimMontage*> Anims_Internal;

public:
	FCsTArrayAnimMontage() :
		Anims(),
		Anims_LoadFlags(0),
		Anims_Internal()
	{
	}

	FORCEINLINE TArray<UAnimMontage*>* Get()
	{
		return &Anims_Internal;
	}

	FORCEINLINE UAnimMontage* Get(const int32 Index)
	{
		return Index < Anims_Internal.Num() ? Anims_Internal[Index] : NULL;
	}

	FORCEINLINE uint8 Find(UAnimMontage* Anim)
	{
		int index;
		if (Anims_Internal.Find(Anim, index))
			return (uint8)index;
		else
			return INDEX_NONE;
	}
};

#pragma endregion FCsTArrayAnimMontage

// FpvAnimBlueprintMember
#pragma region

UENUM(BlueprintType)
enum class ECsFpvAnimBlueprintMember : uint8
{
	Blueprint1P						UMETA(DisplayName = "Blueprint1P"),
	Blueprint3P						UMETA(DisplayName = "Blueprint3P"),
	Blueprint3P_Low					UMETA(DisplayName = "Blueprint3P_Low"),
	BlueprintVR						UMETA(DisplayName = "BlueprintVR"),
	ECsFpvAnimBlueprintMember_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsFpvAnimBlueprintMember : public TCsEnumMap<ECsFpvAnimBlueprintMember>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsFpvAnimBlueprintMember)
};

namespace NCsFpvAnimBlueprintMember
{
	typedef ECsFpvAnimBlueprintMember Type;

	namespace Ref
	{
		extern CSCORE_API const Type Blueprint1P;
		extern CSCORE_API const Type Blueprint3P;
		extern CSCORE_API const Type Blueprint3P_Low;
		extern CSCORE_API const Type BlueprintVR;
		extern CSCORE_API const Type ECsFpvAnimBlueprintMember_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FString& ToStringFromViewType(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::BlueprintVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#pragma endregion FpvAnimBlueprintMember

// FCsAnimBlueprint
#pragma region

class UAnimBlueprintGeneratedClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimBlueprint> Blueprint;


	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* Blueprint_Internal;

public:

	FCsAnimBlueprint() :
		Blueprint(nullptr),
		Blueprint_LoadFlags(0),
		Blueprint_Internal(nullptr)
	{
	}

	FORCEINLINE UAnimBlueprintGeneratedClass* Get()
	{
		return Blueprint_Internal;
	}
};

#pragma endregion FCsAnimBlueprint

// FCsFpvAnimBlueprint
#pragma region

class UAnimBlueprint;
class UAnimBlueprintGeneratedClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimBlueprint> Blueprint1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimBlueprint> Blueprint3P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimBlueprint> Blueprint3P_Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimBlueprint> BlueprintVR;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint1P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint3P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlueprintVR_LoadFlags;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* Blueprint1P_Internal;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* Blueprint3P_Internal;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* Blueprint3P_Low_Internal;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* BlueprintVR_Internal;

public:

	FCsFpvAnimBlueprint() :
		Blueprint1P(nullptr),
		Blueprint3P(nullptr),
		Blueprint3P_Low(nullptr),
		BlueprintVR(nullptr),
		Blueprint1P_LoadFlags(0),
		Blueprint3P_LoadFlags(0),
		Blueprint3P_Low_LoadFlags(0),
		BlueprintVR_LoadFlags(0),
		Blueprint1P_Internal(nullptr),
		Blueprint3P_Internal(nullptr),
		Blueprint3P_Low_Internal(nullptr),
		BlueprintVR_Internal(nullptr)
	{
	}

	FORCEINLINE UAnimBlueprintGeneratedClass* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blueprint1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blueprint3P_Low_Internal : Blueprint3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlueprintVR_Internal;
		return Blueprint3P_Internal;
	}
};

#pragma endregion FCsFpvAnimBlueprint

// FpvAnimBlendSpaceMember
#pragma region

UENUM(BlueprintType)
enum class ECsFpvAnimBlendSpaceMember : uint8
{
	Blend1P							UMETA(DisplayName = "Blend1P"),
	Blend3P							UMETA(DisplayName = "Blend3P"),
	Blend3P_Low						UMETA(DisplayName = "Blend3P_Low"),
	BlendVR							UMETA(DisplayName = "BlendVR"),
	ECsFpvAnimBlendSpaceMember_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsFpvAnimBlendSpaceMember : public TCsEnumMap<ECsFpvAnimBlendSpaceMember>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsFpvAnimBlendSpaceMember)
};

namespace NCsFpvAnimBlendSpaceMember
{
	typedef ECsFpvAnimBlendSpaceMember Type;

	namespace Ref
	{
		extern CSCORE_API const Type Blend1P;
		extern CSCORE_API const Type Blend3P;
		extern CSCORE_API const Type Blend3P_Low;
		extern CSCORE_API const Type BlendVR;
		extern CSCORE_API const Type ECsFpvAnimBlendSpaceMember_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FString& ToStringFromViewType(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::BlendVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#pragma endregion FpvAnimBlendSpaceMember

// FCsBlendSpace1D
#pragma region

class UBlendSpace1D;

USTRUCT(BlueprintType)
struct CSCORE_API FCsBlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBlendSpace1D> Blend;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend_Internal;

public:

	FCsBlendSpace1D() :
		Blend(nullptr),
		Blend_LoadFlags(0),
		Blend_Internal(nullptr)
	{
	}

	FORCEINLINE UBlendSpace1D* Get()
	{
		return Blend_Internal;
	}
};

#pragma endregion FCsBlendSpace1D

// FCsFpvBlendSpace1D
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvBlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBlendSpace1D> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBlendSpace1D> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBlendSpace1D> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBlendSpace1D> BlendVR;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend1P_Internal;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend3P_Internal;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	UBlendSpace1D* BlendVR_Internal;

public:

	FCsFpvBlendSpace1D() :
		Blend1P(nullptr),
		Blend3P(nullptr),
		Blend3P_Low(nullptr),
		BlendVR(nullptr),
		Blend1P_LoadFlags(0),
		Blend3P_LoadFlags(0),
		Blend3P_Low_LoadFlags(0),
		BlendVR_LoadFlags(0),
		Blend1P_Internal(nullptr),
		Blend3P_Internal(nullptr),
		Blend3P_Low_Internal(nullptr),
		BlendVR_Internal(nullptr)
	{
	}

	FORCEINLINE UBlendSpace1D* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UBlendSpace1D> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}
};

#pragma endregion FCsFpvBlendSpace1D

// FCsBlendSpace
#pragma region

class UBlendSpace;

USTRUCT(BlueprintType)
struct CSCORE_API FCsBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBlendSpace> Blend;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace* Blend_Internal;

public:

	FCsBlendSpace() :
		Blend(nullptr),
		Blend_LoadFlags(0),
		Blend_Internal(nullptr)
	{
	}

	FORCEINLINE UBlendSpace* Get()
	{
		return Blend_Internal;
	}
};

#pragma endregion FCsBlendSpace

// FCsFpvBlendSpace
#pragma region

class UBlendSpace;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace> BlendVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace* Blend1P_Internal;

	UPROPERTY(Transient)
	UBlendSpace* Blend3P_Internal;

	UPROPERTY(Transient)
	UBlendSpace* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	UBlendSpace* BlendVR_Internal;

public:

	FCsFpvBlendSpace() :
		Blend1P(nullptr),
		Blend3P(nullptr),
		Blend3P_Low(nullptr),
		BlendVR(nullptr),
		Blend1P_LoadFlags(0),
		Blend3P_LoadFlags(0),
		Blend3P_Low_LoadFlags(0),
		BlendVR_LoadFlags(0),
		Blend1P_Internal(nullptr),
		Blend3P_Internal(nullptr),
		Blend3P_Low_Internal(nullptr),
		BlendVR_Internal(nullptr)
	{
	}

	FORCEINLINE UBlendSpace* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UBlendSpace> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}
};

#pragma endregion FCsFpvBlendSpace

// FCsAimOffset
#pragma region

class UAimOffsetBlendSpace;

USTRUCT(BlueprintType)
struct CSCORE_API FCsAimOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend_LoadFlags;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend_Internal;

public:

	FCsAimOffset() :
		Blend(nullptr),
		Blend_LoadFlags(0),
		Blend_Internal(nullptr)
	{
	}

	FORCEINLINE UAimOffsetBlendSpace* Get()
	{
		return Blend_Internal;
	}
};

#pragma endregion FCsAimOffset

// FCsFpvAimOffset
#pragma region

class UAimOffsetBlendSpace;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAimOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UAimOffsetBlendSpace> BlendVR;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend1P_Internal;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend3P_Internal;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* BlendVR_Internal;

public:

	FCsFpvAimOffset() :
		Blend1P(nullptr),
		Blend3P(nullptr),
		Blend3P_Low(nullptr),
		BlendVR(nullptr),
		Blend1P_LoadFlags(0),
		Blend3P_LoadFlags(0),
		Blend3P_Low_LoadFlags(0),
		BlendVR_LoadFlags(0),
		Blend1P_Internal(nullptr),
		Blend3P_Internal(nullptr),
		Blend3P_Low_Internal(nullptr),
		BlendVR_Internal(nullptr)
	{
	}

	FORCEINLINE UAimOffsetBlendSpace* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UAimOffsetBlendSpace> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}
};

#pragma endregion FCsFpvAimOffset

// AdditiveBasePoseType
#pragma region

UENUM(BlueprintType)
enum class ECsAdditiveBasePoseType : uint8
{
	/** Will be deprecated. */
	ABPT_None		UMETA(DisplayName = "None"),
	/** Use the Skeleton's ref pose as base. */
	ABPT_RefPose	UMETA(DisplayName = "Skeleton Reference Pose"),
	/** Use a whole animation as a base pose. BasePoseSeq must be set. */
	ABPT_AnimScaled	UMETA(DisplayName = "Selected animation scaled"),
	/** Use one frame of an animation as a base pose. BasePoseSeq and RefFrameIndex must be set (RefFrameIndex will be clamped). */
	ABPT_AnimFrame	UMETA(DisplayName = "Selected animation frame"),
	ABPT_MAX		UMETA(Hidden),
};

struct CSCORE_API EMCsAdditiveBasePoseType : public TCsEnumMap<ECsAdditiveBasePoseType>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsAdditiveBasePoseType)
};

namespace NCsAdditiveBasePoseType
{
	typedef ECsAdditiveBasePoseType Type;

	namespace Ref
	{
		extern CSCORE_API const Type ABPT_None;
		extern CSCORE_API const Type ABPT_RefPose;
		extern CSCORE_API const Type ABPT_AnimScaled;
		extern CSCORE_API const Type ABPT_AnimFrame;
		extern CSCORE_API const Type ABPT_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FString& ToString(const EAdditiveBasePoseType &EType)
	{
		if (EType == EAdditiveBasePoseType::ABPT_None) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_None); }
		if (EType == EAdditiveBasePoseType::ABPT_RefPose) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_RefPose); }
		if (EType == EAdditiveBasePoseType::ABPT_AnimScaled) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_AnimScaled); }
		if (EType == EAdditiveBasePoseType::ABPT_AnimFrame) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_AnimFrame); }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EAdditiveBasePoseType ToBaseType(const FString &String)
	{
		const Type& Enum = EMCsAdditiveBasePoseType::Get().ToType(String);

		if (Enum == Ref::ABPT_None) { return EAdditiveBasePoseType::ABPT_None; }
		if (Enum == Ref::ABPT_RefPose) { return EAdditiveBasePoseType::ABPT_RefPose; }
		if (Enum == Ref::ABPT_AnimScaled) { return EAdditiveBasePoseType::ABPT_AnimScaled; }
		if (Enum == Ref::ABPT_AnimFrame) { return EAdditiveBasePoseType::ABPT_AnimFrame; }
		return EAdditiveBasePoseType::ABPT_MAX;
	}
}

#pragma endregion AdditiveBasePoseType

// AdditiveAnimationType
#pragma region

UENUM(BlueprintType)
enum class ECsAdditiveAnimationType : uint8
{
	/** No additive. */
	AAT_None					UMETA(DisplayName = "None"),
	/* Create Additive from LocalSpace Base. */
	AAT_LocalSpaceBase			UMETA(DisplayName = "Local Space"),
	/* Create Additive from MeshSpace Rotation Only, Translation still will be LocalSpace. */
	AAT_RotationOffsetMeshSpace	UMETA(DisplayName = "Mesh Space"),
	AAT_MAX						UMETA(Hidden),
};

struct CSCORE_API EMCsAdditiveAnimationType : public TCsEnumMap<ECsAdditiveAnimationType>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsAdditiveAnimationType)
};

namespace NCsAdditiveAnimationType
{
	typedef ECsAdditiveAnimationType Type;

	namespace Ref
	{
		extern CSCORE_API const Type AAT_None;
		extern CSCORE_API const Type AAT_LocalSpaceBase;
		extern CSCORE_API const Type AAT_RotationOffsetMeshSpace;
		extern CSCORE_API const Type AAT_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FString& ToString(const EAdditiveAnimationType &EType)
	{
		if (EType == EAdditiveAnimationType::AAT_None) { return EMCsAdditiveAnimationType::Get().ToString(Ref::AAT_None); }
		if (EType == EAdditiveAnimationType::AAT_LocalSpaceBase) { return EMCsAdditiveAnimationType::Get().ToString(Ref::AAT_LocalSpaceBase); }
		if (EType == EAdditiveAnimationType::AAT_RotationOffsetMeshSpace) { return EMCsAdditiveAnimationType::Get().ToString(Ref::AAT_RotationOffsetMeshSpace); }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EAdditiveAnimationType ToBaseType(const FString &String)
	{
		const Type& Enum = EMCsAdditiveAnimationType::Get().ToType(String);

		if (Enum == Ref::AAT_None) { return EAdditiveAnimationType::AAT_None; }
		if (Enum == Ref::AAT_LocalSpaceBase) { return EAdditiveAnimationType::AAT_LocalSpaceBase; }
		if (Enum == Ref::AAT_RotationOffsetMeshSpace) { return EAdditiveAnimationType::AAT_RotationOffsetMeshSpace; }
		return EAdditiveAnimationType::AAT_MAX;
	}
}

#pragma endregion AdditiveAnimationType