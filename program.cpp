#include <dbus/dbus.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

class BluetoothManager {
public:
    BluetoothManager() {
        dbus_error_init(&err);
        conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
        if (dbus_error_is_set(&err)) {
            throw std::runtime_error(err.message);
        }
    }

    ~BluetoothManager() {
        if (conn) dbus_connection_unref(conn);
        dbus_error_free(&err);
    }

    void scanDevices() {
        DBusMessage* msg = dbus_message_new_method_call("org.bluez", "/", "org.bluez.Adapter1", "StartDiscovery");
        if (!msg) {
            throw std::runtime_error("Failed to create message");
        }

        if (!dbus_connection_send(conn, msg, nullptr)) {
            throw std::runtime_error("Out Of Memory!");
        }
        dbus_connection_flush(conn);
        dbus_message_unref(msg);

        std::cout << "Bluetooth scan started\n";
    }

    std::string getMACAddress() {
        DBusMessage* msg = dbus_message_new_method_call("org.bluez", "/org/bluez/hci0", "org.freedesktop.DBus.Properties", "Get");
        if (!msg) {
            throw std::runtime_error("Failed to create message");
        }

        const char* adapter_interface = "org.bluez.Adapter1";
        const char* property = "Address";
        dbus_message_append_args(msg, DBUS_TYPE_STRING, &adapter_interface, DBUS_TYPE_STRING, &property, DBUS_TYPE_INVALID);

        DBusMessage* reply = dbus_connection_send_with_reply_and_block(conn, msg, -1, &err);
        if (dbus_error_is_set(&err)) {
            throw std::runtime_error(err.message);
        }

        DBusMessageIter args;
        if (!dbus_message_iter_init(reply, &args)) {
            throw std::runtime_error("Failed to read reply");
        }

        DBusMessageIter variant_iter;
        int type = dbus_message_iter_get_arg_type(&args);
        char* str;
        if (type == DBUS_TYPE_VARIANT) {
            dbus_message_iter_recurse(&args, &variant_iter);
            dbus_message_iter_get_basic(&variant_iter, &str);
            printf("Retrieved string from variant: %s\n", str);
        }
        dbus_message_unref(msg);
        dbus_message_unref(reply);
        return str ? std::string(str) : std::string();
    }

private:
    DBusError err;
    DBusConnection* conn = nullptr;
};

int main() {
    try {
        BluetoothManager btManager;
        btManager.scanDevices();
        std::string macAddress = btManager.getMACAddress();
        std::cout << "Bluetooth MAC Address: " << macAddress << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}