#include "MainWindow.hpp"


MainWindow::MainWindow(QWindow *parent)
        : QWindow(parent),
        renderer(Renderer()){
    setTitle("VulkanDemo");
    //setIcon(QIcon(":/VulkanDemo/app.ico"));
    //QWindow::vulkanInstance()->create();
    setSurfaceType(VulkanSurface);
	renderer.setSurface(
			surfaceForWindow(*this, renderer.instance));
}

void MainWindow::showEvent(QShowEvent *show_event) {
    renderThread = std::jthread([&]{renderer.run();});
}

void MainWindow::closeEvent(QCloseEvent *close_event) {
    renderer.window_should_close = true;
}
