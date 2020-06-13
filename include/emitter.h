#pragma once

#include <functional>
#include <type_traits>
#include <string>
#include <cassert>

namespace Connector {

template<typename>
struct FnTraits {};

template<class T, class U>
struct FnTraits<U T::*>
{
	using member_type = U;
};

template<typename Sender, typename SenderFn, typename Target, typename TargetFn>
class Emitter
{
public:
	Emitter() = delete;
	constexpr Emitter(
		  Sender sender
		, SenderFn sFn
		, Target target
		, TargetFn tFn
		)
		: m_sender(sender)
		, m_senderCallback(sFn)
		, m_target(target)
		, m_targetCallback(tFn)
	{
//		static_assert(std::is_pointer_v<sender>, "Sender param must be a pointer to calling object");
//		static_assert(std::is_function<typename FnTraits<decltype(sFn)>::member_type>::value,
//					  "SenderFn param must be a member function of U type");
	}
	Emitter(const Emitter &) = delete;
	Emitter &
	operator=(const Emitter &) = delete;
	Emitter(Emitter &&) noexcept = default;
	Emitter &
	operator=(Emitter &&) noexcept = default;

	template<typename ... Args>
	constexpr void
	emit(Args &&... args) {
		if (!m_sender)
			return assert(false);
		std::invoke(m_senderCallback, m_sender, args...);
		std::invoke(m_targetCallback, m_target, args...);
	}

private:
	Sender   m_sender        ;
	SenderFn m_senderCallback;
	Target   m_target        ;
	TargetFn m_targetCallback;
};

template<typename Sender, typename SenderFn, typename Target, typename TargetFn>
[[nodiscard]] constexpr Emitter<Sender, SenderFn, Target, TargetFn>
connect(Sender sender, SenderFn senderFn, Target target, TargetFn targetFn) {
	return Emitter(sender, senderFn, target, targetFn);
}

}
