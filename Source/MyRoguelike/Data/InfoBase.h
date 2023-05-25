// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Engine/DataTable.h>
#include "InfoBase.generated.h"

/**
 *
 */
USTRUCT()
struct MYROGUELIKE_API FInfoBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FInfoBase() : Level(1), HP(100.0f), Attack(10.0f), DropExp(10), NextExp(100) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};
