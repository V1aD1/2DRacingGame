#include "include/PhysicsComponent.h"
#include "include/Car.h"
#include "include/MathCommon.h"


PhysicsComponent::PhysicsComponent()
{
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(CarState& currState, CarState& newState, float dtMilli)
{
	newState.ApplyFriction(Car::c_frictionForce, dtMilli);

	if (MathCommon::GetMagnitude(newState.momentum) > Car::c_maxMomentum)
		newState.momentum = MathCommon::ChangeLength(newState.momentum, Car::c_maxMomentum);

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


