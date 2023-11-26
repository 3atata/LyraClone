#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "LyraCloneExperienceManagerComponent.generated.h"

/** forward declaration */
class ULyraCloneExperienceDefinition;

// Experience에서 로딩 상태를 추적하기 위한 Enum
enum class ELyraCloneExperienceLoadState
{
	Unloaded,
	Loading,
	Loaded,
	Deactivating
};

// 로딩이 완료된 Experience를 전달하는 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLyraCloneExperienceLoaded, const ULyraCloneExperienceDefinition*);

/**
 * UULyraCloneExperienceManagerComponent
 * - 말 그대로, 해당 component는 game state를 owner로 가지면서, experience의 상태 정보를 가지고 있는 component이다
 * - 뿐만 아니라, manager라는 단어가 포함되어 있듯이, experience 로딩 상태 업데이트 및 이벤트를 관리한다
 */
UCLASS()
class ULyraCloneExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
public:
	ULyraCloneExperienceManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** 현재 Experience가 로딩이 다 되었는지 체크하는 함수 */
	bool IsExperienceLoaded() const { return (LoadState == ELyraCloneExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }

	/** OnExperienceLoaded에 바인딩하거나 , 이미 Experience 로딩이 완료되었다면 바로 호출함*/
	void CallOrRegister_OnExperienceLoaded(FOnLyraCloneExperienceLoaded::FDelegate&& Delegate);
	void ServerSetCurrentExperience(FPrimaryAssetId ExperienceId);
	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnExperienceFullLoadCompleted();
	const ULyraCloneExperienceDefinition* GetCurrentExperienceChecked() const;

	/**
	 * member variables
	 */

	/**
	 * 참고로 해당 멤버 변수는 Lyra에서는 'ReplicatedUsing='으로 선언되어있다:
	 * - 현재 우리는 아직 Replication을 신경쓰지 않을 것이기에, 최대한 네트워크 서버 코드를 배제하도록 하겠다
	 */
	UPROPERTY()
	TObjectPtr<const ULyraCloneExperienceDefinition> CurrentExperience;

	/** Experience의 로딩 상태를 모니터링 */
	ELyraCloneExperienceLoadState LoadState = ELyraCloneExperienceLoadState::Unloaded;

	/** Experience 로딩이 완료된 이후 BroadCast Delegate */
	FOnLyraCloneExperienceLoaded OnExperienceLoaded;
};