// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#include "Containers/CsInterfaceMap.h"
#include "Managers/Creep/CsTdTypes_Creep.h"

#include "CsTdTypes_Spawner_Creep.generated.h"
#pragma once

// SpawnerCreep
#pragma region

USTRUCT(BlueprintType)
struct CSTD_API FECsTdSpawnberCreep : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsTdSpawnberCreep)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsTdSpawnberCreep)

struct CSTD_API EMCsTdSpawnerCreep : public TCsEnumStructMap<FECsTdSpawnberCreep, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsTdSpawnerCreep, FECsTdSpawnberCreep, uint8)
};

#pragma endregion Creep

// ICsTdSpawnerCreepParams
#pragma region

struct CSTD_API ICsTdSpawnerCreepParams : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

	virtual ~ICsTdSpawnerCreepParams() {}

	virtual const FECsTdCreep& GetType() const = 0;

	virtual float GetInterval() const = 0;

	virtual int32 GetCountByInterval() const = 0;

	virtual int32 GetCount() const = 0;
};

#pragma endregion ICsTdSpawnerCreepParams