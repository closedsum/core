// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsEthereumKeystore.generated.h"

USTRUCT(BlueprintType)
struct FCsEthereumKeystoreKdfParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	int32 dklen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	int32 n;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	int32 p;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	int32 r;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString salt;

	FCsEthereumKeystoreKdfParams(){}
	~FCsEthereumKeystoreKdfParams(){}
};

USTRUCT(BlueprintType)
struct FCsEthereumKeystoreCipherParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString iv;

	FCsEthereumKeystoreCipherParams() {}
	~FCsEthereumKeystoreCipherParams() {}
};

USTRUCT(BlueprintType)
struct FCsEthereumKeystoreCrypto
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString cipher;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString ciphertext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FCsEthereumKeystoreCipherParams cipherparams;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString kdf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FCsEthereumKeystoreKdfParams kdfparams;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString mac;

	FCsEthereumKeystoreCrypto() {}
	~FCsEthereumKeystoreCrypto() {}
};

USTRUCT(BlueprintType)
struct FCsEthereumKeystore
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString address;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FCsEthereumKeystoreCrypto crypto;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum Keystore")
	int32 version;

	void Parse(const FString &Str)
	{
		//JsonConvert.PopulateObject(str, (object)this);
	}

	void ParseFromFilePath(const FString &Path)
	{
		//if (File.Exists(path))
		//	Parse(File.ReadAllText(path));
	}
};