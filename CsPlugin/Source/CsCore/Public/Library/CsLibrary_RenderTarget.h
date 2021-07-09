// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.
#pragma once
// Types
#include "Engine/TextureRenderTarget2D.h"

class UTextureRenderTarget2D;

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
		};
	}
}