#include "Application.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);
    MainWindow w;
    w.show();
    return Application::exec();
}