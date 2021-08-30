#pragma once
#include "Engine.h"
#include <string>

namespace nc
{
	class AudioComponent : public Component
	{
	public:
		virtual void Update() override;

		void Play();
		void Stop();

		//write read
		bool Write(const rapidjson::Value& value) const;
		bool Read(const rapidjson::Value& value);

	public:
		std::string soundName;
		float volume = 1;
		float pitch = 1;
		bool loop = false;
		bool playOnAwake = false;

	private:
		AudioChannel channel;
		bool played = false;
	};
}
