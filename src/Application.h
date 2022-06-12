#pragma once

#include "MainWindow.h"

#include <QApplication>

class Application final : public QApplication {
public:
    Application(int argc, char **argv);

    static int exec();
};
