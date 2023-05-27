#ifndef OOPPROJECT_SNAKEWINDOW_H
#define OOPPROJECT_SNAKEWINDOW_H

#include <wx/wx.h>
#include <mutex>
class Board;

class SnakeWindow : public wxFrame {
public:
    SnakeWindow(const wxString &title, const wxPoint &pos, const wxSize &size, int width, int height);

    void startSnake();
    void OnClose(wxCloseEvent &event);

    void stop();
private:
    Board *childBoard;
    std::mutex mx;
    int width;
    int height;
};


#endif //OOPPROJECT_SNAKEWINDOW_H
