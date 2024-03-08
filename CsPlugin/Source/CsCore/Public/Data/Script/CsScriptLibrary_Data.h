// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Data.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Data : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// ICsScriptData
#pragma region
public:

	/**
	* Call the method Script_Load for Object.
	*  Object MUST implement the interface: ICsScriptData
	* 
	* @param Context	The calling context.
	* @param Object
	* @param LoadFlags
	* return			
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|ICsScriptData", meta = (AutoCreateRefTerm = "Context,LoadFlags"))
	static bool Script_Load(const FString& Context, UObject* Object, const int32& LoadFlags, bool& OutSuccess);

#pragma endregion ICsScriptData
};