//
// Created by marcos on 2/5/20.
//

#ifndef TP1DBUS_DBUS_H
#define TP1DBUS_DBUS_H

typedef struct DBus {
    char x;
} DBus;

void DBusCreate(DBus* this);

int DBusRun(DBus* this, int argc, char* argv[]);

void DBusDestroy(DBus* this);

#endif //TP1DBUS_DBUS_H
