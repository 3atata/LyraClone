#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraCloneUserFacingExperienceDefinition.generated.h"

/**
 * ULyraCloneUserFacingExperienceDefinition
 * 게임 기능을 세부적으로 게임 로직 및 동작 , 애셋 및 리소스 , 설정등을 정의
 */
UCLASS(BlueprintType)
class LYRACLONE_API ULyraCloneUserFacingExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	/**
	 * member variables
	 */

	 /** the specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapID;

	/** the gameplay expierence to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "LyraCloneExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
};