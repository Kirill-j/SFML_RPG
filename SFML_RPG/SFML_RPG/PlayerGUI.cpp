#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(2.f, this->vm);
	float height = gui::p2pY(4.f, this->vm);
	float x = gui::p2pX(1.6f, this->vm);
	float y = gui::p2pY(3.6f, this->vm);;
		  
	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setOutlineThickness(2.f);
	this->levelBarBack.setOutlineColor(sf::Color::White);
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 100));
	this->levelBarText.setFillColor(sf::Color::White);
	this->levelBarText.setPosition(
		x + gui::p2pX(0.7f, this->vm),
		y
	);
}

void PlayerGUI::initEXPBar()
{
	float width = gui::p2pX(14.6, this->vm);;
	float height = gui::p2pY(2.f, this->vm);;
	float x = gui::p2pX(1.6f, this->vm);
	float y = gui::p2pX(7.f, this->vm);

	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setOutlineThickness(1.f);
	this->expBarBack.setOutlineColor(sf::Color::White);
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setFillColor(sf::Color(250, 250, 20, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 170));
	this->expBarText.setFillColor(sf::Color::White);
	this->expBarText.setPosition(
		this->expBarBack.getGlobalBounds().width / 2.f - this->expBarText.getGlobalBounds().width,
		y
	);
}

void PlayerGUI::initHpBar()
{
	float width = gui::p2pX(22.f, this->vm);
	float height = gui::p2pY(2.6f, this->vm);
	float x = gui::p2pX(1.6f, this->vm);
	float y = gui::p2pY(9.f, this->vm);

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setOutlineThickness(1.f);
	this->hpBarBack.setOutlineColor(sf::Color::White);
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 140));
	this->hpBarText.setFillColor(sf::Color::White);
	this->hpBarText.setPosition(
		this->hpBarBack.getGlobalBounds().width / 2.f  + gui::p2pX(0.07f, this->vm),
		y
	);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initEXPBar();
	this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{

}

// Functions
void PlayerGUI::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateEXPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarInner.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
			this->hpBarInner.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::update(const float& dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{

	this->renderLevelBar(target);
	this->renderEXPBar(target);
	this->renderHpBar(target);
}
