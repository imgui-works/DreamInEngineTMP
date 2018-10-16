#include <ResourceManager.h>

#include <GLFWEnvironment.h>

#include <scenes/SceneManager.h>

//#define SCREEN_WIDTH 1920
//#define SCREEN_HEIGHT 1080

// TODO: Animation Component/System &how to listen/update animation component regarding the "State" of the object
// TODO: Need of a State Component along with the Animation component ?
//Another alternative would be to have the entity dispatch an event to its components when its state changes.
//Animation would listen to this event and update its animation accordingly.
//This eliminates the dependencies, although you could argue that the dependent version is a more transparent design

#include <utils/filesystem.h>

class Project
{
public:
	std::string name;
	bool is_dirty = false;
};

class ProjectService
{
private:
	Project * m_project;
public:
	ProjectService(Project* project) : m_project(project)
	{
	}

	// Load EXISTING project
	bool LoadProject()
	{
		if (FolderExists(m_project->name))
		{
			// 1. Load Project shaders
			// TODO: Create a LoadResources("project_name", "resource_type")
			for (auto &shader_path : GetFilePathsFromDirectory(m_project->name + "\\resources\\shaders"))
			{
				/*ResourceManager::LoadShader(shader_path.c_str(), );*/
			}

			// 2. Load Project Textures


			// 3. Load Project Scenes

		}
	}

	// Create NEW project on disk
	bool CreateProject();


};

class Engine
{
public:
	void Start()
	{
		//GLFWEnvironment* m_glfw_environment = new GLFWEnvironment("DreamIn Engine", 1920, 1080, GL_FALSE);
		GLFWEnvironment* m_glfw_environment = new GLFWEnvironment(false);
		m_glfw_environment->init();

		// TODO: Move all GL/GLEW options/parameters to a GLEWEnvironment/GLEWContext class
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			throw std::runtime_error("glewInit failed");
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_SMOOTH);

		// Load shaders & count
		unsigned int shader_count = ResourceManager::LoadShaders("projects\\test\\resources\\shaders");
		std::cout << "Shaders Loaded: " << shader_count << std::endl;

		// Load textures & count
		unsigned int texture_count = ResourceManager::LoadTextures("projects\\test\\resources\\textures");
		std::cout << "Textures Loaded: " << texture_count << std::endl;

		SceneManager* sm = new SceneManager(m_glfw_environment);

		// Create a new Scene and add it to the Scene Manager
		sm->createScene("Aloha");

		// Select a scene to be marked as active
		sm->select_scene("Aloha");

		sm->start();

		delete sm; sm = nullptr;
	}
};

int main() {
	Engine *DreamInEngine = new Engine();
	DreamInEngine->Start();

	delete DreamInEngine;DreamInEngine = nullptr;

	return (int)DreamInEngine;
}
