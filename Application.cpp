#include "Application.h"

int main()
{
	Application application;
	return 0;
}

Application::Application() : 
	m_window(sf::RenderWindow(sf::VideoMode(640, 640), "Application", sf::Style::Close)),
	m_running(true),
	m_active(true)
{
	run();
}

Application::~Application()
{

}

void Application::run()
{
	Initialize();

	sf::Clock dt;
	sf::Time deltaTime;
	sf::Time updateTime = sf::seconds(1.f/60.f);

	while(m_running)
	{
		deltaTime += dt.getElapsedTime();
		dt.restart();

		HandleEvents();
		Render();
		while (deltaTime >= updateTime && m_active)
		{
			Update(deltaTime);
			deltaTime -= updateTime;
		}
	}
}

void Application::Initialize()
{
	Matrix<char, int> matrix;

	matrix.SetValue('a', 'a', 0);
	matrix.SetValue('a', 'b', 1);

	std::cout << matrix.GetValue('a', 'a') << "\n";
	std::cout << matrix.GetValue('a', 'b') << "\n";
}

void Application::HandleEvents()
{
	sf::Event event;

	while(m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_running = false;
			}
		}
	}
}

void Application::Update(sf::Time & p_deltaTime)
{

}

void Application::Render()
{
	m_window.clear(sf::Color(46, 46, 46));

	m_window.display();
}
