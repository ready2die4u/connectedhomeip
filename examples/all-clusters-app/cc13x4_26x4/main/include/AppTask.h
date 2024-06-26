/*
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef APP_TASK_H
#define APP_TASK_H

#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "AppEvent.h"

#include <ti/drivers/apps/Button.h>

#ifdef CC13XX_26XX_FACTORY_DATA
#include <platform/cc13xx_26xx/FactoryDataProvider.h>
#endif

class AppTask
{
public:
    int StartAppTask();
    static void AppTaskMain(void * pvParameter);

    void PostEvent(const AppEvent * event);

private:
    friend AppTask & GetAppTask(void);

    int Init();

    void DispatchEvent(AppEvent * event);
    void uiInit();

    static void ButtonLeftEventHandler(Button_Handle handle, Button_EventMask events);
    static void ButtonRightEventHandler(Button_Handle handle, Button_EventMask events);
    static void TimerEventHandler(void * p_context);

    enum Function_t
    {
        kFunction_NoneSelected   = 0,
        kFunction_SoftwareUpdate = 0,
        kFunction_FactoryReset,

        kFunction_Invalid
    } Function;

    Function_t mFunction;
    bool mFunctionTimerActive;

    static AppTask sAppTask;

#ifdef CC13XX_26XX_FACTORY_DATA
    chip::DeviceLayer::FactoryDataProvider mFactoryDataProvider;
#endif
};

inline AppTask & GetAppTask(void)
{
    return AppTask::sAppTask;
}

#endif // APP_TASK_H
