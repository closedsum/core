// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Multi/CsProperty_Multi_FString_Enum_TwoParams.h"

#include "CsTypes_View.generated.h"

// View
#pragma region

	// ViewType
#pragma region

UENUM(BlueprintType)
enum class ECsViewType : uint8
{
	FirstPerson		UMETA(DisplayName = "1st Person"),
	ThirdPerson		UMETA(DisplayName = "3rd Person"),
	VR				UMETA(DisplayName = "VR"),
	ECsViewType_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsViewType : public TCsEnumMap<ECsViewType>
{
	CS_ENUM_MAP_BODY(EMCsViewType, ECsViewType)
};

namespace NCsViewType
{
	typedef ECsViewType Type;

	namespace Ref
	{
		extern CSTYPES_API const Type FirstPerson;
		extern CSTYPES_API const Type ThirdPerson;
		extern CSTYPES_API const Type VR;
		extern CSTYPES_API const Type ECsViewType_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

#define ECS_VIEW_TYPE_MAX (uint8)ECsViewType::ECsViewType_MAX

#pragma endregion ViewType

	// FCsViewFlags
#pragma region

USTRUCT(BlueprintType)
struct FCsViewFlags
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|View")
	bool Flag1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|View")
	bool Flag3P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|View")
	bool FlagVR;

	FCsViewFlags() :
		Flag1P(false),
		Flag3P(false),
		FlagVR(false)
	{
	}

	bool Get(const ECsViewType& ViewType)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Flag1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return Flag3P;
		if (ViewType == ECsViewType::VR)
			return FlagVR;
		return false;
	}

	FCsViewFlags& operator=(const FCsViewFlags& B)
	{
		Flag1P = B.Flag1P;
		Flag3P = B.Flag3P;
		FlagVR = B.FlagVR;
		return *this;
	}

	bool operator==(const FCsViewFlags& B) const
	{
		return Flag1P == B.Flag1P && Flag3P == B.Flag3P && FlagVR == B.FlagVR;
	}

	bool operator!=(const FCsViewFlags& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsViewFlags

#pragma endregion View

// Render
#pragma region

	// Visibility
#pragma region

UENUM(BlueprintType)
namespace ECsVisibility
{
	enum Type
	{
		Hidden				UMETA(DisplayName = "Hidden"),
		Visible				UMETA(DisplayName = "Visible"),
		ECsVisibility_MAX	UMETA(Hidden),
	};
}

namespace ECsVisibility
{
	typedef TCsProperty_Multi_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Hidden = TCsString(TEXT("Hidden"), TEXT("hidden"));
		const TCsString Visible = TCsString(TEXT("Visible"), TEXT("visible"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Hidden) { return Str::Hidden.Value; }
		if (EType == Type::Visible) { return Str::Visible.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Hidden) { return Type::Hidden; }
		if (String == Str::Visible) { return Type::Visible; }
		return Type::ECsVisibility_MAX;
	}
}

#define ECS_VISIBILITY_MAX (uint8)ECsVisibility::ECsVisibility_MAX
typedef ECsVisibility::Type TCsVisibility;

#pragma endregion Visibility

	// FCsDrawDistance
#pragma region

USTRUCT(BlueprintType)
struct FCsDrawDistance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|View", meta = (ClampMin = "0", UIMin = "0"))
	float Distance;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCoreLibrary|View")
	float DistanceSq;

	FCsDrawDistance()
	{
		Reset();
	}

	FCsDrawDistance& operator=(const FCsDrawDistance& B)
	{
		Distance = B.Distance;
		DistanceSq = B.DistanceSq;
		return *this;
	}

	bool operator==(const FCsDrawDistance& B) const
	{
		return Distance == B.Distance && DistanceSq == B.DistanceSq;
	}

	bool operator!=(const FCsDrawDistance& B) const
	{
		return !(*this == B);
	}

	void Square()
	{
		DistanceSq = Distance * Distance;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("Distance=%3.3f"), Distance);
	}

	bool InitFromString(const FString& InSourceString)
	{
		Distance = 0.0f;

		// The initialization is only successful if the Distance values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("Distance="), Distance);

		Square();

		return bSuccessful;
	}

	void Reset()
	{
		Distance = 3000.0f;
		Square();
	}
};

#pragma endregion FCsDrawDistance

	// FCsFpvDrawDistance
#pragma region

USTRUCT(BlueprintType)
struct FCsFpvDrawDistance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|View", meta = (ClampMin = "0", UIMin = "0"))
	float Distance1P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCoreLibrary|View")
	float Distance1PSq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|View", meta = (ClampMin = "0", UIMin = "0"))
	float Distance3P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCoreLibrary|View")
	float Distance3PSq;

	FCsFpvDrawDistance()
	{
		Reset();
	}

	FCsFpvDrawDistance& operator=(const FCsFpvDrawDistance& B)
	{
		Distance1P   = B.Distance1P;
		Distance1PSq = B.Distance1PSq;
		Distance3P   = B.Distance3P;
		Distance3PSq = B.Distance3PSq;
		return *this;
	}

	bool operator==(const FCsFpvDrawDistance& B) const
	{
		return Distance1P == B.Distance1P && Distance1PSq == B.Distance1PSq && Distance3P == B.Distance3P && Distance3PSq == B.Distance3PSq;
	}

	bool operator!=(const FCsFpvDrawDistance& B) const
	{
		return !(*this == B);
	}

	void Square()
	{
		Distance1PSq = Distance1P * Distance1P;
		Distance3PSq = Distance3P * Distance3P;
	}

	const float& Get(const ECsViewType& ViewType) const
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return Distance1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return Distance3P;
		static const float DEFAULT_VALUE = 0.0f;
		return DEFAULT_VALUE;
	}

	const float& GetSquared(const ECsViewType& ViewType) const
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return Distance1PSq;
		if (ViewType == ECsViewType::ThirdPerson)
			return Distance3PSq;
		static const float DEFAULT_VALUE = 0.0f;
		return DEFAULT_VALUE;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("1P=%3.3f 3P=%3.3f"), Distance1P, Distance3P);
	}

	bool InitFromString(const FString& InSourceString)
	{
		Distance1P = Distance3P = 0.0f;

		// The initialization is only successful if the Distance1P and Distance3P values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("1P="), Distance1P) && FParse::Value(*InSourceString, TEXT("3P="), Distance3P);

		Square();

		return bSuccessful;
	}

	void Reset()
	{
		Distance1P = 3000.0f;
		Distance3P = 3000.0f;
		Square();
	}
};

#pragma endregion FCsFpvDrawDistance

#pragma endregion Render