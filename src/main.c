#include "app/app.h"
#include "constants.h"

int main(int argc, char* argv[]) {
    App app;
    init_constants();

    printf("RENDER SCALE: %d\n", RENDER_SCALE);

    if (app_init(&app) == 1) {
        return 1;
    }

    app_run(&app);

    return 0;
}
