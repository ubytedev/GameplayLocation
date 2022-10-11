// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "GameplayLocationContainer.h"
#include "GameplayTagContainer.h"
#include "GameplayLocationQuerier.generated.h"

/* Interface for classes that want to resolve gameplay location tags */
UINTERFACE(BlueprintType)
class UGameplayLocationQuerier : public UInterface
{
	GENERATED_BODY()
};

class GAMEPLAYLOCATIONRUNTIME_API IGameplayLocationQuerier
{
	GENERATED_BODY()

public: 
	/**
	 * The implementation that returns a vector from a gameplay tag.
	 * The tags the implementer *must* resolve are all descendants of the picked Gameplay location groups this class was marked to resolve.
	 * 
	 * The class supported tags are defined inside Project Settings > Plugins > GameplayLocation.
	 * In the future, a dedicated edit section will appear inside the Class Defaults editor panel (just like data layers) for all IGameplayLocationQuerier implementing classes.
	 * 
	 * @note Deliberately not BlueprintCallable. Use methods build around the encapsulated FGameplayLocation structure instead.
	 * @see UGameplayLocationStatics::ResolveGameplayLocation
	 */
	UFUNCTION(BlueprintNativeEvent)
	FVector ResolveGameplayLocation(FGameplayTag GameplayTag) const;

protected:
	virtual FVector ResolveGameplayLocation_Implementation(FGameplayTag GameplayTag) const
	{
		LowLevelFatalError(TEXT("Pure virtual not implemented (%s). More often than not, Blueprint classes should implement ResolveGameplayLocation for the best editor experience."), PREPROCESSOR_TO_STRING(IGameplayLocationQuerier::ResolveGameplayLocation_Implementation));
		return FVector();
	}
};


