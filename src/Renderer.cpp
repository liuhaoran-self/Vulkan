#include "Renderer.h"

#include <iostream>

Renderer::Renderer() {
    //Init
    currentFps = 0;
    surface = nullptr;
    lastTime = time(nullptr);
    window_should_close = false;

    //Create vulkan instance
    try {
        const auto app_info = new vk::ApplicationInfo(
                "VulkanDemo", VK_MAKE_API_VERSION(0, 1, 0, 0),
                "No Engine", VK_MAKE_API_VERSION(0, 1, 3, 0),
                VK_MAKE_API_VERSION(0, 1, 3, 0)
        );
        const auto layers = getRequiredLayers();
        const auto extensions = getRequiredExtensions();
        const auto create_info = vk::InstanceCreateInfo(
                {}, app_info,
                static_cast<uint32_t>(layers.size()),
                layers.data(),
                static_cast<uint32_t>(extensions.size()),
                extensions.data()
        );
        instance = vk::createInstance(create_info);
    }
    catch (std::exception &e) {
        std::cout << e.what() << '\n';
    }
    dld = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

    //Pick physical device
    const std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();
    for (const auto &device: devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }
    if (physicalDevice == vk::PhysicalDevice(nullptr)) {
        throw std::runtime_error("ERR_NO_SUITABLE_DEVICE_DETECTED");
    }
}

Renderer::~Renderer() {
    instance.destroy(nullptr);
}


bool Renderer::isDeviceSuitable(const vk::PhysicalDevice device) {
    auto feature = device.getFeatures();
    auto properties = device.getProperties();
    return properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu
        && feature.shaderInt64;
}

std::vector<const char *> Renderer::getRequiredLayers() {
    auto layers = VALIDATION_LAYERS;

    int32_t count = 0;
    std::vector supportedLayers = vk::enumerateInstanceLayerProperties();

    for (const auto& supportedLayer:supportedLayers) {
        for (const auto& layer : layers) {
            if (strcmp(layer, supportedLayer.layerName.data()) == 0){
                ++count;
            }
        }
    }
    if (count!=layers.size())throw std::runtime_error("ERR_LAYER_NOT_SUPPORTED");
    return layers;
}

std::vector<const char *> Renderer::getRequiredExtensions() {
    auto extensions = std::vector<const char *>{
            "VK_KHR_surface",
    };

    int32_t count = 0;
    std::vector supportedExtensions = vk::enumerateInstanceExtensionProperties();

    for (const auto& supportedExtension:supportedExtensions) {
        for (const auto& extension : extensions) {
            if (strcmp(extension,supportedExtension.extensionName.data())==0){
                ++count;
            }
        }
    }
    if (count!=extensions.size())throw std::runtime_error("ERR_EXTENSION_NOT_SUPPORTED");
    return extensions;
}

void Renderer::mainLoop() {
    while (!window_should_close) {
        //Calculate fps
        const int64_t current_time = time(nullptr);
        if (current_time - lastTime == 0) {
            currentFps++;
        } else {
            std::cout << surface << "Current framerate is"
                      << currentFps << '\n';
            currentFps = 0;
        }
        lastTime = current_time;

    }
}

void Renderer::run() {
    try {
        mainLoop();
    }
    catch (std::exception &e) {
        std::cout << e.what() << '\n';
    }
}



