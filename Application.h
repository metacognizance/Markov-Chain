#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include "Chain.h"
#include <iostream>

class Application
{
public:
	Application();
	~Application();
	
private:
	void run();

	void Initialize();

	void HandleEvents();

	void Update(sf::Time & p_deltaTime);

	void Render();

	bool m_running, m_active;

	sf::RenderWindow m_window;
};