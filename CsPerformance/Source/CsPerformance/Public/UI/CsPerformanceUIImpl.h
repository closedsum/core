// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Blueprint/UserWidget.h"
// Interface
#include "UI/CsPerformanceUI.h"

#include "CsPerformanceUIImpl.generated.h"

class UTextBlock;

UCLASS(Blueprintable)
class CSPERFORMANCE_API UCsPerformanceUIImpl : public UUserWidget,
											   public ICsPerformanceUI
{
	GENERATED_UCLASS_BODY()

public:

// UUserWidget Interface
#pragma region
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma endregion UUserWidget Interface

// ICsPerformanceUI
#pragma region
public:

	void Init(UObject* InRoot);

#pragma endregion ICsPerformanceUI

// Root
#pragma region
private:

	UObject* MyRoot;

public:

	FORCEINLINE void SetMyRoot(UObject* InRoot) { MyRoot = InRoot; }
	FORCEINLINE UObject* GetMyRoot() const { return MyRoot; }

#pragma endregion Root

// FPS
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FPS_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FPS_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameThread_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameThread_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RenderThread_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RenderThread_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RHIThread_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RHIThread_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SwapBuffer_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SwapBuffer_Value_Text;

private:

	TArray<UTextBlock*> FPS_Texts;

	bool bShowFPS;

	struct FStatUnit
	{
		friend class UCsPerformanceUIImpl;

	private:

		UCsPerformanceUIImpl* Outer;

	public:

		int32 MaxCount;

		TArray<float> Values_Fps;

		float Average_Fps;

		TArray<float> Values_GameThread_Ms;

		float Average_GameThread_Ms;

		TArray<float> Values_RenderThread_Ms;

		float Average_RenderThread_Ms;

		TArray<float> Values_RHIThread_Ms;

		float Average_RHIThread_Ms;

		TArray<float> Values_SwapBuffer_Ms;

		float Average_SwapBuffer_Ms;

		FStatUnit() :
			Outer(nullptr),
			MaxCount(100),
			Values_Fps(),
			Average_Fps(0.0f),
			Values_GameThread_Ms(),
			Average_GameThread_Ms(0.0f),
			Values_RenderThread_Ms(),
			Average_RenderThread_Ms(0.0f),
			Values_RHIThread_Ms(),
			Average_RHIThread_Ms(0.0f),
			Values_SwapBuffer_Ms(),
			Average_SwapBuffer_Ms(0.0f)
		{
		}

		FORCEINLINE const float& GetAverageFps() const { return Average_Fps; }
		FORCEINLINE const float& GetAverageGameThreadMs() const { return Average_GameThread_Ms; }
		FORCEINLINE const float& GetAverageRenderThreadMs() const { return Average_RenderThread_Ms; }
		FORCEINLINE const float& GetAverageRHIThreadMs() const { return Average_RHIThread_Ms; }
		FORCEINLINE const float& GetAverageSwapBufferMs() const { return Average_SwapBuffer_Ms; }

		void Init();
		
		void Update(const float& DeltaTime);
	};

	FStatUnit StatUnit;

	void UpdateFPS();

	void OnToggle_FPS(bool IsEnabled);

#pragma endregion FPS
};