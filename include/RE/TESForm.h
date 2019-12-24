#pragma once

#include "RE/BaseFormComponent.h"
#include "RE/BSTArray.h"
#include "RE/FormTypes.h"


namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class BSFixedString;
	class TESFile;


	class TESForm : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_TESForm;


		enum { kTypeID = FormType::None };


		struct RecordFlags
		{
			enum RecordFlag : UInt32
			{
				kPlayable = 1 << 2,
				kInitialized = 1 << 3,
				kDeleted = 1 << 5,
				kKnown = 1 << 6,
				kMustUpdate = 1 << 8,
				kOnLocalMap = 1 << 9,
				kIgnored = 1 << 12,
				kRandomAnim = 1 << 16,
				kDangerous = 1 << 17,
				kHasCurrents = 1 << 19,
				kObstacle = 1 << 25
			};
		};


		class TESFileArray : public BSStaticArray<TESFile*>
		{
		public:
		};
		STATIC_ASSERT(sizeof(TESFileArray) == 0x10);


		class TESFileContainer
		{
		public:
			TESFileArray* array;	// 0
		};
		STATIC_ASSERT(sizeof(TESFileContainer) == 0x8);


		virtual ~TESForm();																																		// 00

		// override (BaseFormComponent)
		virtual void					InitializeDataComponent() override;																						// 01 - { return; }
		virtual void					ClearDataComponent() override;																							// 02 - { SetEditorID(""); }
		virtual void					CopyComponent(BaseFormComponent* a_rhs) override;																		// 03

		// add
		virtual void					InitializeData();																										// 04 - { return; }
		virtual void					ClearData();																											// 05 - { return; }
		virtual bool					Load(TESFile* a_mod);																									// 06 - { return true; }
		virtual bool					LoadPartial(TESFile* a_mod);																							// 07 - { return true; }
		virtual bool					LoadEdit(TESFile* a_mod);																								// 08 - { return Load(a_mod); }
		virtual TESForm*				CreateDuplicateForm(void* a_arg1, void* a_arg2);																		// 09
		virtual bool					AddChange(UInt32 a_changeFlags);																						// 0A
		virtual void					RemoveChange(UInt32 a_changeFlags);																						// 0B
		virtual bool					FindInFileFast(TESFile* a_mod);																							// 0C - { return false; }
		virtual bool					CheckSaveGame(BGSSaveFormBuffer* a_buf);																				// 0D - { return true; }
		virtual void					SaveGame(BGSSaveFormBuffer* a_buf);																						// 0E
		virtual void					LoadGame(BGSLoadFormBuffer* a_buf);																						// 0F
		virtual void					InitLoadGame(void* a_arg1);																								// 10 - { return; }
		virtual void					FinishLoadGame(void* a_arg1);																							// 11 - { return; }
		virtual void					Revert(void* a_arg1);																									// 12 - { return; }
		virtual void					InitItemImpl();																											// 13 - { return; }
		virtual TESFile*				GetDescriptionOwnerFile();																								// 14 - returns the file that last modified this form
		virtual FormType				GetSavedFormType() const;																								// 15 - { return formType; }
		virtual void					GetFormDetailedString(char* a_buf, UInt32 a_bufLen);																	// 16 - { return std::sprintf_s(a_buf, a_bufLen, "%s Form '%s' (%08X)", g_formStrings[3 * formID], "", formID); }
		virtual bool					GetKnown() const;																										// 17 - { return (flags >> 6 ) & 1; }
		virtual bool					GetRandomAnim() const;																									// 18 - { return (flags >> 16) & 1; }
		virtual bool					GetPlayable() const;																									// 19 - { return (flags >> 2) & 1; }
		virtual bool					IsHeadingMarker() const;																								// 1A - { return false; }
		virtual bool					GetDangerous() const;																									// 1B - { return (flags >> 17) & 1; }
		virtual bool					QHasCurrents() const;																									// 1C - { return (flags >> 19) & 1; }
		virtual bool					GetObstacle() const;																									// 1D - { return (flags >> 25) & 1; }
		virtual bool					QIsLODLandObject() const;																								// 1E - { return false; }
		virtual bool					GetOnLocalMap() const;																									// 1F - { return (flags >> 9) & 1; }
		virtual bool					GetMustUpdate() const;																									// 20 - { return (flags >> 8) & 1; }
		virtual void					SetOnLocalMap(bool a_set);																								// 21 - { if (a_set) flags &= 0xFFFFFDFF; else flags |= 0x200; }
		virtual bool					GetIgnoredBySandbox() const;																							// 22 - { return false; }
		virtual void					SetDelete(bool a_set);																									// 23 - { bool result = (flags >> 5) & 1; if (result != a_set) { if (a_set) flags |= 0x20; else flags &= 0xFFFFFFDF; MarkChanged(1); return result; }
		virtual void					SetAltered(bool a_set);																									// 24
		virtual void					SaveObjectBound(void);																									// 25 - { return; }
		virtual void					LoadObjectBound(TESFile* a_mod);																						// 26 - { return; }
		virtual bool					IsBoundObject() const;																									// 27 - { return false; }
		virtual bool					IsObject() const;																										// 28 - { return false; }
		virtual bool					IsMagicItem() const;																									// 29 - { return false; }
		virtual bool					IsWater() const;																										// 2A - { return false; }
		virtual const TESObjectREFR*	AsReference() const;																									// 2B - { return 0; }
		virtual TESObjectREFR*			AsReference();																											// 2C - { return 0; }
		virtual UInt32					GetRefCount() const;																									// 2D - { return 0; }
		virtual const char*				GetTextForParsedSubTag(const BSFixedString& a_alias);																	// 2E
		virtual void					Copy(TESForm* a_srcForm);																								// 2F - { return; }
		virtual bool					BelongsInGroup(void);																									// 30
		virtual void					CreateGroupData(void);																									// 31
		virtual const char*				GetFormEditorID();																										// 32 - { return ""; }
		virtual bool					SetFormEditorID(const char* a_str);																						// 33 - { return true; }
		virtual bool					IsParentForm() const;																									// 34 - { return false; }
		virtual bool					IsParentFormTree() const;																								// 35 - { return false; }
		virtual bool					IsFormTypeChild(FormType a_type) const;																					// 36 - { return false; }
		virtual bool					Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, UInt8 a_arg3, UInt64 a_arg4, SInt32 a_targetCount);	// 37 - { return false; }
		virtual void					SetFormID(FormID a_id, bool a_generateID);																				// 38
		virtual const char*				GetObjectTypeName() const;																								// 39 - { return ""; }
		virtual bool					QAvailableInGame(void);																									// 3A - { return true; }

		static TESForm*					LookupByID(FormID a_formID);
		template <class T> static T*	LookupByID(FormID a_formID);
		static TESForm*					LookupByEditorID(const std::string_view& a_editorID);
		template <class T> static T*	LookupByEditorID(const std::string_view& a_editorID);

		bool										Is(FormType a_type) const;
		template <class First, class... Rest> bool	Is(First a_first, Rest... a_rest) const;
		bool										IsNot(FormType a_type) const;
		template <class First, class... Rest> bool	IsNot(First a_first, Rest... a_rest) const;

		template <class T> constexpr T		As();
		template <class T> constexpr auto	As() const;

		FormID		GetFormID() const;
		SInt32		GetGoldValue() const;
		const char*	GetName() const;
		float		GetWeight() const;
		bool		HasVMAD() const;
		bool		HasWorldModel() const;
		bool		IsAmmo() const;
		bool		IsArmor() const;
		bool		IsDeleted() const;
		bool		IsDynamicForm() const;
		bool		IsGold() const;
		bool		IsIgnored() const;
		bool		IsKey() const;
		bool		IsLockpick() const;
		bool		IsPlayer() const;
		bool		IsPlayerRef() const;
		bool		IsSoulGem() const;
		bool		IsWeapon() const;


		// members
		TESFileContainer	sourceFiles;		// 08
		UInt32				flags;				// 10
		FormID				formID;				// 14
		UInt16				inGameFormFlags;	// 18
		FormType			formType;			// 1A
		UInt8				pad1B;				// 1B
		UInt32				pad1C;				// 1C
	};
	STATIC_ASSERT(sizeof(TESForm) == 0x20);


	template <class T>
	inline static T* TESForm::LookupByID(FormID a_formID)
	{
		auto form = LookupByID(a_formID);
		return (form && form->formType == static_cast<FormType>(T::kTypeID)) ? static_cast<T*>(form) : 0;
	}


	template <class T>
	inline static T* TESForm::LookupByEditorID(const std::string_view& a_editorID)
	{
		auto form = LookupByEditorID(a_editorID);
		return (form && form->formType == static_cast<FormType>(T::kTypeID)) ? static_cast<T*>(form) : 0;
	}


	template <class First, class... Rest>
	inline bool TESForm::Is(First a_first, Rest... a_rest) const
	{
		return Is(a_first) || Is(a_rest...);
	}


	template <class First, class... Rest>
	inline bool TESForm::IsNot(First a_first, Rest... a_rest) const
	{
		return IsNot(a_first) && IsNot(a_rest...);
	}
}
