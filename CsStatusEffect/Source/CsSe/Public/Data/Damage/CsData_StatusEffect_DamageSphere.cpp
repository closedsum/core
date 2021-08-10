// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_StatusEffect_DamageSphere.h"
#include "CsSe.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Data/Shape/CsData_DamageSphereProxy.h"

const FName NCsStatusEffect::NData::NDamage::FSphereProxy::Name = FName("NCsStatusEffect::NData::NDamage::FSphereProxy");

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NDamage
		{
			FSphereProxy::FSphereProxy() :
				Outer(nullptr),
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// NCsStatusEffect::NData::IData
				TriggerCondition(nullptr),
				TriggerFrequencyParams(nullptr),
				TransferFrequencyParams(nullptr),
				Children(nullptr),
				// NCsStatusEffect::NData::NDamage::IDamage
				DamageData(nullptr)
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FSphereProxy>(this);

				typedef NCsData::IData DataType;
				typedef NCsStatusEffect::NData::IData StatusEffectDataType;
				typedef NCsStatusEffect::NData::NDamage::IDamage StatusEffectDamageDataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
				InterfaceMap->Add<StatusEffectDataType>(static_cast<StatusEffectDataType*>(this));
				InterfaceMap->Add<StatusEffectDamageDataType>(static_cast<StatusEffectDamageDataType*>(this));
			}

			FSphereProxy::~FSphereProxy()
			{
				delete InterfaceMap;
			}
		}
	}
}

const FName UCsData_StatusEffect_DamageSphere::Name = FName("UCsData_StatusEffect_DamageSphere");

UCsData_StatusEffect_DamageSphere::UCsData_StatusEffect_DamageSphere(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsData_StatusEffect_DamageSphere::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_StatusEffect_DamageSphere>())
	{
		Init();
		bLoaded = false;
	}
}

void UCsData_StatusEffect_DamageSphere::BeginDestroy()
{
	Super::BeginDestroy();

	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	// ICsStatusEffect_Damage
	if (DamageSphereProxy)
	{
		typedef NCsDamage::NData::NShape::NSphere::FProxy SphereDataProxyType;

		SphereDataProxyType* Proxy = static_cast<SphereDataProxyType*>(DamageSphereProxy);
		delete Proxy;
		DamageSphereProxy = nullptr;
	}
	if (DataProxy)
	{
		delete DataProxy;
		DataProxy = nullptr;
	}
}

#pragma endregion UObject Interface

void UCsData_StatusEffect_DamageSphere::Init()
{
	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRoot<UCsData_StatusEffect_DamageSphere>(this);

		InterfaceMap->Add<ICsData>(Cast<ICsData>(this));
		InterfaceMap->Add<ICsData_StatusEffect>(Cast<ICsData_StatusEffect>(this));
		InterfaceMap->Add<ICsData_StatusEffect_Damage>(Cast<ICsData_StatusEffect_Damage>(this));
	}
	// ICsStatusEffect_Damage
	if (!DamageSphereProxy)
	{
		typedef NCsDamage::NData::NShape::NSphere::FProxy SphereDataProxyType;

		DamageSphereProxy = new SphereDataProxyType();
		DamageSphere.SetData(static_cast<SphereDataProxyType*>(DamageSphereProxy));
	}
	if (!DataProxy)
	{
		typedef NCsStatusEffect::NData::NDamage::FSphereProxy DataProxyType;

		DataProxy = new DataProxyType();

		DataProxyType* Proxy = (DataProxyType*)DataProxy;
		Proxy->SetOuter(this);
		// // NCsStatusEffect::NData::IData
		//Proxy->SetTriggerCondition(this);
		//Proxy->SetTriggerFrequencyParams(this);
		//Proxy->SetTransferFrequencyParams(this);
		//Proxy->SetChildren(this);
		// NCsStatusEffect::NData::NDamage::IDamage
		//Proxy->SetDamageData();
	}
}

// ICsData
#pragma region

bool UCsData_StatusEffect_DamageSphere::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_StatusEffect_DamageSphere::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

#if WITH_EDITOR
	Init();
#endif // #if WITH_EDITOR

	bLoaded = true;
}

void UCsData_StatusEffect_DamageSphere::Unload()
{

}

bool UCsData_StatusEffect_DamageSphere::IsLoaded() const
{
	return bLoaded;
}

#pragma endregion ICsData