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
	/*Matrix<char, int> matrix, _matrix;

	matrix.SetValue('a', 'a', 10);
	matrix.SetValue('a', 'b', 1);
	matrix.SetValue('a', 'c', 2);

	_matrix.SetValue('a', 'a', 3);
	_matrix.SetValue('a', 'b', 1);
	_matrix.SetValue('a', 'c', 2);

	_matrix.SetValue('b', 'a', 5);
	_matrix.SetValue('b', 'b', 6);
	_matrix.SetValue('b', 'c', 7);

	_matrix.SetValue('c', 'a', 8);
	_matrix.SetValue('c', 'b', 9);
	_matrix.SetValue('c', 'c', 10);

	matrix = matrix * _matrix;*/

	m_chain.m_probabilityMatrix.SetValue('a', 'a', 1.0f);
	m_chain.m_probabilityMatrix.SetValue('a', 'b', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('a', 'c', 0.0f);

	m_chain.m_probabilityMatrix.SetValue('b', 'a', 0.3f);
	m_chain.m_probabilityMatrix.SetValue('b', 'b', 0.4f);
	m_chain.m_probabilityMatrix.SetValue('b', 'c', 0.3f);

	m_chain.m_probabilityMatrix.SetValue('c', 'a', 0.1f);
	m_chain.m_probabilityMatrix.SetValue('c', 'b', 0.3f);
	m_chain.m_probabilityMatrix.SetValue('c', 'c', 0.6f);

	m_chain.m_state['a'] = 10;
	m_chain.m_state['b'] = 70;
	m_chain.m_state['c'] = 20;

	m_chain.SetPosition();
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				m_chain.Increment(1);
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

	m_window.draw(m_chain);

	m_window.display();
}
