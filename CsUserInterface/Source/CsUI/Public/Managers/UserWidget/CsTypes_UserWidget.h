// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Engine/DataTable.h"
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_UserWidget.generated.h"

// UserWidget
#pragma region

/**
* Enum for UserWidget types, objects that extend from the class:
* UUserWidget.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidget : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidget)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidget)

struct CSUI_API EMCsUserWidget final : public TCsEnumStructMap<FECsUserWidget, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidget, FECsUserWidget, uint8)
};

class UObject;
struct FCsUIDataRootSet;

namespace NCsUserWidget
{
	typedef EMCsUserWidget EnumMapType;
	typedef FECsUserWidget Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSUI_API void FromEnumSettings(const FString& Context);

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidget

// UserWidgetClass
#pragma region

/**
* Enum for UserWidget class types, classes that extend from the class:
* UUserWidget.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetClass)

struct CSUI_API EMCsUserWidgetClass : public TCsEnumStructMap<FECsUserWidgetClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetClass, FECsUserWidgetClass, uint8)
};

namespace NCsUserWidgetClass
{
	typedef EMCsUserWidgetClass EnumMapType;
	typedef FECsUserWidgetClass Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidgetClass

// UserWidgetData
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetData : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetData)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetData)

struct CSUI_API EMCsUserWidgetData : public TCsEnumStructMap<FECsUserWidgetData, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetData, FECsUserWidgetData, uint8)
};

namespace NCsUserWidgetData
{
	typedef FECsUserWidgetData Type;
}

#pragma endregion UserWidgetData

// UserWidgetPooled
#pragma region

/**
* Enum for UserWidgetPooled types, objects that implement the interface:
* ICsUserWidgetPooled.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetPooled : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetPooled)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetPooled)

struct CSUI_API EMCsUserWidgetPooled final : public TCsEnumStructMap<FECsUserWidgetPooled, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetPooled, FECsUserWidgetPooled, uint8)
};

class UObject;

namespace NCsUserWidgetPooled
{
	typedef EMCsUserWidgetPooled EnumMapType;
	typedef FECsUserWidgetPooled Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSUI_API void FromEnumSettings(const FString& Context);

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidget

// UserWidgetPooledClass
#pragma region

/**
* Enum for UserWidgetPooled class types, classes that implement the interface:
* ICsUserWidgetPooled.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetPooledClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetPooledClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetPooledClass)

struct CSUI_API EMCsUserWidgetPooledClass : public TCsEnumStructMap<FECsUserWidgetPooledClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass, uint8)
};

namespace NCsUserWidgetPooledClass
{
	typedef EMCsUserWidgetPooledClass EnumMapType;
	typedef FECsUserWidgetPooledClass Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidgetPooledClass

// FCsUserWidgetPtr
#pragma region

class UUserWidget;
class UClass;

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidgetPtr : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UUserWidget> Widget;

	UPROPERTY()
	int32 Widget_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UUserWidget* Widget_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Widget_Class;

	UPROPERTY(Transient, BlueprintReadOnly)
	TSubclassOf<UUserWidget> Widget_SubclassOf;

	FCsUserWidgetPtr() :
		Widget(nullptr),
		Widget_LoadFlags(0),
		Widget_Internal(nullptr),
		Widget_Class(nullptr),
		Widget_SubclassOf(nullptr)
	{
	}

	FORCEINLINE UUserWidget* Get() const { return Widget_Internal; }
	
	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Widget_Class; }

	template<typename T>
	FORCEINLINE T* GetClass() const { return Cast<T>(GetClass()); }

	FORCEINLINE UClass* GetClassChecked() const
	{
		checkf(Widget.ToSoftObjectPath().IsValid(), TEXT("FCsUserWidgetPtr::GetClassChecked: Widget's Path: %s is NOT Valid."), *(Widget.ToSoftObjectPath().ToString()));

		checkf(Widget_Class, TEXT("FCsUserWidgetPtr::GetClassChecked: Widget has NOT been loaded from Path @ %s."), *(Widget.ToSoftObjectPath().ToString()));

		return Widget_Class;
	}

	FORCEINLINE UClass** GetClassPtr() { return &Widget_Class; }

	FORCEINLINE const TSubclassOf<UUserWidget>& GetSubclassOf() const { return Widget_SubclassOf; }

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(Widget.ToSoftObjectPath().IsValid(), TEXT("%s: FCsUserWidgetPtr.Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString()));

		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const
	{
		if (!Widget.ToSoftObjectPath().IsValid())
		{
			if (Log)
			{
				Log(FString::Printf(TEXT("%s: FCsUserWidgetPtr.Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString())));
			}
			return false;
		}
		return true;
	}

	UClass* LoadChecked(const FString& Context);
	UClass* SafeLoad(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

	// Added functions to mimic behavior for containers for interfaces

	void SetObject(UObject* InWidget);

	UObject* GetObject() const;
};

#pragma endregion FCsUserWidgetPtr

// FCsUserWidgetClassEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidgetClassEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsUserWidgetClass) name for the user widget class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsUserWidgetClass) display name for the user widget class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Soft Reference to a user widget class of type: UUserWidget. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsUserWidgetPtr Class;

	FCsUserWidgetClassEntry() :
		Name(),
		DisplayName(),
		Class()
	{
	}
};

#pragma endregion FCsUserWidgetClassEntry

// FCsData_UserWidgetPtr
#pragma region

class UObject;

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsData_UserWidgetPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "/Script.CsUI.CsData_UserWidget"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Data_Class;

	FCsData_UserWidgetPtr() :
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

#pragma endregion FCsData_UserWidgetPtr

// FCsUserWidgetEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidgetEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsUserWidget) name for the user widget. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsUserWidget) display name for the user widget. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidgetClass Class;

	/** Soft Reference to a data of type: ICsData_UserWidget. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsData_UserWidgetPtr Data;

	FCsUserWidgetEntry() :
		Name(),
		DisplayName(),
		Class(),
		Data()
	{
	}
};

#pragma endregion FCsUserWidgetEntry

// FCsUserWidgetPooledPtr
#pragma region

class UObject;
class UClass;

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidgetPooledPtr : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	/** Soft Class reference to an object that implements the interface: ICsUserWidgetPooled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "/Script.CsUI.CsUserWidgetPooled"))
	TSoftClassPtr<UObject> Widget;

	UPROPERTY()
	int32 Widget_LoadFlags;

	/** Hard reference to an object that implements the interface: ICsUserWidgetPooled. */
	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Widget_Internal;

	/** Hard reference to the class that implements the interface: ICsUserWidgetPooled. */
	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Widget_Class;

	/** Subclass to a hard reference to the class that implements the interface: ICsUserWidgetPooled. */
	UPROPERTY(Transient, BlueprintReadOnly)
	TSubclassOf<UObject> Widget_SubclassOf;

	FCsUserWidgetPooledPtr() :
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

#pragma endregion FCsUserWidgetPooledPtr

// FCsUserWidgetPooledClassEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidgetPooledClassEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsUserWidgetPooledClass) name for the user widget pooled class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsUserWidgetPooledClass) display name for the user widget pooled class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Soft Reference to a user widget class of type: ICsUserWidgetPooled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsUserWidgetPooledPtr Class;

	FCsUserWidgetPooledClassEntry() :
		Name(),
		DisplayName(),
		Class()
	{
	}
};

#pragma endregion FCsUserWidgetClassEntry

// FCsUserWidgetPooledEntry
#pragma region

/**
* Row struct / entry in a DataTable that contains information related
* to a Pooled UserWidget of type: UUserWidget. 
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidgetPooledEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsUserWidgetPooled) name for the user widget pooled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsUserWidgetPooled) display name for the user widget pooled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** The class type associated with this entry.
		If populated from a DataTable, the DataTable row struct will usually be 
		FCsUserWidgetPooledClassEntry or something similar. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidgetPooledClass Class;

	/** The widget type associated with this entry.
		If populated from a DataTable, the DataTable row struct will usually be 
		FCsUserWidgetEntry or something similar. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidget UserWidget;

	FCsUserWidgetPooledEntry() :
		Name(),
		DisplayName(),
		Class(),
		UserWidget()
	{
	}
};

#pragma endregion FCsUserWidgetPooledEntry

// UserWidgetDeallocateMethod
#pragma region

/**
* Type for different ways to deallocate a pooled UserWidget.
*  UserWidget is an object that implements the interface: ICsUserWidgetPooled.
*/
UENUM(BlueprintType)
enum class ECsUserWidgetDeallocateMethod : uint8
{
	/** If an UserWidget is attached to a parent object,
		  LifeTime == 0.of means the UserWidget object will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the UserWidget object.
		If an UserWidget is NOT attached to a parent object,
		  LifeTime == 0.0f means the UserWidget object will stay active forever.
		  LifeTime > 0.0f means the UserWidget will be deallocated after LifeTime amount of time after
		   the UserWidget object has been allocated. */
	LifeTime						  UMETA(DisplayName = "LifeTime"),
	/** */
	Complete						  UMETA(DisplayName = "Complete"),
	ECsUserWidgetDeallocateMethod_MAX UMETA(Hidden),
};

struct CSUI_API EMCsUserWidgetDeallocateMethod final : public TCsEnumMap<ECsUserWidgetDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsUserWidgetDeallocateMethod, ECsUserWidgetDeallocateMethod)
};

namespace NCsUserWidgetDeallocateMethod
{
	typedef ECsUserWidgetDeallocateMethod Type;

	namespace Ref
	{
		extern CSUI_API const Type LifeTime;
		extern CSUI_API const Type Complete;
		extern CSUI_API const Type ECsUserWidgetDeallocateMethod_MAX;
	}

	extern CSUI_API const uint8 MAX;
}

namespace NCsUserWidget
{
	enum class EDeallocateMethod : uint8
	{
		/** If an UserWidget is attached to a parent object,
		  LifeTime == 0.of means the UserWidget object will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the UserWidget object.
		If an UserWidget is NOT attached to a parent object,
		  LifeTime == 0.0f means the UserWidget object will stay active forever.
		  LifeTime > 0.0f means the UserWidget will be deallocated after LifeTime amount of time after
		   the UserWidget object has been allocated. */
		LifeTime,
		/** */
		Complete
	};

	struct CSUI_API EMDeallocateMethod final : public TCsEnumMap<EDeallocateMethod>
	{
		CS_ENUM_MAP_BODY(EMDeallocateMethod, EDeallocateMethod)
	};

	namespace NDeallocateMethod
	{
		namespace Ref
		{
			typedef EDeallocateMethod Type;

			extern CSUI_API const Type LifeTime;
			extern CSUI_API const Type Complete;
		}
	}
}

#pragma endregion UserWidgetDeallocateMethod

// UserWidgetPosition
#pragma region

/**
* Type for different ways to interpret Position information for being
*  converted to screen space for a UserWidget.
*  UserWidget is an object that implements the interface: ICsUserWidgetPooled.
*/
UENUM(BlueprintType)
enum class ECsUserWidgetPosition : uint8
{
	/** */
	Screen						UMETA(DisplayName = "Screen"),
	/** Position is in World Space and converted to Screen Space */
	World						UMETA(DisplayName = "World"),
	/** Position is retrieved from a Parent object and converted to Screen Space */
	Parent						UMETA(DisplayName = "Parent"),
	ECsUserWidgetPosition_MAX	UMETA(Hidden),
};

struct CSUI_API EMCsUserWidgetPosition final : public TCsEnumMap<ECsUserWidgetPosition>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsUserWidgetPosition, ECsUserWidgetPosition)
};

namespace NCsUserWidgetPosition
{
	typedef ECsUserWidgetPosition Type;

	namespace Ref
	{
		extern CSUI_API const Type Screen;
		extern CSUI_API const Type World;
		extern CSUI_API const Type Parent;
		extern CSUI_API const Type ECsUserWidgetPosition_MAX;
	}

	extern CSUI_API const uint8 MAX;
}

namespace NCsUserWidget
{
	/**
	* Type for different ways to interpret Position information for being
	*  converted to screen space for a UserWidget.
	*  UserWidget is an object that implements the interface: ICsUserWidgetPooled.
	*/
	enum class EPosition : uint8
	{
		Screen,
		/** Position is in World Space and converted to Screen Space */
		World,
		/** Position is retrieved from a Parent object and converted to Screen Space */
		Parent,
		EPosition_MAX
	};

	struct CSUI_API EMPosition final : public TCsEnumMap<EPosition>
	{
		CS_ENUM_MAP_BODY(EMPosition, EPosition)
	};

	namespace NPosition
	{
		namespace Ref
		{
			typedef EPosition Type;

			extern CSUI_API const Type Screen;
			extern CSUI_API const Type World;
			extern CSUI_API const Type Parent;
			extern CSUI_API const Type EPosition_MAX;
		}
	}
}

#pragma endregion UserWidgetPosition

// NCsUserWidget::NPayload::EChange
#pragma region

namespace NCsUserWidget
{
	namespace NPayload
	{
		enum class EChange : uint32
		{
			AddedToViewport = 1<<0,
			ZOrder			= 1<<1
		};
	}
}

#pragma endregion NCsUserWidget::NPayload::EChange