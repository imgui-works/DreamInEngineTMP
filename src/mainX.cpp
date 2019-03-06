#define STB_IMAGE_IMPLEMENTATION

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

// Include all GLM core / GLSL features
//#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/glm.hpp>
// Include all GLM extensions
//#include <glm/ext/matrix_projection.hpp>
#include <glm/gtc/matrix_transform.hpp> // perspective, translate, rotate

glm::mat4 transform(glm::vec2 const &Orientation, glm::vec3 const &Translate, glm::vec3 const &Up) {
    glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
    glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
    glm::mat4 Model = glm::mat4(1.0f);
    return Proj * View * Model;
}

class Project
{
public:
	std::string name;
	bool is_dirty = false;
};

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

class Engine
{
public:
	void Start()
	{
		//GLFWEnvironment* m_glfw_environment = new GLFWEnvironment("DreamIn Engine", 1920, 1080, GL_FALSE);
		GLFWEnvironment* m_glfw_environment = new GLFWEnvironment(false);
		m_glfw_environment->init();

		// TODO: Move all GL/GLEW options/parameters to a GLEWEnvironment/GLEWContext class
		//glewExperimental = GL_TRUE;
		//if (glewInit() != GLEW_OK)
		//{
		//	throw std::runtime_error("glewInit failed");
		//}
		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Smoother textures
		glEnable(GL_SMOOTH);

		// Load shaders & count
		unsigned int shader_count = ResourceManager::LoadShaders("..\\assets\\shaders");
		std::cout << "Shaders Loaded: " << shader_count << std::endl;

		// Load textures & count
		unsigned int texture_count = ResourceManager::LoadTextures("..\\assets\\textures");
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

int mainX(int argc, char **argv) {
	auto DreamInEngine = new Engine();
	DreamInEngine->Start();

	delete DreamInEngine; DreamInEngine = nullptr;

	return 0;
}

//class ProjectService
//{
//private:
//    Project * m_project;
//public:
//    ProjectService(Project* project) : m_project(project)
//    {
//    }
//
//    // Load EXISTING project
//    bool LoadProject()
//    {
//        if (FolderExists(m_project->name))
//        {
//            // 1. Load Project shaders
//            // TODO: Create a LoadResources("project_name", "resource_type")
//            for (auto &shader_path : GetFilePathsFromDirectory(m_project->name + "\\assets\\shaders"))
//            {
//                /*ResourceManager::LoadShader(shader_path.c_str(), );*/
//            }
//
//            // 2. Load Project Textures
//
//
//            // 3. Load Project Scenes
//
//        }
//    }
//
//    // Create NEW project on disk
//    bool CreateProject();
//};