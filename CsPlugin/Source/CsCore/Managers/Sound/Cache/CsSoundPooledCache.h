// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Sound/CsTypes_Sound.h"

#pragma once

class UAudioComponent;

/**
* Cache associated with a Sound Pooled Object.
*  The Manager for Sound primarily interacts with the Cache object in terms
*  of allocation and deallocation.
*/
struct CSCORE_API ICsSoundPooledCache : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsSoundPooledCache() {}

	/**
	*
	*
	* return
	*/
	virtual UAudioComponent* GetAudioComponent() const = 0;

	/**
	*
	*
	* return
	*/
	virtual USoundAttenuation* GetSoundAttenuation() const = 0;
};