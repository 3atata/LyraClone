#pragma once

#include "Engine/AssetManager.h"
#include "LyraCloneAssetManager.generated.h"

UCLASS()
class ULyraCloneAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	ULyraCloneAssetManager();

public:
	virtual void StartInitialLoading() override final;

public:
	static ULyraCloneAssetManager& Get();

	static bool ShouldLogAssetLoads();

	void AddLoadedAsset(const UObject* Asset);

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/* Asset들을 동기적으로 로딩한 후 bKeepInMemory가 true라면 LoadedAssets에 저장 + 반환해주는 함수
	 * Asset은 게임 내에서 사용되는 리소스들 -> 블루프린트, 메쉬 , 텍스처 등등
	 * TSubClassOf는 C++코드 그 자체를 지칭하는 경우가 많으며 타입의 안정성이 중점
	 */
	template <typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

public:
	/** 로딩이 된 Asset들을 저장 GC 필수*/
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	/** Object Lock 전용 */
	FCriticalSection SyncObject;
};

template <typename AssetType>
AssetType* ULyraCloneAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	// TSoftObjectPtr은 FSoftObjectPath를 감싸고 있는 TWeakObjectPtr이며 경로 , 해당 에셋이 메모리에 존재하는지 확인 가능

	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if(AssetPath.IsValid())
	{
		// 에셋이 메모리에 존재하는지
		LoadedAsset = AssetPointer.Get();

		// 에셋이 존재하지 않는다면 불러오기
		if(!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load Asset [%s]"), *AssetPointer.ToString());
		}

		// AddLoadedAsset은 메모리에 상주하기 위한 장치 - 한번 등록되면 직접내리지 않는한 제거되지 않음
		if(LoadedAsset && bKeepInMemory)
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
	}

	return LoadedAsset;
}

template <typename AssetType>
TSubclassOf<AssetType> ULyraCloneAssetManager::GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer,bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;
	const FSoftObjectPath& AssetPath = AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();

		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Faileed to load asset class [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass & bKeepInMemory)
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
	}

	return LoadedSubclass;
}
