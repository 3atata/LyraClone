#include "LyraClone.h"
#include "Modules/ModuleManager.h"
#include "System/LyraCloneAssetManager.h"

class FLyraCloneGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FLyraCloneGameModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("StartupModule"));
}

void FLyraCloneGameModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("ShutdownModule"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FLyraCloneGameModule, LyraClone, "LyraClone");
