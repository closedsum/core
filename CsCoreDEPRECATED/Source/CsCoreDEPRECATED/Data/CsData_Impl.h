// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "Types/CsTypes_Load.h"
#include "CsData_Impl.generated.h"

// Macros
#pragma region

#define CS_DATA_DEFINE_LOAD_INTERNAL_FUNCTION_POINTERS(CLASS)	GetAssetReferencesFromObject_Internal = &CLASS::GetAssetReferencesFromObject_Internal; \
																LoadObjectWithTSoftObjectPtrs_Internal = &CLASS::LoadObjectWithTSoftObjectPtrs_Internal; \
																WriteObjectToJson_Internal = &CLASS::WriteObjectToJson_Internal; \
																ReadObjectFromJson_Internal = &CLASS::ReadObjectFromJson_Internal;

#pragma endregion Macros

// Structs
#pragma region

USTRUCT(BlueprintType)
struct FCsDataAddToDataMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool AddToDataMapping;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 LoadFlags;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;

	FCsDataAddToDataMapping() :
		AddToDataMapping(false),
		LoadFlags(0),
		Message(),
		Output()
	{
		CS_SET_BLUEPRINT_BITFLAG(LoadFlags, ECsLoadFlags::Game);
	}
};

USTRUCT(BlueprintType)
struct FCsDataAddToPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool AddToPayload;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FECsDataCollectionType DataCollectionType;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	ECsLoadFlags_Editor LoadFlags;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT(BlueprintType)
struct FCsDataLoadFromJson
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Load;
};

#pragma endregion Structs

class UClass;
class UCsDataMapping;
class UCsData_Payload;

UCLASS(Abstract, NotBlueprintable)
class CSCORE_API UCsData_Impl : public UObject
{
	GENERATED_UCLASS_BODY()

	// Default

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Default")
	FECsDataType Type;

	/** Short Code - linked with Backend */
	UPROPERTY(EditDefaultsOnly, Category = "00 Default")
	FName ShortCode;

	FString ShortCodeAsString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 Default")
	FName Name;

	/** Alternative Names - used for to quickly access class - DEBUG */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 Default")
	TArray<FName> AlternativeNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 Default")
	bool IgnoreIsValidCheck;

	virtual void PostLoad() override;
	virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;

#if WITH_EDITOR
	virtual void OnPreSave();
#endif // #if WITH_EDITOR

	virtual bool IsValid(const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

	TCsGetAssetReferencesFromObject_Internal GetAssetReferencesFromObject_Internal;

	virtual void PopulateAssetReferences(const bool &CalculateResourceSizes);

	UPROPERTY(VisibleDefaultsOnly, Category = "00 Default")
	TArray<FCsCategoryMemberAssociation> CategoryMemberAssociations;

#if WITH_EDITOR
	void VerifyJsonIntegrity();
#endif // #if WITH_EDITOR

	UPROPERTY(VisibleDefaultsOnly, Category = "00 Default")
	FCsTArrayStringAssetReference AssetReferences[ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

	virtual void Load(const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

	TCsLoadObjectWithTSoftObjectPtrs_Internal LoadObjectWithTSoftObjectPtrs_Internal;

	virtual void UnLoad();
	virtual bool IsLoaded();

	virtual FString GetAbsolutePath();

	TCsWriteObjectToJson_Internal WriteObjectToJson_Internal;
	TCsReadObjectFromJson_Internal ReadObjectFromJson_Internal;

	virtual void SaveToJson();

	bool HasLoadedFromJson;

	virtual void LoadFromJson();

// 99 Data Mapping
#pragma region

	UPROPERTY()
	FString DataMappingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "-99 Data Mapping")
	FCsDataAddToDataMapping AddToDataMapping;

	UPROPERTY()
	FString PayloadName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "-99 Data Mapping")
	FCsDataAddToPayload AddToPayload;

#if WITH_EDITOR

	UClass* DataMappingClass;

	UCsDataMapping* GetDataMapping();
	UCsData_Payload* GetPayload();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion 99 Data Mapping

// 100 Json
#pragma region

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "-100 Json")
	FCsDataLoadFromJson PerformLoadFromJson;

#pragma endregion 100 Json
};