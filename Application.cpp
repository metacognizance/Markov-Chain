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

	m_chain.ptr_window = &m_window;

	m_chain.m_probabilityMatrix.SetValue('f', 'f', 0.9f);
	m_chain.m_probabilityMatrix.SetValue('f', '1', 0.1f);
	m_chain.m_probabilityMatrix.SetValue('f', '2', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('f', '3', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('f', 'p', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('f', 's', 0.0f);

	m_chain.m_probabilityMatrix.SetValue('1', 'f', 0.5f);
	m_chain.m_probabilityMatrix.SetValue('1', '1', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('1', '2', 0.5f);
	m_chain.m_probabilityMatrix.SetValue('1', '3', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('1', 'p', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('1', 's', 0.0f);

	m_chain.m_probabilityMatrix.SetValue('2', 'f', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('2', '1', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('2', '2', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('2', '3', 0.8f);
	m_chain.m_probabilityMatrix.SetValue('2', 'p', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('2', 's', 0.2f);

	m_chain.m_probabilityMatrix.SetValue('3', 'f', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('3', '1', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('3', '2', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('3', '3', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('3', 'p', 0.4f);
	m_chain.m_probabilityMatrix.SetValue('3', 's', 0.6f);

	m_chain.m_probabilityMatrix.SetValue('p', 'f', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('p', '1', 0.2f);
	m_chain.m_probabilityMatrix.SetValue('p', '2', 0.4f);
	m_chain.m_probabilityMatrix.SetValue('p', '3', 0.4f);
	m_chain.m_probabilityMatrix.SetValue('p', 'p', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('p', 's', 0.0f);

	m_chain.m_probabilityMatrix.SetValue('s', 'f', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('s', '1', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('s', '2', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('s', '3', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('s', 'p', 0.0f);
	m_chain.m_probabilityMatrix.SetValue('s', 's', 1.0f);

	m_chain.m_state['f'] = 100;
	m_chain.m_state['1'] = 0;
	m_chain.m_state['2'] = 0;
	m_chain.m_state['3'] = 0;
	m_chain.m_state['p'] = 0;
	m_chain.m_state['s'] = 0;

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
