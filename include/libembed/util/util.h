/**
 * @file util.h
 * @author Gabriel Heinzer
 * @brief Various utility classes.
 */

#include <stdlib.h>
#include <cstdarg>
#include <memory>
#include <vector>
#include <any>

#ifndef LIBEMBED_UTIL_UTIL_H_
#define LIBEMBED_UTIL_UTIL_H_

/**
 * Various utility classes and templates.
 */
namespace embed::util {
    /**
     * @brief Class template for a pseudo-buffer allowing for any number of
     * any object to be grouped in a pseudo-buffer.
     * 
     * This requires the objects to have an `operator =` method allowing them to
     * have a value assigned to them. They also must support `operator bool` allowing
     * them to be read.
     * 
     * The first element in the buffer corresponds to the LSB of the buffer's binary
     * value; the last element corresponds to the MSB.
     * 
     * @tparam T The type of the objects you want to group in the buffer.
     * @tparam size The size of the buffer that you want to create.
     */
    template<typename T, size_t size>
    class PBuf {
        protected:
            /**
             * @brief Internal array of pointer pointing to the objects
             * contained in the buffer.
             */
            T* const objects_[size];

        public:
            /**
             * @brief Construct a new @ref PBuf object with the given objects.
             * The objects are passed by reference.
             * 
             * @tparam fT The parameter pack types used for the objects.
             * This must be equal to the base type @p T.
             * @param objects The objects you want to put into the buffer.
             */
            template<typename... fT>
            PBuf(fT&&... objects) : objects_{ std::addressof(objects)... } {
                static_assert(size <= 64, "The buffer size must not be greater than 64 elements.");
                static_assert(sizeof...(fT) == size, "Number of passed elements does not match the buffer size.");
            }

            /**
             * @brief Operator overload for accessing a specific item of the buffer.
             * 
             * @param index Index of the item you want to access.
             * @return Returns a reference to the element with the @p index from the buffer.
             */
            T& operator [](size_t index) {
                return *(objects_[index]);
            }

            /**
             * @brief Operator overload for binarily setting the value of the buffer.
             * The LSB corresponds to the first object, the MSB to the last object.
             * 
             * @param data The data you want to assign to the buffer's objects.
             */
            void operator =(uint64_t data) {
                for(size_t bit = 0; bit < size; bit++) {
                    *(objects_[bit]) = (bool)((data & (1 << bit)) >= 1);
                }
            }

            /**
             * @brief Conversion overload for `uint64_t`. Reads the binary value of
             * the buffer.
             * 
             * @return Returns the binary value of the buffer. The LSB corresponds
             * to the first element in the buffer, the MSB to the last element.
             */
            operator uint64_t() {
                uint64_t data = 0;
                for(size_t bit = 0; bit < size; bit++) {
                    data |= (bool)(*(objects_[bit])) << bit;
                }
                return data;
            }

            /**
             * @brief Operator overload for shifting the buffer to the
             * left by @p n elements. Elements which are shifted out are
             * lost.
             * 
             * @param n The number of positions to shift the buffer
             * to the left.
             */
            void operator <<(int n) {
                if(n < 0) this->operator>>(-n);
                else {
                    uint64_t previousData = *this;
                    *this = previousData << n;
                }
            }

            /**
             * @brief Operator overload for shifting the buffer to the
             * right by @p n elements. Elements which are shifted out are
             * lost.
             * 
             * @param n The number of positions to shift the buffer
             * to the right.
             */
            void operator >>(int n) {
                if(n < 0) this->operator<<(-n);
                else {
                    uint64_t previousData = *this;
                    *this = previousData >> n;
                }
            }
    };

    /**
     * @brief Class template for a pseudo-ring buffer allowing for any number of
     * any object to be grouped in a pseudo-ring buffer.
     * 
     * In contrast to @ref PBuf, this puts shifted-out bits to the end of the buffer.
     * 
     * This requires the objects to have an `operator =` method allowing them to
     * have a value assigned to them. They also must support `operator bool` allowing
     * them to be read.
     * 
     * The first element in the buffer corresponds to the LSB of the buffer's binary
     * value; the last element corresponds to the MSB.
     * 
     * @tparam T The type of the objects you want to group in the buffer.
     * @tparam size The size of the buffer that you want to create.
     */
    template<typename T, size_t size>
    class PRingBuf {
        protected:
            /**
             * @brief Internal array of pointer pointing to the objects
             * contained in the buffer.
             */
            T* const objects_[size];

            /**
             * @brief Internal function for shifting the buffer to the left
             * by one position.
             */
            void shift_once_left_() {
                uint64_t previousData = (uint64_t)(*this);
                bool highestBit = (*this)[size - 1];
                (*this) = previousData << 1;
                (*this)[0] = highestBit;
            }

            /**
             * @brief Internal function for shifting the buffer to the right
             * by one position.
             */
            void shift_once_right_() {
                uint64_t previousData = (uint64_t)(*this);
                bool lowestBit = (*this)[0];
                (*this) = previousData >> 1;
                (*this)[size - 1] = lowestBit;
            }

        public:
            /**
             * @brief Construct a new @ref PRingBuf object with the given objects.
             * The objects are passed by reference.
             * 
             * @tparam fT The parameter pack types used for the objects.
             * This must be equal to the base type @p T.
             * @param objects The objects you want to put into the buffer.
             */
            template<typename... fT>
            PRingBuf(fT&&... objects) : objects_{ std::addressof(objects)... } {
                static_assert(size <= 64, "The buffer size must not be greater than 64 elements.");
                static_assert(sizeof...(fT) == size, "Number of passed elements does not match the buffer size.");
            }

            /**
             * @brief Operator overload for accessing a specific item of the buffer.
             * 
             * @param index Index of the item you want to access.
             * @return Returns a reference to the element with the @p index from the buffer.
             */
            T& operator [](size_t index) {
                return *(objects_[index]);
            }

            /**
             * @brief Operator overload for binarily setting the value of the buffer.
             * The LSB corresponds to the first object, the MSB to the last object.
             * 
             * @param data The data you want to assign to the buffer's objects.
             */
            void operator =(uint64_t data) {
                for(size_t bit = 0; bit < size; bit++) {
                    *(objects_[bit]) = (bool)((data & (1 << bit)) >= 1);
                }
            }

            /**
             * @brief Conversion overload for `uint64_t`. Reads the binary value of
             * the buffer.
             * 
             * @return Returns the binary value of the buffer. The LSB corresponds
             * to the first element in the buffer, the MSB to the last element.
             */
            operator uint64_t() {
                uint64_t data = 0;
                for(size_t bit = 0; bit < size; bit++) {
                    data |= (bool)(*(objects_[bit])) << bit;
                }
                return data;
            }

            /**
             * @brief Operator overload for shifting the buffer to the
             * left by @p n elements. Elements which are shifted out are
             * restored to the other end of the buffer.
             * 
             * @param n The number of positions to shift the buffer
             * to the left.
             */
            void operator <<(int n) {
                if(n < 0) operator>>(-n);
                else {
                    for(int i = 0; i < n; i++) { shift_once_left_(); }
                }
            }

            /**
             * @brief Operator overload for shifting the buffer to the
             * right by @p n elements. Elements which are shifted out are
             * restored to the other end of the buffer.
             * 
             * @param n The number of positions to shift the buffer
             * to the right.
             */
            void operator >>(int n) {
                if(n < 0) operator<<(-n);
                else {
                    for(int i = 0; i < n; i++) { shift_once_right_(); }
                }
            }
    };

    //! Enumerator representing available edge types
    typedef enum {
        //! Rising edge
        EDGE_RISING,
        //! Falling edge
        EDGE_FALLING,
        //! Both rising and falling edge
        EDGE_BOTH
    } EdgeType;

    // Pre-declaration of EdgeDetectorGroup
    struct EdgeDetectorGroup;

    /**
     * @brief Base class for @ref EdgeDetector.
     * 
     * Don't use this class directly, use @ref EdgeDetector instead.
     */
    class EdgeDetector_Base {
        protected:
            //! Protected constructor for the @ref EdgeDetector_Base class
            EdgeDetector_Base() { };

        public:
            /**
             * @brief Await an edge with the given @p edgeType.
             * 
             * @param edgeType The edge type to await. This must be one of @ref util::EdgeType.
             * @param debounceDelay Delay for debouncing buttons in milliseconds.
             */
            void wait(EdgeType edgeType = EDGE_FALLING, const uint32_t debounceDelay = 2);

            /**
             * @brief Internal initialization function for the edge detection.
             * 
             * Allocates any needed objects on the heap and returns something.
             * 
             * Called at the entry of @ref wait().
             * 
             * @return Returns any pointers to the allocated objects. This will
             * be passed to @ref __edgeDetectionCycle and @ref __deinitEdgeDetection.
             */
            virtual std::any __initEdgeDetection() { return 0; };

            /**
             * @brief Internal edge detection function.
             * 
             * Takes a state object as an argument @p statePtr and does one edge
             * detection cycle. This function must not wait on an edge, but just
             * return `true` if an edge was just detected or `false` if no edge
             * was detected-
             * 
             * @param edgeType Edge type to detect.
             * @param statePtr Pointer to the state object initialized by @ref __initEdgeDetection.
             * @return Returns a boolean specifying whether an edge was just detected or not. 
             */
            virtual bool __edgeDetectionCycle(EdgeType edgeType, std::any statePtr) { return false; };

            /**
             * @brief Internal deinitialization function.
             * 
             * Deallocates any objects allocated in @ref __initEdgeDetection.
             * 
             * @param statePtr Pointer to the state object created by @ref __initEdgeDetection.
             */
            virtual void __deinitEdgeDetection(std::any statePtr) {};

            /**
             * @brief Operator overload for the `|` operator.
             * 
             * This allows for easy creation of edge detector groups.
             * 
             * @param ep2 Pointer to the second @ref EdgeDetector_Base object.
             * @return Returns a newly-created @ref EdgeDetectorGroup.
             */
            EdgeDetectorGroup operator |(EdgeDetector_Base& ep2);
    };

    /**
     * @brief Edge detector class which supports detecting rising
     * and falling edges, e.g. on a GPIO pin.
     * 
     * @tparam T The type you want to detect the edges from.
     */
    template <typename T>
    class EdgeDetector : public EdgeDetector_Base {
        protected:
            //! Internal state structure
            class State {
                public:
                    //! Whether the @ref previousState variable is initialized
                    bool initialized : 1;
                    //! State of the polling target at the end of the previous call
                    bool previousState : 1;

                    //! Constructs a new @ref State object
                    State() : initialized(false) {};
            };

            //! Reference to the polling target object
            T& pollTarget_;

        public:
            /**
             * @brief Construct a new Edge Detector object.
             * 
             * @param pollTarget The target object you want to poll for edges.
             */
            EdgeDetector(T& pollTarget) : pollTarget_(pollTarget) {}

            std::any __initEdgeDetection() override {
                return new State();
            }

            bool __edgeDetectionCycle(EdgeType edgeType, std::any statePtr) override {
                State& state = *(std::any_cast<State*>(statePtr));
                if(!state.initialized) {
                    state.previousState = (bool)pollTarget_;
                    state.initialized = true;
                }
                bool edgeDetected = false;
                bool currentState = (bool)pollTarget_;
                switch(edgeType) {
                    case EDGE_RISING:
                        if(!state.previousState && currentState) edgeDetected = true;
                        break;

                    case EDGE_FALLING:
                        if(state.previousState && !currentState) edgeDetected = true;
                        break;

                    case EDGE_BOTH:
                        if(state.previousState != currentState) edgeDetected = true;
                        break;
                }
                state.previousState = currentState;
                return edgeDetected;
            }

            void __deinitEdgeDetection(std::any statePtr) override {
                State* state = std::any_cast<State*>(statePtr);
            }
    };

    /**
     * @brief Group of two @ref EdgeDetector.
     * 
     * Acts as one, but accepts edges from both sub-edge detectors.
     */
    class EdgeDetectorGroup : public EdgeDetector_Base {
        protected:
            //! @ref EdgeDetector_Base object 1 to monitor
            EdgeDetector_Base& ep1_;
            //! @ref EdgeDetector_Base object 2 to monitor.
            EdgeDetector_Base& ep2_;

            //! Internal polling state structure
            typedef struct {
                //! State object of the first @ref EdgeDetector
                std::any ep1_statePtr;
                //! State object of the second @ref EdgeDetector
                std::any ep2_statePtr;
            } State;

        public:
            /**
             * @brief Construct a new group of @ref EdgeDetector objects.
             * 
             * @param ep1 A reference to the first @ref EdgeDetector detector
             * @param ep2 A reference to the second @ref EdgeDetector object.
             */
            EdgeDetectorGroup(EdgeDetector_Base& ep1, EdgeDetector_Base& ep2) : ep1_(ep1), ep2_(ep2) { }
            
            std::any __initEdgeDetection() override;
            bool __edgeDetectionCycle(EdgeType edgeType, std::any statePtr) override;
            void __deinitEdgeDetection(std::any statePtr) override;
    };
}

#endif /* LIBEMBED_UTIL_UTIL_H_ */