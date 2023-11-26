#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraClonePawnData.generated.h"

class ULyraCloneCameraMode;

UCLASS(BlueprintType)
class ULyraClonePawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	ULyraClonePawnData(const FObjectInitializer& ObjectInitializer);

	/** 소환될 Pawn Class */
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , Category = "LyraClone|Pawn")
	TSubclassOf<APawn> PawnClass;

	/** Camera Mode */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LyraClone|Camera")
	TSubclassOf<ULyraCloneCameraMode> DefaultCameraMode;
};