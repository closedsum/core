// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
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
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString FirstPerson = TCsString(TEXT("FirstPerson"), TEXT("firstperson"), TEXT("1st person"));
		const TCsString ThirdPerson = TCsString(TEXT("ThirdPerson"), TEXT("thirdperson"), TEXT("3rd person"));
		const TCsString VR = TCsString(TEXT("VR"), TEXT("vr"), TEXT("vr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
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
typedef TEnumAsByte<ECsViewType::Type> TCsViewType;

USTRUCT()
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