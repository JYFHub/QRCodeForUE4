// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QRCodeComponent.generated.h"

UENUM(BlueprintType)
enum class EQRecLevel : uint8
{
	QR_ECLEVEL_L = 0	 UMETA(DisplayName = "QR_ECLEVEL_L"),
	QR_ECLEVEL_M		 UMETA(DisplayName = "QR_ECLEVEL_M"),
	QR_ECLEVEL_Q		 UMETA(DisplayName = "QR_ECLEVEL_Q"),
	QR_ECLEVEL_H		 UMETA(DisplayName = "QR_ECLEVEL_H")
};

UENUM(BlueprintType)
enum class EQRencodeMode : uint8
{
	QR_MODE_NUL = 0		UMETA(DisplayName = "QR_MODE_NUL"),  ///< Terminator (NUL character). Internal use only
	QR_MODE_NUM = 1		UMETA(DisplayName = "QR_MODE_NUM"),   ///< Numeric mode
	QR_MODE_AN			UMETA(DisplayName = "QR_MODE_AN"),        ///< Alphabet-numeric mode
	QR_MODE_8			UMETA(DisplayName = "QR_MODE_8"),         ///< 8-bit data mode
	QR_MODE_KANJI		UMETA(DisplayName = "QR_MODE_KANJI"),     ///< Kanji (shift-jis) mode
	QR_MODE_STRUCTURE	UMETA(DisplayName = "QR_MODE_STRUCTURE"), ///< Internal use only
	QR_MODE_ECI			UMETA(DisplayName = "QR_MODE_ECI"),       ///< ECI mode
	QR_MODE_FNC1FIRST	UMETA(DisplayName = "QR_MODE_FNC1FIRST"),  ///< FNC1, first position
	QR_MODE_FNC1SECOND	UMETA(DisplayName = "QR_MODE_FNC1SECOND") ///< FNC1, second position
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QRCODE_API UQRCodeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQRCodeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = QRCode)
	UTexture2D* GenerateQRCode(const FString& QRCodeName, const FString &str, int32 version, UObject* Outer, EQRencodeMode QrencodeMode, EQRecLevel QrecLevel, int32 casesensitive, FLinearColor color1, FLinearColor color2, const bool bSRGB = true, const bool bUseAlpha = false);

};
