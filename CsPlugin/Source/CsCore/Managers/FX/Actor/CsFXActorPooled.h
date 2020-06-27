// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsFXActorPooled.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsFXActorPooled : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ANiagaraActor;

/**
* Interface for a pooled UObject "container" holding a reference to an FX Actor.
* Pipe pool related interface functions through the container to avoid having to make
* derived classes for FX Actor (at this point it seems unnecessary).
*
* FUTURE: Potentially do NOT have a UObject as the container and use a normal class / struct
*		  that is more light weight.
*/
class CSCORE_API ICsFXActorPooled
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	* 
	*
	* return
	*/
	virtual ANiagaraActor* GetFX() const = 0;
};

// FCsFXActorPooled
#pragma region

class ICsFXActorPooled;

struct CSCORE_API FCsFXActorPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsFXActorPooled Empty;

protected:

	/** Reference to interface of type: ICsFXActorPooled. */
	ICsFXActorPooled* FXActor;

	/** Does the FX Actor implement a script interface of type: ICsFXActorPooled. */
	bool bScriptFXActor;

// Script
#pragma region
public:

	// ICsFXActorPooled
#pragma region
public:

	/**
	* Delegate type for getting the pooled FX Actor.
	*  The object implements a script interface of type: ICsFXActorPooled.
	*
	* @param Object		An object of type: ICsFXActorPooled.
	* return FX			FX Actor.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(ANiagaraActor* /*FX*/, FScript_GetFX, UObject* /*Object*/);

	/** Delegate for getting the pooled FX Actor. 
		 The object implements a script interface of type: ICsFXActorPooled. */
	FScript_GetFX Script_GetFX_Impl;

#pragma endregion ICsFXActorPooled

#pragma endregion Script

public:

	FCsFXActorPooled();

	virtual ~FCsFXActorPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsFXActorPooled
#pragma region
public:

	ANiagaraActor* GetFX() const;

#pragma endregion ICsFXActorPooled

	FORCEINLINE void SetScriptFXActor()
	{
		bScriptFXActor = true;
	}

	FORCEINLINE const bool& IsScriptFXActor() const
	{
		return bScriptFXActor;
	}

	FORCEINLINE ICsFXActorPooled* GetFXActorPooled() const
	{
		return FXActor;
	}

	FORCEINLINE void SetFXActorPooled(ICsFXActorPooled* InFXActor)
	{
		FXActor = InFXActor;
	}

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);
};

#pragma endregion FCsFXActorPooled