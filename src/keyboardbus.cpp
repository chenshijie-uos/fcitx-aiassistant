#include "keyboardbus.h"
#include "eim.h"
#include <fcitx/module/dbus/fcitx-dbus.h>

KeyboardBus::KeyboardBus(struct _FcitxAiassistantAddonInstance* aiassistant, QObject *parent) : QObject(parent)
  , m_keyboardInter(new ComFcitxAiassistantServerInterface("com.fcitx.aiassistant.server",
                                                         "/keyboard",
                                                         QDBusConnection::sessionBus(), this))
{
    m_aiassistant = aiassistant;
}

void KeyboardBus::initView()
{
    printf("init\n");
    m_keyboardInter->initView();
}

void KeyboardBus::showView()
{
    printf("show\n");
    m_keyboardInter->showView();
}

void KeyboardBus::hideView()
{
    printf("hide\n");
    m_keyboardInter->hideView();
}
