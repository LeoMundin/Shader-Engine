#include "TuftEngine.h"

TuftEngine::TuftEngine(unsigned int width, unsigned int height)
{

    _screenWidth = width;
    _screenHeight = height;

    InitialiseGLFW();
    InitialiseGlad();

    // Define Physics Settings to be applied to all scenes
    PhysicsSettings.defaultVelocitySolverNbIterations = 20;
    PhysicsSettings.isSleepingEnabled = false;
    PhysicsSettings.gravity = rp3d::Vector3(0, GRAVITY, 0);

}


// Starts the Game Engine loop initiating lifecycle hooks for the active scene.
void TuftEngine::init() {
    if (_LoadedScenes.empty()) { // Error Checking.
        std::cout << "Engine has no Scenes. Please add a Scene to be played." << std::endl;
        return;
    }
    _currentFrameTime = (float)glfwGetTime();

    // Sets the active scene to be the first in the load order.
    _activeScene = GetScene(_sceneLoadOrder.front());

    Awake();

    while (!glfwWindowShouldClose(Window)) {
        _currentFrameTime = (float)glfwGetTime();
        DeltaTime = _currentFrameTime - _lastFrameTime;

        ProcessInput();
        Update();
        Render();

        _lastFrameTime = _currentFrameTime;
    };
    glfwTerminate();

}


// ------ Scene Lifecycle hooks ------

void TuftEngine::ProcessInput() {
    glfwPollEvents(); // Checks for event updates such as user input, and calls any registered call-back functions
}


void TuftEngine::Awake() {
    _activeScene->Awake();
}

void TuftEngine::Update() {
    _activeScene->Update();
    _activeScene->PhysicSimulation->update(DeltaTime);
}

void TuftEngine::Render() {
    glClearColor(0.388f, 0.588f, 0.684f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _activeScene->Render();

    // Clear depth information and draw UI ontop of 3D elements
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    _activeScene->RenderUI();
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    glfwSwapBuffers(Window);// Swaps the rendered, back buffer, with the front buffer to display rendered content.
}















// ------ GLAD initialization ------

void TuftEngine::AddScene(Scene* scene) {
    scene->Load(this, Physics.createPhysicsWorld(PhysicsSettings));
    _sceneLoadOrder.push(scene->ID);
    _LoadedScenes.insert({ scene->ID, scene });
}

Scene* TuftEngine::GetScene(std::string sceneName) {
    return _LoadedScenes[sceneName];
}

std::string TuftEngine::GetNextSceneID() {
    _sceneLoadOrder.pop();
    return _sceneLoadOrder.front();
}





// ------ GLAD initialization ------

void TuftEngine::InitialiseGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ // Error checking.
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, _screenWidth, _screenHeight);
    DefineGLADSettings();

}

void TuftEngine::DefineGLADSettings() {
    // Depth Testing
    glEnable(GL_DEPTH_TEST); 

    // Alpha Testing.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}



// ------ Window initialization ------

void TuftEngine::InitialiseGLFW() {
    glfwInit(); // Define Correct GLFW Libary settings.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window = glfwCreateWindow(_screenWidth, _screenHeight, "Shader Engine", NULL, NULL);
    if (Window == NULL){ // Error Checking.
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(Window);
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// Hide and capture cursor.

    SetGLFWCallbacks();

}

void TuftEngine::SetGLFWCallbacks() {
    glfwSetFramebufferSizeCallback(Window, OnWindowResize);
    Input = InputSystem(Window);

}

// Updates the render window to match the GLFW Window as its scaled.
void TuftEngine::OnWindowResize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}






