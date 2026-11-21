#pragma once

#include "Global.h"
#include "runtime.h"
#include "buttons.h"
#include "Components/mainMenu/screenMainMenu.h"
#include "Apps/App.h"
#include "Apps/Guitar-Hero-Songs.h"

#include <pgmspace.h>
#include <stdlib.h>
#include <string.h>

static constexpr uint32_t GUITAR_HERO_FRAME_PERIOD_MS = 17;
static constexpr uint32_t GUITAR_HERO_REPLAY_DELAY_MS = 2000;
static constexpr uint32_t GUITAR_HERO_LANE_FLASH_MS = 120;
static constexpr uint32_t GUITAR_HERO_NOTE_TRAVEL_MS[] = {500, 800, 1200};
static constexpr int32_t GUITAR_HERO_SCREEN_WIDTH = 64;
static constexpr int32_t GUITAR_HERO_SCREEN_HEIGHT = 128;
static constexpr int32_t GUITAR_HERO_LANE_START_Y = 38;
static constexpr int32_t GUITAR_HERO_HIT_LINE_Y = 100;
static constexpr int32_t GUITAR_HERO_FEEDBACK_Y = 120;
static constexpr int32_t GUITAR_HERO_NOTE_SIZE = 4;
static constexpr uint16_t GUITAR_HERO_VISIBLE_NOTES = 24;
static constexpr int32_t GUITAR_HERO_MAX_JUDGEMENT_MS = 30;

static lv_obj_t *guitarHeroScreen = nullptr;
static lv_obj_t *guitarHeroTitleLabel = nullptr;
static lv_obj_t *guitarHeroInstructionLabel = nullptr;
static lv_obj_t *guitarHeroScoreLabel = nullptr;
static lv_obj_t *guitarHeroStreakLabel = nullptr;
static lv_obj_t *guitarHeroJudgementLabel = nullptr;
static lv_obj_t *guitarHeroLaneLines[4] = {};
static lv_obj_t *guitarHeroLaneLabels[4] = {};
static lv_obj_t *guitarHeroNoteObjects[GUITAR_HERO_VISIBLE_NOTES] = {};
static lv_obj_t *guitarHeroHitLine = nullptr;
static lv_timer_t *guitarHeroFrameTimer = nullptr;
static lv_point_precise_t guitarHeroLanePoints[4][2] = {};
static lv_point_precise_t guitarHeroHitLinePoints[2] = {};
static uint32_t guitarHeroLaneFlashUntil[4] = {};

static GuitarHeroBeat *guitarHeroActiveBeats = nullptr;
static uint8_t *guitarHeroBeatJudgements = nullptr;
static uint16_t guitarHeroActiveBeatCount = 0;
static uint8_t guitarHeroSelectedSong = 0;
static uint8_t guitarHeroSelectedSpeed = 1;
static uint32_t guitarHeroStartTimeMs = 0;
static uint32_t guitarHeroSongCompletedMs = 0;
static uint32_t guitarHeroScore = 0;
static uint32_t guitarHeroStreak = 0;
static uint32_t guitarHeroExitChordStartedMs = 0;
static bool guitarHeroIsPlaying = false;
static bool guitarHeroChoosingSpeed = false;
static bool guitarHeroSongComplete = false;
static bool guitarHeroChordLatched = false;
static bool guitarHeroExitChordActive = false;
static uint8_t guitarHeroFramePhase = 0;
static bool guitarHeroButtonsBound = false;

struct GuitarHeroButtonCallbacks
{
    void (*pressed)();
    void (*released)();
    void (*down)();
};

static GuitarHeroButtonCallbacks guitarHeroPreviousCallbacks[4] = {};

static int32_t guitarHeroLaneX(uint8_t lane, int32_t y)
{
    const int32_t startX = 48 - (static_cast<int32_t>(lane) * 32) / 3;
    const int32_t hitX = 61 - (static_cast<int32_t>(lane) * 58) / 3;
    const int32_t progress = y - GUITAR_HERO_LANE_START_Y;
    const int32_t laneLength = GUITAR_HERO_HIT_LINE_Y - GUITAR_HERO_LANE_START_Y;
    return startX + ((hitX - startX) * progress) / laneLength;
}

static void releaseGuitarHeroSong()
{
    free(guitarHeroActiveBeats);
    free(guitarHeroBeatJudgements);
    guitarHeroActiveBeats = nullptr;
    guitarHeroBeatJudgements = nullptr;
    guitarHeroActiveBeatCount = 0;
}

static bool loadGuitarHeroSong(uint8_t songIndex)
{
    if (guitarHeroSongCount == 0 || songIndex >= guitarHeroSongCount)
        return false;

    GuitarHeroSong song{};
    memcpy_P(&song, &guitarHeroSongs[songIndex], sizeof(song));
    if (song.beat_count == 0 || song.beats == nullptr)
        return false;

    GuitarHeroBeat *beats = static_cast<GuitarHeroBeat *>(malloc(sizeof(GuitarHeroBeat) * song.beat_count));
    uint8_t *judgements = static_cast<uint8_t *>(calloc(song.beat_count, sizeof(uint8_t)));
    if (beats == nullptr || judgements == nullptr)
    {
        free(beats);
        free(judgements);
        Serial.printf("[Guitar Hero] Failed to allocate song %u\n", songIndex);
        return false;
    }

    memcpy_P(beats, song.beats, sizeof(GuitarHeroBeat) * song.beat_count);
    for (uint16_t i = 0; i < song.beat_count; ++i)
    {
        if (beats[i].lane > 3 || (i > 0 && beats[i].time_ms < beats[i - 1].time_ms))
        {
            free(beats);
            free(judgements);
            Serial.printf("[Guitar Hero] Invalid beat data in song %u\n", songIndex);
            return false;
        }
    }

    releaseGuitarHeroSong();
    guitarHeroActiveBeats = beats;
    guitarHeroBeatJudgements = judgements;
    guitarHeroActiveBeatCount = song.beat_count;
    guitarHeroSelectedSong = songIndex;
    lv_label_set_text(guitarHeroTitleLabel, song.title);
    return true;
}

static void setGuitarHeroFeedback(const char *text)
{
    if (guitarHeroJudgementLabel != nullptr)
        lv_label_set_text(guitarHeroJudgementLabel, text);
}

static void updateGuitarHeroScore()
{
    lv_label_set_text_fmt(guitarHeroScoreLabel, "SCORE %lu", static_cast<unsigned long>(guitarHeroScore));
    lv_label_set_text_fmt(
        guitarHeroStreakLabel,
        "STREAK %lu",
        static_cast<unsigned long>(guitarHeroStreak));
}

static void showGuitarHeroSongSelection()
{
    guitarHeroIsPlaying = false;
    guitarHeroChoosingSpeed = false;
    guitarHeroSongComplete = false;
    lv_obj_clear_flag(guitarHeroTitleLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guitarHeroInstructionLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guitarHeroInstructionLabel, 0, 12);
    lv_label_set_text(guitarHeroTitleLabel, guitarHeroActiveBeats != nullptr ? "SONG SELECT" : "NO SONGS");
    if (guitarHeroActiveBeats != nullptr)
    {
        GuitarHeroSong song{};
        memcpy_P(&song, &guitarHeroSongs[guitarHeroSelectedSong], sizeof(song));
        lv_label_set_text(guitarHeroTitleLabel, song.title);
    }
    lv_label_set_text(guitarHeroInstructionLabel, "K2/K3 NAV");
    lv_obj_set_pos(guitarHeroScoreLabel, 0, 22);
    lv_label_set_text(guitarHeroScoreLabel, "K1 SELECT");
    lv_obj_clear_flag(guitarHeroScoreLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guitarHeroStreakLabel, 0, 32);
    lv_label_set_text(guitarHeroStreakLabel, "K1+K4 EXIT");
    lv_obj_clear_flag(guitarHeroStreakLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guitarHeroJudgementLabel, LV_OBJ_FLAG_HIDDEN);
    for (uint8_t i = 0; i < 4; ++i)
        lv_obj_add_flag(guitarHeroLaneLines[i], LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guitarHeroHitLine, LV_OBJ_FLAG_HIDDEN);
    for (uint16_t i = 0; i < GUITAR_HERO_VISIBLE_NOTES; ++i)
        lv_obj_add_flag(guitarHeroNoteObjects[i], LV_OBJ_FLAG_HIDDEN);
    for (uint8_t i = 0; i < 4; ++i)
        lv_obj_add_flag(guitarHeroLaneLabels[i], LV_OBJ_FLAG_HIDDEN);
}

static void updateGuitarHeroSpeedLabel();

static void showGuitarHeroSpeedSelection()
{
    guitarHeroIsPlaying = false;
    guitarHeroChoosingSpeed = true;
    guitarHeroSongComplete = false;
    lv_obj_clear_flag(guitarHeroTitleLabel, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guitarHeroTitleLabel, "NOTE SPEED");
    lv_obj_set_pos(guitarHeroInstructionLabel, 0, 12);
    lv_label_set_text(guitarHeroInstructionLabel, "K2/K3 SET");
    lv_obj_clear_flag(guitarHeroInstructionLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guitarHeroScoreLabel, 0, 22);
    updateGuitarHeroSpeedLabel();
    lv_obj_clear_flag(guitarHeroScoreLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guitarHeroStreakLabel, 0, 32);
    lv_label_set_text(guitarHeroStreakLabel, "K1 START");
    lv_obj_clear_flag(guitarHeroStreakLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guitarHeroJudgementLabel, LV_OBJ_FLAG_HIDDEN);
    for (uint8_t i = 0; i < 4; ++i)
        lv_obj_add_flag(guitarHeroLaneLines[i], LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guitarHeroHitLine, LV_OBJ_FLAG_HIDDEN);
    for (uint16_t i = 0; i < GUITAR_HERO_VISIBLE_NOTES; ++i)
        lv_obj_add_flag(guitarHeroNoteObjects[i], LV_OBJ_FLAG_HIDDEN);
    for (uint8_t i = 0; i < 4; ++i)
        lv_obj_add_flag(guitarHeroLaneLabels[i], LV_OBJ_FLAG_HIDDEN);
}

static void updateGuitarHeroSpeedLabel()
{
    static const char *const speedNames[] = {"FAST", "MEDIUM", "SLOW"};
    lv_label_set_text(guitarHeroScoreLabel, speedNames[guitarHeroSelectedSpeed]);
}

static void flashGuitarHeroLane(uint8_t lane, uint8_t width)
{
    if (lane > 3)
        return;

    lv_obj_set_style_line_width(guitarHeroLaneLines[lane], width, LV_PART_MAIN);
    lv_obj_set_style_line_opa(
        guitarHeroLaneLines[lane],
        width == 0 ? LV_OPA_TRANSP : LV_OPA_50,
        LV_PART_MAIN);
    guitarHeroLaneFlashUntil[lane] = millis() + GUITAR_HERO_LANE_FLASH_MS;
}

static void startGuitarHeroSong()
{
    if (guitarHeroActiveBeats == nullptr || guitarHeroActiveBeatCount == 0)
    {
        setGuitarHeroFeedback("SONG LOAD ERROR");
        return;
    }

    memset(guitarHeroBeatJudgements, 0, guitarHeroActiveBeatCount * sizeof(uint8_t));
    guitarHeroScore = 0;
    guitarHeroStreak = 0;
    guitarHeroSongComplete = false;
    guitarHeroChoosingSpeed = false;
    guitarHeroStartTimeMs = millis();
    guitarHeroIsPlaying = true;
    lv_obj_add_flag(guitarHeroTitleLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guitarHeroInstructionLabel, 0, 18);
    lv_label_set_text(guitarHeroInstructionLabel, "K1-K4 HIT");
    lv_obj_set_pos(guitarHeroJudgementLabel, 0, GUITAR_HERO_FEEDBACK_Y);
    lv_label_set_text(guitarHeroJudgementLabel, "K2+K3 BACK");
    lv_obj_set_pos(guitarHeroScoreLabel, 0, 0);
    lv_obj_set_pos(guitarHeroStreakLabel, 0, 9);
    lv_obj_clear_flag(guitarHeroScoreLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guitarHeroStreakLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guitarHeroJudgementLabel, LV_OBJ_FLAG_HIDDEN);
    for (uint8_t i = 0; i < 4; ++i)
    {
        lv_obj_clear_flag(guitarHeroLaneLines[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guitarHeroLaneLabels[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(guitarHeroLaneLabels[i], guitarHeroLaneX(i, GUITAR_HERO_HIT_LINE_Y) - 2, 102);
    }
    lv_obj_clear_flag(guitarHeroHitLine, LV_OBJ_FLAG_HIDDEN);
    setGuitarHeroFeedback("READY");
    updateGuitarHeroScore();
}

static void createGuitarHeroScreen(lv_obj_t *parent)
{
    guitarHeroScreen = lv_obj_create(parent);
    lv_obj_set_size(guitarHeroScreen, GUITAR_HERO_SCREEN_WIDTH, GUITAR_HERO_SCREEN_HEIGHT);
    lv_obj_set_pos(guitarHeroScreen, 0, 0);
    lv_obj_set_style_bg_color(guitarHeroScreen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(guitarHeroScreen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(guitarHeroScreen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(guitarHeroScreen, 0, LV_PART_MAIN);
    lv_obj_add_flag(guitarHeroScreen, LV_OBJ_FLAG_IGNORE_LAYOUT);

    guitarHeroTitleLabel = lv_label_create(guitarHeroScreen);
    lv_obj_set_pos(guitarHeroTitleLabel, 0, 0);
    lv_obj_set_size(guitarHeroTitleLabel, GUITAR_HERO_SCREEN_WIDTH, 8);
    lv_obj_set_style_text_color(guitarHeroTitleLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(guitarHeroTitleLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(guitarHeroTitleLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    guitarHeroInstructionLabel = lv_label_create(guitarHeroScreen);
    lv_obj_set_pos(guitarHeroInstructionLabel, 0, 12);
    lv_obj_set_size(guitarHeroInstructionLabel, GUITAR_HERO_SCREEN_WIDTH, 8);
    lv_obj_set_style_text_color(guitarHeroInstructionLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(guitarHeroInstructionLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(guitarHeroInstructionLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    guitarHeroScoreLabel = lv_label_create(guitarHeroScreen);
    lv_obj_set_pos(guitarHeroScoreLabel, 0, 0);
    lv_obj_set_size(guitarHeroScoreLabel, GUITAR_HERO_SCREEN_WIDTH, 8);
    lv_obj_set_style_text_color(guitarHeroScoreLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(guitarHeroScoreLabel, &fixed6, LV_PART_MAIN);

    guitarHeroStreakLabel = lv_label_create(guitarHeroScreen);
    lv_obj_set_pos(guitarHeroStreakLabel, 0, 9);
    lv_obj_set_size(guitarHeroStreakLabel, GUITAR_HERO_SCREEN_WIDTH, 8);
    lv_obj_set_style_text_color(guitarHeroStreakLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(guitarHeroStreakLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(guitarHeroStreakLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    guitarHeroJudgementLabel = lv_label_create(guitarHeroScreen);
    lv_obj_set_pos(guitarHeroJudgementLabel, 0, 22);
    lv_obj_set_size(guitarHeroJudgementLabel, GUITAR_HERO_SCREEN_WIDTH, 8);
    lv_obj_set_style_text_color(guitarHeroJudgementLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(guitarHeroJudgementLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(guitarHeroJudgementLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    for (uint8_t lane = 0; lane < 4; ++lane)
    {
        guitarHeroLaneLines[lane] = lv_line_create(guitarHeroScreen);
        guitarHeroLanePoints[lane][0] = {
            guitarHeroLaneX(lane, GUITAR_HERO_LANE_START_Y),
            GUITAR_HERO_LANE_START_Y};
        guitarHeroLanePoints[lane][1] = {
            guitarHeroLaneX(lane, GUITAR_HERO_HIT_LINE_Y),
            GUITAR_HERO_HIT_LINE_Y};
        lv_line_set_points(guitarHeroLaneLines[lane], guitarHeroLanePoints[lane], 2);
        lv_obj_set_style_line_color(guitarHeroLaneLines[lane], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_line_width(guitarHeroLaneLines[lane], 2, LV_PART_MAIN);

        guitarHeroLaneLabels[lane] = lv_label_create(guitarHeroScreen);
        lv_label_set_text_fmt(guitarHeroLaneLabels[lane], "%u", static_cast<unsigned>(lane + 1));
        lv_obj_set_pos(
            guitarHeroLaneLabels[lane],
            guitarHeroLaneX(lane, GUITAR_HERO_HIT_LINE_Y) - 2,
            GUITAR_HERO_HIT_LINE_Y + 2);
        lv_obj_set_style_text_color(guitarHeroLaneLabels[lane], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_font(guitarHeroLaneLabels[lane], &fixed6, LV_PART_MAIN);
    }

    guitarHeroHitLine = lv_line_create(guitarHeroScreen);
    guitarHeroHitLinePoints[0] = {1, GUITAR_HERO_HIT_LINE_Y};
    guitarHeroHitLinePoints[1] = {63, GUITAR_HERO_HIT_LINE_Y};
    lv_line_set_points(guitarHeroHitLine, guitarHeroHitLinePoints, 2);
    lv_obj_set_style_line_color(guitarHeroHitLine, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_line_width(guitarHeroHitLine, 2, LV_PART_MAIN);

    for (uint16_t i = 0; i < GUITAR_HERO_VISIBLE_NOTES; ++i)
    {
        guitarHeroNoteObjects[i] = lv_obj_create(guitarHeroScreen);
        lv_obj_set_size(guitarHeroNoteObjects[i], GUITAR_HERO_NOTE_SIZE, GUITAR_HERO_NOTE_SIZE);
        lv_obj_set_style_bg_color(guitarHeroNoteObjects[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(guitarHeroNoteObjects[i], LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_border_width(guitarHeroNoteObjects[i], 0, LV_PART_MAIN);
        lv_obj_set_style_pad_all(guitarHeroNoteObjects[i], 0, LV_PART_MAIN);
        lv_obj_add_flag(guitarHeroNoteObjects[i], LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_add_flag(guitarHeroScreen, LV_OBJ_FLAG_HIDDEN);
}

static void markGuitarHeroMiss(uint16_t beatIndex)
{
    if (guitarHeroBeatJudgements[beatIndex] != 0)
        return;
    guitarHeroBeatJudgements[beatIndex] = 2;
    flashGuitarHeroLane(guitarHeroActiveBeats[beatIndex].lane, 0);
    guitarHeroStreak = 0;
    setGuitarHeroFeedback("MISS");
    updateGuitarHeroScore();
}

static void updateGuitarHeroFrame(lv_timer_t *)
{
    const uint32_t now = millis();
    for (uint8_t lane = 0; lane < 4; ++lane)
    {
        if (guitarHeroLaneFlashUntil[lane] != 0 &&
            static_cast<int32_t>(now - guitarHeroLaneFlashUntil[lane]) >= 0)
        {
            lv_obj_set_style_line_width(guitarHeroLaneLines[lane], 2, LV_PART_MAIN);
            lv_obj_set_style_line_opa(guitarHeroLaneLines[lane], LV_OPA_COVER, LV_PART_MAIN);
            guitarHeroLaneFlashUntil[lane] = 0;
        }
    }

    if (guitarHeroExitChordActive)
    {
        if (!(buttonK1->isDown() && buttonK4->isDown()))
        {
            guitarHeroExitChordActive = false;
        }
        else if (now - guitarHeroExitChordStartedMs >= 1000)
        {
            guitarHeroExitChordActive = false;
            guitarHeroIsPlaying = false;
            App::closeActiveApp();
            return;
        }
    }

    if (guitarHeroSongComplete)
    {
        lv_label_set_text(
            guitarHeroInstructionLabel,
            now - guitarHeroSongCompletedMs < GUITAR_HERO_REPLAY_DELAY_MS ? "WAIT 2 SEC" : "K1 REPLAY");
    }

    if (!guitarHeroIsPlaying || guitarHeroActiveBeats == nullptr)
        return;

    const uint32_t elapsedMs = now - guitarHeroStartTimeMs;
    uint16_t visibleNotes = 0;
    bool allJudged = true;

    for (uint16_t i = 0; i < guitarHeroActiveBeatCount; ++i)
    {
        if (guitarHeroBeatJudgements[i] != 0)
            continue;

        allJudged = false;
        const int32_t timeUntilBeat = static_cast<int32_t>(guitarHeroActiveBeats[i].time_ms) -
                                      static_cast<int32_t>(elapsedMs);
        if (timeUntilBeat < -GUITAR_HERO_MAX_JUDGEMENT_MS)
        {
            markGuitarHeroMiss(i);
            continue;
        }

        if (timeUntilBeat <= static_cast<int32_t>(GUITAR_HERO_NOTE_TRAVEL_MS[guitarHeroSelectedSpeed]) &&
            visibleNotes < GUITAR_HERO_VISIBLE_NOTES)
        {
            const int32_t y = GUITAR_HERO_HIT_LINE_Y -
                              (timeUntilBeat * (GUITAR_HERO_HIT_LINE_Y - GUITAR_HERO_LANE_START_Y)) /
                                  static_cast<int32_t>(GUITAR_HERO_NOTE_TRAVEL_MS[guitarHeroSelectedSpeed]);
            const int32_t x = guitarHeroLaneX(guitarHeroActiveBeats[i].lane, y);
            lv_obj_set_pos(
                guitarHeroNoteObjects[visibleNotes],
                x - GUITAR_HERO_NOTE_SIZE / 2,
                y - GUITAR_HERO_NOTE_SIZE / 2);
            lv_obj_clear_flag(guitarHeroNoteObjects[visibleNotes], LV_OBJ_FLAG_HIDDEN);
            ++visibleNotes;
        }
    }

    while (visibleNotes < GUITAR_HERO_VISIBLE_NOTES)
    {
        lv_obj_add_flag(guitarHeroNoteObjects[visibleNotes], LV_OBJ_FLAG_HIDDEN);
        ++visibleNotes;
    }

    if (allJudged)
    {
        guitarHeroIsPlaying = false;
        guitarHeroSongComplete = true;
        guitarHeroSongCompletedMs = now;
        setGuitarHeroFeedback("SONG COMPLETE");
    }

    guitarHeroFramePhase = static_cast<uint8_t>((guitarHeroFramePhase + 1) % 3);
    lv_timer_set_period(
        guitarHeroFrameTimer,
        guitarHeroFramePhase == 1 ? 16 : GUITAR_HERO_FRAME_PERIOD_MS);
}

static void handleGuitarHeroLaneHit(uint8_t lane)
{
    if (!guitarHeroIsPlaying || guitarHeroActiveBeats == nullptr || lane > 3)
        return;

    const uint32_t elapsedMs = millis() - guitarHeroStartTimeMs;
    int32_t closestDifference = GUITAR_HERO_MAX_JUDGEMENT_MS + 1;
    int16_t closestBeat = -1;

    for (uint16_t i = 0; i < guitarHeroActiveBeatCount; ++i)
    {
        if (guitarHeroBeatJudgements[i] != 0 || guitarHeroActiveBeats[i].lane != lane)
            continue;

        const int32_t difference = static_cast<int32_t>(elapsedMs) -
                                   static_cast<int32_t>(guitarHeroActiveBeats[i].time_ms);
        if (abs(difference) < abs(closestDifference))
        {
            closestDifference = difference;
            closestBeat = static_cast<int16_t>(i);
        }
    }

    if (closestBeat < 0 || abs(closestDifference) > GUITAR_HERO_MAX_JUDGEMENT_MS)
    {
        guitarHeroStreak = 0;
        flashGuitarHeroLane(lane, 0);
        setGuitarHeroFeedback("MISS");
        updateGuitarHeroScore();
        return;
    }

    guitarHeroBeatJudgements[closestBeat] = 1;
    flashGuitarHeroLane(lane, 2);
    if (closestDifference < -20)
    {
        guitarHeroScore += 25;
        setGuitarHeroFeedback("EARLY");
    }
    else if (closestDifference < -10)
    {
        guitarHeroScore += 50;
        setGuitarHeroFeedback("GOOD");
    }
    else if (closestDifference <= 10)
    {
        guitarHeroScore += 100;
        setGuitarHeroFeedback("PERFECT");
    }
    else if (closestDifference <= 20)
    {
        guitarHeroScore += 50;
        setGuitarHeroFeedback("GOOD");
    }
    else
    {
        guitarHeroScore += 25;
        setGuitarHeroFeedback("LATE");
    }

    ++guitarHeroStreak;
    updateGuitarHeroScore();
}

static void handleGuitarHeroButtonPress(uint8_t lane);
static void handleGuitarHeroButtonRelease();

static void guitarHeroButtonPressedK1()
{
    handleGuitarHeroButtonPress(0);
}

static void guitarHeroButtonPressedK2()
{
    handleGuitarHeroButtonPress(1);
}

static void guitarHeroButtonPressedK3()
{
    handleGuitarHeroButtonPress(2);
}

static void guitarHeroButtonPressedK4()
{
    handleGuitarHeroButtonPress(3);
}

static void guitarHeroButtonReleased()
{
    handleGuitarHeroButtonRelease();
}

static void guitarHeroButtonDown()
{
}

static void bindGuitarHeroButtons()
{
    if (!guitarHeroButtonsBound)
    {
        Button *buttons[] = {buttonK1, buttonK2, buttonK3, buttonK4};
        for (uint8_t i = 0; i < 4; ++i)
        {
            guitarHeroPreviousCallbacks[i] = {
                buttons[i]->pressedFunction,
                buttons[i]->releasedFunction,
                buttons[i]->downFunction};
        }
        guitarHeroButtonsBound = true;
    }

    buttonK1->pressedFunction = guitarHeroButtonPressedK1;
    buttonK2->pressedFunction = guitarHeroButtonPressedK2;
    buttonK3->pressedFunction = guitarHeroButtonPressedK3;
    buttonK4->pressedFunction = guitarHeroButtonPressedK4;
    buttonK1->releasedFunction = guitarHeroButtonReleased;
    buttonK2->releasedFunction = guitarHeroButtonReleased;
    buttonK3->releasedFunction = guitarHeroButtonReleased;
    buttonK4->releasedFunction = guitarHeroButtonReleased;
    buttonK1->downFunction = guitarHeroButtonDown;
    buttonK2->downFunction = guitarHeroButtonDown;
    buttonK3->downFunction = guitarHeroButtonDown;
    buttonK4->downFunction = guitarHeroButtonDown;
}

static void unbindGuitarHeroButtons()
{
    if (!guitarHeroButtonsBound)
        return;

    Button *buttons[] = {buttonK1, buttonK2, buttonK3, buttonK4};
    for (uint8_t i = 0; i < 4; ++i)
    {
        buttons[i]->pressedFunction = guitarHeroPreviousCallbacks[i].pressed;
        buttons[i]->releasedFunction = guitarHeroPreviousCallbacks[i].released;
        buttons[i]->downFunction = guitarHeroPreviousCallbacks[i].down;
    }
    guitarHeroButtonsBound = false;
}

static void handleGuitarHeroButtonPress(uint8_t lane)
{
    configASSERT(isRuntimeUiTask());
    const bool exitChord = buttonK1->isDown() && buttonK4->isDown();
    const bool selectionChord = buttonK2->isDown() && buttonK3->isDown();

    if (exitChord || selectionChord)
    {
        if (guitarHeroChordLatched)
            return;
        guitarHeroChordLatched = true;
        if (exitChord)
        {
            guitarHeroExitChordActive = true;
            guitarHeroExitChordStartedMs = millis();
            lv_obj_clear_flag(guitarHeroJudgementLabel, LV_OBJ_FLAG_HIDDEN);
            setGuitarHeroFeedback("HOLD TO EXIT");
        }
        else
        {
            showGuitarHeroSongSelection();
        }
        return;
    }

    if (guitarHeroChordLatched)
        return;

    if (guitarHeroChoosingSpeed)
    {
        if (lane == 0)
            startGuitarHeroSong();
        else if (lane == 1 || lane == 2)
        {
            guitarHeroSelectedSpeed = static_cast<uint8_t>(
                (guitarHeroSelectedSpeed + (lane == 1 ? 2 : 1)) % 3);
            updateGuitarHeroSpeedLabel();
        }
        return;
    }

    if (guitarHeroSongComplete)
    {
        if (millis() - guitarHeroSongCompletedMs < GUITAR_HERO_REPLAY_DELAY_MS)
            return;

        if (lane == 0)
            startGuitarHeroSong();
        else if (lane == 1 || lane == 2)
            showGuitarHeroSongSelection();
        return;
    }

    if (!guitarHeroIsPlaying)
    {
        if (lane == 0)
            showGuitarHeroSpeedSelection();
        else if (lane == 1 || lane == 2)
        {
            if (guitarHeroSongCount > 0)
            {
                const uint8_t offset = lane == 1 ? guitarHeroSongCount - 1 : 1;
                const uint8_t nextSong = static_cast<uint8_t>(
                    (guitarHeroSelectedSong + offset) % guitarHeroSongCount);
                if (!loadGuitarHeroSong(nextSong))
                    setGuitarHeroFeedback("SONG LOAD ERROR");
                else
                    showGuitarHeroSongSelection();
            }
        }
        return;
    }

    handleGuitarHeroLaneHit(lane);
}

static void handleGuitarHeroButtonRelease()
{
    if (!(buttonK1->isDown() && buttonK4->isDown()))
    {
        guitarHeroExitChordActive = false;
        if (!guitarHeroIsPlaying)
            lv_obj_add_flag(guitarHeroJudgementLabel, LV_OBJ_FLAG_HIDDEN);
        else
            setGuitarHeroFeedback("READY");
    }

    if (guitarHeroChordLatched &&
        !(buttonK1->isDown() && buttonK4->isDown()) &&
        !(buttonK2->isDown() && buttonK3->isDown()))
        guitarHeroChordLatched = false;
}

static bool activateGuitarHeroUI()
{
    configASSERT(isRuntimeUiTask());
    lv_display_set_rotation(nullptr, LV_DISPLAY_ROTATION_90);
    if (guitarHeroScreen == nullptr)
        createGuitarHeroScreen(lv_scr_act());
    else
        lv_obj_set_size(guitarHeroScreen, GUITAR_HERO_SCREEN_WIDTH, GUITAR_HERO_SCREEN_HEIGHT);

    if (!loadGuitarHeroSong(guitarHeroSelectedSong))
    {
        lv_label_set_text(guitarHeroTitleLabel, "SONG LOAD ERROR");
        Serial.println("[Guitar Hero] Unable to load the selected song");
        lv_display_set_rotation(nullptr, LV_DISPLAY_ROTATION_0);
        return false;
    }

    guitarHeroChordLatched = false;
    guitarHeroExitChordActive = false;
    guitarHeroFramePhase = 0;
    lv_obj_clear_flag(guitarHeroScreen, LV_OBJ_FLAG_HIDDEN);
    showGuitarHeroSongSelection();
    bindGuitarHeroButtons();
    if (lv_menu_screen != nullptr)
        lv_obj_add_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);
    guitarHeroFrameTimer = lv_timer_create(updateGuitarHeroFrame, GUITAR_HERO_FRAME_PERIOD_MS, nullptr);
    if (guitarHeroFrameTimer == nullptr)
    {
        Serial.println("[Guitar Hero] Failed to create the frame timer");
        unbindGuitarHeroButtons();
        releaseGuitarHeroSong();
        lv_obj_add_flag(guitarHeroScreen, LV_OBJ_FLAG_HIDDEN);
        lv_display_set_rotation(nullptr, LV_DISPLAY_ROTATION_0);
        return false;
    }
    return true;
}

static void restoreGuitarHeroUI()
{
    configASSERT(isRuntimeUiTask());
    guitarHeroIsPlaying = false;
    guitarHeroChordLatched = false;
    guitarHeroExitChordActive = false;
    if (guitarHeroFrameTimer != nullptr)
    {
        lv_timer_delete(guitarHeroFrameTimer);
        guitarHeroFrameTimer = nullptr;
    }
    releaseGuitarHeroSong();
    unbindGuitarHeroButtons();
    if (guitarHeroScreen != nullptr)
        lv_obj_add_flag(guitarHeroScreen, LV_OBJ_FLAG_HIDDEN);
    lv_display_set_rotation(nullptr, LV_DISPLAY_ROTATION_0);
    if (lv_menu_screen != nullptr)
        lv_obj_clear_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);
    setMainMenuActive(true);
}
