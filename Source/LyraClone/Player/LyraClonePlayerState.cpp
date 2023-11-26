#include "LyraClonePlayerState.h"
#include "LyraClone/GameModes/LyraCloneExperienceManagerComponent.h"
#include "LyraClone/GameModes/LyraCloneGameMode.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraClonePlayerState)

PRAGMA_DISABLE_OPTIMIZATION
ALyraClonePlayerState::ALyraClonePlayerState(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}
PRAGMA_ENABLE_OPTIMIZATION

PRAGMA_DISABLE_OPTIMIZATION
void ALyraClonePlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	ULyraCloneExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<ULyraCloneExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	// Experience가 로딩이 완료되면 폰 데이터를 초기화해야 하기 때문에 Delegate를 걸어놈
	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnLyraCloneExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}
PRAGMA_ENABLE_OPTIMIZATION

void ALyraClonePlayerState::SetPawnData(const ULyraClonePawnData* InPawnData)
{
	check(InPawnData);

	// PawnData가 두번 설정되는 것은 원하지 않음!
	check(!PawnData);

	PawnData = InPawnData;
}

// 로딩이 완료 된 후 Expericne를 받아와서 초기화 해주기 위한 함수
void ALyraClonePlayerState::OnExperienceLoaded(const ULyraCloneExperienceDefinition* CurrentExperience)
{
	if (ALyraCloneGameMode* GameMode = GetWorld()->GetAuthGameMode<ALyraCloneGameMode>())
	{
		// ALyraCloneGameMode에서 GetPawnDataForController를 구현해야 함
		// - ALyraCloneGameMode에서 아직 PawnData를 설정하지 않았으므로, ExperienceMangerComponent의 DefaultPawnData로 설정한다
		const ULyraClonePawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}
