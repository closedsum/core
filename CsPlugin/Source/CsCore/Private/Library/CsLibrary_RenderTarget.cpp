// Copyright 2017-2024 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_RenderTarget.h"

// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Render
#include "Kismet/KismetRenderingLibrary.h"
// Material
#include "Materials/MaterialInterface.h"
// Texture
#include "Engine/TextureRenderTarget2D.h"
// World
#include "Engine/World.h"

namespace NCsRenderTarget
{
	namespace N2D
	{
		UTextureRenderTarget2D* FLibrary::CreateChecked(const FString& Context, UObject* WorldContext, const int32& Width /*=256*/, const int32& Height /*=256*/, const ETextureRenderTargetFormat& Format /*=RTF_RGBA16f*/, const FLinearColor& ClearColor /*=FLinearColor::Black*/, const bool& bAutoGenerateMipMaps /*=false*/)
		{
			CS_IS_PENDING_KILL_CHECKED(WorldContext)
			CS_IS_INT_GREATER_THAN_CHECKED(Width, 0)
			CS_IS_INT_GREATER_THAN_CHECKED(Height, 0)

			UTextureRenderTarget2D* NewRenderTarget2D = NewObject<UTextureRenderTarget2D>(WorldContext);

			checkf(NewRenderTarget2D, TEXT("%s: Failed to create TextureRenderTarget2D from WorldContext: %s."), *Context, *(WorldContext)->GetName());

			NewRenderTarget2D->RenderTargetFormat = Format;
			NewRenderTarget2D->ClearColor = ClearColor;
			NewRenderTarget2D->bAutoGenerateMips = bAutoGenerateMipMaps;
			NewRenderTarget2D->InitAutoFormat(Width, Height);
			NewRenderTarget2D->UpdateResourceImmediate(true);

			return NewRenderTarget2D;
		}

		void FLibrary::DrawMaterialToRenderTargetChecked(const FString& Context, UObject* WorldContext, UTextureRenderTarget2D* TextureRenderTarget, UMaterialInterface* Material)
		{
			// TODO: Maybe. Assert?
			if (!FApp::CanEverRender())
			{
				// Returning early to avoid warnings about missing resources that are expected when CanEverRender is false.
				return;
			}
			
			CS_IS_PENDING_KILL_CHECKED(Material)
			CS_IS_PENDING_KILL_CHECKED(TextureRenderTarget)
			CS_IS_PTR_NULL_CHECKED(TextureRenderTarget->GetResource())

			UKismetRenderingLibrary::DrawMaterialToRenderTarget(WorldContext, TextureRenderTarget, Material);
		}

		void FLibrary::ClearChecked(const FString& Context, UObject* WorldContext, UTextureRenderTarget2D* TextureRenderTarget, const FLinearColor& ClearColor /*=FLinearColor(0, 0, 0, 1)*/)
		{
			CS_IS_PENDING_KILL_CHECKED(WorldContext)
			CS_IS_PENDING_KILL_CHECKED(TextureRenderTarget)
			CS_IS_PTR_NULL_CHECKED(TextureRenderTarget->GetResource())

			UKismetRenderingLibrary::ClearRenderTarget2D(WorldContext, TextureRenderTarget, ClearColor);
		}
	}
}