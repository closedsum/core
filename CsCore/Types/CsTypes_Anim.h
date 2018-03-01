// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Animation/BlendSpace.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AnimBlueprint.h"

#include "CsTypes_Anim.generated.h"
#pragma once

// Anim
#pragma region

namespace ECsAnimCachedString
{
	namespace Str
	{
		const FString Empty = TEXT("");

		const FString AnimSequence = TEXT("AnimSequence");
		const FString Anim_Sequence = TEXT("Anim Sequence");
		const FString AnimMontage = TEXT("AnimMontage");
		const FString Anim_Montage = TEXT("Anim Montage");
	}
}

UENUM(BlueprintType)
namespace ECsFpsAnimMember
{
	enum Type
	{
		Anim1P					UMETA(DisplayName = "Anim1P"),
		Anim3P					UMETA(DisplayName = "Anim3P"),
		Anim3P_Low				UMETA(DisplayName = "Anim3P_Low"),
		AnimVR					UMETA(DisplayName = "AnimVR"),
		ECsFpsAnimMember_MAX	UMETA(Hidden),
	};
}

namespace ECsFpsAnimMember
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Anim1P = TCsString(TEXT("Anim1P"), TEXT("anim1p"), TEXT("anim 1p"));
		const TCsString Anim3P = TCsString(TEXT("Anim3P"), TEXT("anim3p"), TEXT("anim 3p"));
		const TCsString Anim3P_Low = TCsString(TEXT("Anim3P_Low"), TEXT("anim3p_low"), TEXT("anim 3p low"));
		const TCsString AnimVR = TCsString(TEXT("AnimVR"), TEXT("animvr"), TEXT("anim vr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Anim1P) { return Str::Anim1P.Value; }
		if (EType == Type::Anim3P) { return Str::Anim3P.Value; }
		if (EType == Type::Anim3P_Low) { return Str::Anim3P_Low.Value; }
		if (EType == Type::AnimVR) { return Str::AnimVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return Str::Anim1P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return Str::Anim3P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return Str::Anim3P_Low.Value; }
		if (ViewType == ECsViewType::VR) { return Str::AnimVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Anim1P) { return Type::Anim1P; }
		if (String == Str::Anim3P) { return Type::Anim3P; }
		if (String == Str::Anim3P_Low) { return Type::Anim3P_Low; }
		if (String == Str::AnimVR) { return Type::AnimVR; }
		return Type::ECsFpsAnimMember_MAX;
	}
}

#define ECS_FPS_ANIM_MEMBER_MAX (uint8)ECsFpsAnimMember::ECsFpsAnimMember_MAX
typedef ECsFpsAnimMember::Type TCsFpsAnimMember;

USTRUCT(BlueprintType)
struct FCsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim;


	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimSequence* Anim_Internal;

public:

	FCsAnimSequence()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim_LoadFlags, ECsLoadFlags::Game);
	}

	UAnimSequence* Get()
	{
		return Anim_Internal;
	}

	FCsAnimSequence& operator=(const FCsAnimSequence& B)
	{
		Anim = B.Anim;
		Anim_LoadFlags = B.Anim_LoadFlags;
		Anim_Internal = B.Anim_Internal;
		return *this;
	}

	bool operator==(const FCsAnimSequence& B) const
	{
		return Anim == B.Anim && Anim_LoadFlags == B.Anim_LoadFlags && Anim_Internal == B.Anim_Internal;
	}

	bool operator!=(const FCsAnimSequence& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> AnimVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimSequence* Anim1P_Internal;

	UPROPERTY(Transient)
	class UAnimSequence* Anim3P_Internal;

	UPROPERTY(Transient)
	class UAnimSequence* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	class UAnimSequence* AnimVR_Internal;

public:

	FCsFpsAnimSequence()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	TAssetPtr<UAnimSequence> GetAssetPtr(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	UAnimSequence* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	FCsFpsAnimSequence& operator=(const FCsFpsAnimSequence& B)
	{
		Anim1P = B.Anim1P;
		Anim3P = B.Anim3P;
		Anim3P_Low = B.Anim3P_Low;
		AnimVR = B.AnimVR;

		Anim1P_LoadFlags = B.Anim1P_LoadFlags;
		Anim3P_LoadFlags = B.Anim3P_LoadFlags;
		Anim3P_Low_LoadFlags = B.Anim3P_Low_LoadFlags;
		AnimVR_LoadFlags = B.AnimVR_LoadFlags;

		Anim1P_Internal = B.Anim1P_Internal;
		Anim3P_Internal = B.Anim3P_Internal;
		Anim3P_Low_Internal = B.Anim3P_Low_Internal;
		AnimVR_Internal = B.AnimVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsAnimSequence& B) const
	{
		return Anim1P == B.Anim1P && Anim3P == B.Anim3P && Anim3P_Low == B.Anim3P_Low && AnimVR == B.AnimVR &&
			Anim1P_LoadFlags == B.Anim1P_LoadFlags && Anim3P_LoadFlags == B.Anim3P_LoadFlags && Anim3P_Low_LoadFlags == B.Anim3P_Low_LoadFlags && AnimVR_LoadFlags == B.AnimVR_LoadFlags &&
			Anim1P_Internal == B.Anim1P_Internal && Anim3P_Internal == B.Anim3P_Internal && Anim3P_Low_Internal == B.Anim3P_Low_Internal && AnimVR_Internal == B.AnimVR_Internal;
	}

	bool operator!=(const FCsFpsAnimSequence& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim;


	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimMontage* Anim_Internal;

public:

	FCsAnimMontage()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim_LoadFlags, ECsLoadFlags::Game);
	}

	UAnimMontage* Get()
	{
		return Anim_Internal;
	}

	FCsAnimMontage& operator=(const FCsAnimMontage& B)
	{
		Anim = B.Anim;
		Anim_LoadFlags = B.Anim_LoadFlags;
		Anim_Internal = B.Anim_Internal;
		return *this;
	}

	bool operator==(const FCsAnimMontage& B) const
	{
		return Anim == B.Anim && Anim_LoadFlags == B.Anim_LoadFlags && Anim_Internal == B.Anim_Internal;
	}

	bool operator!=(const FCsAnimMontage& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> AnimVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimMontage* Anim1P_Internal;

	UPROPERTY(Transient)
	class UAnimMontage* Anim3P_Internal;

	UPROPERTY(Transient)
	class UAnimMontage* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	class UAnimMontage* AnimVR_Internal;

public:

	FCsFpsAnimMontage()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::GameVR);
	}


	TAssetPtr<UAnimMontage> GetAssetPtr(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	UAnimMontage* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	FCsFpsAnimMontage& operator=(const FCsFpsAnimMontage& B)
	{
		Anim1P = B.Anim1P;
		Anim3P = B.Anim3P;
		Anim3P_Low = B.Anim3P_Low;
		AnimVR = B.AnimVR;

		Anim1P_LoadFlags = B.Anim1P_LoadFlags;
		Anim3P_LoadFlags = B.Anim3P_LoadFlags;
		Anim3P_Low_LoadFlags = B.Anim3P_Low_LoadFlags;
		AnimVR_LoadFlags = B.AnimVR_LoadFlags;

		Anim1P_Internal = B.Anim1P_Internal;
		Anim3P_Internal = B.Anim3P_Internal;
		Anim3P_Low_Internal = B.Anim3P_Low_Internal;
		AnimVR_Internal = B.AnimVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsAnimMontage& B) const
	{
		return Anim1P == B.Anim1P && Anim3P == B.Anim3P && Anim3P_Low == B.Anim3P_Low && AnimVR == B.AnimVR &&
			Anim1P_LoadFlags == B.Anim1P_LoadFlags && Anim3P_LoadFlags == B.Anim3P_LoadFlags && Anim3P_Low_LoadFlags == B.Anim3P_Low_LoadFlags && AnimVR_LoadFlags == B.AnimVR_LoadFlags &&
			Anim1P_Internal == B.Anim1P_Internal && Anim3P_Internal == B.Anim3P_Internal && Anim3P_Low_Internal == B.Anim3P_Low_Internal && AnimVR_Internal == B.AnimVR_Internal;
	}

	bool operator!=(const FCsFpsAnimMontage& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsTArrayAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UAnimMontage>> Anims;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anims_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UAnimMontage*> Anims_Internal;

public:
	FCsTArrayAnimMontage()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anims_LoadFlags, ECsLoadFlags::Game);
	}

	FCsTArrayAnimMontage& operator=(const FCsTArrayAnimMontage& B)
	{
		Anims.Reset();

		const int32 Count = B.Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Anims.Add(B.Anims[I]);
		}
		Anims_LoadFlags = B.Anims_LoadFlags;
		return *this;
	}

	bool operator==(const FCsTArrayAnimMontage& B) const
	{
		int32 Count = Anims.Num();
		int32 CountB = B.Anims.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Anims[I] != B.Anims[I])
				return false;
		}

		Count = Anims_Internal.Num();
		CountB = B.Anims_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Anims_Internal[I] != B.Anims_Internal[I])
				return false;
		}
		return Anims_LoadFlags == B.Anims_LoadFlags;
	}

	bool operator!=(const FCsTArrayAnimMontage& B) const
	{
		return !(*this == B);
	}

	TArray<class UAnimMontage*>* Get()
	{
		return &Anims_Internal;
	}

	class UAnimMontage* Get(const int32 Index)
	{
		return Index < Anims_Internal.Num() ? Anims_Internal[Index] : NULL;
	}

	uint8 Find(UAnimMontage* Anim)
	{
		int index;
		if (Anims_Internal.Find(Anim, index))
			return (uint8)index;
		else
			return INDEX_NONE;
	}
};

UENUM(BlueprintType)
namespace ECsFpsAnimBlueprintMember
{
	enum Type
	{
		Blueprint1P						UMETA(DisplayName = "Blueprint1P"),
		Blueprint3P						UMETA(DisplayName = "Blueprint3P"),
		Blueprint3P_Low					UMETA(DisplayName = "Blueprint3P_Low"),
		BlueprintVR						UMETA(DisplayName = "BlueprintVR"),
		ECsFpsAnimBlueprintMember_MAX	UMETA(Hidden),
	};
}

namespace ECsFpsAnimBlueprintMember
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Blueprint1P = TCsString(TEXT("Blueprint1P"), TEXT("blueprint1p"), TEXT("blueprint 1p"));
		const TCsString Blueprint3P = TCsString(TEXT("Blueprint3P"), TEXT("blueprint3p"), TEXT("blueprint 3p"));
		const TCsString Blueprint3P_Low = TCsString(TEXT("Blueprint3P_Low"), TEXT("blueprint3p_low"), TEXT("blueprint 3p low"));
		const TCsString BlueprintVR = TCsString(TEXT("BlueprintVR"), TEXT("blueprintvr"), TEXT("blueprint vr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Blueprint1P) { return Str::Blueprint1P.Value; }
		if (EType == Type::Blueprint3P) { return Str::Blueprint3P.Value; }
		if (EType == Type::Blueprint3P_Low) { return Str::Blueprint3P_Low.Value; }
		if (EType == Type::BlueprintVR) { return Str::BlueprintVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return Str::Blueprint1P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return Str::Blueprint3P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return Str::Blueprint3P_Low.Value; }
		if (ViewType == ECsViewType::VR) { return Str::BlueprintVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Blueprint1P) { return Type::Blueprint1P; }
		if (String == Str::Blueprint3P) { return Type::Blueprint3P; }
		if (String == Str::Blueprint3P_Low) { return Type::Blueprint3P_Low; }
		if (String == Str::BlueprintVR) { return Type::BlueprintVR; }
		return Type::ECsFpsAnimBlueprintMember_MAX;
	}
}

#define ECS_FPS_ANIM_BLUEPRINT_MEMBER_MAX (uint8)ECsFpsAnimBlueprintMember::ECsFpsAnimBlueprintMember_MAX
typedef ECsFpsAnimBlueprintMember::Type TCsFpsAnimBlueprintMember;

USTRUCT(BlueprintType)
struct FCsAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<class UAnimBlueprint> Blueprint;


	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint_Internal;

public:

	FCsAnimBlueprint()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
	}

	UAnimBlueprintGeneratedClass* Get()
	{
		return Blueprint_Internal;
	}

	FCsAnimBlueprint& operator=(const FCsAnimBlueprint& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_LoadFlags = B.Blueprint_LoadFlags;
		Blueprint_Internal = B.Blueprint_Internal;
		return *this;
	}

	bool operator==(const FCsAnimBlueprint& B) const
	{
		return Blueprint == B.Blueprint && Blueprint_LoadFlags == B.Blueprint_LoadFlags && Blueprint_Internal == B.Blueprint_Internal;
	}

	bool operator!=(const FCsAnimBlueprint& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> Blueprint1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> Blueprint3P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> Blueprint3P_Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> BlueprintVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlueprintVR_LoadFlags;

public:

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint1P_Internal;

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint3P_Internal;

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint3P_Low_Internal;

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* BlueprintVR_Internal;

public:

	FCsFpsAnimBlueprint()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(BlueprintVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(BlueprintVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	UAnimBlueprintGeneratedClass* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blueprint1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blueprint3P_Low_Internal : Blueprint3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlueprintVR_Internal;
		return Blueprint3P_Internal;
	}

	FCsFpsAnimBlueprint& operator=(const FCsFpsAnimBlueprint& B)
	{
		Blueprint1P = B.Blueprint1P;
		Blueprint3P = B.Blueprint3P;
		Blueprint3P_Low = B.Blueprint3P_Low;
		BlueprintVR = B.BlueprintVR;

		Blueprint1P_LoadFlags = B.Blueprint1P_LoadFlags;
		Blueprint3P_LoadFlags = B.Blueprint3P_LoadFlags;
		Blueprint3P_Low_LoadFlags = B.Blueprint3P_Low_LoadFlags;
		BlueprintVR_LoadFlags = B.BlueprintVR_LoadFlags;

		Blueprint1P_Internal = B.Blueprint1P_Internal;
		Blueprint3P_Internal = B.Blueprint3P_Internal;
		Blueprint3P_Low_Internal = B.Blueprint3P_Low_Internal;
		BlueprintVR_Internal = B.BlueprintVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsAnimBlueprint& B) const
	{
		return Blueprint1P == B.Blueprint1P && Blueprint3P == B.Blueprint3P && Blueprint3P_Low == B.Blueprint3P_Low && BlueprintVR == B.BlueprintVR &&
			Blueprint1P_LoadFlags == B.Blueprint1P_LoadFlags && Blueprint3P_LoadFlags == B.Blueprint3P_LoadFlags && Blueprint3P_Low_LoadFlags == B.Blueprint3P_Low_LoadFlags && BlueprintVR_LoadFlags == B.BlueprintVR_LoadFlags &&
			Blueprint1P_Internal == B.Blueprint1P_Internal && Blueprint3P_Internal == B.Blueprint3P_Internal && Blueprint3P_Low_Internal == B.Blueprint3P_Low_Internal && BlueprintVR_Internal == B.BlueprintVR_Internal;
	}

	bool operator!=(const FCsFpsAnimBlueprint& B) const
	{
		return !(*this == B);
	}
};

UENUM(BlueprintType)
namespace ECsFpsAnimBlendSpaceMember
{
	enum Type
	{
		Blend1P							UMETA(DisplayName = "Blend1P"),
		Blend3P							UMETA(DisplayName = "Blend3P"),
		Blend3P_Low						UMETA(DisplayName = "Blend3P_Low"),
		BlendVR							UMETA(DisplayName = "BlendVR"),
		ECsFpsAnimBlendSpaceMember_MAX	UMETA(Hidden),
	};
}

namespace ECsFpsAnimBlendSpaceMember
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Blend1P = TCsString(TEXT("Blend1P"), TEXT("blend1p"), TEXT("blend 1p"));
		const TCsString Blend3P = TCsString(TEXT("Blend3P"), TEXT("blend3p"), TEXT("blend 3p"));
		const TCsString Blend3P_Low = TCsString(TEXT("Blend3P_Low"), TEXT("blend3p_low"), TEXT("blend 3p low"));
		const TCsString BlendVR = TCsString(TEXT("BlendVR"), TEXT("blendvr"), TEXT("blend vr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Blend1P) { return Str::Blend1P.Value; }
		if (EType == Type::Blend3P) { return Str::Blend3P.Value; }
		if (EType == Type::Blend3P_Low) { return Str::Blend3P_Low.Value; }
		if (EType == Type::BlendVR) { return Str::BlendVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return Str::Blend1P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return Str::Blend3P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return Str::Blend3P_Low.Value; }
		if (ViewType == ECsViewType::VR) { return Str::BlendVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Blend1P) { return Type::Blend1P; }
		if (String == Str::Blend3P) { return Type::Blend3P; }
		if (String == Str::Blend3P_Low) { return Type::Blend3P_Low; }
		if (String == Str::BlendVR) { return Type::BlendVR; }
		return Type::ECsFpsAnimBlendSpaceMember_MAX;
	}
}

#define ECS_FPS_ANIM_BLEND_SPACE_MEMBER_MAX (uint8)ECsFpsAnimBlendSpaceMember::ECsFpsAnimBlendSpaceMember_MAX
typedef ECsFpsAnimBlendSpaceMember::Type TCsFpsAnimBlendSpaceMember;

USTRUCT(BlueprintType)
struct FCsBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend_LoadFlags;

public:

	UPROPERTY(Transient)
	class UBlendSpace* Blend_Internal;

public:

	FCsBlendSpace()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blend_LoadFlags, ECsLoadFlags::Game);
	}

	UBlendSpace* Get()
	{
		return Blend_Internal;
	}

	FCsBlendSpace& operator=(const FCsBlendSpace& B)
	{
		Blend = B.Blend;
		Blend_LoadFlags = B.Blend_LoadFlags;
		Blend_Internal = B.Blend_Internal;
		return *this;
	}

	bool operator==(const FCsBlendSpace& B) const
	{
		return Blend == B.Blend && Blend_LoadFlags == B.Blend_LoadFlags && Blend_Internal == B.Blend_Internal;
	}

	bool operator!=(const FCsBlendSpace& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> BlendVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

public:

	UPROPERTY(Transient)
	class UBlendSpace* Blend1P_Internal;

	UPROPERTY(Transient)
	class UBlendSpace* Blend3P_Internal;

	UPROPERTY(Transient)
	class UBlendSpace* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	class UBlendSpace* BlendVR_Internal;

public:

	FCsFpsBlendSpace()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blend1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blend1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Blend3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blend3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Blend3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blend3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(BlendVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(BlendVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	UBlendSpace* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FCsFpsBlendSpace& operator=(const FCsFpsBlendSpace& B)
	{
		Blend1P = B.Blend1P;
		Blend3P = B.Blend3P;
		Blend3P_Low = B.Blend3P_Low;
		BlendVR = B.BlendVR;

		Blend1P_LoadFlags = B.Blend1P_LoadFlags;
		Blend3P_LoadFlags = B.Blend3P_LoadFlags;
		Blend3P_Low_LoadFlags = B.Blend3P_Low_LoadFlags;
		BlendVR_LoadFlags = B.BlendVR_LoadFlags;

		Blend1P_Internal = B.Blend1P_Internal;
		Blend3P_Internal = B.Blend3P_Internal;
		Blend3P_Low_Internal = B.Blend3P_Low_Internal;
		BlendVR_Internal = B.BlendVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsBlendSpace& B) const
	{
		return Blend1P == B.Blend1P && Blend3P == B.Blend3P && Blend3P_Low == B.Blend3P_Low && BlendVR == B.BlendVR &&
			Blend1P_LoadFlags == B.Blend1P_LoadFlags && Blend3P_LoadFlags == B.Blend3P_LoadFlags && Blend3P_Low_LoadFlags == B.Blend3P_Low_LoadFlags && BlendVR_LoadFlags == B.BlendVR_LoadFlags &&
			Blend1P_Internal == B.Blend1P_Internal && Blend3P_Internal == B.Blend3P_Internal && Blend3P_Low_Internal == B.Blend3P_Low_Internal && BlendVR_Internal == B.BlendVR_Internal;
	}

	bool operator!=(const FCsFpsBlendSpace& B) const
	{
		return !(*this == B);
	}
};

UENUM(BlueprintType)
namespace ECsAdditiveBasePoseType
{
	enum Type
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
}

namespace ECsAdditiveBasePoseType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString ABPT_None = TCsString(TEXT("ABPT_None"), TEXT("abpt_none"), TEXT("none"));
		const TCsString ABPT_RefPose = TCsString(TEXT("ABPT_RefPose"), TEXT("abpt_refpose"), TEXT("ref pose"));
		const TCsString ABPT_AnimScaled = TCsString(TEXT("ABPT_AnimScaled"), TEXT("abpt_animscaled"), TEXT("anim scaled"));
		const TCsString ABPT_AnimFrame = TCsString(TEXT("ABPT_AnimFrame"), TEXT("abpt_animframe"), TEXT("anim frame"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::ABPT_None) { return Str::ABPT_None.Value; }
		if (EType == Type::ABPT_RefPose) { return Str::ABPT_RefPose.Value; }
		if (EType == Type::ABPT_AnimScaled) { return Str::ABPT_AnimScaled.Value; }
		if (EType == Type::ABPT_AnimFrame) { return Str::ABPT_AnimFrame.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const EAdditiveBasePoseType &EType)
	{
		if (EType == EAdditiveBasePoseType::ABPT_None) { return Str::ABPT_None.Value; }
		if (EType == EAdditiveBasePoseType::ABPT_RefPose) { return Str::ABPT_RefPose.Value; }
		if (EType == EAdditiveBasePoseType::ABPT_AnimScaled) { return Str::ABPT_AnimScaled.Value; }
		if (EType == EAdditiveBasePoseType::ABPT_AnimFrame) { return Str::ABPT_AnimFrame.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::ABPT_None) { return Type::ABPT_None; }
		if (String == Str::ABPT_RefPose) { return Type::ABPT_RefPose; }
		if (String == Str::ABPT_AnimScaled) { return Type::ABPT_AnimScaled; }
		if (String == Str::ABPT_AnimFrame) { return Type::ABPT_AnimFrame; }
		return Type::ABPT_MAX;
	}

	FORCEINLINE EAdditiveBasePoseType ToBaseType(const FString &String)
	{
		if (String == Str::ABPT_None) { return EAdditiveBasePoseType::ABPT_None; }
		if (String == Str::ABPT_RefPose) { return EAdditiveBasePoseType::ABPT_RefPose; }
		if (String == Str::ABPT_AnimScaled) { return EAdditiveBasePoseType::ABPT_AnimScaled; }
		if (String == Str::ABPT_AnimFrame) { return EAdditiveBasePoseType::ABPT_AnimFrame; }
		return EAdditiveBasePoseType::ABPT_MAX;
	}
}

#define ECS_ADDITIVE_BASE_POSE_TYPE_MAX (uint8)ECsAdditiveBasePoseType::ABPT_MAX
typedef ECsAdditiveBasePoseType::Type TCsAdditiveBasePoseType;

UENUM(BlueprintType)
namespace ECsAdditiveAnimationType
{
	enum Type
	{
		/** No additive. */
		AAT_None					UMETA(DisplayName = "None"),
		/* Create Additive from LocalSpace Base. */
		AAT_LocalSpaceBase			UMETA(DisplayName = "Local Space"),
		/* Create Additive from MeshSpace Rotation Only, Translation still will be LocalSpace. */
		AAT_RotationOffsetMeshSpace	UMETA(DisplayName = "Mesh Space"),
		AAT_MAX						UMETA(Hidden),
	};
}

namespace ECsAdditiveAnimationType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString AAT_None = TCsString(TEXT("AAT_None"), TEXT("aat_none"), TEXT("none"));
		const TCsString AAT_LocalSpaceBase = TCsString(TEXT("AAT_LocalSpaceBase"), TEXT("aat_localspacebase"), TEXT("local space base"));
		const TCsString AAT_RotationOffsetMeshSpace = TCsString(TEXT("AAT_RotationOffsetMeshSpace"), TEXT("aat_rotationoffsetmeshspace"), TEXT("rotation offset mesh space"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::AAT_None) { return Str::AAT_None.Value; }
		if (EType == Type::AAT_LocalSpaceBase) { return Str::AAT_LocalSpaceBase.Value; }
		if (EType == Type::AAT_RotationOffsetMeshSpace) { return Str::AAT_RotationOffsetMeshSpace.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const EAdditiveAnimationType &EType)
	{
		if (EType == EAdditiveAnimationType::AAT_None) { return Str::AAT_None.Value; }
		if (EType == EAdditiveAnimationType::AAT_LocalSpaceBase) { return Str::AAT_LocalSpaceBase.Value; }
		if (EType == EAdditiveAnimationType::AAT_RotationOffsetMeshSpace) { return Str::AAT_RotationOffsetMeshSpace.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::AAT_None) { return Type::AAT_None; }
		if (String == Str::AAT_LocalSpaceBase) { return Type::AAT_LocalSpaceBase; }
		if (String == Str::AAT_RotationOffsetMeshSpace) { return Type::AAT_RotationOffsetMeshSpace; }
		return Type::AAT_MAX;
	}

	FORCEINLINE EAdditiveAnimationType ToBaseType(const FString &String)
	{
		if (String == Str::AAT_None) { return EAdditiveAnimationType::AAT_None; }
		if (String == Str::AAT_LocalSpaceBase) { return EAdditiveAnimationType::AAT_LocalSpaceBase; }
		if (String == Str::AAT_RotationOffsetMeshSpace) { return EAdditiveAnimationType::AAT_RotationOffsetMeshSpace; }
		return EAdditiveAnimationType::AAT_MAX;
	}
}

#define ECS_ADDITIVE_ANIMATION_TYPE_MAX (uint8)ECsAdditiveAnimationType::AAT_MAX
typedef ECsAdditiveAnimationType::Type TCsAdditiveAnimationType;

#pragma endregion Anim