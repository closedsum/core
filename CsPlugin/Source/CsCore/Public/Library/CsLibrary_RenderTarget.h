// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.
#pragma once
// Types
#include "Engine/TextureRenderTarget2D.h"

class UTextureRenderTarget2D;
class UMaterialInterface;

namespace NCsRenderTarget
{
	namespace N2D
	{
		struct CSCORE_API FLibrary final
		{
			/**
			* Creates a new render target and initializes it to the specified dimensions
			* 
			* @param Context				The calling context
			* @param WorldContext
			* @param Width					(optional)
			* @param Height					(optional)
			* @param Format					(optional)
			* @param ClearColor				(optional)
			* @param bAutoGenerateMipMaps	(optional)
			*/
			static UTextureRenderTarget2D* CreateChecked(const FString& Context, UObject* WorldContext, const int32& Width = 256, const int32& Height = 256, const ETextureRenderTargetFormat& Format = RTF_RGBA16f, const FLinearColor& ClearColor = FLinearColor::Black, const bool& bAutoGenerateMipMaps = false);

			/**
			* Renders a quad with the material applied to the specified render target.
			* This sets the render target even if it is already set, which is an expensive operation.
			* Use BeginDrawCanvasToRenderTarget / EndDrawCanvasToRenderTarget instead if rendering multiple primitives to the same render target.
			* 
			* @param Context				The calling context.
			* @param WorldContext
			* @param TextureRenderTarget
			* @param Material
			*/
			static void DrawMaterialToRenderTargetChecked(const FString& Context, UObject* WorldContext, UTextureRenderTarget2D* TextureRenderTarget, UMaterialInterface* Material);

			/**
			* Clears the specified TextureRenderTarget with the given ClearColor.
			* 
			* @param Context				The calling context.
			* @param WorldContext
			* @param TextureRenderTarget
			* @param ClearColor				(optional) Default is Black.
			*/
			static void ClearChecked(const FString& Context, UObject* WorldContext, UTextureRenderTarget2D* TextureRenderTarget, const FLinearColor& ClearColor = FLinearColor(0, 0, 0, 1));
		};
	}
}