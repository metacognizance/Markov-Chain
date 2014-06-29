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
	Matrix<char, int> matrix, _matrix;

	matrix.SetValue('a', 'a', 0);
	matrix.SetValue('a', 'b', 1);
	matrix.SetValue('a', 'c', 2);

	matrix.SetValue('b', 'a', 3);
	matrix.SetValue('b', 'b', 4);
	matrix.SetValue('b', 'c', 5);

	matrix.SetValue('c', 'a', 6);
	matrix.SetValue('c', 'b', 7);
	matrix.SetValue('c', 'c', 8);

	_matrix.SetValue('a', 'a', 0);
	_matrix.SetValue('a', 'b', 1);
	_matrix.SetValue('a', 'c', 2);

	_matrix.SetValue('b', 'a', 3);
	_matrix.SetValue('b', 'b', 4);
	_matrix.SetValue('b', 'c', 5);

	_matrix.SetValue('c', 'a', 6);
	_matrix.SetValue('c', 'b', 7);
	_matrix.SetValue('c', 'c', 8);
	
	matrix = matrix * _matrix;

	for (int j = 0; j < matrix.GetRows().size(); j++)
	{
		for (int i = 0; i < matrix.GetColumns().size(); i++)
		{
			std::cout << matrix.GetValue(matrix.GetRows()[j], matrix.GetColumns()[i]) << " ";
		}
		std::cout << "\n";
	}
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
