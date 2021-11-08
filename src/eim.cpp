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
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
}

static void FcitxAiassistantSave(void* arg);


/**
 * @brief Reset the status.
 *
 **/
void FcitxAiassistantReset(void* arg)
{
    FcitxAiassistant* aiassistant = (FcitxAiassistant*) arg;
    aiassistant->reset();
}


/**
 * @brief Process Key Input and return the status
 *
 * @param keycode keycode from XKeyEvent
 * @param state state from XKeyEvent
 * @param count count from XKeyEvent
 * @return INPUT_RETURN_VALUE
 **/
INPUT_RETURN_VALUE FcitxAiassistantDoInput(void* arg, FcitxKeySym sym, unsigned int state)
{
    return IRV_TO_PROCESS;
}

boolean FcitxAiassistantInit(void* arg)
{
    FcitxAiassistant* aiassistant = (FcitxAiassistant*) arg;
    aiassistant->init();
    return true;
}

void FcitxAiassistant::init() {
    FcitxInstanceSetContext(m_owner->owner, CONTEXT_IM_KEYBOARD_LAYOUT, "us");
    m_owner->k_bus->initView();

}

void FcitxAiassistant::reset() {
    m_owner->k_bus->showView();

}

void FcitxAiassistant::save() {
    m_owner->k_bus->hideView();

}


FcitxAiassistant::FcitxAiassistant(FcitxAiassistantAddonInstance* aiassistantaddon) :
    m_owner(aiassistantaddon)
{
}

FcitxAiassistant::~FcitxAiassistant()
{

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

    aiassistantaddon->pinyin = new FcitxAiassistant(aiassistantaddon);

    aiassistantaddon->bus = new FcitxAiassistantBus(aiassistantaddon);
    aiassistantaddon->k_bus = new KeyboardBus(aiassistantaddon);

    return aiassistantaddon;
}

/**
 * @brief Destroy the input method while unload it.
 *
 * @return int
 **/
void FcitxAiassistantDestroy(void* arg)
{
    FcitxAiassistantAddonInstance* aiassistant = (FcitxAiassistantAddonInstance*) arg;
    aiassistant->k_bus->hideView();
    delete aiassistant->pinyin;
    delete aiassistant->bus;
    delete aiassistant->k_bus;
    free(aiassistant);
}

void FcitxAiassistantReloadConfig(void* arg)
{

}

void FcitxAiassistantSave(void* arg)
{
    FcitxAiassistant* libaiassistant = (FcitxAiassistant*) arg;
    libaiassistant->save();
}

