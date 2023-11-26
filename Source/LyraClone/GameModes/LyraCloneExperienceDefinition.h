#pragma once

#include "Engine/DataAsset.h"
#include "LyraCloneExperienceDefinition.generated.h"

/** forward declaration */
class ULyraClonePawnData;

/**
 * ULyraCloneExperienceDefinition
 * 사용자의 경험을 정의
 */
UCLASS()
class ULyraCloneExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	ULyraCloneExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** the default pawn class to spawn for players */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<ULyraClonePawnData> DefaultPawnData;

	/** lost if game feature plugins this experience wants to have active */
	// 해당 property는 단순히 마킹 및 기억용으로 남겨놓도록 하겠다:
	// - GameMode에 따라 필요한 GameFeature plugin들을 로딩하는데 이에 대한 연결고리로 생각하면 된다 (현재는 쓰지 않음)
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;
};