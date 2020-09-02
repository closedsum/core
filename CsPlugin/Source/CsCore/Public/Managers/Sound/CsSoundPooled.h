// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsSoundPooled.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsSoundPooled : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UAudioComponent;
class USoundAttenuation;

/**
* Interface for a Sound object that can be pooled.
*/
class CSCORE_API ICsSoundPooled
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
	/**
	* 
	*
	* return
	*/
	virtual UAudioComponent* GetAudioComponent() const = 0;
};

// FCsSoundPooled
#pragma region

class ICsSoundPooled;

struct CSCORE_API FCsSoundPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsSoundPooled Empty;

protected:

	/** Reference to interface of type: ICsSoundPooled. */
	ICsSoundPooled* Sound;

	/** Does the Sound implement a script interface of type: ICsSoundPooled. */
	bool bScriptSound;

// Script
#pragma region
public:

	// ICsSoundPooled
#pragma region
public:

	/**
	* Delegate type for getting the pooled AudioComponent.
	*  The Object implements a script interface of type: ICsSoundPooled.
	*
	* @param Object			An object of type: ICsSoundPooled.
	* return AudioComponent	Component of type UAudioComponent.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UAudioComponent* /*AudioComponent*/, FScript_GetAudioComponent, UObject* /*Object*/);

	/** Delegate for getting the pooled AudioComponent. 
		 The Object implements a script interface of type: ICsSoundPooled. */
	FScript_GetAudioComponent Script_GetAudioComponent_Impl;

#pragma endregion ICsSoundPooled

#pragma endregion Script

public:

	FCsSoundPooled();

	virtual ~FCsSoundPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsSoundPooled
#pragma region
public:

	UAudioComponent* GetAudioComponent() const;

#pragma endregion ICsSoundPooled

	FORCEINLINE void SetScriptSound()
	{
		bScriptSound = true;
	}

	FORCEINLINE const bool& IsScriptSound() const
	{
		return bScriptSound;
	}

	FORCEINLINE ICsSoundPooled* GetSoundPooled() const
	{
		return Sound;
	}

	FORCEINLINE void SetSoundPooled(ICsSoundPooled* InSound)
	{
		Sound = InSound;
	}

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);
};

#pragma endregion FCsFXActorPooled