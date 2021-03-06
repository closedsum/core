// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_View.h"
// Log
#include "Utility/CsLog.h"

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

class UAnimSequence;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimSequence> Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite)
	UAnimSequence* Anim_Internal;

public:

	FCsAnimSequence() :
		Anim(nullptr),
		Anim_LoadFlags(0),
		Anim_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the Anim.
	*
	* return Anim
	*/
	FORCEINLINE UAnimSequence* Get() const { return Anim_Internal; }

	FORCEINLINE UAnimSequence** GetPtr() { return &Anim_Internal; }

	/**
	* Get the Hard reference to the Anim.
	*
	* @param Context	The calling context.
	* return			Anim
	*/
	FORCEINLINE UAnimSequence* GetChecked(const FString& Context) const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("%s: Anim is NULL."), *Context);

		checkf(Anim_Internal, TEXT("%s: Anim has NOT been loaded from Path @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	FORCEINLINE UAnimSequence* GetChecked() const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("FCsAnimSequence::GetChecked: Anim is NULL or the Path is NOT Valid."));

		checkf(Anim_Internal, TEXT("FCsAnimSequence::GetChecked: Failed to load Anim @ %s."), *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	UAnimSequence* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Anim.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim is NULL."), *Context));
			return nullptr;
		}

		if (!Anim_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim has NOT been loaded from Path @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString())));
		}
		return Anim_Internal;
	}

	UAnimSequence* GetSafe()
	{
		if (!Anim.ToSoftObjectPath().IsValid())
			return nullptr;
		return Anim_Internal;
	}

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsAnimSequence

// FCsAnimSequenceInfo
#pragma region

// NCsAnim::NSequence::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NSequence, FInfo)

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimSequenceInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsAnimSequence Anim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PlayRate;

	FCsAnimSequenceInfo() :
		Anim(),
		PlayRate(1.0f)
	{
	}

#define InfoType NCsAnim::NSequence::FInfo
	void CopyToInfo(InfoType* Info);
#undef InfoType

private:

	FORCEINLINE void __Nothing() const {}
};

class UAnimSequence;

namespace NCsAnim
{
	namespace NSequence
	{
		struct CSCORE_API FInfo
		{
		private:

			UAnimSequence* Anim;
			UAnimSequence** Anim_Emu;

			float PlayRate;
			float* PlayRate_Emu;

		public:

			FInfo() :
				Anim(nullptr),
				Anim_Emu(nullptr),
				PlayRate(1.0f),
				PlayRate_Emu(nullptr)
			{
				Anim_Emu = &Anim;
				PlayRate_Emu = &PlayRate;
			}

			FORCEINLINE void SetAnim(UAnimSequence** Value) { Anim_Emu = Value; }
			FORCEINLINE void SetAnim(UAnimSequence* Value)
			{
				Anim	 = Value;
				Anim_Emu = &Anim;
			}

			FORCEINLINE UAnimSequence* GetAnim() const { return *Anim_Emu; }

			FORCEINLINE void SetPlayRate(float* Value) { PlayRate_Emu = Value; }
			FORCEINLINE void SetPlayRate(const float& Value)
			{
				PlayRate	 = Value;
				PlayRate_Emu = &PlayRate;
			}

			FORCEINLINE const float& GetPlayRate() const { return *PlayRate_Emu; }
		};
	}
}

#pragma endregion FCsAnimSequenceInfo

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimMontage> Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite)
	UAnimMontage* Anim_Internal;

public:

	FCsAnimMontage() :
		Anim(nullptr),
		Anim_LoadFlags(0),
		Anim_Internal(nullptr)
	{
	}

	FORCEINLINE UAnimMontage* Get() const { return Anim_Internal; }

	FORCEINLINE UAnimMontage** GetPtr() { return &Anim_Internal; }

	FORCEINLINE UAnimMontage* GetChecked(const FString& Context) const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("%s: Anim is NULL or the Path is NOT Valid."), *Context);

		checkf(Anim_Internal, TEXT("%s: Failed to load Blueprint @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	FORCEINLINE UAnimMontage* GetChecked() const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("FCsAnimMontage::GetChecked: Anim is NULL or the Path is NOT Valid."));

		checkf(Anim_Internal, TEXT("FCsAnimMontage::GetChecked: Failed to load Anim @ %s."), *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	UAnimMontage* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Anim.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim is NULL."), *Context));
			return nullptr;
		}

		if (!Anim_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim has NOT been loaded from Path @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString())));
		}
		return Anim_Internal;
	}

	UAnimMontage* GetSafe()
	{
		if (!Anim.ToSoftObjectPath().IsValid())
			return nullptr;
		return Anim_Internal;
	}

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsAnimMontage

// FCsAnimMontageInfo
#pragma region

// NCsAnim::NMontage::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NMontage, FInfo)

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimMontageInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsAnimMontage Anim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PlayRate;

	FCsAnimMontageInfo() :
		Anim(),
		PlayRate(1.0f)
	{
	}

#define InfoType NCsAnim::NMontage::FInfo
	void CopyToInfo(InfoType* Info);
#undef InfoType

private:

	FORCEINLINE void __Nothing() const {}
};

class UAnimMontage;

namespace NCsAnim
{
	namespace NMontage
	{
		struct CSCORE_API FInfo
		{
		private:

			UAnimMontage* Anim;
			UAnimMontage** Anim_Emu;

			float PlayRate;
			float* PlayRate_Emu;

		public:

			FInfo() :
				Anim(nullptr),
				Anim_Emu(nullptr),
				PlayRate(1.0f),
				PlayRate_Emu(nullptr)
			{
				Anim_Emu = &Anim;
				PlayRate_Emu = &PlayRate;
			}

			FORCEINLINE void SetAnim(UAnimMontage** Value) { Anim_Emu = Value; }
			FORCEINLINE void SetAnim(UAnimMontage* Value)
			{
				Anim	 = Value;
				Anim_Emu = &Anim;
			}

			FORCEINLINE UAnimMontage* GetAnim() const { return *Anim_Emu; }

			FORCEINLINE void SetPlayRate(float* Value) { PlayRate_Emu = Value; }
			FORCEINLINE void SetPlayRate(const float& Value)
			{
				PlayRate	 = Value;
				PlayRate_Emu = &PlayRate;
			}

			FORCEINLINE const float& GetPlayRate() const { return *PlayRate_Emu; }
		};
	}
}

#pragma endregion FCsAnimMontageInfo

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSoftObjectPtr<UAnimBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite)
	UAnimBlueprintGeneratedClass* Blueprint_Internal;

public:

	FCsAnimBlueprint() :
		Blueprint(nullptr),
		Blueprint_LoadFlags(0),
		Blueprint_Internal(nullptr)
	{
	}

	FORCEINLINE UAnimBlueprintGeneratedClass* Get() const { return Blueprint_Internal; }

	FORCEINLINE UAnimBlueprintGeneratedClass** GetPtr() { return &Blueprint_Internal; }

	FORCEINLINE UAnimBlueprintGeneratedClass* GetChecked(const FString& Context) const
	{
		checkf(Blueprint.ToSoftObjectPath().IsValid(), TEXT("%s: Blueprint is NULL or the Path is NOT Valid."), *Context);

		checkf(Blueprint_Internal, TEXT("%s: Failed to load Blueprint @ %s."), *Context, *(Blueprint.ToSoftObjectPath().ToString()));

		return Blueprint_Internal;
	}

	FORCEINLINE UAnimBlueprintGeneratedClass* GetChecked() const
	{
		checkf(Blueprint.ToSoftObjectPath().IsValid(), TEXT("FCsAnimBlueprint::GetChecked: Blueprint is NULL or the Path is NOT Valid."));

		checkf(Blueprint_Internal, TEXT("FCsAnimBlueprint::GetChecked: Failed to load Blueprint @ %s."), *(Blueprint.ToSoftObjectPath().ToString()));

		return Blueprint_Internal;
	}

	UAnimBlueprintGeneratedClass* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Blueprint.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blueprint is NULL."), *Context));
			return nullptr;
		}

		if (!Blueprint_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blueprint has NOT been loaded from Path @ %s."), *Context, *(Blueprint.ToSoftObjectPath().ToString())));
		}
		return Blueprint_Internal;
	}

	UAnimBlueprintGeneratedClass* GetSafe()
	{
		if (!Blueprint.ToSoftObjectPath().IsValid())
			return nullptr;
		return Blueprint_Internal;
	}

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
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

	FORCEINLINE UBlendSpace1D* Get() const { return Blend_Internal; }

	FORCEINLINE UBlendSpace1D* GetChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend is NULL or the Path is NOT Valid."), *Context);

		checkf(Blend_Internal, TEXT("%s: Failed to load Blend @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	FORCEINLINE UBlendSpace1D* GetChecked() const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("FCsBlendSpace1D::GetChecked: Blend is NULL or the Path is NOT Valid."));

		checkf(Blend_Internal, TEXT("FCsBlendSpace1D::GetChecked: Failed to load Blend @ %s."), *(Blend.ToSoftObjectPath().ToString()));

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

	FORCEINLINE UBlendSpace* Get() const { return Blend_Internal; }

	FORCEINLINE UBlendSpace* GetChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend is NULL or the Path is NOT Valid."), *Context);

		checkf(Blend_Internal, TEXT("%s: Failed to load Blend @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	FORCEINLINE UBlendSpace* GetChecked() const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("FCsBlendSpace1D::GetChecked: Blend is NULL or the Path is NOT Valid."));

		checkf(Blend_Internal, TEXT("FCsBlendSpace1D::GetChecked: Failed to load Blend @ %s."), *(Blend.ToSoftObjectPath().ToString()));

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