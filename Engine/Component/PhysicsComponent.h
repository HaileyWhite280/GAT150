#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace nc
{
	class PhysicsComponent : public Component
	{
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<PhysicsComponent>(*this); }

		void Update() override;
		virtual void ApplyForce(const Vector2& force) { acceleration += force; }

	public:
		Vector2 velocity;
		Vector2 force;
		Vector2 acceleration;
		float drag = 1;

		// Inherited via Serializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};
}
