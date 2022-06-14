#pragma once

#include "debug.hpp"

#include <vulkan/vulkan.hpp>
#include <iostream>
#include <thread>

class Renderer {
    vk::SurfaceKHR surface;
    vk::PhysicalDevice physicalDevice;
    vk::DispatchLoaderDynamic dld;
    int64_t lastTime;
    int32_t currentFps;

    static bool isDeviceSuitable(vk::PhysicalDevice device);

    static std::vector<const char *> getRequiredLayers();

    static std::vector<const char *> getRequiredExtensions();

    void mainLoop();

    PFN_vkDebugReportCallbackEXT debugCallback;

public:
    explicit Renderer ();

    ~Renderer();

    void run();

    inline void setSurface(vk::SurfaceKHR s);

	vk::Instance instance;
	bool window_should_close;
};

void Renderer::setSurface(vk::SurfaceKHR s) {
    surface = s;
}
//Todo:
// Use windows native API to create a vulkan surface
// Debug Callback function
