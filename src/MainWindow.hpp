#pragma once

#include "surface.hpp"

#include "Renderer.hpp"

#include <QVulkanWindow>
#include <QWindow>
#include <QShowEvent>
#include <QCloseEvent>
#include <QVulkanInstance>
#include <thread>

inline void sleep(const int millisecond)
{
	std::this_thread::sleep_for(
		std::chrono::milliseconds(millisecond));
}

class MainWindow final : public QWindow
{
	Q_OBJECT
	Renderer renderer;
	std::jthread renderThread;
public:
	explicit MainWindow(QWindow* parent = nullptr);
	void showEvent(QShowEvent*) override;
	void closeEvent(QCloseEvent*) override;
};