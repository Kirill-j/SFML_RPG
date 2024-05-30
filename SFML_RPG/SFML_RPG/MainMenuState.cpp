#include "stdafx.h"
#include "MainMenuState.h"

// Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/main_menu_background.png"))
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initButtons()
{
	const sf::VideoMode& vm = stateData->gfxSettings->resolution;

	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(7.3f, vm), gui::p2pX(19.5f, vm),
		gui::p2pX(18.3f, vm), gui::p2pY(9.7f, vm),
		&this->font, "New Game", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 240), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(20, 20, 20, 0), sf::Color(150, 150, 150, 0)
		);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(7.3f, vm), gui::p2pY(32.5f, vm),
		gui::p2pX(18.3f, vm), gui::p2pY(9.7f, vm),
		&this->font, "Settings", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 240), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(20, 20, 20, 0), sf::Color(150, 150, 150, 0)
	);

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(7.3f, vm), gui::p2pY(42.9f, vm),
		gui::p2pX(18.3f, vm), gui::p2pY(9.7f, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 240), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(20, 20, 20, 0), sf::Color(150, 150, 150, 0)
	);

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(7.3f, vm), gui::p2pY(52.f, vm),
		gui::p2pX(18.3f, vm), gui::p2pY(9.7f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 240), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(20, 20, 20, 0), sf::Color(150, 150, 150, 0)
	);
}


MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initBackground();
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::updateButtons()
{
	/* Update all the buttons in the state and handles their functionality.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	// Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	// Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	// REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setFillColor(sf::Color::Black);
	mouseText.setPosition(this->mousePosView.x , this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(16);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}