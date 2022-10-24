// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#include "GameplayLocationStatics.h"
#include "GameplayLocationSettings.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameplayLocationManager, Log, All)


bool UGameplayLocationStatics::ResolvesGameplayLocation(TSubclassOf<UObject> Class, FGameplayTagContainer GameplayTags, bool bIncludeSuper)
{
	if (!Class.Get()) 
	{
		UE_VLOG_UELOG(GetDefault<UGameplayLocationStatics>(), LogGameplayLocationManager, Error, TEXT("%s failed. Provided Class is null."), __FUNCTIONW__);
		return false;
	}
	
	if (GameplayTags.IsEmpty())
	{
		return false;
	}

	const UGameplayLocationSettings* Settings = GetDefault<UGameplayLocationSettings>();
	check(Settings);
	
	return TraverseClassHierarchyByPredicate(
		[Settings, &GameplayTags](const UClass* ClassPtr) -> bool
		{
			if (const FGameplayLocationConfig* Config = Settings->ConfigMap.Find(ClassPtr))
			{
				for (const FGameplayTag& GroupTag : Config->ImplementedGroups)
				{
					if (!GameplayTags.HasTag(GroupTag) || GameplayTags.HasTagExact(GroupTag))
					{
						return false;
					}
				}

				return true;
			}

			return false;
		}, Class, bIncludeSuper);
}

bool UGameplayLocationStatics::ResolvesGameplayLocationDescendants(TSubclassOf<UObject> Class, FGameplayTagContainer GameplayTags, bool bIncludeSuper)
{
	if (!Class.Get()) 
	{
		UE_VLOG_UELOG(GetDefault<UGameplayLocationStatics>(), LogGameplayLocationManager, Error, TEXT("%s failed. Provided Class is null."), __FUNCTIONW__);
		return false;
	}
	
	if (GameplayTags.IsEmpty())
	{
		return false;
	}
	
	const UGameplayLocationSettings* Settings = GetDefault<UGameplayLocationSettings>();
	check(Settings);
	
	return TraverseClassHierarchyByPredicate(
		[Settings, &GameplayTags](const UClass* ClassPtr) -> bool
		{
			if (const FGameplayLocationConfig* Config = Settings->ConfigMap.Find(ClassPtr))
			{
				return GameplayTags.HasAllExact(Config->ImplementedGroups);
			}
			
			return false;
		}, Class, bIncludeSuper);
}

FGameplayLocation UGameplayLocationStatics::K2_MakeOutgoingGameplayLocation(
	TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTag GameplayTag)
{
	return FGameplayLocation(GameplayLocationQuerier, GameplayTag);
}

FGameplayLocationContainer UGameplayLocationStatics::K2_MakeOutgoingGameplayLocationContainer(
	TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTagContainer GameplayTags)
{
	return FGameplayLocationContainer(GameplayLocationQuerier, GameplayTags);
}

FVector UGameplayLocationStatics::ResolveGameplayLocation(const FGameplayLocation& GameplayLocation)
{
	if (GameplayLocation.IsValid())
	{
		return GameplayLocation.Get();
	}
	
	UE_VLOG_UELOG(GetDefault<UGameplayLocationStatics>(), LogGameplayLocationManager, Error, TEXT("%s failed. Provided GameplayLocation is invalid."), __FUNCTIONW__);
	return FVector();
}

TArray<FVector> UGameplayLocationStatics::ResolveGameplayLocationContainer(
	const FGameplayLocationContainer& GameplayLocationContainer)
{
	if (GameplayLocationContainer.IsValid())
	{
		return GameplayLocationContainer.Get();
	}

	UE_VLOG_UELOG(GetDefault<UGameplayLocationStatics>(), LogGameplayLocationManager, Error, TEXT("%s failed. Provided GameplayLocationContainer is invalid."), __FUNCTIONW__);
	return TArray<FVector>();
}

bool UGameplayLocationStatics::IsValid_GameplayLocation(const FGameplayLocation& GameplayLocation)
{
	return GameplayLocation.IsValid();
}

template <typename Predicate>
bool UGameplayLocationStatics::TraverseClassHierarchyByPredicate(Predicate Pred, TSubclassOf<UObject> Class, bool bIncludeSuper)
{
	if (bIncludeSuper)
	{
		for (const UClass* ClassItr = Class.Get(); ClassItr; ClassItr = ClassItr->GetSuperClass())
		{
			if (Invoke(Pred, ClassItr))
			{
				return true;
			}
		}
	}
	else
	{
		if (Invoke(Pred, Class.Get()))
		{
			return true;
		}
	}

	return false;
}