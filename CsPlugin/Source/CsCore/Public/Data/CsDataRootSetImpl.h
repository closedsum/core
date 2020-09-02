// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Data/CsDataRootSet.h"

#include "CsDataRootSetImpl.generated.h"

class UDataTable;

UCLASS(Blueprintable)
class CSCORE_API UCsDataRootSetImpl : public UObject,
									  public ICsDataRootSet
{
	GENERATED_UCLASS_BODY()

public:

// Flow
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root", meta = (AllowedClasses = "World"))
	FSoftObjectPath EntryMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root", meta = (AllowedClasses = "World"))
	FSoftObjectPath TransitionEntryToMainMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root", meta = (AllowedClasses = "World"))
	FSoftObjectPath MainMap;

#pragma endregion Flow

// Startup
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	FName StartupPayload;

#pragma endregion Startup

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* Datas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* DataTables;

#if WITH_EDITOR

	void AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable);
	void AddDataTable(const FName& Entryname, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames);

#endif // #if WITH_EDITOR

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* Payloads;

// ICsDataRootSet
#pragma region
public:

	FORCEINLINE const FSoftObjectPath& GetEntryMap() const
	{
		return EntryMap;
	}

	FORCEINLINE const FSoftObjectPath& GetTransitionEntryToMainMap() const
	{
		return TransitionEntryToMainMap;
	}

	FORCEINLINE const FSoftObjectPath& GetMainMap() const
	{
		return MainMap;
	}

	FORCEINLINE const FName& GetStartupPayload() const
	{
		return StartupPayload;
	}

	FORCEINLINE UDataTable* GetDatas() const
	{
		return Datas;
	}

	FORCEINLINE UDataTable* GetDataTables() const
	{
		return DataTables;
	}

	FORCEINLINE UDataTable* GetPayloads() const
	{
		return Payloads;
	}

#pragma endregion ICsDataRootSet

	// Editor
#pragma region
#if WITH_EDITOR
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
#pragma endregion Editor

};