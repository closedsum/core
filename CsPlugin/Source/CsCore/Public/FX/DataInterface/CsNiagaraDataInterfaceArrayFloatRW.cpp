// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "FX/DataInterface/CsNiagaraDataInterfaceArrayFloatRW.h"

#include "NiagaraDataInterfaceArrayImpl.h"
//#include "NiagaraRenderer.h"

struct CSCORE_API FCsNDIArrayImplHelper_float : public FNDIArrayImplHelperBase<float>
{
	static constexpr TCHAR const* HLSLValueTypeName = TEXT("float");
	static constexpr TCHAR const* HLSLBufferTypeName = TEXT("float");
	static constexpr EPixelFormat PixelFormat = PF_R32_FLOAT;
	static const FNiagaraTypeDefinition& GetTypeDefinition() { return FNiagaraTypeDefinition::GetFloatDef(); }
	static const float GetDefaultValue() { return 0.0f; }
};

UCsNiagaraDataInterfaceArrayFloatRW::UCsNiagaraDataInterfaceArrayFloatRW(FObjectInitializer const& ObjectInitializer)
	: UNiagaraDataInterfaceArray(ObjectInitializer)
{
	//Proxy.Reset(new FNiagaraDataInterfaceProxyArrayImpl());
	//Impl.Reset(new FNiagaraDataInterfaceArrayImpl<float, UCsNiagaraDataInterfaceArrayFloatRW>(this, FloatData));
}