// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

	/**
	* Stop the sound with optional Fade Out Time
	* 
	* @param FadeOutTime	(optional) Time to Fade Out Sound.
	*/
	virtual void Stop(const float& FadeOutTime = 0.0f) = 0;

	/**
	* Fade In the sound from 0 Volume to the Default Volume over a Duration of 
	* time in seconds.
	* 
	* @param Duration	Time in seconds.
	*/
	virtual void FadeIn(const float& Duration) = 0;

	/**
	* Fade Out the sound from the Default Volume to 0 Volume over a Duration of
	* time in seconds.
	*
	* @param Duration	Time in seconds.
	*/
	virtual void FadeOut(const float& Duration) = 0;
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

	/**
	* Delegate type for Stopping the Sound.
	*  The Object implements a script interface of type: ICsSoundPooled.
	*
	* @param Object			An object of type: ICsSoundPooled.
	* @param FadeOutTime	
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Stop, UObject* /*Object*/, const float& /*FadeOutTime*/);

	/** Delegate for Stopping the Sound.
		 The Object implements a script interface of type: ICsSoundPooled. */
	FScript_Stop Script_Stop_Impl;

	/**
	* Delegate type for Fading In the Sound.
	*  The Object implements a script interface of type: ICsSoundPooled.
	*
	* @param Object			An object of type: ICsSoundPooled.
	* @param Duration
	*/
	DECLARE_DELEGATE_TwoParams(FScript_FadeIn, UObject* /*Object*/, const float& /*Duration*/);

	/** Delegate for Fading In the Sound.
		 The Object implements a script interface of type: ICsSoundPooled. */
	FScript_FadeIn Script_FadeIn_Impl;

	/**
	* Delegate type for Fading Out the Sound.
	*  The Object implements a script interface of type: ICsSoundPooled.
	*
	* @param Object			An object of type: ICsSoundPooled.
	* @param Duration
	*/
	DECLARE_DELEGATE_TwoParams(FScript_FadeOut, UObject* /*Object*/, const float& /*Duration*/);

	/** Delegate for Fading Out the Sound.
		 The Object implements a script interface of type: ICsSoundPooled. */
	FScript_FadeOut Script_FadeOut_Impl;

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

	FORCEINLINE UAudioComponent* GetAudioComponent() const
	{
		if (bScriptSound)
			return Script_GetAudioComponent_Impl.Execute(Object);
		return Sound->GetAudioComponent();
	}

	FORCEINLINE void Stop(const float& FadeOutTime = 0.0f)
	{
		if (bScriptSound)
			return Script_Stop_Impl.Execute(Object, FadeOutTime);
		Sound->Stop(FadeOutTime);
	}

	FORCEINLINE void FadeIn(const float& Duration)
	{
		if (bScriptSound)
			return Script_FadeIn_Impl.Execute(Object, Duration);
		Sound->FadeIn(Duration);
	}

	FORCEINLINE void FadeOut(const float& Duration)
	{
		if (bScriptSound)
			return Script_FadeOut_Impl.Execute(Object, Duration);
		Sound->FadeOut(Duration);
	}

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