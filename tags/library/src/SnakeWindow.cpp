#include "SnakeWindow.h"
#include "Board.h"

SnakeWindow::SnakeWindow(const wxString &title, const wxPoint &pos, const wxSize &size, int width, int height) :
        wxFrame(NULL,wxID_ANY, title, pos, size), width(width), height(height) {

    CreateStatusBar();
    SetBackgroundColour(wxColour(*wxBLACK));

    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(SnakeWindow::OnClose));
}

void SnakeWindow::startSnake() {
    try {
        auto *board = new Board(this, width, height);
        childBoard = board;
        board->SetFocus();
        board->playSnake();
    }  catch (NoFileException &e) {
        std::cout << e.message() << std::endl;
        wxCloseEvent x;
        OnClose(x);
        exit(1);
    }  catch (OutOfBody &e) {
        std::cout << e.message() << std::endl;
        wxCloseEvent x;
        OnClose(x);
        exit(2);
    }  catch (OutOfFruits &e) {
        std::cout << e.message() << std::endl;
        wxCloseEvent x;
        OnClose(x);
        exit(3);
    }
}

void SnakeWindow::OnClose(wxCloseEvent &event) {
    stop();
    Destroy();
}

void SnakeWindow::stop() {
    std::lock_guard<std::mutex> guard(mx);
    childBoard->exit = true;
}

