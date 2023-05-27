#include <iostream>
#include "World.h"
#include "Board.h"
#include "SnakeWindow.h"
#include <wx/wx.h>
#include <thread>

using namespace std;

class snakeApp : public wxApp {
private:
    thread *simulationThread;

public:
    bool OnInit() override ;
    int OnExit() override ;

};

bool snakeApp::OnInit() {
    //cout << "INIT" << endl;
    auto *frame = new SnakeWindow("Snake game", wxPoint(0, 0),
                                  wxSize(800, 800), 20, 20);

    simulationThread = new thread(&SnakeWindow::startSnake, frame);
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

int snakeApp::OnExit() {
    if (simulationThread->joinable())
        simulationThread->join();
    delete simulationThread;
    //cout << "EXIT" << endl;
}

wxIMPLEMENT_APP(snakeApp);