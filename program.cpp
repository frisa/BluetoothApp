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

    void setBluetoothLowEnergyMode(bool enable) {
        DBusError err;
        dbus_error_init(&err);

        // connect to the system bus
        DBusConnection* conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
        if (dbus_error_is_set(&err)) {
            std::cerr << "Connection Error: " << err.message << std::endl;
            dbus_error_free(&err);
            return;
        }

        // request a handle to the org.bluez object
        DBusMessage* msg = dbus_message_new_method_call("org.bluez", "/org/bluez/hci0", "org.freedesktop.DBus.Properties", "Set");
        if (nullptr == msg) {
            std::cerr << "Message Null" << std::endl;
            return;
        }

        // append arguments to the message
        const char* adapter_interface = "org.bluez.Adapter1";
        const char* property = "Powered";
        dbus_bool_t value = enable ? TRUE : FALSE;
        DBusMessageIter args, variant;
        dbus_message_iter_init_append(msg, &args);
        dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &adapter_interface);
        dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &property);
        dbus_message_iter_open_container(&args, DBUS_TYPE_VARIANT, DBUS_TYPE_BOOLEAN_AS_STRING, &variant);
        dbus_message_iter_append_basic(&variant, DBUS_TYPE_BOOLEAN, &value);
        dbus_message_iter_close_container(&args, &variant);

        // send the message
        dbus_connection_send(conn, msg, nullptr);
        dbus_connection_flush(conn);

        // free the message
        dbus_message_unref(msg);
    }

    void registerAdvertisement(const std::string& advertisementPath) {
        // request a handle to the org.bluez object
        DBusMessage* msg = dbus_message_new_method_call("org.bluez", "/org/bluez/hci0", "org.bluez.LEAdvertisingManager1", "RegisterAdvertisement");
        if (nullptr == msg) {
            std::cerr << "Message Null" << std::endl;
            return;
        }

        // append arguments to the message
        const char* path = advertisementPath.c_str();
        const char* policy = "default";
        DBusMessageIter args;
        dbus_message_iter_init_append(msg, &args);
        dbus_message_iter_append_basic(&args, DBUS_TYPE_OBJECT_PATH, &path);
        dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &policy);

        // send the message
        dbus_connection_send(conn, msg, nullptr);
        dbus_connection_flush(conn);

        // free the message
        dbus_message_unref(msg);
    }

    void registerAdvertisement() {
        // create a new D-Bus message
        DBusMessage* msg = dbus_message_new_method_call("org.bluez", "/org/bluez/hci0", "org.bluez.LEAdvertisingManager1", "RegisterAdvertisement");
        if (nullptr == msg) {
            std::cerr << "Message Null" << std::endl;
            return;
        }

        // create a new D-Bus object path
        const char* path = "/com/example/Advertisement1";
        dbus_message_append_args(msg, DBUS_TYPE_OBJECT_PATH, &path, DBUS_TYPE_INVALID);

        // create a new D-Bus dictionary for the advertisement properties
        DBusMessageIter iter;
        dbus_message_iter_init_append(msg, &iter);
        DBusMessageIter dict;
        dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, "{sv}", &dict);

        // add the Type property
        const char* type = "peripheral";
        appendDictEntry(&dict, "Type", DBUS_TYPE_STRING, &type);

        // add the ServiceUUIDs property
        const char* uuids[] = {"0000180d-0000-1000-8000-00805f9b34fb", nullptr};
        appendDictEntry(&dict, "ServiceUUIDs", DBUS_TYPE_ARRAY, &uuids);

        // close the dictionary and the message
        dbus_message_iter_close_container(&iter, &dict);

        // send the message
        DBusPendingCall* pending;
        dbus_bool_t stat = dbus_connection_send_with_reply(conn, msg, &pending, -1); // -1 is default timeout
        if (stat == FALSE) {
            std::cerr << "Out Of Memory!" << std::endl;
            return;
        }

        // free the message
        dbus_message_unref(msg);
    }


private:
    DBusError err;
    DBusConnection* conn = nullptr;

    void appendDictEntry(DBusMessageIter* dict, const char* key, int type, void* value) {
        DBusMessageIter entry;
        dbus_message_iter_open_container(dict, DBUS_TYPE_DICT_ENTRY, nullptr, &entry);

        // append the key
        dbus_message_iter_append_basic(&entry, DBUS_TYPE_STRING, &key);

        // append the value
        DBusMessageIter variant;
        dbus_message_iter_open_container(&entry, DBUS_TYPE_VARIANT, dbus_type_to_string(type), &variant);
        dbus_message_iter_append_basic(&variant, type, value);
        dbus_message_iter_close_container(&entry, &variant);

        dbus_message_iter_close_container(dict, &entry);
    }

    const char* dbus_type_to_string(int type) {
        switch (type) {
            case DBUS_TYPE_STRING: return "s";
            case DBUS_TYPE_INT32: return "i";
            case DBUS_TYPE_BOOLEAN: return "b";
            // add more cases as needed
            default: return "?";
    }
}
};

int main() {
    try {
        BluetoothManager btManager;
        btManager.scanDevices();
        std::string macAddress = btManager.getMACAddress();
        std::cout << "Bluetooth MAC Address: " << macAddress << std::endl;
        btManager.setBluetoothLowEnergyMode(true);
        btManager.registerAdvertisement("/org/bluez/hci0/advertisement0");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}