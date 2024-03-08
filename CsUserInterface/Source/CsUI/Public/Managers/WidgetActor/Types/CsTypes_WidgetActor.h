// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Engine/DataTable.h"
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_WidgetActor.generated.h"

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
	typedef EMCsWidgetActor EnumMapType;
	typedef FECsWidgetActor Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

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
	typedef EMCsWidgetActorClass EnumMapType;
	typedef FECsWidgetActorClass Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (MustImplement = "/Script/CsUI.CsWidgetActor"))
	TSoftClassPtr<UObject> Widget;

	UPROPERTY()
	int32 Widget_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	UObject* Widget_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	UClass* Widget_Class;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsUI|Widget Actor")
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

	/** The enum (FECsWidgetActorClass) name for the widget actor class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FString Name;

	/** The enum (FECsWidgetActorClass) display name for the widget actor class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FString DisplayName;

	/** Soft Reference to a widget actor class of type: ICsWidgetActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
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

	/** Soft Reference to an object that implements the interface: ICsData_WidgetActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (MustImplement = "/Script/CsUI.CsData_WidgetActor"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(BlueprintReadOnly, Category = "CsUI|Widget Actor")
	int32 Data_LoadFlags;

	/** Hard Reference to an object that implements the interface: ICsData_WidgetActor. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	UObject* Data_Internal;

	/** Hard Reference to a class that implements the interface: ICsData_WidgetActor. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	UClass* Data_Class;

	FCsData_WidgetActorPtr() :
		Data(nullptr),
		Data_LoadFlags(0),
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

	/** The enum (FECsWidgetActor) name for the widget actor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FString Name;

	/** The enum (FECsWidgetActor) display name for the widget actor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FString DisplayName;

	/** The type of WidgetActor. A reference to the WidgetActor is obtained 
		from Manager_WidgetActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
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

// FCsWidgetActorPooled_CameraInfo
#pragma region

// NCsWidgetActor::NCamera::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWidgetActor, NCamera, FInfo)

/**
* Describes any information related to the Camera for a pooled WidgetActor.
*  WidgetActor is an object that implements the interface: ICsWidgetActor
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsWidgetActorPooled_CameraInfo
{
	GENERATED_USTRUCT_BODY()

	/** How fast to interpolate the the rotation of the Widget Actor to face
		the Player Camera. 
		LerpRate == 0.0f -> Instance / Snap to face Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (UIMIn = "0.0", ClampMin = "0.0"))
	float LerpRate;

	/** Which Axes to Lock, which should NOT Snap to the Player Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsRotationRules"))
	int32 LockAxes;

	/** Any rotation offset to apply after the Widget Actor has been oriented to face
		the Player Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FRotator3f Rotation;

	FCsWidgetActorPooled_CameraInfo() : 
		LerpRate(0.0f),
		LockAxes(4), // Roll (1 << 2)
		Rotation(0.0f)
	{
	}

#define InfoType NCsWidgetActor::NCamera::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

namespace NCsWidgetActor
{
	namespace NCamera
	{
		/**
		* Describes any information related to the Camera for a pooled WidgetActor.
		*  WidgetActor is an object that implements the interface: ICsWidgetActor
		*  This is mostly used by object pooled by a Manager
		*/
		struct CSUI_API FInfo
		{
		private:

			/** How fast to interpolate the the rotation of the Widget Actor to face
				the Player Camera.
				LerpRate == 0.0f -> Instance / Snap to face Camera. */
			CS_DECLARE_MEMBER_WITH_PROXY(LerpRate, float)
			/** Which Axes to Lock, which should NOT Snap to the Player Camera. */
			CS_DECLARE_MEMBER_WITH_PROXY(LockAxes, int32)
			/** Any rotation offset to apply after the Widget Actor has been oriented to face
				the Player Camera. */
			CS_DECLARE_MEMBER_WITH_PROXY(Rotation, FRotator3f)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(LerpRate, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(LockAxes, 4), // Roll (1 << 2)
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Rotation, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(LerpRate);
				CS_CTOR_SET_MEMBER_PROXY(LockAxes);
				CS_CTOR_SET_MEMBER_PROXY(Rotation);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LerpRate, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LockAxes, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Rotation, FRotator3f)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsWidgetActorPooled_CameraInfo

// FCsWidgetActorPooledInfo
#pragma region

/**
* Container holding general information for a pooled WidgetActor.
*  WidgetActor is an object that implements the interface: ICsWidgetActor
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsWidgetActorPooledInfo
{
	GENERATED_USTRUCT_BODY()

	/** Type of WidgetActor. The reference for the WidgetActor is obtained from
	    Manager_WidgetActor. Generally, this should be set to the DefaultType set 
		in UCsUserInterfaceSettings->Manager_WidgetActor.DefaultType. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FECsWidgetActor WidgetActor;

	/** Condition to determine when to deallocate the WidgetActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	ECsWidgetActorDeallocateMethod DeallocateMethod;

	/** Valid if the DeallocateMethod == ECsWidgetActorDeallocateMethod::LifeTime.
		- If a WidgetActor IS attached to a Parent object, 
		   LifeTime == 0.of means the WidgetActor will be deallocated immediately
	        when the Parent object has been destroyed / deallocated.
		   LifeTime > 0.0f will be the time after the Parent object has been 
		    destroyed / deallocated to deallocate the WidgetActor.
	    - If a WidgetActor is NOT attached to a Parent object,
		   LifeTime == 0.0f means the WidgetActor will stay active forever.
		   LifeTime > 0.0f means the WidgetActor will be deallocated after LifeTime amount of time after
	        the WidgetActor has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** Valid if the WidgetActor is attached to a Parent object or when a WidgetActor is
		allocated, the Parent field of the payload is set.If the Parent object is NULL,
		the WidgetActor will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FCsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the WidgetActor is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FName Bone;

	/** Which of the components of Transform to apply to the WidgetActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the WidgetActor.
		If the WidgetActor is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FTransform Transform;

	/** Whether to use CameraInfo or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (ScriptName = "m_bCameraInfo", InlineEditConditionToggle))
	bool bCameraInfo;

	/** Describes any information related to the Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor", meta = (ScriptName = "m_CameraInfo", editcondition = "bCameraInfo"))
	FCsWidgetActorPooled_CameraInfo CameraInfo;

public:

	FCsWidgetActorPooledInfo() :
		WidgetActor(),
		DeallocateMethod(ECsWidgetActorDeallocateMethod::Complete),
		LifeTime(0.0f),
		AttachmentTransformRules(FCsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform::Identity),
		bCameraInfo(true),
		CameraInfo()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

#pragma endregion FCsWidgetActorPooledInfo