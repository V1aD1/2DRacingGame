#include "include/PhysicsComponent.h"
#include "include/Entity.h"
#include "include/MathCommon.h"


const float PhysicsComponent::c_length = 40.0f;
const float PhysicsComponent::c_height = 10.0f;

const float PhysicsComponent::c_rotationSpeed = 180.0f;
const float PhysicsComponent::c_acceleration = 0.25f;
const float PhysicsComponent::c_brakeForce = 0.1f;
const float PhysicsComponent::c_frictionForce = 0.1f;
const float PhysicsComponent::c_dbg_slideSpeed = 150.0f;
const float PhysicsComponent::c_maxMomentum = 0.3f;

PhysicsComponent::PhysicsComponent()
{
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(Entity entity, float dtMilli)
{
	ApplyFriction(dtMilli);

	if (MathCommon::GetMagnitude(newState.momentum) > c_maxMomentum)
		newState.momentum = MathCommon::ChangeLength(newState.momentum, c_maxMomentum);

	//this calculation MUST ONLY happen in Update() to enusre
	//position isn't getting updated multiple times
	newState.SetPosition(newState.GetPosition() + newState.momentum * dtMilli);

	//update to new state only if NO collision occured
	if (!CollisionDetected(newState))
		currState.UpdateToNewState(newState);


	else {
		//if collision occurs then halt all momentum on the car
		currState.momentum = sf::Vector2f(0.0f, 0.0f);
		newState.UpdateToNewState(currState);
	}
}

///NOTE: function should only be called after computing 
///final position of newState
bool PhysicsComponent::CollisionDetected(const CarState& state) {
	//check every static object for a collision
	//using point triangle test method
	for (auto object : G_STATICOBJECTS) {
		std::array<sf::Vector2f, 4> objCorners = (*object).GetWorldCorners();

		for (auto &carCorner : state.GetWorldCorners()) {

			bool collision = true;

			for (size_t i = 0; i < objCorners.size(); i++) {

				//this operation must be performed in this order!!
				float check = MathCommon::CrossProduct(objCorners[i] - objCorners[(i + 1) % objCorners.size()], objCorners[i] - carCorner);

				if (check < 0.0f) {
					collision = false;
					break;
				}
				//todo handle check == 0
			}

			if (collision)
				return true;
		}
	}

	return false;
}

void PhysicsComponent::Accelerate(float dtTimeMilli, bool forward)
{
	if (forward)
		newState.momentum += newState.forwardDir * c_acceleration * (dtTimeMilli / 1000.0f);
	else
		newState.momentum += -(newState.forwardDir * c_acceleration * (dtTimeMilli / 1000.0f));
}

void PhysicsComponent::Brake(float dtTimeMilli)
{
	ApplySlowDownForce(c_brakeForce, dtTimeMilli);
}

void PhysicsComponent::DBG_Slide(const sf::Vector2f& dir, float dtMilli)
{
	//halting all movement on the car
	newState.momentum = sf::Vector2f(0.0f, 0.0f);
	currState.momentum = sf::Vector2f(0.0f, 0.0f);

	//placing car to exact position
	currState.SetPosition(currState.GetPosition() + dir * dtMilli / 1000.0f * c_dbg_slideSpeed);
	newState.SetPosition(currState.GetPosition());
}

void PhysicsComponent::ApplyFriction(float dtTimeMilli)
{
	ApplySlowDownForce(c_frictionForce, dtTimeMilli);
}

void PhysicsComponent::ApplySlowDownForce(float forceMag, float dtTimeMilli)
{
	sf::Vector2f momentumDir = MathCommon::Normalize(newState.momentum);
	sf::Vector2f stoppingForceToApply = MathCommon::Normalize(newState.momentum) * forceMag * (dtTimeMilli / 1000.0f);

	float momentumMag = MathCommon::GetMagnitude(newState.momentum);
	float stoppingForceMag = MathCommon::GetMagnitude(stoppingForceToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (momentumMag > stoppingForceMag)
		newState.momentum -= stoppingForceToApply;
	else
		newState.momentum = sf::Vector2f(0.0f, 0.0f);
}

void PhysicsComponent::Rotate(Entity& entity, float dtTimeMilli, bool left)
{
	int direction = left ? -1 : 1;

	float rotAmount = direction * c_rotationSpeed * (dtTimeMilli / 1000.0f);

	entity.Rotate(rotAmount);

	m_newState.forwardDir = sf::Vector2f(std::cos(m_newState.GetRotationInRadians()), std::sin(m_newState.GetRotationInRadians()));
}


