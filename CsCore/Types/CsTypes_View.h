// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_View.generated.h"
#pragma once

// View
#pragma region

UENUM(BlueprintType)
namespace ECsViewType
{
	enum Type
	{
		FirstPerson		UMETA(DisplayName = "1st Person"),
		ThirdPerson		UMETA(DisplayName = "3rd Person"),
		VR				UMETA(DisplayName = "VR"),
		ECsViewType_MAX	UMETA(Hidden),
	};
}

namespace ECsViewType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString FirstPerson = TCsString(TEXT("FirstPerson"), TEXT("firstperson"), TEXT("1st person"));
		const TCsString ThirdPerson = TCsString(TEXT("ThirdPerson"), TEXT("thirdperson"), TEXT("3rd person"));
		const TCsString VR = TCsString(TEXT("VR"), TEXT("vr"), TEXT("vr"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::FirstPerson) { return Str::FirstPerson.Value; }
		if (EType == Type::ThirdPerson) { return Str::ThirdPerson.Value; }
		if (EType == Type::VR) { return Str::VR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::FirstPerson) { return Type::FirstPerson; }
		if (String == Str::ThirdPerson) { return Type::ThirdPerson; }
		if (String == Str::VR) { return Type::VR; }
		return Type::ECsViewType_MAX;
	}
}

#define ECS_VIEW_TYPE_MAX (uint8)ECsViewType::ECsViewType_MAX
typedef ECsViewType::Type TCsViewType;

USTRUCT(BlueprintType)
struct FCsViewFlags
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags")
	bool Flag1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags")
	bool Flag3P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags")
	bool FlagVR;

	bool Get(const TCsViewType &ViewType)
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

#pragma endregion View

// Render
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
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

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

USTRUCT(BlueprintType)
struct FCsDrawDistance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Distance", meta = (ClampMin = "0", UIMin = "0"))
	float Distance;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Draw Distance")
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

USTRUCT(BlueprintType)
struct FCsFpsDrawDistance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Distance", meta = (ClampMin = "0", UIMin = "0"))
	float Distance1P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Draw Distance")
	float Distance1PSq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Distance", meta = (ClampMin = "0", UIMin = "0"))
	float Distance3P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Draw Distance")
	float Distance3PSq;

	FCsFpsDrawDistance()
	{
		Reset();
	}

	FCsFpsDrawDistance& operator=(const FCsFpsDrawDistance& B)
	{
		Distance1P   = B.Distance1P;
		Distance1PSq = B.Distance1PSq;
		Distance3P   = B.Distance3P;
		Distance3PSq = B.Distance3PSq;
		return *this;
	}

	bool operator==(const FCsFpsDrawDistance& B) const
	{
		return Distance1P == B.Distance1P && Distance1PSq == B.Distance1PSq && Distance3P == B.Distance3P && Distance3PSq == B.Distance3PSq;
	}

	bool operator!=(const FCsFpsDrawDistance& B) const
	{
		return !(*this == B);
	}

	void Square()
	{
		Distance1PSq = Distance1P * Distance1P;
		Distance3PSq = Distance3P * Distance3P;
	}

	float Get(const TCsViewType &ViewType) const
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return Distance1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return Distance3P;
		return 0.0f;
	}

	float GetSquared(const TCsViewType &ViewType) const
	{
		if (ViewType == ECsViewType::FirstPerson || ViewType == ECsViewType::VR)
			return Distance1PSq;
		if (ViewType == ECsViewType::ThirdPerson)
			return Distance3PSq;
		return 0.0f;
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

#pragma endregion Render