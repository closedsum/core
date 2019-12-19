// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#ifndef __ICS_MANAGER_MEMORY_RESOURCE_H__
#define __ICS_MANAGER_MEMORY_RESOURCE_H__

class CSCORE_API ICsManager_MemoryResource
{
public:

	virtual ~ICsManager_MemoryResource(){}

	virtual void SetName(const FString& InName) = 0;

	virtual void Clear()= 0;

	virtual void Shutdown() = 0;

	// Pool
#pragma region
public:

	virtual void CreatePool(const int32& InSize) = 0;

	virtual const int32& GetPoolSize() const = 0;

	virtual bool IsExhausted() const = 0;

#pragma endregion Pool

	// Deallocate
#pragma region

	virtual bool DellocateHead() = 0;

	virtual void DeallocateAll() = 0;

#pragma endregion Deallocate
};

#endif // #ifndef __ICS_MANAGER_MEMORY_RESOURCE_H__