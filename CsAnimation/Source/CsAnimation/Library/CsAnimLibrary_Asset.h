// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "CsAnimLibrary_Asset.generated.h"

class ULevelSequence;

UCLASS()
class CSANIMATION_API UCsAnimLibrary_Asset : public UObject
{
	GENERATED_UCLASS_BODY()

// Asset Registry
#pragma region
public:

#if WITH_EDITOR

	static ULevelSequence* CreateLevelSequence(const FString& Name, const FString& PackagePath);

#endif // #if WITH_EDITOR

#pragma endregion Asset Registry
};