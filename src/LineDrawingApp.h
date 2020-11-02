//
// Created by stevenp6 on 7/24/2020.
//

#ifndef BASICAPP_LINEDRAWINGAPP_H
#define BASICAPP_LINEDRAWINGAPP_H

// We'll create a new Cinder Application by deriving from the App class.
class LineDrawingApp : public ci::app::App {
 public:
    // Cinder will call 'setup' when the app is first created or initialized.
    void setup() override;

    // Cinder will call 'update' before each call to 'draw'.
    void update() override;

    // Cinder will call 'draw' each time the contents of the window need to be redrawn.
    void draw() override;

    // Cinder will call 'mouseDown' when the user presses down on one of the mouse buttons.
    // See also: mouseMove, mouseUp and mouseWheel.
    void mouseDown(ci::app::MouseEvent event) override;

    // Cinder will call 'mouseDrag' when the user moves the mouse while holding one of its buttons.
    void mouseDrag(ci::app::MouseEvent event) override;

    // Cinder will call 'keyDown' when the user presses a key on the keyboard.
    // See also: keyUp.
    void keyDown(ci::app::KeyEvent event) override;

    // In Cinder, setup() is called once at the start, and then update() and draw() are called in an infinite loop.
    // So, the order of function calls in a Cinder app looks like the following:
    // setup() -> update() -> draw() -> update() -> draw() -> update() -> draw() -> etc.
 private:
    std::vector<ci::vec2> points_;
    int frame_count_;
    const static std::string kFrameCountTag;
};

#endif //BASICAPP_LINEDRAWINGAPP_H