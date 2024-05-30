#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
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

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	const sf::VideoMode& vm = stateData->gfxSettings->resolution;

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(38.4f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(7.3f, vm), gui::p2pY(3.2f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 240), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(20, 20, 20, 0), sf::Color(150, 150, 150, 0)
	);

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(53.4f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(7.3f, vm), gui::p2pY(3.2f, vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 240), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(20, 20, 20, 0), sf::Color(150, 150, 150, 0)
	);

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownList["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(22.f, vm), gui::p2pY(10.f, vm),
		gui::p2pX(14.5f, vm), gui::p2pY(6.5f, vm),
		font, 
		modes_str.data(), modes_str.size()
	);
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(100.f, 70.f));

	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialising \n\n"
	);
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initBackground();
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownList.begin();
	for (it2 = this->dropDownList.begin(); it2 != this->dropDownList.end(); ++it2)
	{
		delete it2->second;
	}
}
// Accessors

// Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/* Update all the gui elements in the state and handles their functionality.*/

	// Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// Button functionality
	// Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	// Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST REMOVE LATER
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownList["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

	// Dropdown lists
	for (auto& it : this->dropDownList)
	{
		it.second->update(this->mousePosWindow, dt);
	}

	// Dropdown lists functionality

}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownList)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	// REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setFillColor(sf::Color::Black);
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(16);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
