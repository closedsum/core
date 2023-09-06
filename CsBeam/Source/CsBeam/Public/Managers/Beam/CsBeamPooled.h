// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Managers/Pool/CsPooledObject.h"

class ICsBeam;

struct CSBEAM_API FCsBeamPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsBeamPooled Empty;

protected:

	/** Reference to interface of type: ICsProjecitle. */
	ICsBeam* Beam;

	/** Does the Beam implement a script interface of type: ICsBeam. */
	bool bScriptBeam;

// Script
#pragma region
public:

	/**
	* Delegate type for getting the Owner of a Beam.
	*  The Beam implements a script interface of type: ICsBeam.
	*
	* @param Object		A Beam of type: ICsBeam.
	* return Owner		Owner of the Beam.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetOwner, UObject* /*Object*/);

	/** Delegate for getting the Owner of a Beam. 
		 The Beam implements a script interface of type: ICsBeam. */
	FScript_GetOwner Script_GetOwner_Impl;

	/**
	* Delegate type for getting the Instigator of a Beam.
	*  The Beam implements a script interface of type: ICsBeam.
	*
	* @param Object			A Beam of type: ICsBeam.
	* return Instigator		Instigator of the Beam.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Instigator*/, FScript_GetInstigator, UObject* /*Object*/);

	/** Delegate for getting the Instigator of a Beam. 
		 The Beam implements a script interface of type: ICsBeam. */
	FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion Script

public:

	FCsBeamPooled();

	virtual ~FCsBeamPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsBeam
#pragma region
public:

	UObject* GetOwner() const;

	UObject* GetInstigator() const;

#pragma endregion ICsBeam

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);

	FORCEINLINE void SetScriptBeam()
	{
		bScriptBeam = true;
	}

	FORCEINLINE const bool& IsScriptBeam() const 
	{
		return bScriptBeam;
	}

	FORCEINLINE ICsBeam* GetBeam() const
	{
		return Beam;
	}

	FORCEINLINE void SetBeam(ICsBeam* InBeam)
	{
		Beam = InBeam;
	}
};