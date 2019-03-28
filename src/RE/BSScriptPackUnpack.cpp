#include "RE/BSScriptPackUnpack.h"

#include "RE/BSScriptClass.h"  // BSScriptClass
#include "RE/BSScriptObjectBindPolicy.h"  // ObjectBindPolicy
#include "RE/BSScriptObject.h"  // BSScriptObject
#include "RE/BSScriptVariable.h"  // BSScriptVariable
#include "RE/IObjectHandlePolicy.h"  // IObjectHandlePolicy
#include "RE/VirtualMachine.h"  // Internal::VirtualMachine


namespace RE
{
	namespace BSScript
	{
		VMTypeID GetTypeIDFromFormTypeID(UInt32 a_typeID)
		{
			auto vm = Internal::VirtualMachine::GetSingleton();
			BSTSmartPointer<BSScriptClass> classPtr;
			if (vm->GetScriptClassByTypeID(a_typeID, classPtr)) {
				return classPtr->GetTypeID();
			} else {
				_FATALERROR("[FATAL ERROR] Failed to get vm type id for class!\n");
				return VMTypeID::kNone;
			}
		}


		void BindID(BSTSmartPointer<BSScriptObject>& a_objectPtr, const void* a_srcData, UInt32 a_typeID)
		{
			auto vm = Internal::VirtualMachine::GetSingleton();
			UInt32 id = 0;
			BSTSmartPointer<BSScriptClass> classPtr(a_objectPtr->GetClass());
			if (vm->GetFormTypeID(classPtr->GetName(), id)) {
				auto handlePolicy = vm->GetHandlePolicyBS();
				VMHandle handle = handlePolicy->Create(a_typeID, a_srcData);

				if (handlePolicy->IsType(id, handle) || handle == handlePolicy->GetInvalidHandle()) {
					vm->GetObjectBindPolicyBS()->BindObject(a_objectPtr, handle);
				}
			}
		}


		void PackHandle(BSScriptVariable* a_dst, const void* a_src, UInt32 a_typeID)
		{
			a_dst->SetNone();

			if (!a_src) {
				return;
			}

			auto vm = Internal::VirtualMachine::GetSingleton();
			BSTSmartPointer<BSScriptClass> classPtr;
			vm->GetScriptClassByTypeID(a_typeID, classPtr);
			if (!classPtr) {
				return;
			}

			auto handlePolicy = vm->GetHandlePolicyBS();
			VMHandle handle = handlePolicy->Create(a_typeID, a_src);

			BSTSmartPointer<BSScriptObject> objectPtr;
			if (!vm->ResolveScriptObject(handle, classPtr->GetName(), objectPtr)) {
				// when cannot be resolved, then create new objectPtr
				if (vm->CreateScriptObject(classPtr->GetName(), objectPtr) && objectPtr) {
					// create handle and bind it to the new objectPtr
					BindID(objectPtr, a_src, a_typeID);
				}
			}

			if (objectPtr) {
				a_dst->SetData<BSScriptObject*>(objectPtr.get());
			}
		}


		void* UnpackHandle(const BSScriptVariable* a_src, UInt32 a_typeID)
		{
			const BSScriptObject* object = a_src->GetObject();
			return object ? object->Resolve(a_typeID) : 0;
		}
	}
}