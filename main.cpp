#include "engine.h"

int main() {
    Logger::Log::InitLogFile();

    Sigma::Engine engine("Game", 600, 800);
    engine.run();
    return 0;
}