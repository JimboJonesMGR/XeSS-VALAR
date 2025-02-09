// Copyright (C) 2022 Intel Corporation

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
// OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once
#include <Math/Vector.h>

class CameraController;
class ColorBuffer;
class DemoApp;

enum UnitTestState
{
    TestStateNone,
    Setup,
    MoveCamera,
    RunExperiment,
    Wait,
    TakeScreenshot,
    AccumulateFrametime,
    Teardown,
    FlyCamera,
    WaitFlyCamera,
};

enum UnitTestMode
{
    TestModeNone,
    LionHead,
    FirstFloor,
    Tapestry
};

class Location
{
private:
    const float heading;
    const float pitch;
    const Math::Vector3 position;

public:
    Location(float heading, float pitch, Math::Vector3 position) :
        heading(heading), pitch(pitch), position(position) {}
    Location() :
        heading(0.0f), pitch(0.0f), position(Math::Vector3(0.0f, 0.0f, 0.0f)) {}
    float GetHeading() const { return heading; }
    float GetPitch() const { return pitch; }
    Math::Vector3 GetPosition() const { return position; }
};

class Experiment
{
public:
    Experiment(std::string& experimentName, bool captureVRSbuffer, bool captureStats, bool isControl);

    void (*ExperimentFunction)();

    std::string& GetName();
    bool CaptureVRSBuffer();
    bool CaptureStats();
    bool IsControl();
private:
    bool m_isControl;
    bool m_captureVRSBuffer;
    bool m_captureStats;
    std::string m_experimentName;
};

class UnitTest
{
public:
    UnitTest(std::string& testName, UnitTestMode testMode);

    void AddExperiment(Experiment* exp);

    void Setup();

    std::string& GetName();
public:
    std::string m_testName;
    std::list<Experiment*> m_experiments;
    UnitTestMode m_testMode;
};

class DemoApp;

namespace VRSTest
{
    void Init(DemoApp* App);
    void Update(CameraController* camera, float deltaT);
    bool Render(CommandContext& context, ColorBuffer& source, ColorBuffer& vrsBuffer);
    void MoveCamera(CameraController* camera, UnitTestMode testMode);
    UnitTestMode CheckIfChangeLocationKeyPressed();
    void ResetExperimentData();
    void WriteExperimentData(
        std::string& AE, std::string& DSSIM, std::string& FUZZ, 
        std::string& MAE, std::string& MEPP, std::string& MSE, 
        std::string& NCC, std::string& PAE, std::string& PHASH, 
        std::string& RMSE, std::string& SSIM, std::string& PSNR, 
        std::string& FLIP);

    extern DemoApp* m_App;
}

