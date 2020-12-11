// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UWidget;
class UEditableTextBox;


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

/*
* Members *
*/
private:

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuHostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuJoinButton;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuCancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuJoinButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPAddressField;

/*
* Methods *
*/

protected:

	virtual bool Initialize() override;

private:
	
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitGame();
};
