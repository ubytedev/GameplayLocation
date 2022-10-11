// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "GameplayLocationContainer.h"
#include "GameplayLocationQuerier.h"
#include "GameplayLocationStatics.generated.h"

/** Contains useful static GameplayLocation- related utility functions that can be called from both Blueprint and C++ */
UCLASS()
class GAMEPLAYLOCATIONRUNTIME_API UGameplayLocationStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Return whether this class resolves the given explicit Gameplay Tags.
	 * @see GameplayLocationConfig. It's defined under Project Settings > Plugins > Gameplay Location
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (MustImplement = "GameplayLocationQuerier"))
	static bool ResolvesGameplayLocation(const TSoftClassPtr<UObject> Class, const FGameplayTagContainer GameplayTags);

	/**
	 * Return whether this class resolves all descendants of the given implicit Gameplay Tags. These tags *always* have one or more children.
	 * @see GameplayLocationConfig. It's defined under Project Settings > Plugins > Gameplay Location
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (MustImplement = "GameplayLocationQuerier"))
	static bool ResolvesGameplayLocationDescendants(const TSoftClassPtr<UObject> Class, const FGameplayTagContainer GameplayTags);

	/**
	 * Make an outgoing GameplayLocation. It holds a weak reference to the querier.

	 * @param GameplayLocationQuerier The context GameplayLocationQuerier
	 * @param GameplayTag The explicit tag to resolve, which has no children.
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (DisplayName = "Make Outgoing Gameplay Location", DefaultToSelf = "GameplayLocationQuerier"))
	static FGameplayLocation K2_MakeOutgoingGameplayLocation(const TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTag GameplayTag);

	/**
	 * Make an outgoing GameplayLocationContainer structure. It holds a weak reference to querier.
	 * 
	 * @param GameplayLocationQuerier The context target
	 * @param GameplayTags Gameplay tags to add
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (DisplayName = "Make Outgoing Gameplay Location Container", DefaultToSelf = "GameplayLocationQuerier"))
	static FGameplayLocationContainer K2_MakeOutgoingGameplayLocationContainer(const TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTagContainer GameplayTags);
	
	/** Exercise this GameplayLocation, yielding a Vector. @Important: Refrain from caching the return value, and always call this on-demand instead. */
	UFUNCTION(BlueprintPure, Category = GameplayLocation)
	static FVector ResolveGameplayLocation(const FGameplayLocation& GameplayLocation);

	/** Exercise this GameplayLocationContainer, yielding an array of Vectors. @Important: Refrain from caching the return value, and call this on-demand instead. */
	UFUNCTION(BlueprintPure, Category = GameplayLocation)
	static TArray<FVector> ResolveGameplayLocationContainer(const FGameplayLocationContainer& GameplayLocationContainer);

	/** Return whether the members of the GameplayLocation structure itself are valid. */
	UFUNCTION(BlueprintPure, Category = GameplayLocation)
	static bool IsValid_GameplayLocation(const FGameplayLocation& GameplayLocation);
};