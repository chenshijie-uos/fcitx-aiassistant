#ifndef FCITX_AISSISTANT_BUS_H
#define FCITX_AISSISTANT_BUS_H

#include <dbus/dbus.h>
#include <fcitx/instance.h>

class FcitxAiassistantBus {
public:
    FcitxAiassistantBus(struct _FcitxAiassistantAddonInstance* aiassistant);
    virtual ~FcitxAiassistantBus();

    DBusHandlerResult dbusEvent(DBusConnection* connection, DBusMessage* message);
private:
    DBusConnection* m_privconn;
    DBusConnection* m_conn;
    _FcitxAiassistantAddonInstance* m_aiassistant;
};

#endif // FCITX_AISSISTANT_BUS_H
