#include "stdafx.h"
#include "Player.h"


// Initializer function
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}

// Const / Desctr
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);
	this->setSize(3, 3);

	this->createHitboxComponent(this->sprite, 18.f, 5.f, 33.f, 88.f);
	this->createMovementComponent(200.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 12.f, 0, 0, 4, 0, 20, 34);
	this->animationComponent->addAnimation("WALK", 10.f, 0, 1, 5, 1, 20, 34);
	this->animationComponent->addAnimation("ATTACK", 10.f, 0, 2, 2, 2, 46, 36);
}

Player::~Player()
{

}

// Accessors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

// Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		// Set origin depending on direction
		if (this->sprite.getScale().x > 0.f) // Facing left
		{
			this->sprite.setOrigin(15.f, 0.f);
		}
		else// Facing right
		{
			this->sprite.setOrigin(38.f, 0.f);
		}

		// Animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f) // Facing left
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else// Facing right
			{
				this->sprite.setOrigin(23.f, 0.f);
			}
		}
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(23.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
