#include <PulsarEngine.hpp>
#include <PulsarMesh.hpp>
#include <PulsarShader.hpp>
#include "TileShader.hpp"
using namespace Pulsar;

#include <iostream>
#include <string>
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();
	void render();
	void update();
	void handleEvent(SDL_Event* event);

protected:
	TileShader* shader;
};

MainWindow::MainWindow()
{
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PulsarEngine Example");

	bool result = true;
	shader = new TileShader;
	result &= shader->loadVertexShader("data/shader/tile.vs");
	result &= shader->loadFragmentShader("data/shader/tile.fs");
	result &= shader->compile();
	if(result == false)
	{
		terminate();
		exit(0);
	}
}

MainWindow::~MainWindow()
{
}

void MainWindow::render()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->render();
}

float zoom = 0.1;

void MainWindow::update()
{
	shader->Shader::bind();
	mat4 projection = scale(vec3(zoom)) * scale(vec3(1, -1, 1)) * translate(vec3(-5, -5, 0));
	shader->setParameter("projection", projection);
	shader->Shader::unbind();

	// if(getKeyState(Key::Esc) == true)
	// 	exit(0);

	vec2 mousePos = getMousePos();
	if(getMouseState(Button::ButtonLeft) == true)
	{
	}
}

void MainWindow::handleEvent(SDL_Event* event)
{
	if(event->type == SDL_MOUSEWHEEL)
	{
		printf("wheel: %d, %d\r\n", event->wheel.x, event->wheel.y);
		float newzoom = zoom * (1 + event->wheel.y * .1);
		if (newzoom > 0.001 && newzoom < 0.2)
		{
			zoom = newzoom;
			printf("zoom: %f\r\n", zoom);
		}

	}
}

int main()
{
	MainWindow window;
	window.startLoop();
	window.terminate();

	return 0;
}
