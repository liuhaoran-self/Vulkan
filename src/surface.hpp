//
// Created by liuha on 2022/6/14.
// Important: always include this before vulkan.hpp
//

#pragma once

#include <QWindow>
#include <iostream>

#if defined(WIN32)

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.hpp>
#undef VK_USE_PLATFORM_WIN32_KHR
#include <windows.h>

vk::SurfaceKHR surfaceForWindow(QWindow& window, vk::Instance& instance){
	auto hwnd =  reinterpret_cast<HWND>(window.winId());
	auto hinstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
	std::cout << hwnd << ' ' << hinstance << '\n';
	vk::Win32SurfaceCreateInfoKHR createInfo;
	try {
		createInfo = vk::Win32SurfaceCreateInfoKHR({},hinstance,hwnd);
	} catch (std::exception &e) {
		std::cout << e.what() << '\n';
	}

	return instance.createWin32SurfaceKHR(createInfo);
}
#endif