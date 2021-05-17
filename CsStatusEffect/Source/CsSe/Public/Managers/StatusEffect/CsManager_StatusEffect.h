// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// StatusEffect
#include "Event/CsStatusEffectEventInfo.h"
#include "CsReceiveStatusEffect.h"


#include "CsManager_StatusEffect.generated.h"

// Structs
#pragma region

	// NCsStatuseffect::NEvent::NInfo::FImpl

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NInfo
		{
			/**
			* Container for holding a reference to an object of type: NCsDamage::NEvent::NInfo::FImpl.
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSSE_API FResource : public TCsResourceContainer<FImpl>
			{
			};

			/**
			* A manager handling allocating and deallocating objects of type: NCsDamage::NEvent::NInfo::FImpl and
			* are wrapped in the container: NCsDamage::NEvent::FResource.
			*/
			struct CSSE_API FManager : public TCsManager_ResourceValueType_Fixed<FImpl, FResource, 0>
			{
			};
		}
	}
}

#pragma endregion Structs

// NCsStatusEffect::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NEvent, IEvent)
// NCsStatusEffect::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NEvent, FResource)

UCLASS()
class CSSE_API UCsManager_StatusEffect : public UObject
{
	GENERATED_UCLASS_BODY()

#define EventType NCsStatusEffect::NEvent::IEvent
#define EventResourceType NCsStatusEffect::NEvent::FResource

#define EventInfoManagerType NCsStatusEffect::NEvent::NInfo::FManager

public:

	void Init(UObject* InRoot);

	void Shutdown(UObject* InRoot = nullptr);

	// Root
#pragma region
protected:

	FCsReceiveStatusEffect MyRoot;

	void SetMyRoot(UObject* InRoot);

public:
	 
	FORCEINLINE const FCsReceiveStatusEffect& GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

public:

	void Update(const FCsDeltaTime& DeltaTime);

private:

	EventInfoManagerType Manager_Event;

public:

	void ApplyStatusEffect(EventResourceType* Event);

	void ApplyStatusEffect(EventType* Event);

#undef EventType
#undef EventResourceType

#undef EventInfoManagerType
};