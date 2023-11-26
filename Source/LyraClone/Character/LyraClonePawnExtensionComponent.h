#pragma once

#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "LyraClonePawnExtensionComponent.generated.h"

class ULyraClonePawnData;

/**
 * 초기화 전반을 조정하는 컴포넌트
 * LyraClonePawnExtensionComponent는 캐릭터에 대한 초기화를 담당하는 컴포넌트 입니다.
 * 또한 캐릭터에 대한 관련 컴포넌트를 조율합니다. 현재는 HeroComponent와 PawnComponent를 조율합니다.
 */
UCLASS()
class ULyraClonePawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()
public:
	ULyraClonePawnExtensionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** FeatureName 정의 */
	// NAME_ActorFeatureName은 RegisterInitStateFeature()에서 내부적으로 GameFeatureName을 정의해야 해당 이름으로 컴포넌트를 Bind하기 때문에 PawnComponent를 상속받았다면 반드시 유니크한 이름을 정의해야 합니다.
	static const FName NAME_ActorFeatureName;

	/**
	 * member methods
	 */
	static ULyraClonePawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<ULyraClonePawnExtensionComponent>() : nullptr); }
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }
	void SetPawnData(const ULyraClonePawnData* InPawnData);
	void SetupPlayerInputComponent();


	/**
	 * UPawnComponent interfaces
	 */
	virtual void OnRegister() final;
	virtual void BeginPlay() final;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final;

	/**
	 * IGameFrameworkInitStateInterface
	 */
	// GetFeatureName()을 오버라이딩하여 이름을 반환하도록 구현합니다.
	virtual FName GetFeatureName() const final { return NAME_ActorFeatureName; } 
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) final;
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const final;
	virtual void CheckDefaultInitialization() final;

	/**
	 * Pawn을 생성한 데이터를 캐싱
	 */
	UPROPERTY(EditInstanceOnly, Category = "LyraClone|Pawn")
	TObjectPtr<const ULyraClonePawnData> PawnData;
};

// IGameFrameworkInitStateInterface는 폭 넓고 자유도 있게 초기화 할 수 있도록 선언되어 있는 Interface입니다.
// 대표적으로 GameInstance에서 초기화를 위해 다양한 GameTag를 등록했는데 Tag를 이용하여 단계별로 초기화를 하기 위해서 사용이 가능합니다.

