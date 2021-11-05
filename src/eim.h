#ifndef EIM_H
#define EIM_H

#include <fcitx/ime.h>
#include <fcitx-config/fcitx-config.h>
#include <fcitx/instance.h>
#include <fcitx/candidate.h>
#include <vector>
#include <string>
#include "bus.h"
#include "common.h"
#include "keyboardbus.h"


struct FcitxAiassistantConfig
{
    FcitxGenericConfig gconfig;
};


CONFIG_BINDING_DECLARE(FcitxAiassistantConfig);
void* FcitxAiassistantCreate(FcitxInstance* instance);
void FcitxAiassistantDestroy(void* arg);
INPUT_RETURN_VALUE FcitxAiassistantDoInput(void* arg, FcitxKeySym sym, unsigned int state);
boolean FcitxAiassistantInit(void*);
void FcitxAiassistantReloadConfig(void*);

class FcitxAiassistant;

typedef struct _FcitxAiassistantAddonInstance {
    FcitxAiassistantConfig config;

    FcitxAiassistant* pinyin;
    FcitxInstance* owner;
    KeyboardBus* k_bus;
    FcitxAiassistantBus* bus;
} FcitxAiassistantAddonInstance;

class FcitxAiassistant
{
public:
    FcitxAiassistant(FcitxAiassistantAddonInstance* aiassistantaddon);
    ~FcitxAiassistant();

    void reset();
    void init();
    void destroy();
    void save();

private:
    FcitxAiassistantAddonInstance* m_owner;
};

#endif
//
