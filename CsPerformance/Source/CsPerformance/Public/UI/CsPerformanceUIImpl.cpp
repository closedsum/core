// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "UI/CsPerformanceUIImpl.h"
#include "CsPerformance.h"

// CVar
#include "CsCVars_Performance.h"
// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsPerformanceSettings.h"
// UI
#include "Components/TextBlock.h"
// Render
#include "RenderCore.h"

// Cached
#pragma region

namespace NCsPerformanceUIImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsPerformanceUIImpl, Init);
		}
	}
}

#pragma endregion Cached

UCsPerformanceUIImpl::UCsPerformanceUIImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Root
	MyRoot(nullptr),
	// FPS
	FPS_Text(nullptr),
	FPS_Value_Text(nullptr),
	GameThread_Text(nullptr),
	GameThread_Value_Text(nullptr),
	RenderThread_Text(nullptr),
	RenderThread_Value_Text(nullptr),
	RHIThread_Text(nullptr),
	RHIThread_Value_Text(nullptr),
	SwapBuffer_Text(nullptr),
	SwapBuffer_Value_Text(nullptr),
	bShowFPS(false),
	StatUnit()
{
}

#define USING_NS_CACHED using namespace NCsPerformanceUIImpl::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsPerformanceUIImpl::NCached; \
	const FString& Context = Str::__FunctionName

// UUserWidget Interface
#pragma region

void UCsPerformanceUIImpl::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCsPerformanceUIImpl::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UCsPerformanceSettings* Settings = GetMutableDefault<UCsPerformanceSettings>();

	// Determine all Toggles
	bool bShow = false;
	bool bToggle = false;

	const bool bLast_ShowFPS = bShowFPS;
#if UE_BUILD_SHIPPING
	bShowFPS				 = Settings->bShowFPS;
#else
	bShowFPS				 = CS_CVAR_TOGGLE_IS_ENABLED(ShowPerformanceFPS);
#endif // #if UE_BUILD_SHIPPING
	const bool bToggleFPS	 = bShowFPS != bLast_ShowFPS;
	bToggle					|= bToggleFPS;
	bShow					|= bShowFPS;

	if (bToggle)
	{
		//SetVisibility(bShow ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
	SetVisibility(ESlateVisibility::HitTestInvisible);

	// FPS
	{
		if (bToggleFPS)
		{
			OnToggle_FPS(bShowFPS);
		}

		if (bShowFPS)
		{
			StatUnit.Update(InDeltaTime);
			UpdateFPS();
		}
	}
}

#pragma endregion UUserWidget Interface

// ICsPerformanceUI
#pragma region

void UCsPerformanceUIImpl::Init(UObject* InRoot)
{
	SET_CONTEXT(Init);

	MyRoot = InRoot;

	bool bShow = false;

	// FPS
	FPS_Texts.Add(FPS_Text);
	FPS_Texts.Add(FPS_Value_Text);
	FPS_Texts.Add(GameThread_Text);
	FPS_Texts.Add(GameThread_Value_Text);
	FPS_Texts.Add(RenderThread_Text);
	FPS_Texts.Add(RenderThread_Value_Text);
	FPS_Texts.Add(RHIThread_Text);
	FPS_Texts.Add(RHIThread_Value_Text);
	FPS_Texts.Add(SwapBuffer_Text);
	FPS_Texts.Add(SwapBuffer_Value_Text);

	UCsPerformanceSettings* Settings = GetMutableDefault<UCsPerformanceSettings>();

#if UE_BUILD_SHIPPING
	bShowFPS = Settings->bShowFPS;
#else
	bShowFPS = CS_CVAR_TOGGLE_IS_ENABLED(ShowPerformanceFPS);
#endif // #if UE_BUILD_SHIPPING
	bShow	|= bShowFPS;

	for (UTextBlock* Text : FPS_Texts)
	{
		//Text->SetVisibility(bShowFPS ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
		Text->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	StatUnit.Outer = this;
	StatUnit.Init();

	//SetVisibility(bShow ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

#pragma endregion ICsPerformanceUI

// FPS
#pragma region

void UCsPerformanceUIImpl::FStatUnit::Init()
{
	Values_Fps.Reset(MaxCount);
	Values_GameThread_Ms.Reset(MaxCount);
	Values_RenderThread_Ms.Reset(MaxCount);
	Values_RHIThread_Ms.Reset(MaxCount);
	Values_SwapBuffer_Ms.Reset(MaxCount);
}

void UCsPerformanceUIImpl::FStatUnit::Update(const float& DeltaTime)
{
	// Fps
	const float LatestFps = 1.0f / DeltaTime;

	if (Values_Fps.Num() < MaxCount)
	{
		Values_Fps.Add(LatestFps);

		const int32 Count = Values_Fps.Num();

		Average_Fps = 0.0f;

		for (int32 I = 0; I < Count; ++I)
		{
			Average_Fps += Values_Fps[I];
		}

		Average_Fps /= Count;
	}
	else
	{
		const int32 Count = Values_Fps.Num();

		Average_Fps = 0.0f;

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (I > 0)
			{
				Values_Fps[I] = Values_Fps[I - 1];
			}
			else
			{
				Values_Fps[I] = LatestFps;
			}
			Average_Fps += Values_Fps[I];
		}

		Average_Fps /= Count;
	}
	// Game
	const float RawGameThreadTime = FPlatformTime::ToMilliseconds(GGameThreadTime);

	if (Values_GameThread_Ms.Num() < MaxCount)
	{
		Values_GameThread_Ms.Add(RawGameThreadTime);

		const int32 Count = Values_GameThread_Ms.Num();

		Average_GameThread_Ms = 0.0f;

		for (int32 I = 0; I < Count; ++I)
		{
			Average_GameThread_Ms += Values_GameThread_Ms[I];
		}

		Average_GameThread_Ms /= Count;
	}
	else
	{
		const int32 Count = Values_GameThread_Ms.Num();

		Average_GameThread_Ms = 0.0f;

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (I > 0)
			{
				Values_GameThread_Ms[I] = Values_GameThread_Ms[I - 1];
			}
			else
			{
				Values_GameThread_Ms[I] = RawGameThreadTime;
			}
			Average_GameThread_Ms += Values_GameThread_Ms[I];
		}

		Average_GameThread_Ms /= Count;
	}
	// Render
	const float RawRenderThreadTime = FPlatformTime::ToMilliseconds(GRenderThreadTime);

	if (Values_RenderThread_Ms.Num() < MaxCount)
	{
		Values_RenderThread_Ms.Add(RawRenderThreadTime);

		const int32 Count = Values_RenderThread_Ms.Num();

		Average_RenderThread_Ms = 0.0f;

		for (int32 I = 0; I < Count; ++I)
		{
			Average_RenderThread_Ms += Values_RenderThread_Ms[I];
		}

		Average_RenderThread_Ms /= Count;
	}
	else
	{
		const int32 Count = Values_RenderThread_Ms.Num();

		Average_RenderThread_Ms = 0.0f;

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (I > 0)
			{
				Values_RenderThread_Ms[I] = Values_RenderThread_Ms[I - 1];
			}
			else
			{
				Values_RenderThread_Ms[I] = RawRenderThreadTime;
			}
			Average_RenderThread_Ms += Values_RenderThread_Ms[I];
		}

		Average_RenderThread_Ms /= Count;
	}
	// RHI
	const float RawRHIThreadTime = FPlatformTime::ToMilliseconds(GRHIThreadTime);

	if (Values_RHIThread_Ms.Num() < MaxCount)
	{
		Values_RHIThread_Ms.Add(RawRHIThreadTime);

		const int32 Count = Values_RHIThread_Ms.Num();

		Average_RHIThread_Ms = 0.0f;

		for (int32 I = 0; I < Count; ++I)
		{
			Average_RHIThread_Ms += Values_RHIThread_Ms[I];
		}

		Average_RHIThread_Ms /= Count;
	}
	else
	{
		const int32 Count = Values_RHIThread_Ms.Num();

		Average_RHIThread_Ms = 0.0f;

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (I > 0)
			{
				Values_RHIThread_Ms[I] = Values_RHIThread_Ms[I - 1];
			}
			else
			{
				Values_RHIThread_Ms[I] = RawRHIThreadTime;
			}
			Average_RHIThread_Ms += Values_RHIThread_Ms[I];
		}

		Average_RHIThread_Ms /= Count;
	}
	// Swap Buffer
	const float RawSwapBufferTime = FPlatformTime::ToMilliseconds(GSwapBufferTime);

	if (Values_SwapBuffer_Ms.Num() < MaxCount)
	{
		Values_SwapBuffer_Ms.Add(RawSwapBufferTime);

		const int32 Count = Values_SwapBuffer_Ms.Num();

		Average_SwapBuffer_Ms = 0.0f;

		for (int32 I = 0; I < Count; ++I)
		{
			Average_SwapBuffer_Ms += Values_SwapBuffer_Ms[I];
		}

		Average_SwapBuffer_Ms /= Count;
	}
	else
	{
		const int32 Count = Values_SwapBuffer_Ms.Num();

		Average_SwapBuffer_Ms = 0.0f;

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (I > 0)
			{
				Values_SwapBuffer_Ms[I] = Values_SwapBuffer_Ms[I - 1];
			}
			else
			{
				Values_SwapBuffer_Ms[I] = RawSwapBufferTime;
			}
			Average_SwapBuffer_Ms += Values_SwapBuffer_Ms[I];
		}

		Average_SwapBuffer_Ms /= Count;
	}
}

void UCsPerformanceUIImpl::UpdateFPS()
{
	// FPS
	static const float FPS_MIN_GOOD = 50.0f;
	static const float FPS_MIN_OKAY = 30.0f;

	FPS_Value_Text->SetText(FText::FromString(FString::Printf(TEXT("%f"), StatUnit.GetAverageFps())));
	// Good
	if (StatUnit.GetAverageFps() > FPS_MIN_GOOD)
	{
		FPS_Text->SetColorAndOpacity(FLinearColor::Green);
		FPS_Value_Text->SetColorAndOpacity(FLinearColor::Green);
	}
	// Okay
	else
	if (StatUnit.GetAverageFps() > FPS_MIN_OKAY)
	{
		FPS_Text->SetColorAndOpacity(FLinearColor::Yellow);
		FPS_Value_Text->SetColorAndOpacity(FLinearColor::Yellow);
	}
	// Bad
	else
	{
		FPS_Text->SetColorAndOpacity(FLinearColor::Red);
		FPS_Value_Text->SetColorAndOpacity(FLinearColor::Red);
	}

	static const float THREAD_MAX_GOOD = 16.67f;
	static const float THREAD_MAX_OKAY = 33.33f;

	// Game
	GameThread_Value_Text->SetText(FText::FromString(FString::Printf(TEXT("%f"), StatUnit.GetAverageGameThreadMs())));
		// Good
	if (StatUnit.GetAverageGameThreadMs() < THREAD_MAX_GOOD)
	{
		GameThread_Text->SetColorAndOpacity(FLinearColor::Green);
		GameThread_Value_Text->SetColorAndOpacity(FLinearColor::Green);
	}
		// Okay
	else
	if (StatUnit.GetAverageGameThreadMs() < THREAD_MAX_OKAY)
	{
		GameThread_Text->SetColorAndOpacity(FLinearColor::Yellow);
		GameThread_Value_Text->SetColorAndOpacity(FLinearColor::Yellow);
	}
		// Bad
	else
	{
		GameThread_Text->SetColorAndOpacity(FLinearColor::Red);
		GameThread_Value_Text->SetColorAndOpacity(FLinearColor::Red);
	}

	// Render
	RenderThread_Value_Text->SetText(FText::FromString(FString::Printf(TEXT("%f"), StatUnit.GetAverageRenderThreadMs())));
		// Good
	if (StatUnit.GetAverageRenderThreadMs() < THREAD_MAX_GOOD)
	{
		RenderThread_Text->SetColorAndOpacity(FLinearColor::Green);
		RenderThread_Value_Text->SetColorAndOpacity(FLinearColor::Green);
	}
		// Okay
	else
	if (StatUnit.GetAverageRenderThreadMs() < THREAD_MAX_OKAY)
	{
		RenderThread_Text->SetColorAndOpacity(FLinearColor::Yellow);
		RenderThread_Value_Text->SetColorAndOpacity(FLinearColor::Yellow);
	}
		// Bad
	else
	{
		RenderThread_Text->SetColorAndOpacity(FLinearColor::Red);
		RenderThread_Value_Text->SetColorAndOpacity(FLinearColor::Red);
	}

	// RHI
	RHIThread_Value_Text->SetText(FText::FromString(FString::Printf(TEXT("%f"), StatUnit.GetAverageRHIThreadMs())));
		// Good
	if (StatUnit.GetAverageRHIThreadMs() < THREAD_MAX_GOOD)
	{
		RHIThread_Text->SetColorAndOpacity(FLinearColor::Green);
		RHIThread_Value_Text->SetColorAndOpacity(FLinearColor::Green);
	}
		// Okay
	else
	if (StatUnit.GetAverageRHIThreadMs() < THREAD_MAX_OKAY)
	{
		RHIThread_Text->SetColorAndOpacity(FLinearColor::Yellow);
		RHIThread_Value_Text->SetColorAndOpacity(FLinearColor::Yellow);
	}
		// Bad
	else
	{
		RHIThread_Text->SetColorAndOpacity(FLinearColor::Red);
		RHIThread_Value_Text->SetColorAndOpacity(FLinearColor::Red);
	}

	// Swap Buffer
	SwapBuffer_Value_Text->SetText(FText::FromString(FString::Printf(TEXT("%f"), StatUnit.GetAverageSwapBufferMs())));
		// Good                                       
	if (StatUnit.GetAverageSwapBufferMs() < THREAD_MAX_GOOD)
	{
		SwapBuffer_Text->SetColorAndOpacity(FLinearColor::Green);
		SwapBuffer_Value_Text->SetColorAndOpacity(FLinearColor::Green);
	}
		// Okay
	else
	if (StatUnit.GetAverageSwapBufferMs() < THREAD_MAX_OKAY)
	{
		SwapBuffer_Text->SetColorAndOpacity(FLinearColor::Yellow);
		SwapBuffer_Value_Text->SetColorAndOpacity(FLinearColor::Yellow);
	}
		// Bad
	else
	{
		SwapBuffer_Text->SetColorAndOpacity(FLinearColor::Red);
		SwapBuffer_Value_Text->SetColorAndOpacity(FLinearColor::Red);
	}
}

void UCsPerformanceUIImpl::OnToggle_FPS(bool IsEnabled)
{
	bShowFPS = IsEnabled;

	for (UTextBlock* Text : FPS_Texts)
	{
		Text->SetVisibility(IsEnabled ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}

#pragma endregion FPS

#undef USING_NS_CACHED
#undef SET_CONTEXT