// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Data_ProjectileImpact.generated.h"
#pragma once

// FCsData_ProjectileImpactPtr
#pragma region

class UCsData_ProjectileImpact;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsData_ProjectileImpactPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<UCsData_ProjectileImpact> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	UCsData_ProjectileImpact* Data_Internal;

public:
	FCsData_ProjectileImpactPtr() :
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE bool operator==(const FCsData_ProjectileImpactPtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsData_ProjectileImpactPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCsData_ProjectileImpact* Get() const
	{
		return Data_Internal;
	}
};

#pragma endregion FCsData_ProjectileImpactPtr