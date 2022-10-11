// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "GameplayLocationSettings.generated.h"

USTRUCT(BlueprintType)
struct FGameplayLocationConfig
{
	GENERATED_BODY()
	
	/** Tags a Gameplay Location querier resolves all descendant tags for */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Category = GameplayLocation))
	FGameplayTagContainer ImplementedGroups;
};

UCLASS(Config = GameplayLocation, DefaultConfig, NotPlaceable)
class GAMEPLAYLOCATIONRUNTIME_API UGameplayLocationSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Meta = (MustImplement = "GameplayLocationQuerier", Category = GameplayLocation))
	TMap<TSoftClassPtr<UObject>, FGameplayLocationConfig> ConfigMap;
};