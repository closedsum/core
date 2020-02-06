// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTdTypes_Creep.generated.h"
#pragma once

// Creep
#pragma region

USTRUCT(BlueprintType)
struct CSTD_API FECsTdCreep : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsTdCreep)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsTdCreep)

struct CSTD_API EMCsTdCreep : public TCsEnumStructMap<FECsTdCreep, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsTdCreep, FECsTdCreep, uint8)
};

#pragma endregion Creep

// ICsTdCreepPayload
#pragma region

struct CSTD_API ICsTdCreepPayload
{
	virtual ~ICsTdCreepPayload() {}
};

#pragma endregion ICsTdCreepPayload