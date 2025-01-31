// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Data/ICsData.h"

#include "CsScriptData.generated.h"

UINTERFACE(BlueprintType, MinimalApi)
class UCsScriptData : public UCsData
{
	GENERATED_UINTERFACE_BODY()
};

class CSDATA_API ICsScriptData : public ICsData
{
	GENERATED_BODY()

// ICsData
#pragma region
public:

	CsDataType* _getIData() const { return nullptr; }

	bool IsValid(const int32& LoadFlags);
	void Load(const int32& LoadFlags);
	void Unload();
	bool IsLoaded() const;

#pragma endregion ICsData

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Is Valid"))
	bool Script_IsValid(const int32& LoadFlags, bool& OutSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Load"))
	bool Script_Load(const int32& LoadFlags, bool& OutSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Unload"))
	bool Script_Unload(bool& OutSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Is Loaded"))
	bool Script_IsLoaded(bool& OutSuccess) const;
};