// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Params_FX.generated.h"
#pragma once

// FXParameterValue
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsFXParameterValue : uint8
{
	Float					UMETA(DisplayName = "Float"),
	Vector					UMETA(DisplayName = "Vector"),
	ECsFXParameterValue_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsFXParameterValue final : public TCsEnumMap<ECsFXParameterValue>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXParameterValue, ECsFXParameterValue)
};

namespace NCsFXParameterValue
{
	typedef ECsFXParameterValue Type;

	namespace Ref
	{
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type Vector;
		extern CSCORE_API const Type ECsFXParameterValue_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion FXParameterValue

// FCsFXParameterVector
#pragma region

// NCsFX::NParameter::NVector::FVectorTypeEmu
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NVector, FVectorTypeEmu)

/**
* Container holding information for Niagara Vector Parameter
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsFXParameterVector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Value;

public:

	FCsFXParameterVector() :
		Name(NAME_None),
		Value(0.0f)
	{
	}

#define ParameterType NCsFX::NParameter::NVector::FVectorTypeEmu
	void CopyParams(ParameterType* Params);
#undef ParameterType

private:

	FORCEINLINE void __Nothing() const {}
};

#pragma endregion FCsFXParameterVector