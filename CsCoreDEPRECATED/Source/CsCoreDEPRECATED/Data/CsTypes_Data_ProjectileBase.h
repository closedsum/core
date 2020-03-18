// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Data_ProjectileBase.generated.h"
#pragma once

// FCsData_ProjectileBasePtr
#pragma region

class UCsData_ProjectileBase;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_ProjectileBasePtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<UCsData_ProjectileBase> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	UCsData_ProjectileBase* Data_Internal;

public:
	FCsData_ProjectileBasePtr() :
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE bool operator==(const FCsData_ProjectileBasePtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsData_ProjectileBasePtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCsData_ProjectileBase* Get() const
	{
		return Data_Internal;
	}
};

#pragma endregion FCsData_ProjectileBasePtr