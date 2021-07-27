// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"

#include "CsTypes_Data_Damage.generated.h"
#pragma once

// FCsData_DamagePoint
#pragma region

// NCsDamage::NData::NPoint::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NData, NPoint, FProxy)

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsDamageType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	FCsData_DamagePoint() :
		Type(),
		Damage(0.0f)
	{
	}

private:

	typedef NCsDamage::NData::NPoint::FProxy PointDataProxyType;

public:

	void SetData(PointDataProxyType* Data);
};

#pragma endregion FCsData_DamagePoint