// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Animation/BlendSpace1D.h"
#include "Animation/BlendSpace.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AnimBlueprint.h"

#include "CsTypes_Anim.generated.h"
#pragma once

// Anim
#pragma region

namespace ECsAnimCached
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

UENUM(BlueprintType)
namespace ECsFpvAnimMember
{
	enum Type
	{
		Anim1P					UMETA(DisplayName = "Anim1P"),
		Anim3P					UMETA(DisplayName = "Anim3P"),
		Anim3P_Low				UMETA(DisplayName = "Anim3P_Low"),
		AnimVR					UMETA(DisplayName = "AnimVR"),
		ECsFpvAnimMember_MAX	UMETA(Hidden),
	};
}

typedef ECsFpvAnimMember::Type TCsFpvAnimMember;

struct CSCORE_API EMCsFpvAnimMember: public TCsEnumMap<ECsFpvAnimMember::Type>
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimSequence> Anim;


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

	FORCEINLINE bool operator==(const FCsAnimSequence& B) const
	{
		return Anim == B.Anim && Anim_LoadFlags == B.Anim_LoadFlags && Anim_Internal == B.Anim_Internal;
	}

	FORCEINLINE bool operator!=(const FCsAnimSequence& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimSequence> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimSequence> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimSequence> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimSequence> AnimVR;

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

	FCsFpvAnimSequence()
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

	FORCEINLINE TSoftObjectPtr<UAnimSequence> GeTSoftObjectPtr(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	FORCEINLINE UAnimSequence* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	FORCEINLINE FCsFpvAnimSequence& operator=(const FCsFpvAnimSequence& B)
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

	FORCEINLINE bool operator==(const FCsFpvAnimSequence& B) const
	{
		return Anim1P == B.Anim1P && Anim3P == B.Anim3P && Anim3P_Low == B.Anim3P_Low && AnimVR == B.AnimVR &&
			Anim1P_LoadFlags == B.Anim1P_LoadFlags && Anim3P_LoadFlags == B.Anim3P_LoadFlags && Anim3P_Low_LoadFlags == B.Anim3P_Low_LoadFlags && AnimVR_LoadFlags == B.AnimVR_LoadFlags &&
			Anim1P_Internal == B.Anim1P_Internal && Anim3P_Internal == B.Anim3P_Internal && Anim3P_Low_Internal == B.Anim3P_Low_Internal && AnimVR_Internal == B.AnimVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpvAnimSequence& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimMontage> Anim;

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

	FORCEINLINE UAnimMontage* Get()
	{
		return Anim_Internal;
	}

	FORCEINLINE FCsAnimMontage& operator=(const FCsAnimMontage& B)
	{
		Anim = B.Anim;
		Anim_LoadFlags = B.Anim_LoadFlags;
		Anim_Internal = B.Anim_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAnimMontage& B) const
	{
		return Anim == B.Anim && Anim_LoadFlags == B.Anim_LoadFlags && Anim_Internal == B.Anim_Internal;
	}

	FORCEINLINE bool operator!=(const FCsAnimMontage& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimMontage> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimMontage> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimMontage> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAnimMontage> AnimVR;

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

	FCsFpvAnimMontage()
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


	FORCEINLINE TSoftObjectPtr<UAnimMontage> GeTSoftObjectPtr(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	FORCEINLINE UAnimMontage* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	FORCEINLINE FCsFpvAnimMontage& operator=(const FCsFpvAnimMontage& B)
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

	FORCEINLINE bool operator==(const FCsFpvAnimMontage& B) const
	{
		return Anim1P == B.Anim1P && Anim3P == B.Anim3P && Anim3P_Low == B.Anim3P_Low && AnimVR == B.AnimVR &&
			Anim1P_LoadFlags == B.Anim1P_LoadFlags && Anim3P_LoadFlags == B.Anim3P_LoadFlags && Anim3P_Low_LoadFlags == B.Anim3P_Low_LoadFlags && AnimVR_LoadFlags == B.AnimVR_LoadFlags &&
			Anim1P_Internal == B.Anim1P_Internal && Anim3P_Internal == B.Anim3P_Internal && Anim3P_Low_Internal == B.Anim3P_Low_Internal && AnimVR_Internal == B.AnimVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpvAnimMontage& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct CSCORE_API FCsTArrayAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class UAnimMontage>> Anims;

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

	FORCEINLINE FCsTArrayAnimMontage& operator=(const FCsTArrayAnimMontage& B)
	{
		Anims.Reset();

		for (const TSoftObjectPtr<class UAnimMontage>& Anim : B.Anims)
		{
			Anims.Add(Anim);
		}
		Anims_LoadFlags = B.Anims_LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTArrayAnimMontage& B) const
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

	FORCEINLINE bool operator!=(const FCsTArrayAnimMontage& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE TArray<class UAnimMontage*>* Get()
	{
		return &Anims_Internal;
	}

	FORCEINLINE class UAnimMontage* Get(const int32 Index)
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

UENUM(BlueprintType)
namespace ECsFpvAnimBlueprintMember
{
	enum Type
	{
		Blueprint1P						UMETA(DisplayName = "Blueprint1P"),
		Blueprint3P						UMETA(DisplayName = "Blueprint3P"),
		Blueprint3P_Low					UMETA(DisplayName = "Blueprint3P_Low"),
		BlueprintVR						UMETA(DisplayName = "BlueprintVR"),
		ECsFpvAnimBlueprintMember_MAX	UMETA(Hidden),
	};
}

typedef ECsFpvAnimBlueprintMember::Type TCsFpvAnimBlueprintMember;

struct CSCORE_API EMCsFpvAnimBlueprintMember : public TCsEnumMap<ECsFpvAnimBlueprintMember::Type>
{
protected:
	EMCsFpvAnimBlueprintMember() {}
	EMCsFpvAnimBlueprintMember(const EMCsFpvAnimBlueprintMember &) = delete;
	EMCsFpvAnimBlueprintMember(EMCsFpvAnimBlueprintMember &&) = delete;
public:
	~EMCsFpvAnimBlueprintMember() {}
private:
	static EMCsFpvAnimBlueprintMember* Instance;

public:
	static EMCsFpvAnimBlueprintMember& Get();
};

namespace ECsFpvAnimBlueprintMember
{
	namespace Ref
	{
		extern CSCORE_API const Type Blueprint1P;
		extern CSCORE_API const Type Blueprint3P;
		extern CSCORE_API const Type Blueprint3P_Low;
		extern CSCORE_API const Type BlueprintVR;
		extern CSCORE_API const Type ECsFpvAnimBlueprintMember_MAX;
	}

	FORCEINLINE const FString& ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::BlueprintVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<class UAnimBlueprint> Blueprint;


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

	FORCEINLINE UAnimBlueprintGeneratedClass* Get()
	{
		return Blueprint_Internal;
	}

	FORCEINLINE FCsAnimBlueprint& operator=(const FCsAnimBlueprint& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_LoadFlags = B.Blueprint_LoadFlags;
		Blueprint_Internal = B.Blueprint_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAnimBlueprint& B) const
	{
		return Blueprint == B.Blueprint && Blueprint_LoadFlags == B.Blueprint_LoadFlags && Blueprint_Internal == B.Blueprint_Internal;
	}

	FORCEINLINE bool operator!=(const FCsAnimBlueprint& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TSoftObjectPtr<class UAnimBlueprint> Blueprint1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TSoftObjectPtr<class UAnimBlueprint> Blueprint3P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TSoftObjectPtr<class UAnimBlueprint> Blueprint3P_Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TSoftObjectPtr<class UAnimBlueprint> BlueprintVR;

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

	FCsFpvAnimBlueprint()
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

	FORCEINLINE UAnimBlueprintGeneratedClass* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blueprint1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blueprint3P_Low_Internal : Blueprint3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlueprintVR_Internal;
		return Blueprint3P_Internal;
	}

	FORCEINLINE FCsFpvAnimBlueprint& operator=(const FCsFpvAnimBlueprint& B)
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

	FORCEINLINE bool operator==(const FCsFpvAnimBlueprint& B) const
	{
		return Blueprint1P == B.Blueprint1P && Blueprint3P == B.Blueprint3P && Blueprint3P_Low == B.Blueprint3P_Low && BlueprintVR == B.BlueprintVR &&
			Blueprint1P_LoadFlags == B.Blueprint1P_LoadFlags && Blueprint3P_LoadFlags == B.Blueprint3P_LoadFlags && Blueprint3P_Low_LoadFlags == B.Blueprint3P_Low_LoadFlags && BlueprintVR_LoadFlags == B.BlueprintVR_LoadFlags &&
			Blueprint1P_Internal == B.Blueprint1P_Internal && Blueprint3P_Internal == B.Blueprint3P_Internal && Blueprint3P_Low_Internal == B.Blueprint3P_Low_Internal && BlueprintVR_Internal == B.BlueprintVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpvAnimBlueprint& B) const
	{
		return !(*this == B);
	}
};

UENUM(BlueprintType)
namespace ECsFpvAnimBlendSpaceMember
{
	enum Type
	{
		Blend1P							UMETA(DisplayName = "Blend1P"),
		Blend3P							UMETA(DisplayName = "Blend3P"),
		Blend3P_Low						UMETA(DisplayName = "Blend3P_Low"),
		BlendVR							UMETA(DisplayName = "BlendVR"),
		ECsFpvAnimBlendSpaceMember_MAX	UMETA(Hidden),
	};
}

typedef ECsFpvAnimBlendSpaceMember::Type TCsFpvAnimBlendSpaceMember;

struct CSCORE_API EMCsFpvAnimBlendSpaceMember : public TCsEnumMap<ECsFpvAnimBlendSpaceMember::Type>
{
protected:
	EMCsFpvAnimBlendSpaceMember() {}
	EMCsFpvAnimBlendSpaceMember(const EMCsFpvAnimBlendSpaceMember &) = delete;
	EMCsFpvAnimBlendSpaceMember(EMCsFpvAnimBlendSpaceMember &&) = delete;
public:
	~EMCsFpvAnimBlendSpaceMember() {}
private:
	static EMCsFpvAnimBlendSpaceMember* Instance;

public:
	static EMCsFpvAnimBlendSpaceMember& Get();
};

namespace ECsFpvAnimBlendSpaceMember
{
	namespace Ref
	{
		extern CSCORE_API const Type Blend1P;
		extern CSCORE_API const Type Blend3P;
		extern CSCORE_API const Type Blend3P_Low;
		extern CSCORE_API const Type BlendVR;
		extern CSCORE_API const Type ECsFpvAnimBlendSpaceMember_MAX;
	}

	FORCEINLINE const FString& ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::BlendVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

USTRUCT(BlueprintType)
struct CSCORE_API FCsBlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace1D> Blend;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend_LoadFlags;

public:

	UPROPERTY(Transient)
	class UBlendSpace1D* Blend_Internal;

public:

	FCsBlendSpace1D()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blend_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE UBlendSpace1D* Get()
	{
		return Blend_Internal;
	}

	FORCEINLINE FCsBlendSpace1D& operator=(const FCsBlendSpace1D& B)
	{
		Blend = B.Blend;
		Blend_LoadFlags = B.Blend_LoadFlags;
		Blend_Internal = B.Blend_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlendSpace1D& B) const
	{
		return Blend == B.Blend && Blend_LoadFlags == B.Blend_LoadFlags && Blend_Internal == B.Blend_Internal;
	}

	FORCEINLINE bool operator!=(const FCsBlendSpace1D& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvBlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace1D> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace1D> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace1D> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace1D> BlendVR;

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
	class UBlendSpace1D* Blend1P_Internal;

	UPROPERTY(Transient)
	class UBlendSpace1D* Blend3P_Internal;

	UPROPERTY(Transient)
	class UBlendSpace1D* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	class UBlendSpace1D* BlendVR_Internal;

public:

	FCsFpvBlendSpace1D()
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

	FORCEINLINE UBlendSpace1D* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UBlendSpace1D> GeTSoftObjectPtr(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}

	FORCEINLINE FCsFpvBlendSpace1D& operator=(const FCsFpvBlendSpace1D& B)
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

	FORCEINLINE bool operator==(const FCsFpvBlendSpace1D& B) const
	{
		return Blend1P == B.Blend1P && Blend3P == B.Blend3P && Blend3P_Low == B.Blend3P_Low && BlendVR == B.BlendVR &&
			   Blend1P_LoadFlags == B.Blend1P_LoadFlags && Blend3P_LoadFlags == B.Blend3P_LoadFlags && Blend3P_Low_LoadFlags == B.Blend3P_Low_LoadFlags && BlendVR_LoadFlags == B.BlendVR_LoadFlags &&
			   Blend1P_Internal == B.Blend1P_Internal && Blend3P_Internal == B.Blend3P_Internal && Blend3P_Low_Internal == B.Blend3P_Low_Internal && BlendVR_Internal == B.BlendVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpvBlendSpace1D& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UBlendSpace> Blend;

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

	FORCEINLINE UBlendSpace* Get()
	{
		return Blend_Internal;
	}

	FORCEINLINE FCsBlendSpace& operator=(const FCsBlendSpace& B)
	{
		Blend = B.Blend;
		Blend_LoadFlags = B.Blend_LoadFlags;
		Blend_Internal = B.Blend_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlendSpace& B) const
	{
		return Blend == B.Blend && Blend_LoadFlags == B.Blend_LoadFlags && Blend_Internal == B.Blend_Internal;
	}

	FORCEINLINE bool operator!=(const FCsBlendSpace& B) const
	{
		return !(*this == B);
	}
};

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

	FCsFpvBlendSpace()
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

	FORCEINLINE UBlendSpace* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UBlendSpace> GeTSoftObjectPtr(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}

	FORCEINLINE FCsFpvBlendSpace& operator=(const FCsFpvBlendSpace& B)
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

	FORCEINLINE bool operator==(const FCsFpvBlendSpace& B) const
	{
		return Blend1P == B.Blend1P && Blend3P == B.Blend3P && Blend3P_Low == B.Blend3P_Low && BlendVR == B.BlendVR &&
			Blend1P_LoadFlags == B.Blend1P_LoadFlags && Blend3P_LoadFlags == B.Blend3P_LoadFlags && Blend3P_Low_LoadFlags == B.Blend3P_Low_LoadFlags && BlendVR_LoadFlags == B.BlendVR_LoadFlags &&
			Blend1P_Internal == B.Blend1P_Internal && Blend3P_Internal == B.Blend3P_Internal && Blend3P_Low_Internal == B.Blend3P_Low_Internal && BlendVR_Internal == B.BlendVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpvBlendSpace& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAimOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend_LoadFlags;

public:

	UPROPERTY(Transient)
	class UAimOffsetBlendSpace* Blend_Internal;

public:

	FCsAimOffset()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blend_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE UAimOffsetBlendSpace* Get()
	{
		return Blend_Internal;
	}

	FORCEINLINE FCsAimOffset& operator=(const FCsAimOffset& B)
	{
		Blend = B.Blend;
		Blend_LoadFlags = B.Blend_LoadFlags;
		Blend_Internal = B.Blend_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAimOffset& B) const
	{
		return Blend == B.Blend && Blend_LoadFlags == B.Blend_LoadFlags && Blend_Internal == B.Blend_Internal;
	}

	FORCEINLINE bool operator!=(const FCsAimOffset& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvAimOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TSoftObjectPtr<UAimOffsetBlendSpace> BlendVR;

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
	class UAimOffsetBlendSpace* Blend1P_Internal;

	UPROPERTY(Transient)
	class UAimOffsetBlendSpace* Blend3P_Internal;

	UPROPERTY(Transient)
	class UAimOffsetBlendSpace* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	class UAimOffsetBlendSpace* BlendVR_Internal;

public:

	FCsFpvAimOffset()
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

	FORCEINLINE UAimOffsetBlendSpace* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UAimOffsetBlendSpace> GeTSoftObjectPtr(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}

	FORCEINLINE FCsFpvAimOffset& operator=(const FCsFpvAimOffset& B)
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

	FORCEINLINE bool operator==(const FCsFpvAimOffset& B) const
	{
		return Blend1P == B.Blend1P && Blend3P == B.Blend3P && Blend3P_Low == B.Blend3P_Low && BlendVR == B.BlendVR &&
				Blend1P_LoadFlags == B.Blend1P_LoadFlags && Blend3P_LoadFlags == B.Blend3P_LoadFlags && Blend3P_Low_LoadFlags == B.Blend3P_Low_LoadFlags && BlendVR_LoadFlags == B.BlendVR_LoadFlags &&
				Blend1P_Internal == B.Blend1P_Internal && Blend3P_Internal == B.Blend3P_Internal && Blend3P_Low_Internal == B.Blend3P_Low_Internal && BlendVR_Internal == B.BlendVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpvAimOffset& B) const
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

typedef ECsAdditiveBasePoseType::Type TCsAdditiveBasePoseType;

struct CSCORE_API EMCsAdditiveBasePoseType : public TCsEnumMap<ECsAdditiveBasePoseType::Type>
{
protected:
	EMCsAdditiveBasePoseType() {}
	EMCsAdditiveBasePoseType(const EMCsAdditiveBasePoseType &) = delete;
	EMCsAdditiveBasePoseType(EMCsAdditiveBasePoseType &&) = delete;
public:
	~EMCsAdditiveBasePoseType() {}
private:
	static EMCsAdditiveBasePoseType* Instance;

public:
	static EMCsAdditiveBasePoseType& Get();
};

namespace ECsAdditiveBasePoseType
{
	namespace Ref
	{
		extern CSCORE_API const Type ABPT_None;
		extern CSCORE_API const Type ABPT_RefPose;
		extern CSCORE_API const Type ABPT_AnimScaled;
		extern CSCORE_API const Type ABPT_AnimFrame;
		extern CSCORE_API const Type ABPT_MAX;
	}

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

typedef ECsAdditiveAnimationType::Type TCsAdditiveAnimationType;

struct CSCORE_API EMCsAdditiveAnimationType : public TCsEnumMap<ECsAdditiveAnimationType::Type>
{
protected:
	EMCsAdditiveAnimationType() {}
	EMCsAdditiveAnimationType(const EMCsAdditiveAnimationType &) = delete;
	EMCsAdditiveAnimationType(EMCsAdditiveAnimationType &&) = delete;
public:
	~EMCsAdditiveAnimationType() {}
private:
	static EMCsAdditiveAnimationType* Instance;

public:
	static EMCsAdditiveAnimationType& Get();
};

namespace ECsAdditiveAnimationType
{
	namespace Ref
	{
		extern CSCORE_API const Type AAT_None;
		extern CSCORE_API const Type AAT_LocalSpaceBase;
		extern CSCORE_API const Type AAT_RotationOffsetMeshSpace;
		extern CSCORE_API const Type AAT_MAX;
	}

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

#pragma endregion Anim