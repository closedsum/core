// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/FX/CsTypes_FX.h"

#include "CsTypes_Payload_FX.generated.h"

class UObject;
class UNiagaraSystem;

// NCsFX::NPayload::NImpl::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NPayload, NImpl, FImpl)

USTRUCT(BlueprintType)
struct CSFX_API FCsPayload_FX
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX|Payload")
	UObject* Instigator;

	/** The owner of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX|Payload")
	UObject* Owner;

	/** The parent of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX|Payload")
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX|Payload")
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX|Payload", meta = (Bitmask, BitmaskEnum = "/Script.CsFX.ECsFXPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// FXPayloadType (NCsFX::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX|Payload")
	FCsFX FX;

	FCsPayload_FX() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		FX()
	{
	}

	using PayloadImplType = NCsFX::NPayload::NImpl::FImpl;

	void CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadImplType* Payload) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsFX::FLog::Warning) const;
};