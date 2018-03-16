// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"

#include "Sound/SoundCue.h"

#include "CsTypes_Sound.generated.h"
#pragma once

// Sound
#pragma region

UENUM(BlueprintType)
namespace ECsSoundType
{
	enum Type
	{
		s2D				 UMETA(DisplayName = "2D"),
		s3D				 UMETA(DisplayName = "3D"),
		ECsSoundType_MAX UMETA(Hidden),
	};
}

namespace ECsSoundType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString s2D = TCsString(TEXT("s2D"), TEXT("s2d"), TEXT("2d"));
		const TCsString s3D = TCsString(TEXT("s3D"), TEXT("s3d"), TEXT("3d"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::s2D) { return Str::s2D.Value; }
		if (EType == Type::s3D) { return Str::s3D.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::s2D) { return Type::s2D; }
		if (String == Str::s3D) { return Type::s3D; }
		return Type::ECsSoundType_MAX;
	}
}

#define ECS_SOUND_TYPE_MAX (uint8)ECsSoundType::ECsSoundType_MAX
typedef ECsSoundType::Type TCsSoundType;

UENUM(BlueprintType)
namespace ECsSoundPriority
{
	enum Type
	{
		VeryLow				 UMETA(DisplayName = "Very Low"),
		Low					 UMETA(DisplayName = "Low"),
		Medium				 UMETA(DisplayName = "Medium"),
		High				 UMETA(DisplayName = "High"),
		VeryHigh			 UMETA(DisplayName = "Very High"),
		ECsSoundPriority_MAX UMETA(Hidden),
	};
}

namespace ECsSoundPriority
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString VeryLow = TCsString(TEXT("VeryLow"), TEXT("verylow"), TEXT("very low"));
		const TCsString Low = TCsString(TEXT("Low"), TEXT("low"), TEXT("low"));
		const TCsString Medium = TCsString(TEXT("Medium"), TEXT("medium"), TEXT("medium"));
		const TCsString High = TCsString(TEXT("High"), TEXT("high"), TEXT("high"));
		const TCsString VeryHigh = TCsString(TEXT("VeryHigh"), TEXT("veryhigh"), TEXT("very high"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::VeryLow) { return Str::VeryLow.Value; }
		if (EType == Type::Low) { return Str::Low.Value; }
		if (EType == Type::Medium) { return Str::Medium.Value; }
		if (EType == Type::High) { return Str::High.Value; }
		if (EType == Type::VeryHigh) { return Str::VeryHigh.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::VeryLow) { return Type::VeryLow; }
		if (String == Str::Low) { return Type::Low; }
		if (String == Str::Medium) { return Type::Medium; }
		if (String == Str::High) { return Type::High; }
		if (String == Str::VeryHigh) { return Type::VeryHigh; }
		return Type::ECsSoundPriority_MAX;
	}
}

#define ECS_SOUND_PRIORITY_MAX (uint8)ECsSoundPriority::ECsSoundPriority_MAX
typedef ECsSoundPriority::Type TCsSoundPriority;

USTRUCT(BlueprintType)
struct FCsSoundElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TAssetPtr<class USoundCue> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Sound_LoadFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TEnumAsByte<ECsSoundType::Type> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TEnumAsByte<ECsSoundPriority::Type> Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (ClampMin = "0.05", UIMin = "0.05"))
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	bool IsLooping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float PitchMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	FName Bone;

private:
	UPROPERTY(Transient)
	class USoundCue* Sound_Internal;

public:
	FCsSoundElement()
	{
		CS_SET_BLUEPRINT_BITFLAG(Sound_LoadFlags, ECsLoadFlags::Game);

		Type = ECsSoundType::s3D;
		Priority = ECsSoundPriority::Medium;
		Duration = 0.05f;
		VolumeMultiplier = 1.0f;
		PitchMultiplier = 1.0f;
		Bone = NAME_None;
	}

	FCsSoundElement& operator=(const FCsSoundElement& B)
	{
		Sound = B.Sound;
		Sound_LoadFlags = B.Sound_LoadFlags;
		Type = B.Type;
		Priority = B.Priority;
		Duration = B.Duration;
		IsLooping = B.IsLooping;
		VolumeMultiplier = B.VolumeMultiplier;
		PitchMultiplier = B.PitchMultiplier;
		Bone = B.Bone;
		return *this;
	}

	bool operator==(const FCsSoundElement& B) const
	{
		return Sound == B.Sound &&
				Sound_LoadFlags == B.Sound_LoadFlags &&
				Type == B.Type &&
				Priority == B.Priority &&
				Duration == B.Duration &&
				IsLooping == B.IsLooping &&
				VolumeMultiplier == B.VolumeMultiplier &&
				PitchMultiplier == B.PitchMultiplier &&
				Bone == B.Bone;
	}

	bool operator!=(const FCsSoundElement& B) const
	{
		return !(*this == B);
	}

	void Set(USoundCue* InSound)
	{
		Sound = TAssetPtr<USoundCue>(InSound);
		Sound_Internal = InSound;
	}

	USoundCue* Get() const
	{
		return Sound_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsFpsSoundElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Sound")
	FCsSoundElement Sound1P;

	UPROPERTY(EditAnywhere, Category = "Sound")
	FCsSoundElement Sound3P;

public:

	FCsFpsSoundElement& operator=(const FCsFpsSoundElement& B)
	{
		Sound1P = B.Sound1P;
		Sound3P = B.Sound3P;
		return *this;
	}

	bool operator==(const FCsFpsSoundElement& B) const
	{
		return Sound1P == B.Sound1P && Sound3P == B.Sound3P;
	}

	bool operator!=(const FCsFpsSoundElement& B) const
	{
		return !(*this == B);
	}

	FCsSoundElement* Get(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return &Sound1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return &Sound3P;
		return nullptr;
	}

	USoundCue* GetCue(const TCsViewType &ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return Sound1P.Get();
		if (ViewType == ECsViewType::ThirdPerson)
			return Sound3P.Get();
		return nullptr;
	}
};

#pragma endregion Sound