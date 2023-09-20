// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsScriptableActor.generated.h"

USTRUCT(BlueprintType)
struct CSJS_API FCsScriptableActorInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsJs|Actor|Scriptable")
	bool bEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsJs|Actor|Scriptable")
	FString ClassPath;

	FCsScriptableActorInfo() :
		bEnable(false),
		ClassPath()
	{
	}
};

UINTERFACE(Blueprintable)
class CSJS_API UCsScriptableActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSJS_API ICsScriptableActor
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const FCsScriptableActorInfo& GetScriptableActorInfo() const = 0;
};