// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "NiagaraDataInterfaceArray.h"

#include "CsNiagaraDataInterfaceArrayFloatRW.generated.h"

UCLASS(EditInlineNew, Category = "Array", meta = (DisplayName = "Float RW Array", Experimental), Blueprintable, BlueprintType)
class CSCORE_API UCsNiagaraDataInterfaceArrayFloatRW : public UNiagaraDataInterfaceArray
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<float> FloatData;
};