#ifndef OOPPROJECT_BOARD_H
#define OOPPROJECT_BOARD_H

#include <wx/wx.h>
#include "World.h"
#include <list>
#include <mutex>
#include <fstream>

class NoFileException : public SnakeException {
public:
    explicit NoFileException(const std::string &message);
};

class Board : public wxPanel, Observer {
public:
    Board(wxFrame *parent, int width, int height);
    bool exit;

private:
    int width;
    int height;
    std::mutex mx;
    wxPoint headPoint;
    direction headDirection = none;
    std::list<wxPoint> snakeBody;
    std::list<wxPoint> apples;
    std::list<wxPoint> avocados;
    std::list<wxPoint> melons;
    std::string status;
    wxStatusBar *parentStatusBar;


private:
    void OnPaint(wxPaintEvent &event);
    void OnKey(wxKeyEvent &event);
    void OnTimer(wxCommandEvent &event);

    bool prepare(World *world);

public:
    void playSnake();
    virtual bool observe(World *world);
};


#endif //OOPPROJECT_BOARD_H
