#pragma once

#include "RE/Actor.h"


namespace RE
{
	class Character : public Actor
	{
	public:
		inline static const void* RTTI = RTTI_Character;


		enum { kTypeID = FormType::ActorCharacter };


		struct RecordFlags
		{
			enum RecordFlag : UInt32
			{
				kDeleted = 1 << 5,
				kStartsDead = 1 << 9,
				kPersistent = 1 << 10,
				kInitiallyDisabled = 1 << 11,
				kIgnored = 1 << 12,
				kNoAIAcquire = 1 << 25,
				kDontHavokSettle = 1 << 29
			};
		};


		virtual ~Character();															// 000

		// override (Actor)
		virtual void					SaveGame(BGSSaveFormBuffer* a_buf) override;	// 00E - { Actor::SaveBuffer(a_buf); }
		virtual void					LoadGame(BGSLoadFormBuffer* a_buf) override;	// 00F - { Actor::LoadBuffer(a_buf); }
		virtual void					InitLoadGame(void* a_arg1) override;			// 10 - { Actor::InitLoadGame(a_arg1); }
		virtual void					FinishLoadGame(void* a_arg1) override;			// 11 - { Actor::FinishLoadGame(a_arg1); }
		virtual void					Revert(void* a_arg1) override;					// 12 - { return; }
		virtual void					Predestroy(void) override;						// 03B
		virtual bool					IsChild() const override;						// 05E - { return race ? (race->data.flags & Flag::kChild) != Flag::kNone : false; }
		virtual BSFaceGenNiNode*		GetFaceNodeSkinned() override;					// 061
		virtual BSFaceGenAnimationData*	GetFaceGenAnimationData() override;				// 063
		virtual void					Unk_81(void) override;							// 081
		virtual void					Unk_C0(void) override;							// 0C0
		virtual void					Unk_C4(void) override;							// 0C4 - { unk272 = a_arg1; }
		virtual void					Unk_C5(void) override;							// 0C5 - { return unk272; }
		virtual void					Unk_C6(void) override;							// 0C6 - { return 1; }
		virtual void					OnArmorActorValueChanged() override;			// 0CA
		virtual void					Unk_D7(void) override;							// 0D7
		virtual void					Unk_D9(void) override;							// 0D9
		virtual void					Unk_E6(void) override;							// 0E6 - calculate armor rating?
		virtual void					Unk_E7(void) override;							// 0E7 - something about armor rating
		virtual void					Unk_E8(void) override;							// 0E8 - get unarmed damage?
		virtual void					Unk_120(void) override;							// 120 - something about BSFaceGenNiNodeSkinned

		// add
		virtual void					Unk_128(void);									// 128
		virtual void					Unk_129(void);									// 129 - { return 1; }
	};
	STATIC_ASSERT(sizeof(Character) == 0x2B0);
}
