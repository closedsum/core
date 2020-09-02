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
* Enum for Widget Actor types, objects that implement the interface:
* ICsWidgetActor
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
struct FCsUIDataRootSet;

namespace NCsWidgetActor
{
	typedef FECsWidgetActor Type;

	CSUI_API void FromEnumSettings(const FString& Context);

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion WidgetActor

// WidgetActorClass
#pragma region

/**
* Enum for Widget Actor class types, classes that implement the interface:
* ICsWidgetActor
*/
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

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

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

// FCsWidgetActorPtr
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsWidgetActorPtr : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsWidgetActor"))
	TSoftClassPtr<UObject> Widget;

	UPROPERTY()
	int32 Widget_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Widget_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Widget_Class;

	UPROPERTY(Transient, BlueprintReadOnly)
	TSubclassOf<UObject> Widget_SubclassOf;

	FCsWidgetActorPtr() :
		Widget(nullptr),
		Widget_LoadFlags(0),
		Widget_Internal(nullptr),
		Widget_Class(nullptr),
		Widget_SubclassOf(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Widget_Internal; }
	
	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Widget_Class; }

	template<typename T>
	FORCEINLINE T* GetClass() const { return Cast<T>(GetClass()); }

	FORCEINLINE TSubclassOf<UObject> GetSubclassOf() const { return Widget_SubclassOf; }
};

#pragma endregion FCsWidgetActorPtr

// FCsWidgetActorClassEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsWidgetActorClassEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsWidgetActor) name for the widget actor class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsWidgetActor) display name for the widget actor class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Soft Reference to a widget actor class of type: ICsWidgetActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsWidgetActorPtr Class;

	FCsWidgetActorClassEntry() :
		Name(),
		DisplayName(),
		Class()
	{
	}
};

#pragma endregion FCsProjectileClassEntry

// FCsData_WidgetActorPtr
#pragma region

class UObject;

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsData_WidgetActorPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsData_WidgetActor"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Data_Class;

	FCsData_WidgetActorPtr() :
		Data(nullptr),
		Load_Flags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Data_Class; }
};

#pragma endregion FCsData_WidgetActorPtr

// FCsWidgetActorEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsWidgetActorEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsProjectile) name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsProjectile) display name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsWidgetActorClass Class;

	/** Soft Reference to a data of type: ICsData_Projectile. */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//FCsData_ProjectilePtr Data;

	FCsWidgetActorEntry() :
		Name(),
		DisplayName(),
		Class()
	{
	}
};

#pragma endregion FCsProjectileEntry