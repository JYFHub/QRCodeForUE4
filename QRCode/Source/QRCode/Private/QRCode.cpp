// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "QRCode.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

#define LOCTEXT_NAMESPACE "FQRCodeModule"

void FQRCodeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    UE_LOG(LogInit, Warning, TEXT("StartupModule()1"));
	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("QRCode")->GetBaseDir();


}

void FQRCodeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	//FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	//ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQRCodeModule, QRCode)