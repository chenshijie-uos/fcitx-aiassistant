#include <memory>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcitx/ime.h>
#include <fcitx-config/hotkey.h>
#include <fcitx-config/xdg.h>
#include <fcitx-utils/log.h>
#include <fcitx-config/fcitx-config.h>
#include <fcitx-utils/utils.h>
#include <fcitx/instance.h>
#include <fcitx/keys.h>
#include <fcitx/module.h>
#include <fcitx/context.h>
#include <fcitx/module/punc/fcitx-punc.h>
#include <string>
#include <libintl.h>

#include "config.h"
#include "eim.h"
#include "bus.h"
#include "common.h"

extern "C" {
    FCITX_DEFINE_PLUGIN(fcitx_aiassistant, module, FcitxIMClass2) = {
        FcitxAiassistantCreate,
        FcitxAiassistantDestroy,
        FcitxAiassistantReloadConfig,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    };
}

/**
 * @brief initialize the extra input method
 *
 * @param arg
 * @return successful or not
 **/
void* FcitxAiassistantCreate(FcitxInstance* instance)
{
    FcitxAiassistantAddonInstance* aiassistantaddon = (FcitxAiassistantAddonInstance*) fcitx_utils_malloc0(sizeof(FcitxAiassistantAddonInstance));
    aiassistantaddon->owner = instance;
    aiassistantaddon->bus = new FcitxAiassistantBus(aiassistantaddon);

    return aiassistantaddon;
}

/**
 * @brief Destroy the input method while unload it.
 *
 * @return int
 **/
void FcitxAiassistantDestroy(void* arg)
{
}

void FcitxAiassistantReloadConfig(void* arg)
{

}

