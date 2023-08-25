// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Debug/CsTypes_Debug.h"

#include "CsSettings_Container.generated.h"

// FCsSettings_Container_UniformGrid_Debug
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Container_UniformGrid_Debug
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Container|Settings")
	FCsDebugDrawBox Cell;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Container|Settings")
	FCsDebugDrawSphere Element;

	FCsSettings_Container_UniformGrid_Debug() :
		Cell(),
		Element()
	{
	}

	static const FCsSettings_Container_UniformGrid_Debug& Get();
};

#pragma endregion FCsSettings_Container_UniformGrid_Debug

// FCsSettings_Container_UniformGrid
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Container_UniformGrid
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Container|Settings")
	FCsSettings_Container_UniformGrid_Debug Debug;

	FCsSettings_Container_UniformGrid() :
		Debug()
	{
	}

	static const FCsSettings_Container_UniformGrid& Get();
};

#pragma endregion FCsSettings_Container_UniformGrid

// FCsSettings_Container
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Container
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Container|Settings")
	FCsSettings_Container_UniformGrid UniformGrid;

	FCsSettings_Container() :
		UniformGrid()
	{
	}

	static const FCsSettings_Container& Get();
};

#pragma endregion FCsSettings_Container