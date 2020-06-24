// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsPooledObjectPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

FCsPooledObjectPayload::FCsPooledObjectPayload()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsPooledObjectPayload>(static_cast<ICsPooledObjectPayload*>(this));

	Reset();
}

FCsPooledObjectPayload::~FCsPooledObjectPayload()
{
	delete InterfaceMap;
}

// ICsPooledObjectPayload
#pragma region

void FCsPooledObjectPayload::Reset()
{
	bAllocated = false;

	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
}

#pragma endregion ICsPooledObjectPayload