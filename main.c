#include "DBus.h"

int main(int argc, char* argv[]) {
    DBus tp;
    DBusCreate(&tp);
    int rv = DBusRun(&tp, argc, argv);
    DBusDestroy(&tp);
    return rv;
}
