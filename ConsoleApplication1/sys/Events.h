#pragma once

#include <functional>
#include <list>
#include <algorithm>
#include <utility>
#include <atomic>
#include <mutex>
#include <future>

//Most of this comes from Shmuel Zang's article on a .Net style all native C++
// Event framework https://www.codeproject.com/Articles/1256352/CppEvent-How-to-implement-events-using-standard-cp
// He does some things I found unnecessary at the time of implementation,
// so I'm going to try to simplify it a bit.
//One of the things that he does is keep almost all of the logic in the header file.
// and then uses a namespace to access it. I think I'm going to try to do that as well.
// Not sure if I'll like it or not, but we'll give it a shot.

namespace Events
{
	template <typename... Args> class event_handler
	{
	public:
		typedef std::function<void(Args...)> handler_func_type;
		typedef unsigned int handler_id_type;

		explicit event_handler(const handler_func_type& handlerFunc)
			: m_handlerFunc(handlerFunc)
		{
			m_handlerId = ++m_handlerIdCounter;
		}

		// copy constructor
		event_handler(const event_handler& src)
			: m_handlerFunc(src.m_handlerFunc)
			, m_handlerId(src.m_handlerId)
		{
		}

		// move constructor
		event_handler(event_handler&& src)
			: m_handlerFunc(std::move(src.m_handlerFunc))
			, m_handlerId(src.m_handlerId)
		{
		}

		//RYAN'S NOTE: I don't care for the operators, so I'm going to comment them out for now.
		// copy assignment operator
		//event_handler& operator=(const event_handler& src)
		//{
		//	m_handlerFunc = src.m_handlerFunc;
		//	m_handlerId = src.m_handlerId;

		//	return *this;
		//}

		//RYAN'S NOTE: I don't care for the operators, so I'm going to comment them out for now.
		// move assignment operator
		//event_handler& operator=(event_handler&& src)
		//{
		//	std::swap(m_handlerFunc, src.m_handlerFunc);
		//	m_handlerId = src.m_handlerId;

		//	return *this;
		//}

		// function call operator
		void operator()(Args... params) const
		{
			if (m_handlerFunc)
			{
				m_handlerFunc(params...);
			}
		}

		bool operator==(const event_handler& other) const
		{
			return m_handlerId == other.m_handlerId;
		}

		operator bool() const
		{
			return m_handlerFunc;
		}

		handler_id_type id() const
		{
			return m_handlerId;
		}

	private:
		handler_func_type m_handlerFunc;
		handler_id_type m_handlerId;
		static std::atomic_uint m_handlerIdCounter;
	};

	template <typename... Args> std::atomic_uint event_handler<Args...>::m_handlerIdCounter(0);

	template <typename... Args> class event
	{
	public:
		typedef event_handler<Args...> handler_type;

		event()
		{}

		// copy constructor
		event(const event& src)
		{
			std::lock_guard<std::mutex> lock(src.m_handlersLocker);

			m_handlers = src.m_handlers;
		}

		// move constructor
		event(event&& src)
		{
			std::lock_guard<std::mutex> lock(src.m_handlersLocker);

			m_handlers = std::move(src.m_handlers);
		}

		//RYAN'S NOTE: I don't care for the operators, so I'm going to comment them out for now.
		// copy assignment operator
		//event& operator=(const event& src)
		//{
		//	std::lock_guard<std::mutex> lock(m_handlersLocker);
		//	std::lock_guard<std::mutex> lock2(src.m_handlersLocker);

		//	m_handlers = src.m_handlers;

		//	return *this;
		//}

		//RYAN'S NOTE: I don't care for the operators, so I'm going to comment them out for now.
		// move assignment operator
		//event& operator=(event&& src)
		//{
		//	std::lock_guard<std::mutex> lock(m_handlersLocker);
		//	std::lock_guard<std::mutex> lock2(src.m_handlersLocker);

		//	std::swap(m_handlers, src.m_handlers);

		//	return *this;
		//}

		typename handler_type::handler_id_type add(const handler_type& handler)
		{
			std::lock_guard<std::mutex> lock(m_handlersLocker);

			m_handlers.push_back(handler);

			return handler.id();
		}

		inline typename handler_type::handler_id_type add(
			const typename handler_type::handler_func_type& handler)
		{
			return add(handler_type(handler));
		}

		bool remove(const handler_type& handler)
		{
			std::lock_guard<std::mutex> lock(m_handlersLocker);

			auto it = std::find(  m_handlers.begin()
								, m_handlers.end()
								, handler);

			if (it != m_handlers.end())
			{
				m_handlers.erase(it);
				return true;
			}

			return false;
		}

		bool remove_id(const typename handler_type::handler_id_type& handlerId)
		{
			std::lock_guard<std::mutex> lock(m_handlersLocker);

			auto it = std::find_if(   m_handlers.begin()
									, m_handlers.end()
									, [handlerId](const handler_type& handler) { return handler.id() == handlerId; });
			
			if (it != m_handlers.end())
			{
				m_handlers.erase(it);
				return true;
			}

			return false;
		}

		void call(Args... params) const
		{
			handler_collection_type handlersCopy = get_handlers_copy();

			call_impl(handlersCopy, params...);
		}

		std::future<void> call_async(Args... params) const
		{
			return std::async(std::launch::async
							, [this](Args... asyncParams) { call(asyncParams...); }
							, params...);
		}

		inline void operator()(Args... params) const
		{
			call(params...);
		}

		//RYAN'S NOTE: I don't care for the operators, so I'm going to comment them out for now.
		//inline typename handler_type::handler_id_type operator+=(const handler_type& handler)
		//{
		//	return add(handler);
		//}

		//inline typename handler_type::handler_id_type operator+=(const typename handler_type::handler_func_type& handler)
		//{
		//	return add(handler);
		//}

		//inline bool operator-=(const handler_type& handler)
		//{
		//	return remove(handler);
		//}

	protected:
		typedef std::list<handler_type> handler_collection_type;

		void call_impl(const handler_collection_type& handlers, Args... params) const
		{
			for (const auto& handler : handlers)
			{
				handler(params...);
			}
		}

		handler_collection_type get_handlers_copy() const
		{
			std::lock_guard<std::mutex> lock(m_handlersLocker);

			// Since the function return value is by copy, 
			// before the function returns (and destruct the lock_guard object),
			// it creates a copy of the m_handlers container.

			return m_handlers;
		}

	private:
		handler_collection_type m_handlers;
		mutable std::mutex m_handlersLocker;
	};

} // namespace Events