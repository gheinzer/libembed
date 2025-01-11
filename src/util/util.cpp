#include <libembed/util/util.h>
#include <libembed/hal/clock.h>
#include <libembed/util/coroutines.h>

using namespace embed;

util::EdgeDetectorGroup util::EdgeDetector_Base::operator|(EdgeDetector_Base& ep2) {
    return EdgeDetectorGroup(*this, ep2);
}

void util::EdgeDetector_Base::wait(EdgeType edgeType, uint32_t debounceDelay)  {
    std::any statePtr = __initEdgeDetection();
    bool edgeDetected = false;
    while(!edgeDetected) {
        edgeDetected = __edgeDetectionCycle(edgeType, statePtr);

        if(debounceDelay) clock::delay(debounceDelay);
        else yield;
    }
    __deinitEdgeDetection(statePtr);
}

// *** EdgeDetectorGroup ***
std::any util::EdgeDetectorGroup::__initEdgeDetection() {
    State* state = new State();
    state->ep1_statePtr = ep1_.__initEdgeDetection();
    state->ep2_statePtr = ep2_.__initEdgeDetection();
    return state;
}

bool util::EdgeDetectorGroup::__edgeDetectionCycle(EdgeType edgeType, std::any statePtr) {
    State* state = std::any_cast<State*>(statePtr);

    bool edge1 = ep1_.__edgeDetectionCycle(edgeType, state->ep1_statePtr);
    bool edge2 = false;
    if(!edge1) {
        edge2 = ep2_.__edgeDetectionCycle(edgeType, state->ep2_statePtr);
    }
    return edge1 || edge2;
}

void util::EdgeDetectorGroup::__deinitEdgeDetection(std::any statePtr) {
    State* state = std::any_cast<State*>(statePtr);
    ep1_.__deinitEdgeDetection(state->ep1_statePtr);
    ep2_.__deinitEdgeDetection(state->ep2_statePtr);
    delete state;
}