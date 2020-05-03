#include "DBus.h"

int main(int argc, const char* argv[]) {
    DBus tp;
    DBusCreate(&tp);
    DBusRun(&tp, argc, argv);
    DBusDestroy(&tp);
    return 0;
}
