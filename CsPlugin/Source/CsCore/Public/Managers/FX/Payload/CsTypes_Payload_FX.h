// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/FX/CsTypes_FX.h"

#include "CsTypes_Payload_FX.generated.h"
#pragma once

class UObject;
class UNiagaraSystem;

// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_FX
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UObject* Instigator;

	/** The owner of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UObject* Owner;

	/** The parent of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsFXPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// FXPayloadType (NCsFX::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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

#define PayloadType NCsFX::NPayload::FImpl
	void CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadType* Payload) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};