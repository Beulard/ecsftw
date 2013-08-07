#ifndef GAME_HPP
#define GAME_HPP
#include "Output.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <map>
#include "Wash.hpp"
#include "vec2.hpp"

class InputManager;
class System;
class Game
{
	public:
		Game();
		~Game();

		bool Init();
		void Run();
		void Exit();

		//GLFWwindow* GetWindow() const;
		InputManager* GetInputManager() const;

		void AddSystem( const std::string& name, System* s );
		System* GetSystem( const std::string& name );
		std::map< wash, System* >& GetSystems();

	private:
		GLFWwindow* window;
		InputManager* inputs;
		vec2ui windowSize;
};

#endif // GAME_HPP
