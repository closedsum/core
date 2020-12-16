// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Engine/DataTable.h"

#include "CsTypes_UserWidget.generated.h"
#pragma once

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
	typedef FECsUserWidget Type;

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
	typedef FECsUserWidgetClass Type;

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
	typedef FECsUserWidgetPooled Type;

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
	typedef FECsUserWidgetPooledClass Type;

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

	FORCEINLINE TSubclassOf<UUserWidget> GetSubclassOf() const { return Widget_SubclassOf; }

	bool IsValidChecked(const FString& Context)
	{
		checkf(Widget.ToSoftObjectPath().IsValid(), TEXT("%s: FCsUserWidgetPtr.Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString()));

		return true;
	}

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsData_UserWidget"))
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsUserWidgetPooled"))
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

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidgetPooledClass Class;

	/** */
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