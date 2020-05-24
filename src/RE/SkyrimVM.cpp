#include "RE/SkyrimVM.h"


namespace RE
{
	SkyrimVM* SkyrimVM::GetSingleton()
	{
		REL::Offset<SkyrimVM**> singleton(Offset::SkyrimVM::Singleton);
		return *singleton;
	}


	bool SkyrimVM::QueuePostRenderCall(const BSTSmartPointer<SkyrimScript::DelayFunctor>& a_functor)
	{
		using func_t = decltype(&SkyrimVM::QueuePostRenderCall);
		REL::Offset<func_t> func(Offset::SkyrimVM::QueuePostRenderCall);
		return func(this, a_functor);
	}
}
