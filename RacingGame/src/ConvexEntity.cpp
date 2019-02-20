#include "include/ConvexEntity.h"
#include "include/MathCommon.h"


ConvexEntity::ConvexEntity(): m_graphics(new GraphicsComponent()){}

ConvexEntity::ConvexEntity(sf::Vector2f pos, float rot) : Entity(pos, rot), m_graphics(new GraphicsComponent()) {}

ConvexEntity::ConvexEntity(sf::Vector2f pos, float rot, std::array<sf::Vector2f, 4> localCorners) : Entity(pos, rot), m_localCorners(localCorners), m_graphics(new GraphicsComponent()) {}


ConvexEntity::~ConvexEntity(){}

sf::Shape * const ConvexEntity::GetShape() const
{
	return m_shape;
}

//todo returns COPY of array, maybe should return reference or *?
std::array<sf::Vector2f, 4> ConvexEntity::GetWorldCorners() const
{
	auto worldCorners = std::array<sf::Vector2f, 4>();

	for (int i = 0; i < m_localCorners.size(); i++) {
		(worldCorners)[i] = m_localCorners[i] + m_position;
	}

	return worldCorners;
}

//todo find better way to turn,
//I think corners should be turned always according to entity rotation,
//but now they are decoupled
void ConvexEntity::Rotate(float degrees)
{
	SetRotation(m_rotation + degrees);

	float radsToTurn = MathCommon::DegreesToRadians(degrees);

	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(radsToTurn) - m_localCorners[i].y * std::sin(radsToTurn);
		newPoint.y = m_localCorners[i].x * std::sin(radsToTurn) + m_localCorners[i].y * std::cos(radsToTurn);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}
}

void ConvexEntity::SetShape(sf::Shape * newShape)
{
	m_shape = newShape;
}

void ConvexEntity::SetCorners(const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied)
{
	m_localCorners = cornersWithoutRotationApplied;

	//orienting corners according to Entity rotation
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(m_rotationInRad) - m_localCorners[i].y * std::sin(m_rotationInRad);
		newPoint.y = m_localCorners[i].x * std::sin(m_rotationInRad) + m_localCorners[i].y * std::cos(m_rotationInRad);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}
}

void ConvexEntity::SetPosition(sf::Vector2f newPos)
{
	m_position = newPos;
	m_shape->setPosition(newPos);
}

void ConvexEntity::Update(sf::RenderWindow & window)
{
	m_graphics->Update(*this, window);
}

void ConvexEntity::SetRotation(float newRotInDegrees)
{
	Entity::SetRotation(newRotInDegrees);

	if (m_shape) {
		m_shape->setRotation(m_rotation);
	}
}