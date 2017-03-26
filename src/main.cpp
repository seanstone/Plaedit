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

	shader->Shader::bind();
	shader->setParameter("tileStrobe", vec2(0.1f, 0.1f));
	shader->setParameter("projection", mat4(0.1, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 1));
	shader->Shader::unbind();
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

void MainWindow::update()
{
	// if(getKeyState(Key::Esc) == true)
	// 	exit(0);

	vec2 mousePos = getMousePos();
	if(getMouseState(Button::ButtonLeft) == true)
	{
	}
}

int main()
{
	MainWindow window;
	window.startLoop();
	window.terminate();

	return 0;
}
