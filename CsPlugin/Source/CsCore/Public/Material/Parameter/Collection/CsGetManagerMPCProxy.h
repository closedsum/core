// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsGetManagerMPCProxy.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerMPCProxy : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsMaterial::NParameter::NCollection::NProxy::FManager
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsMaterial, NParameter, NCollection, NProxy, FManager)

class CSCORE_API ICsGetManagerMPCProxy
{
	GENERATED_IINTERFACE_BODY()

public:

#define MPCProxyManagerType NCsMaterial::NParameter::NCollection::NProxy::FManager

	virtual MPCProxyManagerType* GetManagerMPCProxy() = 0;

#undef MPCProxyManagerType
};