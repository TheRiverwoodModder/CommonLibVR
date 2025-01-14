#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSFaceGenAnimationData;
	class NiNode;

	class BSFaceGenNiNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFaceGenNiNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFaceGenNiNode;

		~BSFaceGenNiNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                                                 // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                        // 17
		void          UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2C

		// add
		virtual void FixSkinInstances(NiNode* a_skeleton, bool a_arg2);  // 3E

// members
#ifndef SKYRIMVR
		NiMatrix3                         baseRotation;   // 128
		std::uint32_t                     pad14C;         // 14C
		NiPointer<BSFaceGenAnimationData> animationData;  // 150
		float                             lastTime;       // 158
		ActorHandle                       unk15C;         // 15C
		std::uint16_t                     flags;          // 160
		std::uint16_t                     pad162;         // 162
		std::uint32_t                     pad164;         // 164
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSFaceGenNiNode) == 0x168);
#else
		NiMatrix3                         baseRotation;   // 158
		std::uint32_t                     pad17C;         // 17C
		NiPointer<BSFaceGenAnimationData> animationData;  // 178
		float                             lastTime;       // 180
		ActorHandle                       unk184;         // 184
		std::uint16_t                     flags;          // 188
		std::uint16_t                     pad18A;         // 18A
		std::uint32_t                     pad18C;         // 18C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSFaceGenNiNode) == 0x190);
#endif

}
