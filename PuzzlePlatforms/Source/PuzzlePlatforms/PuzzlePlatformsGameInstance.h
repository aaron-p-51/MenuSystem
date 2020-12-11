// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"


class UUserWidget;
class UMainMenu;
class UInGameMenu;
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

/*
* Members
*/
private:
	TSubclassOf<UUserWidget> MenuClass;
	UMainMenu* Menu;

	TSubclassOf<UUserWidget> InGameMenuClass;
	UInGameMenu* InGameMenu;



/*
* Methods
*/
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& IP_Address) override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	virtual void LoadMainMenu() override;
	
};
