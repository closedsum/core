// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Containers/CsInterfaceMap.h"

#include "CsTdTypes_Spawner_Creep.generated.h"
#pragma once

// SpawnerCreep
#pragma region

USTRUCT(BlueprintType)
struct CSTD_API FECsTdSpawnerCreep : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsTdSpawnerCreep)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsTdSpawnerCreep)

struct CSTD_API EMCsTdSpawnerCreep : public TCsEnumStructMap<FECsTdSpawnerCreep, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsTdSpawnerCreep, FECsTdSpawnerCreep, uint8)
};

#pragma endregion Creep

// ICsTdSpawnerCreepParams
#pragma region

struct CSTD_API ICsTdSpawnerCreepParams : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

	virtual ~ICsTdSpawnerCreepParams() {}

	virtual float GetInterval() const = 0;

	virtual int32 GetCountByInterval() const = 0;

	virtual int32 GetCount() const = 0;
};

#pragma endregion ICsTdSpawnerCreepParams