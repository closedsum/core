// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsTypes_WidgetActor.generated.h"
#pragma once

// WidgetActor
#pragma region

/**
* Enum for Widget Actor types
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsWidgetActor : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWidgetActor)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWidgetActor)

struct CSUI_API EMCsWidgetActor final : public TCsEnumStructMap<FECsWidgetActor, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWidgetActor, FECsWidgetActor, uint8)
};

class UObject;

namespace NCsWidgetActor
{
	typedef FECsWidgetActor Type;

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion WidgetActor

// WidgetActorClass
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FECsWidgetActorClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWidgetActorClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWidgetActorClass)

struct CSUI_API EMCsWidgetActorClass : public TCsEnumStructMap<FECsWidgetActorClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWidgetActorClass, FECsWidgetActorClass, uint8)
};

namespace NCsWidgetActorClass
{
	typedef FECsWidgetActorClass Type;

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion WidgetActorClass

// WidgetActorDeallocateMethod
#pragma region

/**
* Type for different ways to deallocate an FX.
*/
UENUM(BlueprintType)
enum class ECsWidgetActorDeallocateMethod : uint8
{
	/** If a Widget Actor is attached to a parent object,
		  LifeTime == 0.of means the Widget Actor will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the Widget Actor.
		If a Widget Actor is NOT attached to a parent object,
		  LifeTime == 0.0f means the Widget Actor will stay active forever.
		  LifeTime > 0.0f means the Widget Actor will be deallocated after LifeTime amount of time after
		   the Widget Actor has been allocated. */
	LifeTime							UMETA(DisplayName = "LifeTime"),
	/** */
	Complete							UMETA(DisplayName = "Complete"),
	ECsWidgetActorDeallocateMethod_MAX	UMETA(Hidden),
};

struct CSUI_API EMCsWidgetActorDeallocateMethod final : public TCsEnumMap<ECsWidgetActorDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsWidgetActorDeallocateMethod, ECsWidgetActorDeallocateMethod)
};

namespace NCsWidgetActorDeallocateMethod
{
	typedef ECsWidgetActorDeallocateMethod Type;

	namespace Ref
	{
		extern CSUI_API const Type LifeTime;
		extern CSUI_API const Type Complete;
		extern CSUI_API const Type ECsWidgetActorDeallocateMethod_MAX;
	}

	extern CSUI_API const uint8 MAX;
}

#pragma endregion WidgetActorDeallocateMethod