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

	int width, height;

protected:
	TileShader* shader;
};

MainWindow::MainWindow()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);
	createWindow(width, width, "PulsarEngine Example");

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

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	glEnable(GL_MULTISAMPLE);

	glEnable(GL_FRAMEBUFFER_SRGB);
}

MainWindow::~MainWindow()
{
}

void MainWindow::render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->render();
}

float zoom = 0.1;
vec3 offset = vec3(-5, -5, 0);

void MainWindow::update()
{
	shader->Shader::bind();
	mat4 projection = scale(vec3(zoom)) * scale(vec3(1, -1, 1)) * translate(offset);
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
	switch (event->type)
	{
		case SDL_MOUSEWHEEL:
		{
			printf("wheel: %d, %d\r\n", event->wheel.x, event->wheel.y);
			float newzoom = zoom * (1 + event->wheel.y * .1);
			if (newzoom > 0.01 && newzoom < 0.2)
			{
				zoom = newzoom;
				printf("zoom: %f\r\n", zoom);
			}
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if (event->button.button == SDL_BUTTON_LEFT)
			{
				printf("left: %d, %d\r\n", event->button.x, event->button.y);
			}
			else if (event->button.button == SDL_BUTTON_RIGHT)
			{
				printf("right: %d, %d\r\n", event->button.x, event->button.y);
				float dx = (1 - 2 * (float)event->button.x / width) / zoom;
				float dy = (1 - 2 * (float)event->button.y / height) / zoom;
				offset += 0.5f * vec3(dx, dy, 0);
				printf("pan: %f, %f\r\n", dx, dy);
			}
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
