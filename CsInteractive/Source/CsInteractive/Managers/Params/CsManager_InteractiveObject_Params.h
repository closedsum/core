// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "CsTypes_InteractiveObject.h"
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "CsManager_InteractiveObject_Params.generated.h"

// Structs
#pragma region

/*
struct CSINTERACTIVE_API FCsResource_InteractiveObjectHoldParams : public TCsResourceContainer<FCsInteractiveObjectHoldParams>
{
};

struct CSINTERACTIVE_API FCsManager_InteractiveObjectHoldParams : public TCsManager_ResourceValueType_Fixed<FCsInteractiveObjectHoldParams, FCsResource_InteractiveObjectHoldParams, 4>
{
};
*/

#pragma endregion Structs

class ICsGetManagerInteractiveObjectParams;

UCLASS()
class CSINTERACTIVE_API UCsManager_InteractiveObject_Params : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_InteractiveObject_Params* Get(UObject* InRoot = nullptr);
	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerInteractiveObjectParams* Get_GetManagerInteractiveObjectParams(UObject* InRoot);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_InteractiveObject_Params* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
private:

	UObject* MyRoot;

public:

	FORCEINLINE void SetMyRoot(UObject* InRoot)
	{
		MyRoot = InRoot;
	}

	FORCEINLINE const UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton
};