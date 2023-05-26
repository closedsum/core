// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/FX/CsTypes_FX.h"

#include "CsTypes_Payload_FX.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX|Payload", meta = (Bitmask, BitmaskEnum = "ECsFXPayloadChange"))
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

#define PayloadType NCsFX::NPayload::FImpl
	void CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadType* Payload) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};