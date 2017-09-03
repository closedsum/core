// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "CsTypes.h"
#include "CsData.generated.h"

USTRUCT()
struct FCsDataAddToDataMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Add;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 LoadFlags;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;

	FCsDataAddToDataMapping()
	{
		CS_SET_BLUEPRINT_BITFLAG(LoadFlags, ECsLoadFlags::All);
		CS_SET_BLUEPRINT_BITFLAG(LoadFlags, ECsLoadFlags::Game);
	}
};

USTRUCT()
struct FCsDataLoadFromJson
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Load;
};

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData : public AActor
{
	GENERATED_UCLASS_BODY()

	// Default

	TCsAssetType Type;
	TCsAssetType Type_MAX;

	TCsAssetTypeToString AssetTypeToString;
	TCsStringToAssetType StringToAssetType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Default")
	uint8 Type_Script;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 Default")
	FString TypeAsString;

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

	virtual bool IsValid(const ECsLoadFlags &LoadFlags = ECsLoadFlags::All);

	TCsGetAssetReferencesFromObject_Internal GetAssetReferencesFromObject_Internal;

	void PopulateAssetReferences(const bool &CalculateResourceSizes);

	UPROPERTY(VisibleDefaultsOnly, Category = "00 Default")
	TArray<FCsCategoryMemberAssociation> CategoryMemberAssociations;

	UPROPERTY(VisibleDefaultsOnly, Category = "00 Default")
	FCsTArrayStringAssetReference AssetReferences[ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

	virtual void Load(const ECsLoadFlags &LoadFlags = ECsLoadFlags::All);

	TCsLoadObjectWithTAssetPtrs_Internal LoadObjectWithTAssetPtrs_Internal;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "99 Data Mapping")
	FCsDataAddToDataMapping AddToDataMapping;

#if WITH_EDITOR

	class UClass* DataMappingClass;

	class ACsDataMapping* GetDataMapping();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion 99 Data Mapping

// 100 Json
#pragma region

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "100 Json")
	FCsDataLoadFromJson PerformLoadFromJson;

#pragma endregion 100 Json
};