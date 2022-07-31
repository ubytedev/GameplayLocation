// Copyright ubyte digital. All Right Reserved. https://ubyte.dev


#include "GameplayLocationContainer.h"
#include "GameplayLocationQuerier.h"
#include "GameplayLocationStatics.h"
#include "GameplayTagContainer.h"
#include "K2Node_IfThenElse.h"

DEFINE_LOG_CATEGORY(LogGameplayLocation)

bool FGameplayLocation::IsValidSlow() const
{
	if (IsValid())
	{
		for (const UClass* Class = Querier->GetClass(); Class; Class = Class->GetSuperClass())
		{
			if (UGameplayLocationStatics::ResolvesGameplayLocation(Class, GameplayTag.GetSingleTagContainer()))
			{
				return true;
			}
		}
	}
	
	return false;
}

FVector FGameplayLocation::Get() const
{
	check(IsValid())
	
#if DO_GUARD_SLOW
	UE_CLOG(IsValidSlow(), LogGameplayLocation, Error, TEXT("Gameplay location querier '%s' of class '%s' does not resolve '%s'. Will always return an undefined FVector."), *GetNameSafe(Querier.Get()), GetNameSafe(Querier->GetClass()), *GameplayTag.GetTagName().ToString());
#endif
	
	return IGameplayLocationQuerier::Execute_ResolveGameplayLocation(Querier.Get(), GameplayTag);
}

TMap<FGameplayTag, FVector> FGameplayLocationContainer::GetMap() const
{
	TMap<FGameplayTag, FVector> OutMap;
	OutMap.Reserve(TagContainer.Num());

	for (const FGameplayTag& Tag : TagContainer)
	{
		OutMap.Add(Tag, IGameplayLocationQuerier::Execute_ResolveGameplayLocation(Querier.Get(), Tag));
	}
	
	return OutMap;
}

bool FGameplayLocationContainer::IsValidSlow() const
{
	if (IsValid())
	{
		for (const UClass* Class = Querier->GetClass(); Class; Class = Class->GetSuperClass())
		{
			if (UGameplayLocationStatics::ResolvesGameplayLocation(Class, TagContainer))
			{
				return true;
			}
		}
	}

	return false;
}

void FGameplayLocationContainer::ForEachGameplayLocation(const TFunctionRef<void(FVector)> Func)
{
	for (const FGameplayTag& Tag : TagContainer)
	{
		Func(IGameplayLocationQuerier::Execute_ResolveGameplayLocation(Querier.Get(), Tag));
	}
}

void FGameplayLocationContainer::ForEachGameplayLocation(const TFunctionRef<void(FVector)> Func) const
{
	for (const FGameplayTag& Tag : TagContainer)
	{
		Func(IGameplayLocationQuerier::Execute_ResolveGameplayLocation(Querier.Get(), Tag));
	}
}

TArray<FVector> FGameplayLocationContainer::Get() const
{
	TArray<FVector> OutArray;
	OutArray.Reserve(TagContainer.Num());
	
	for (const FGameplayTag& Tag : TagContainer)
	{
		OutArray.Add(IGameplayLocationQuerier::Execute_ResolveGameplayLocation(Querier.Get(), Tag));
	}

	return OutArray;
}
