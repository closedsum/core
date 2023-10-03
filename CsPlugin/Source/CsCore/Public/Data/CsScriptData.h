// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Data/CsData.h"

#include "CsScriptData.generated.h"

UINTERFACE(BlueprintType, MinimalApi)
class UCsScriptData : public UCsData
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsScriptData : public ICsData
{
	GENERATED_IINTERFACE_BODY()

// ICsData
#pragma region
public:

#define DataType NCsData::IData
	DataType* _getIData() const { return nullptr; }
#undef DataType

	bool IsValid(const int32& LoadFlags);
	void Load(const int32& LoadFlags);
	void Unload();
	bool IsLoaded() const;

#pragma endregion ICsData

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Is Valid"))
	bool Script_IsValid(const int32& LoadFlags);

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Load"))
	void Script_Load(const int32& LoadFlags);

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Unload"))
	void Script_Unload();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptData", meta = (DisplayName = "Is Loaded"))
	bool Script_IsLoaded() const;
};