#pragma once
#include <vector>
#include <functional>

namespace kve {
	template <typename... Args>
	class Event;

	template <typename... Args>
	class EventHandler {
		using EventFunction = std::function<void(Args...)>;

	private:
		EventFunction function;

		template <typename... Args>
		friend class Event;

	public:
		EventHandler() {}

		EventHandler(EventFunction function) {
			this->function = function;
		}
	};

	template <typename... Args>
	class Event {
	private:
		std::vector<EventHandler<Args...>*> handlers;

	public:
		EventHandler<Args...>* operator+=(std::function<void(Args...)> function) {
			handlers.push_back(new EventHandler<Args...>(function));
			return handlers.back();
		}

		void operator-=(EventHandler<Args...>* handler) {
			handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
			delete handler;
		}

		void invoke(Args... args) {
			for (auto& handler : handlers) {
				handler->function(args...);
			}
		}

		~Event() {
			for (auto& handler : handlers) {
				delete handler;
			}

			handlers.clear();
		}
	};
}