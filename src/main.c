#include "app/app.h"

int main(int argc, char* argv[]) {
    App app;

    if (app_init(&app) == 1) {
        return 1;
    }

    app_run(&app);

    return 0;
}
