// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


// Enum 값 정의 모음
// UENUM(BlueprintType) 을 사용한 enum class 인 경우 주석으로 UMETA(ToolTip = "") 사용해주세요 ( 크로 )
// 
// ExtraDamage (추가 피해량) 은 여기에 있으면 안될것 같은 느낌이지만 임시 추가


// MoveSpeed 까지가 일단 FCharacterInfo 에서 관리하는 데이터
UENUM(BlueprintType)
enum class EActorStatType : uint8
{
	Hp					UMETA( ToolTip = "체력" ),
	MaxHp				UMETA( ToolTip = "최대 체력" ),
	AttackDamage		UMETA( ToolTip = "공격력 (= 주문력)" ),
	AttackSpeed			UMETA( ToolTip = "공격 속도" ),
	Armor				UMETA( ToolTip = "방어력" ),
	Resistance			UMETA( ToolTip = "마법 저항력" ),
	CriticalRate		UMETA( ToolTip = "치명타 확률" ),
	CriticalDamage		UMETA( ToolTip = "치명타 피해" ),
	SkillCoolTime		UMETA( ToolTip = "스킬 쿨타임 감소" ),
	MoveSpeed			UMETA( ToolTip = "이동 속도" ),

	Mp					UMETA( ToolTip = "(기획서에는 없지만 임시로 추가)" ),
	ExtraDamage			UMETA( ToolTip = "추가 피해량" ),
	Max
};
ENUM_RANGE_BY_COUNT( EActorStatType, EActorStatType::Max );

// 공격 타입. 
UENUM( BlueprintType )
enum class EDamageType : uint8
{
	Physics		UMETA( ToolTip = "물리 공격력" ),
	Magic		UMETA( ToolTip = "마법 공격력" ),
	Fixed		UMETA( ToolTip = "임시로 넣음, 고정 데미지" ),
};

// 오브젝트 타입. 
UENUM( BlueprintType )
enum class EObjectType : uint8
{
	Pc			UMETA( ToolTip = "플레이어 캐릭터" ),
	Npc			UMETA( ToolTip = "NPC" ),
	Monster		UMETA( ToolTip = "Monster" ),
};

// 능력이 완료 되었을때, 어떻게 완료되었는지에 대한 enum 입니다.
UENUM( BlueprintType )
enum class EAbilityCompletedType : uint8
{
	Success		UMETA( ToolTip = "스킬 사용 성공"),
	Canceled	UMETA( ToolTip = "스킬 사용 취소됨"),
	Failed		UMETA( ToolTip = "스킬 사용 실패")
};

// CharacterPC가 가질 수 있는 상태입니다.
// 추후 각성기 사용중, 캐릭터 교대중 등 필요한 상태를 더 추가할 예정입니다. ( 성윤 )
UENUM( BlueprintType )
enum class EPCStateType : uint8
{
	Idle				UMETA( ToolTip = "가만히 있음" ),
	Moving				UMETA( ToolTip = "이동 중" ),
	BasicAttacking		UMETA( ToolTip = "기본 공격 중" ),
	UsingNormalSkill	UMETA( ToolTip = "일반 스킬 사용 중" ),
	UsingUltimateSkill	UMETA( ToolTip = "궁극기 사용 중" ),
	UsingAvoidSkill		UMETA( ToolTip = "회피 스킬 사용 중" ),
	Die					UMETA( ToolTip = "사망" )
};

// PlayerCharacter의 Ability를 호출할때 key로 사용합니다. key별로 호출되는 능력이 상이합니다.
UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	MouseLM				UMETA( ToolTip = "마우스 좌클릭"),
	MouseRM				UMETA( ToolTip = "마우스 우클릭"),
	Shift				UMETA( ToolTip = "쉬프트"),
	SkillQ				UMETA( ToolTip = "Q 스킬"),
	SkillE 				UMETA( ToolTip = "E 스킬"),
	SkillR				UMETA( ToolTip = "R 스킬"),
	None				UMETA( ToolTip = "지정되지 않음"),
};
ENUM_RANGE_BY_COUNT( EAbilityType, EAbilityType::None );

//콜리전 타입에 대한 enum 입니다.
UENUM(BlueprintType)
enum class EActorCollisionShape : uint8
{
	Box			UMETA(ToolTip = "육면체 형태"),
	Sphere		UMETA(ToolTip = "구 형태"),
	Capsule		UMETA(ToolTip = "캡슐 형태")
};

//Buff의 타입을 설정합니다.
UENUM(BlueprintType)
enum class EBuffType : uint8
{
	Stat	UMETA(ToolTip = "스탯변화 버프")
};

//
UENUM(BlueprintType)
enum class EBuffSelectRule : uint8
{
	Range		UMETA(ToolTip = "범위 내의 대상에게 버프를 적용합니다.")
	//Nearest		UMETA(ToolTip = "가장 가까운 대상에게 버프를 적용합니다.")
};

//BuffBase에서 이펙트를 생성할 시기를 정해줍니다.
UENUM(BlueprintType)
enum class EEffectCreationTime : uint8
{
	Enter	UMETA(ToolTip = "버프 시작 시 이펙트 생성"),
	Tick	UMETA(ToolTip = "버프 도중 이펙트 생성"),
	Exit	UMETA(ToolTip = "버프 종료 시 이펙트 생성")
};

// 표면 재질 타입
UENUM( BlueprintType )
enum class EPhysicalSurfaceType : uint8
{
	Default	UMETA( ToolTip = "기본값" ),
	Dirt	UMETA( ToolTip = "흙" ),
	Grass	UMETA( ToolTip = "잔디" ),
	Rock	UMETA( ToolTip = "암석" ),
};

// 캐릭터 태그에 대한 enum 입니다.
UENUM( BlueprintType )
enum class ETagType : uint8
{
	TagCharacter1,
	TagCharacter2,
	TagCharacter3,
	Max
};
ENUM_RANGE_BY_COUNT( ETagType, ETagType::Max );

//AnimationMontage를 재생시킬 타입입니다.
UENUM(BlueprintType)
enum class EPlayAnimMontageType : uint8
{
	AllBody		UMETA(ToolTip = "일반적인 애니메이션 적용"),
	UpperBody	UMETA(ToolTip = "상체에만 애니메이션 적용"),
};

//이펙트를 스폰할 위치입니다.
UENUM(BlueprintType)
enum class ESpawnEffectType : uint8
{
	Location		UMETA(ToolTip = "플레이어를 중심으로 Offset Location, Rotator에 이펙트를 생성합니다."),
	AttachActor		UMETA(ToolTip = "플레이어를 중심으로 Offset Location, Rotator를 적용시킨 채 플레이어에 어태치하여 생성합니다."),
};

// DecorateActorComponent 발동 타입
UENUM( BlueprintType )
enum class EDecorateUseType : uint8
{
	Spawn		UMETA( ToolTip = "스폰되는 시점에 발동" ),
	Despawn		UMETA( ToolTip = "디스폰되는 시점에 발동" ),
	Max,
};

// AnimMontage의 섹션 타입
// TODO : 회의때 어떻게 사용할건지 알려야함.
UENUM( BlueprintType )
enum class EMontageSectionType : uint8
{
	None				UMETA( ToolTip = "지정되지 않음"), 
	BasicAttack			UMETA( ToolTip = "기본 공격"),
	Skill1				UMETA( ToolTip = "1번째 스킬"),
	Skill2 				UMETA( ToolTip = "2번째 스킬"),
	Skill3				UMETA( ToolTip = "3번째 스킬"),
	Skill4 				UMETA( ToolTip = "4번째 스킬"),
	UltimateSkill		UMETA( ToolTip = "궁극기 스킬"),
	AvoidSkill			UMETA( ToolTip = "회피 스킬"),
	Max,
};
