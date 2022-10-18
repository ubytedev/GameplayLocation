// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "GameplayLocationContainer.h"
#include "GameplayLocationQuerier.h"
#include "GameplayLocationStatics.generated.h"

/**
 * Contains useful static GameplayLocation- related utility functions that can be called from both Blueprint and C++
 */
UCLASS()
class GAMEPLAYLOCATIONRUNTIME_API UGameplayLocationStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Return whether instances of this class would resolve the given (explicit) Gameplay Tags.
	 * @see GameplayLocationConfig. It's defined under Project Settings > Plugins > Gameplay Location
	 *
	 * @param Class Class that implements GameplayLocationQuerier
	 * @param GameplayTags Tags without children
	 * @param bIncludeSuper true if parent classes should be tested too, which is the default behavior.
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (MustImplement = "GameplayLocationQuerier", DisplayName = "Resolves Gameplay Location"))
	static bool ResolvesGameplayLocation(TSubclassOf<UObject> Class, FGameplayTagContainer GameplayTags, bool bIncludeSuper = true);
	
	/**
	 * Return whether instances of this class would resolve all descendants of the given (implicit) Gameplay Tags. These tags *always* have one or more children.
	 * @see GameplayLocationConfig. It's defined under Project Settings > Plugins > Gameplay Location
	 *
	 * @param Class Class that implements GameplayLocationQuerier
	 * @param GameplayTags Tags with one or more children.
	 * @param bIncludeSuper true if parent classes should be tested too, which is the default behavior.
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (MustImplement = "GameplayLocationQuerier"))
	static bool ResolvesGameplayLocationDescendants(TSubclassOf<UObject> Class, FGameplayTagContainer GameplayTags, bool bIncludeSuper = true);
	
	/**
	 * Make an outgoing GameplayLocation. It holds a weak reference to the querier.

	 * @param GameplayLocationQuerier The context GameplayLocationQuerier
	 * @param GameplayTag The explicit tag to resolve, which has no children.
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (DisplayName = "Make Outgoing Gameplay Location", DefaultToSelf = "GameplayLocationQuerier"))
	static FGameplayLocation K2_MakeOutgoingGameplayLocation(TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTag GameplayTag);

	/**
	 * Make an outgoing GameplayLocationContainer structure. It holds a weak reference to querier.
	 * 
	 * @param GameplayLocationQuerier The context target
	 * @param GameplayTags Gameplay tags to add
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation, Meta = (DisplayName = "Make Outgoing Gameplay Location Container", DefaultToSelf = "GameplayLocationQuerier"))
	static FGameplayLocationContainer K2_MakeOutgoingGameplayLocationContainer(TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTagContainer GameplayTags);
	
	/**
	 * Resolve this GameplayLocation, returning a Vector.
	 *
	 * @param GameplayLocation The GameplayLocation structure to resolve. Returns a null vector if invalid.
	 * @return A vector coordinate. Refrain from caching the return value, and always call this on-demand instead.
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation)
	static FVector ResolveGameplayLocation(const FGameplayLocation& GameplayLocation);

	/**
	 * Resolve this GameplayLocationContainer, returning an array of Vectors.
	 *
	 * @param GameplayLocationContainer: The GameplayLocationContainer structure to resolve. Returns an empty array if one member is invalid.
	 * @return An array of vectors. Refrain from caching the return value, and always call this on-demand instead.
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation)
	static TArray<FVector> ResolveGameplayLocationContainer(const FGameplayLocationContainer& GameplayLocationContainer);

	/**
	 * Return whether a GameplayLocation structure is valid
	 *
	 * @param GameplayLocation The GameplayLocation structure to test
	 */
	UFUNCTION(BlueprintPure, Category = GameplayLocation)
	static bool IsValid_GameplayLocation(const FGameplayLocation& GameplayLocation);

protected:
	/** Internal helper function */
	template <typename Predicate>
	static bool TraverseClassHierarchyByPredicate(Predicate Pred, TSubclassOf<UObject> Class, bool bIncludeSuper = true);
};

