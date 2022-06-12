#include "MainWindow.h"

#include <iostream>

MainWindow::MainWindow(QWindow *parent)
        : QWindow(parent),
        renderer(Renderer()){
    setTitle("VulkanDemo");
    //setIcon(QIcon(":/VulkanDemo/app.ico"));
    //QWindow::vulkanInstance()->create();
    setSurfaceType(VulkanSurface);
    std::cout << this->surfaceType() << '\n';
}

void MainWindow::showEvent(QShowEvent *show_event) {
    renderThread = std::jthread([&]{renderer.run();});
}

void MainWindow::closeEvent(QCloseEvent *close_event) {
    renderer.window_should_close = true;
}
