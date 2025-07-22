// Developed by SaintFrost

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Shinbi.generated.h"

class UCameraComponent;
class USpringArmComponent;

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTNIGHT_API AShinbi : public ACharacter
{
	GENERATED_BODY()

public:
	AShinbi();

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultContext;

	/**
	 * Input Actions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AttackAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void Attack();
	
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
	
};
