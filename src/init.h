#pragma once
#include "Global.h"

extern uint32_t serialReadTime;
extern bool needsDataRefresh;

int requestTimeFromPC();

void setupLVGL();
void setupUI();
void setupRTC();
void setupNVS(bool freshUpload);
void setupButtons();
void setupApps();
void setupBatteryPin();

void init(bool fresh);