#include "Application.h"

Application::Application(int argc, char **argv)
        : QApplication(argc, argv) {
}

int Application::exec() {
    return QApplication::exec();
}
