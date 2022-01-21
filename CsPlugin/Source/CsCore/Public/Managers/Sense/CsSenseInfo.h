// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Managers/Resource/CsResourceContainer.h"
#include "Managers/Sense/CsSensedObject.h"

#include "CsSenseInfo.generated.h"
#pragma once

class ICsSensedObject;
class ICsSensingObject;
class UObject;

struct CSCORE_API ICsSenseInfo
{
public:

	virtual ~ICsSenseInfo(){}

	/*
	virtual const FECsSenseObjectType& GetType() const = 0;;

	virtual const ECsSenseTeam& GetTeam() const = 0;
	*/

	virtual const FCsSensedObject& GetObject() const = 0;

	virtual void SetObject(ICsSensedObject* InSenseObject, UObject* InObject) = 0;
};


// SenseInfoKey
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSenseInfoKey : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSenseInfoKey)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSenseInfoKey)

struct CSCORE_API EMCsSenseInfoKey : public TCsEnumStructMap<FECsSenseInfoKey, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSenseInfoKey, FECsSenseInfoKey, uint8)
};

namespace NCsSenseInfoKey
{
	typedef FECsSenseInfoKey Type;
}

#pragma endregion SenseInfoKey

// FCsSenseInfoKey
#pragma region

struct CSCORE_API FCsSenseInfoKey
{
public:

	FName Key;

	FName From;

	FName To;

	FName Direction;

	FCsSenseInfoKey() :
		Key(NAME_None),
		From(NAME_None),
		To(NAME_None),
		Direction(NAME_None)
	{
	}

	FCsSenseInfoKey(const FName& InKey, const FName& InFrom, const FName& InTo, const FName& InDirection)
	{
		Key = InKey;
		From = InFrom;
		To = InTo;
		Direction = InDirection;
	}

	FORCEINLINE bool operator==(const FCsSenseInfoKey& B) const
	{
		return Key == B.Key && From == B.From && To == B.To && Direction == B.Direction;
	}

	FORCEINLINE bool operator!=(const FCsSenseInfoKey& B) const
	{
		return !(*this == B);
	}
};

FORCEINLINE uint32 GetTypeHash(const FCsSenseInfoKey& b)
{
	return GetTypeHash(b.Key);
}

#pragma endregion FCsSenseInfoKey

// FCsSenseInfoValue
#pragma region

struct CSCORE_API FCsSenseInfoValue
{
	FVector MeToObject;

// Distance
#pragma region
public:

	float Distance;

	float DistanceSq;

	float DistanceXY;

	float DistanceSqXY;

#pragma endregion Distance;

// Direction
#pragma region
public:

	FVector Direction;

	FVector DirectionXY;

#pragma endregion Direction

// Dot
#pragma region
public:

	float Dot;
	float DotXY;

#pragma endregion Dot

	FCsSenseInfoValue() :
		MeToObject(0.0f),
		Distance(0.0f),
		DistanceSq(0.0f),
		DistanceXY(0.0f),
		DistanceSqXY(0.0f),
		Direction(0.0f),
		DirectionXY(0.0f),
		Dot(0.0f),
		DotXY(0.0f)
	{
	}
};

#pragma endregion FCsSenseInfoValue

// FCsSenseInfo
#pragma region

struct CSCORE_API FCsSenseInfo : public ICsSenseInfo
{
public:

	FCsSensedObject Object;

/** 
 * Info is in relation of Me to Object. 
 *  Me: the Sensing Object.
 *  Object: the Sensed Object. 
 */

	TMap<FCsSenseInfoKey, FCsSenseInfoValue> Data;

	FCsSenseInfo() :
		Object(),
		Data()
	{
	}

	virtual ~FCsSenseInfo()
	{
	}

// ICsSenseInfo
#pragma region
public:

	const FCsSensedObject& GetObject() const;

	void SetObject(ICsSensedObject* InSenseObject, UObject* InObject);

#pragma endregion ICsSenseInfo

public:

	void Update(const float& CurrentTime, ICsSensingObject* SensingObject);

	void Reset()
	{
		Object.Reset();
		Data.Reset();
	}
};

#pragma endregion FCsSenseInfo