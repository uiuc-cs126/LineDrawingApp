#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "LineDrawingApp.h"

const std::string LineDrawingApp::kFrameCountTag = "Frame Count: ";

void prepareSettings(LineDrawingApp::Settings* settings) {
    settings->setMultiTouchEnabled(false);
}

void LineDrawingApp::mouseDown(ci::app::MouseEvent event) {
    if (points_.empty()) {
        // For the first line being drawn, add two points to the mPoints vector.
        // The first point acts as a fixed starting point for the line.
        // The second point is the endpoint of the line,
        // which moves with the mouse until it is released (see mouseDrag).
        points_.push_back(event.getPos());
        points_.push_back(event.getPos());
    } else {
        // For every line after the first, we use the endpoint of the previous line
        // as the starting point. Since this starting point is already in the mPoints vector,
        // we only need to add one new point to the mPoints vector.
        points_.push_back(event.getPos());
    }
}

void LineDrawingApp::mouseDrag(ci::app::MouseEvent event) {
    // Updates the endpoint of the line being drawn to the location of the mouse.
    points_.back() = event.getPos();
}

void LineDrawingApp::keyDown(ci::app::KeyEvent event) {
    if (event.getChar() == 'f') {
        // Toggle full screen when the user presses the 'f' key.
        setFullScreen(!isFullScreen());
    } else if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
        // Clear the list of points when the user presses the space bar.
        points_.clear();
    } else if (event.getCode() == ci::app::KeyEvent::KEY_ESCAPE) {
        // Exit full screen, or quit the application, when the user presses the ESC key.
        if (isFullScreen()) {
            setFullScreen(false);
        } else {
            quit();
        }
    }
}

void LineDrawingApp::setup() {
    // When the app is initialized, we set the frame count to zero.
    frame_count_ = 0;
}

void LineDrawingApp::update() {
    // The frame count will be incremented before every call to 'draw'.
    // [i.e. the user will first see a frame count of 1, then 2, etc.]
    frame_count_++;
}

void LineDrawingApp::draw() {
    // Clear the contents of the window. This call will clear
    // both the color and depth buffers.
    ci::gl::clear(ci::Color::gray( 0.1f ));

    // Set the current draw color to orange by setting values for
    // red, green and blue directly. Values range from 0 to 1.
    // See also: gl::ScopedColor
    ci::gl::color(1.0f, 0.5f, 0.25f);

    // We're going to draw a line through all the points in the list
    // using a few convenience functions: 'begin' will tell OpenGL to
    // start constructing a line strip, 'vertex' will add a point to the
    // line strip and 'end' will execute the draw calls on the GPU.
    ci::gl::begin(GL_LINE_STRIP);
    for (const ci::vec2 &point : points_) {
        ci::gl::vertex(point);
    }

    // Lastly, we draw the frame count text at the top left of the screen.
    ci::gl::drawString(kFrameCountTag + std::to_string(frame_count_), ci::vec2(10.0f, 10.0f));
    ci::gl::end();
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(LineDrawingApp, ci::app::RendererGl, prepareSettings)