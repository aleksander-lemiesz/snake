#include <chrono>
#include <thread>
#include <sstream>
#include "Avocado.h"
#include "Melon.h"
#include "Apple.h"
#include "Board.h"
#include "World.h"
#include "SnakeWindow.h"

Board::Board(wxFrame *parent, int width, int height)
: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize(), wxBORDER_NONE)
,width(width), height(height) {

    parentStatusBar = parent->GetStatusBar();

    Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKey));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));

}

void Board::OnPaint(wxPaintEvent &event) {
    wxSize size = GetClientSize();
    int dx = (size.x / width);
    int dy = (size.y / height);
    int radius = dx/2;
    wxPaintDC dc(this);

    std::lock_guard<std::mutex> guard(mx);

    std::stringstream sout;
    sout << "Score: " << status;
    std::string playerScore = sout.str();
    parentStatusBar->SetStatusText(playerScore);

    std::list<wxPoint>::iterator it;

    dc.SetBrush(*wxRED_BRUSH);
    for (it = apples.begin(); it != apples.end(); it++) {
        wxPoint point = *it;
        dc.DrawCircle(point.x*dx+dx/2, point.y*dy+dy/2, radius);
    }

    dc.SetBrush(*wxMEDIUM_GREY_BRUSH);
    for (it = avocados.begin(); it != avocados.end(); it++) {
        wxPoint point = *it;
        dc.DrawCircle(point.x*dx+dx/2, point.y*dy+dy/2, radius);
    }

    dc.SetBrush(*wxYELLOW_BRUSH);
    for (it = melons.begin(); it != melons.end(); it++) {
        wxPoint point = *it;
        dc.DrawCircle(point.x*dx+dx/2, point.y*dy+dy/2, radius);
    }
// BODY
    dc.SetBrush(wxColour(51, 204, 0));
    for (it = snakeBody.begin(); it != snakeBody.end(); it++) {
        wxPoint point = *it;
        dc.DrawCircle(point.x*dx+dx/2, point.y*dy+dy/2, radius);
    }

    dc.SetBrush(wxColour(255, 255, 102));
    for (it = snakeBody.begin(); it != snakeBody.end(); it++) {
        wxPoint point = *it;
        dc.DrawCircle(point.x*dx+dx/2+7, point.y*dy+dy/2+7, radius/3);
    }

    dc.SetBrush(wxColour(153, 102, 51));
    for (it = snakeBody.begin(); it != snakeBody.end(); it++) {
        wxPoint point = *it;
        dc.DrawCircle(point.x*dx+dx/2-6, point.y*dy+dy/2-3, radius/5);
        dc.DrawCircle(point.x*dx+dx/2+2, point.y*dy+dy/2-7, radius/5);
    }
// HEAD
    dc.SetBrush(wxColour(51, 204, 0));
    dc.DrawCircle(headPoint.x*dx+dx/2, headPoint.y*dy+dy/2, radius);

    dc.SetBrush(*wxWHITE_BRUSH);
    if (headDirection == up) {
        dc.DrawCircle(headPoint.x*dx+dx/2+6, headPoint.y*dy+dy/2+4, radius/3);
        dc.DrawCircle(headPoint.x*dx+dx/2-6, headPoint.y*dy+dy/2+4, radius/3);

    } else if (headDirection == down) {
        dc.DrawCircle(headPoint.x*dx+dx/2+6, headPoint.y*dy+dy/2-4, radius/3);
        dc.DrawCircle(headPoint.x*dx+dx/2-6, headPoint.y*dy+dy/2-4, radius/3);

    } else if (headDirection == left) {
        dc.DrawCircle(headPoint.x*dx+dx/2-4, headPoint.y*dy+dy/2+6, radius/3);
        dc.DrawCircle(headPoint.x*dx+dx/2-4, headPoint.y*dy+dy/2-6, radius/3);

    } else if (headDirection == right) {
        dc.DrawCircle(headPoint.x*dx+dx/2+4, headPoint.y*dy+dy/2+6, radius/3);
        dc.DrawCircle(headPoint.x*dx+dx/2+4, headPoint.y*dy+dy/2-6, radius/3);
    }

    dc.SetBrush(*wxBLACK_BRUSH);
    if (headDirection == up) {
        dc.DrawCircle(headPoint.x*dx+dx/2+6, headPoint.y*dy+dy/2+4, radius/5);
        dc.DrawCircle(headPoint.x*dx+dx/2-6, headPoint.y*dy+dy/2+4, radius/5);

    } else if (headDirection == down) {
        dc.DrawCircle(headPoint.x*dx+dx/2+6, headPoint.y*dy+dy/2-4, radius/5);
        dc.DrawCircle(headPoint.x*dx+dx/2-6, headPoint.y*dy+dy/2-4, radius/5);

    } else if (headDirection == left) {
        dc.DrawCircle(headPoint.x*dx+dx/2-4, headPoint.y*dy+dy/2+6, radius/5);
        dc.DrawCircle(headPoint.x*dx+dx/2-4, headPoint.y*dy+dy/2-6, radius/5);

    } else if (headDirection == right) {
        dc.DrawCircle(headPoint.x*dx+dx/2+4, headPoint.y*dy+dy/2+6, radius/5);
        dc.DrawCircle(headPoint.x*dx+dx/2+4, headPoint.y*dy+dy/2-6, radius/5);
    }

}

void Board::OnKey(wxKeyEvent &event) {
    int key = event.GetKeyCode();
    char kchar = event.GetUnicodeKey();

    if (key == WXK_UP || kchar == 'W') {
        this->input = down;
    } else if (key == WXK_DOWN || kchar == 'S') {
        this->input = up;
    }  else if (key == WXK_LEFT || kchar == 'A') {
        this->input = left;
    } else if (key == WXK_RIGHT || kchar == 'D') {
        this->input = right;
    } else if (key == WXK_ESCAPE) {
        this->input = exitGame;
    } else if (key == WXK_SPACE) {
        this->input = none;
    }
}

bool Board::prepare(World *world) {
    std::lock_guard<std::mutex> guard(mx);
    if (exit) {
        return true;
    }
    snakeBody.clear();
    apples.clear();
    avocados.clear();
    melons.clear();

    /// Loading score
    std::stringstream sout;
    sout << world->getSnake()->getScore();
    wxString score = sout.str();
    status = score;

    /// Comparing with file
    std::string scorePath = "/home/student/Desktop/Project:2Dgame/program/snakeHighScore.txt";
    std::fstream highscoreFile;
    highscoreFile.open(scorePath.c_str());
    if (!highscoreFile.good()) {
        exit = true;
        throw NoFileException("No highscore file!");
    }
    std::string line;
    while(getline(highscoreFile, line)) {
        highscore = std::stoi(line);
        //std::cout << line << std::endl;
    }
    highscoreFile.close();

    /// Saving highscore to file
    highscoreFile.open(scorePath.c_str());
    if (!highscoreFile.good()) {
        exit = true;
        throw NoFileException("No highscore file!");
    }
    if (world->getSnake()->getScore() > highscore) {
        highscore = world->getSnake()->getScore();
        highscoreFile << highscore;
        //std::cout << "Saving " << highscore << std::endl;
    }
    highscoreFile.close();

    /// Iterating through snake
    auto head = world->getSnake()->getHead();
    wxPoint point(head.getX(), head.getY());
    headPoint = point;
    headDirection = head.getDirection();
    for (int i = 0; i < world->getSnake()->length(); ++i) {
        auto body = world->getSnake()->getBody()[i];
        point.x = body->getX();
        point.y = body->getY();
        snakeBody.push_back(point);
    }

    /// Iterating through fruits
    for (int i = 0; i < world->getFruits().size(); ++i) {
        auto fruit = world->getFruits()[i];
        wxPoint point(fruit->getX(), fruit->getY());
        if (dynamic_cast<Apple *>(fruit.get()) != nullptr) {
            apples.push_back(point);
        } else if (dynamic_cast<Avocado *>(fruit.get()) != nullptr) {
            avocados.push_back(point);
        } else if (dynamic_cast<Melon *>(fruit.get()) != nullptr) {
            melons.push_back(point);
        }
    }
    wxQueueEvent(GetEventHandler(), new wxTimerEvent);
    return false;
}

bool Board::observe(World *world) {
    if (prepare(world)) {
        return true;
    }
    int x = world->getSnake()->getSpeed();
    int formula = 700 - (x/2)*10;
    std::chrono::milliseconds time(formula);
    std::this_thread::sleep_for(time);
    return false;
}

void Board::playSnake() {
    World world(width, height);
    world.play(*this);
}

void Board::OnTimer(wxCommandEvent &event) {
    Refresh();
}

NoFileException::NoFileException(const std::string &message) : SnakeException(message) {

}
