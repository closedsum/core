#pragma once
#include "Data/CsData.h"
#include "CsTypes.h"
#include "CsData_Payload.generated.h"

USTRUCT()
struct FCsPayloadFindEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Find;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT()
struct FCsPayloadAddEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Add;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	TEnumAsByte<ECsLoadAssetsType::Type> LoadAssetsType;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	TEnumAsByte<ECsLoadFlags_Editor::Type> LoadFlags;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT()
struct FCsPayloadRemoveEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Remove;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	TEnumAsByte<ECsLoadAssetsType::Type> LoadAssetsType;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT()
struct FCsPayloadValidate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Validate;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Payload : public ACsData
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "01 Payload")
	FCsTArrayPayload Payloads[ECsLoadAssetsType::ECsLoadAssetsType_MAX];

// 98 Editor
#pragma region

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "98 Editor")
	FCsPayloadFindEntry FindEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "98 Editor")
	FCsPayloadAddEntry AddEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "98 Editor")
	FCsPayloadRemoveEntry RemoveEntry;

#if WITH_EDITOR

	bool PerformFindEntry(const FName &InShortCode, TArray<FCsPayload*> &OutPayloads, TArray<TCsLoadAssetsType> &OutLoadAssetsTypes, TArray<int32> &OutIndices);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion 98 Editor
};