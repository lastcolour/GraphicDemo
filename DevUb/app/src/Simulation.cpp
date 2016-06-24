#include "Simulation.hpp"
#include "glUtils.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Hardcoded values

const char* WORLD_FRAG = "shaders/singleColor.glsl";
const char* WORLD_VERT = "shaders/worldVert.glsl";

const char* POINT_FRAG = "shaders/singleColor.glsl";
const char* POINT_VERT = "shaders/pointVert.glsl";
const int   SIDE_COUNT = 24;
const int   POINTS_COUNT = SIDE_COUNT + 2; // Draw as triangle fun

const char* UNI_RADIUS = "vRadius";
const char* UNI_COLOR  = "fColor";
const char* UNI_CENTER = "vCenter";

const float POINT_RADIUS = 0.1f;

Simulation::Simulation(Physics* physics) :
    physicsPtr(physics),
    pointDraw(),
    worldDraw(),
    timePoint(0.f) {

    assert(physicsPtr != nullptr && "Ivalid physics");
}

Simulation::~Simulation() {
}

void Simulation::setViewPort(int width, int height) {
    glViewport(0, 0, width, height);
}

void Simulation::update(float timeDelta) {
    timePoint += timeDelta;
    trajectory.push_back(physicsPtr->getPointLoc(timePoint));
}

void Simulation::restart() {
}

void Simulation::drawPoint(const Point2d& point) {
    Point2d normP = normilze(point);
    glUseProgram(pointDraw.progID);
    glBindVertexArray(pointDraw.vaoID);
    glUniform1f(glGetUniformLocation(pointDraw.progID, UNI_RADIUS), POINT_RADIUS);
    glUniform4f(glGetUniformLocation(pointDraw.progID, UNI_COLOR), 0.4f, 0.f, 0.f, 1.f); // circle color
    glUniform2f(glGetUniformLocation(pointDraw.progID, UNI_CENTER), normP.x, normP.y);

    glDrawArrays(GL_TRIANGLE_FAN, 0, POINTS_COUNT);

    glBindVertexArray(0);
}

Point2d Simulation::normilze(const Point2d& p) {
    // locate point in world 
    Point2d tPoint(0.f, 0.f);
    tPoint.x = (1.f - POINT_RADIUS * 2.f) * (2.f * p.x / worldLen - 1.f);
    tPoint.y = (1.f - POINT_RADIUS * 2.f) * (2.f * p.y / worldHeight - 1.f);
    return tPoint;
}

void Simulation::drawWorld() {
}

void Simulation::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPoint(trajectory.back());
    drawWorld();
}

bool Simulation::init() {
    assert(physicsPtr->isValid() && "Invalid physic for simulation");

    worldHeight = physicsPtr->getFlyHeight();
    worldLen = physicsPtr->getFlyLen();

    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    // quad
    std::vector<GLfloat> tQuad = {
       -1.f, -1.f,  1.f, -1.f,   1.f,  1.f,
        1.f,  1.f, -1.f,  1.f,  -1.f, -1.f,
    };
    worldDraw = createGLDraw(WORLD_VERT, WORLD_FRAG, tQuad);
    // circle
    pointDraw = createGLDraw(POINT_VERT, POINT_FRAG, 
        generateCircle(SIDE_COUNT)
    );
    if (!worldDraw.isValid()) {
        return false;
    }
    if (!pointDraw.isValid()) {
        return false;
    }
    CHECK_GL_STATUS("init()");
    return true;
}