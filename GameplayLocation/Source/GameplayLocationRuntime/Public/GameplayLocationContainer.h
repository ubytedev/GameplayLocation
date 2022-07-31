// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "VisualLogger/VisualLogger.h"
#include "GameplayLocationContainer.generated.h"

class IGameplayLocationQuerier;
struct FGameplayTag;

DECLARE_LOG_CATEGORY_EXTERN(LogGameplayLocation, Log, All);

USTRUCT(BlueprintType)
struct FGameplayLocation
{
	GENERATED_USTRUCT_BODY()

	FGameplayLocation()
		: Querier(nullptr), GameplayTag()
	{}

	FGameplayLocation(const TScriptInterface<IGameplayLocationQuerier>& InQuerier, const FGameplayTag& InGameplayTag)
		: Querier(InQuerier.GetObject()), GameplayTag(InGameplayTag)
	{
		UE_CLOG(IsValidSlow(), LogGameplayLocation, Error, TEXT("In gameplay location querier '%s' of class '%s' does not resolve '%s'. Will always return an undefined FVector."), *GetNameSafe(InQuerier.GetObject()), InQuerier.GetObject() ? *GetNameSafe(InQuerier.GetObject()->GetClass()) : TEXT_NULL, *InGameplayTag.GetTagName().ToString());
	}

	bool IsValidSlow() const;
	FORCEINLINE bool IsValid() const { return Querier.IsValid() && GameplayTag.IsValid(); }
	FORCEINLINE operator FVector() const { return Get(); }

	FVector Get() const;

	FORCEINLINE const FGameplayTag& GetTag() const { return GameplayTag; }
	FORCEINLINE const TWeakObjectPtr<UObject>& GetQuerier() const { return Querier; }
	
protected:
	UPROPERTY(SaveGame)
	TWeakObjectPtr<UObject> Querier;

	UPROPERTY(SaveGame)
	FGameplayTag GameplayTag;
};

USTRUCT(BlueprintType)
struct FGameplayLocationContainer
{
	GENERATED_USTRUCT_BODY()

	FGameplayLocationContainer()
		: Querier(nullptr), TagContainer()
	{}

	FGameplayLocationContainer(const TScriptInterface<IGameplayLocationQuerier>& InQuerier, const FGameplayTagContainer& InTagContainer)
		: Querier(InQuerier.GetObject()), TagContainer(InTagContainer)
	{
		UE_CLOG(IsValidSlow(), LogGameplayLocation, Error, TEXT("In gameplay location querier '%s' of class '%s' does not resolve (one of) the provided tags in the tag container. Will always return an undefined FVector."), *GetNameSafe(InQuerier.GetObject()), InQuerier.GetObject() ? *GetNameSafe(InQuerier.GetObject()->GetClass()) : TEXT_NULL);
	}

	FGameplayLocationContainer(const TScriptInterface<IGameplayLocationQuerier>& InQuerier, FGameplayTagContainer&& InTagContainer)
		: Querier(InQuerier.GetObject()), TagContainer(MoveTemp(InTagContainer))
	{
		UE_CLOG(IsValidSlow(), LogGameplayLocation, Error, TEXT("In gameplay location querier '%s' of class '%s' does not resolve (one of) the provided tags in the tag container. Will always return an undefined FVector."), *GetNameSafe(InQuerier.GetObject()), InQuerier.GetObject() ? *GetNameSafe(InQuerier.GetObject()->GetClass()) : TEXT_NULL);
	}
	
	bool IsValidSlow() const;
	FORCEINLINE bool IsValid() const { return Querier.IsValid() && TagContainer.IsValid(); }
	FORCEINLINE operator TArray<FVector>() const { return Get(); }
	
	void ForEachGameplayLocation(const TFunctionRef<void(FVector)> Func);
	void ForEachGameplayLocation(const TFunctionRef<void(FVector)> Func) const;

	TArray<FVector> Get() const;
	TMap<FGameplayTag, FVector> GetMap() const;

	FORCEINLINE const FGameplayTagContainer& GetTagContainer() const { return TagContainer; }
	FORCEINLINE const TWeakObjectPtr<UObject>& GetQuerier() const { return Querier; }

protected:
	UPROPERTY(SaveGame)
	TWeakObjectPtr<UObject> Querier;

	UPROPERTY(SaveGame)
	FGameplayTagContainer TagContainer;
};

