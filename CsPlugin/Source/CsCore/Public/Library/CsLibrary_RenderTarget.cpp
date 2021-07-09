// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.
#include "Library/CsLibrary_RenderTarget.h"

// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"

namespace NCsRenderTarget
{
	namespace N2D
	{
		UTextureRenderTarget2D* FLibrary::CreateChecked(const FString& Context, UObject* WorldContext, const int32& Width /*=256*/, const int32& Height /*=256*/, const ETextureRenderTargetFormat& Format /*=RTF_RGBA16f*/, const FLinearColor& ClearColor /*=FLinearColor::Black*/, const bool& bAutoGenerateMipMaps /*=false*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

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
	}
}