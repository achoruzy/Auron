// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once


namespace Auron {

    class SplashScreen {
    private:
        float fadeSpeed;
        float elapsedTime;
        bool isSplashActive;
        float alpha;
        void ShowSplashScreen();
        
    public:
        SplashScreen() : fadeSpeed(1.0f), elapsedTime(0.0f), isSplashActive(true), alpha(0.0f) {}
        ~SplashScreen();
        int Run();
        void ShowSplashScreen(void *texture);
        bool IsSplashActive() const { return isSplashActive; }
        void SetFadeSpeed(float speed) { fadeSpeed = speed; }
    };
}