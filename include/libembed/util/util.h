/**
 * @file util.h
 * @author Gabriel Heinzer
 * @brief Various utility classes.
 */

#include <stdlib.h>
#include <cstdarg>
#include <memory>

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
                    SET_BIT(data, (bool)(*(objects_[bit])) << bit);
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
            void operator <<(size_t n) {
                uint64_t previousData = *this;
                *this = previousData << n;
            }

            /**
             * @brief Operator overload for shifting the buffer to the
             * right by @p n elements. Elements which are shifted out are
             * lost.
             * 
             * @param n The number of positions to shift the buffer
             * to the right.
             */
            void operator >>(size_t n) {
                uint64_t previousData = *this;
                *this = previousData >> n;
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
                    SET_BIT(data, (bool)(*(objects_[bit])) << bit);
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
            void operator <<(size_t n) {
                for(int i = 0; i < n; i++) { shift_once_left_(); }
            }

            /**
             * @brief Operator overload for shifting the buffer to the
             * right by @p n elements. Elements which are shifted out are
             * restored to the other end of the buffer.
             * 
             * @param n The number of positions to shift the buffer
             * to the right.
             */
            void operator >>(size_t n) {
                for(int i = 0; i < n; i++) { shift_once_right_(); }
            }
    };
}