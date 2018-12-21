// Fill out your copyright notice in the Description page of Project Settings.

#include "QRCodeComponent.h"
#include "qrencode.h"
#include "ImageUtils.h"


// Sets default values for this component's properties
UQRCodeComponent::UQRCodeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQRCodeComponent::BeginPlay()
{
	Super::BeginPlay();

	
	// ...
	
}


// Called every frame
void UQRCodeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UTexture2D* UQRCodeComponent::GenerateQRCode(const FString& QRCodeName, const FString &str, int32 version, UObject* Outer, EQRencodeMode QrencodeMode, EQRecLevel QrecLevel, int32 casesensitive, FLinearColor color1, FLinearColor color2, const bool bSRGB, const bool bUseAlpha)
{
	QRecLevel ql = QR_ECLEVEL_L;
	if (QrecLevel == EQRecLevel::QR_ECLEVEL_L)ql = QR_ECLEVEL_L;
	else if (QrecLevel == EQRecLevel::QR_ECLEVEL_M)ql = QR_ECLEVEL_M;
	else if (QrecLevel == EQRecLevel::QR_ECLEVEL_Q)ql = QR_ECLEVEL_Q;
	else if (QrecLevel == EQRecLevel::QR_ECLEVEL_H)ql = QR_ECLEVEL_H;

	QRencodeMode qm = QR_MODE_8;
	if (QrencodeMode == EQRencodeMode::QR_MODE_NUL)qm = QR_MODE_NUL;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_NUM)qm = QR_MODE_NUM;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_AN)qm = QR_MODE_AN;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_8)qm = QR_MODE_8;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_KANJI)qm = QR_MODE_KANJI;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_STRUCTURE)qm = QR_MODE_STRUCTURE;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_ECI)qm = QR_MODE_ECI;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_FNC1FIRST)qm = QR_MODE_FNC1FIRST;
	else if (QrencodeMode == EQRencodeMode::QR_MODE_FNC1SECOND)qm = QR_MODE_FNC1SECOND;

	int ver = version;
	int casese = casesensitive;

	
	QRcode* pQRC = QRcode_encodeString(TCHAR_TO_ANSI(*str), ver, ql, qm, casese);
	if (pQRC)
	{
		int width = pQRC->width;
		TArray<FColor> ColorArray;
		ColorArray.SetNum(width * width + 1);
		
		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int a = y * width + x;
				unsigned char b = pQRC->data[a];
				if (b & 0x01)
				{
					ColorArray[a] = color1.ToFColor(bSRGB);
				} else {
					ColorArray[a] = color2.ToFColor(bSRGB);
				}
			}
		}
		FCreateTexture2DParameters Parameters;
		Parameters.bSRGB = bSRGB;
		Parameters.bUseAlpha = bUseAlpha;
		
		QRcode_free(pQRC);
		UTexture2D* qrcodetexture2D = FImageUtils::CreateTexture2D(width, width, ColorArray, Outer, QRCodeName, RF_NoFlags, Parameters);
		qrcodetexture2D->Filter = TF_Nearest;
		return qrcodetexture2D;
	}
	return nullptr;
}

