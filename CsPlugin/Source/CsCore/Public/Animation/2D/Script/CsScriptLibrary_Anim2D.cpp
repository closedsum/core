// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/Script/CsScriptLibrary_Anim2D.h"
#include "CsCore.h"

// Library
#include "Animation/2D/CsLibrary_Anim2D.h"

// Cached
#pragma region

namespace NCsScriptLibraryAnim2D
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Anim2D, PlayMaterialFlipbook);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Anim2D, PlayTextureFlipbook);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Anim2D::UCsScriptLibrary_Anim2D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Texture
#pragma region

FCsRoutineHandle UCsScriptLibrary_Anim2D::PlayTextureFlipbook(const FString& Context, const FCsAnim2DTextureFlipbook_Params& Params)
{
	using namespace NCsScriptLibraryAnim2D::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PlayTextureFlipbook : Context;

	FCsAnim2DTextureFlipbook_Params* ParamsPtr = const_cast<FCsAnim2DTextureFlipbook_Params*>(&Params);

	ParamsPtr->Anim.Resolve();

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy script params to native params.
	typedef NCsAnim::N2D::NTexture::FLibrary AnimLibrary;
	typedef NCsAnim::N2D::NTexture::NPlay::NParams::FResource ParamsResourceType;
	typedef NCsAnim::N2D::NTexture::NPlay::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = AnimLibrary::Get().AllocatePlayParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return AnimLibrary::SafePlay(Ctxt, ParmsContainer);
}

#pragma endregion Texture

// Material
#pragma region

FCsRoutineHandle UCsScriptLibrary_Anim2D::PlayMaterialFlipbook(const FString& Context, const FCsAnim2DMaterialFlipbook_Params& Params)
{
	using namespace NCsScriptLibraryAnim2D::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PlayMaterialFlipbook : Context;

	FCsAnim2DMaterialFlipbook_Params* ParamsPtr = const_cast<FCsAnim2DMaterialFlipbook_Params*>(&Params);

	ParamsPtr->Anim.Resolve();

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy script params to native params.
	typedef NCsAnim::N2D::NMaterial::FLibrary AnimLibrary;
	typedef NCsAnim::N2D::NMaterial::NPlay::NParams::FResource ParamsResourceType;
	typedef NCsAnim::N2D::NMaterial::NPlay::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = AnimLibrary::Get().AllocatePlayParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return AnimLibrary::SafePlay(Ctxt, ParmsContainer);
}

#pragma endregion Material