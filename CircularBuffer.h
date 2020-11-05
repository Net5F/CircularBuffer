#pragma once

#include <array>
#include <stdexcept>

namespace AM {

/**
 * @class CircularBuffer
 *
 * @brief A simple, exceptionally not thread-safe circular buffer.
 *
 * Positively indexes the previous values (e.g. if you pushed 3 values, they will be at
 * arr[0], arr[1], and arr[2], with arr[0] being the most recent).
 */
template <typename T, std::size_t maxSize> class CircularBuffer {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;


    CircularBuffer()
    : valueArr{}
    , head(arrLen - 1)
    {
    }

    CircularBuffer(value_type initialValue)
    : head(arrLen - 1)
    {
        valueArr.fill(initialValue);
    }

    CircularBuffer(const CircularBuffer& other)
    : head(other.head)
    {
        valueArr = other.valueArr;
    }

    CircularBuffer& operator=(const CircularBuffer& other)
    {
        // Check for self assignment.
        if (this != &other) {
            head = other.head;
            valueArr = other.valueArr;
        }

        return *this;
    }

    /**
     * Pushes elements into the buffer.
     *
     * @param value  The value to push.
     * @post value has been copied to index 0.
     *       The oldest value has been written over.
     *       All other previous values are found at their old index + 1.
     */
    void push(const value_type value)
    {
        // Move the head, overwriting any old data.
        head = decrement(head);

        // Write the value
        valueArr[head] = value;
    }

    template <class... Args>
    void emplace_ctor(Args&&... args) {
        // Move the head, overwriting any old data.
        head = decrement(head);

        // Write the value
        valueArr[head] = value_type(args...);
    }

    template <class... Args>
    void emplace_aggregate(Args&&... args) {
        // Move the head, overwriting any old data.
        head = decrement(head);

        // Write the value
        valueArr[head] = {args...};
    }

    /**
     * Wrapping access to the buffer.
     * @throws std::out_of_range if index is larger than maxSize.
     */
    reference operator[](size_type index)
    {
        if (index > arrLen) {
            throw std::out_of_range("index larger than maxSize.");
        }

        size_type requestedIndex = increment(head, index);
        return valueArr[requestedIndex];
    }
    const_reference operator[](size_type index) const
    {
        if (index > arrLen) {
            throw std::out_of_range("index larger than maxSize.");
        }

        size_type requestedIndex = increment(head, index);
        return valueArr[requestedIndex];
    }

    /**
     * Returns the length of the underlying array.
     */
    size_type size() const
    {
        return arrLen;
    }

    /**
     * Fills all elements in the underlying container with the given value.
     */
    void fill(const value_type value)
    {
        valueArr.fill(value);
    }

private:
    /**
     * The length of the underlying array.
     */
    static constexpr size_type arrLen = maxSize;

    /** The data structure that holds the queue's elements. */
    std::array<value_type, arrLen> valueArr;

    /**
     * Index of the most recently inserted element.
     * Starts at the end of the underlying array and gets decremented during every push.
     */
    size_type head;

    //----------------------------------------------------------------------------
    // Convenience Functions
    //----------------------------------------------------------------------------
    /**
     * Returns the index, incremented by amount. Accounts for wrap-around.
     */
    size_type increment(const size_type index, const size_type amount) const
    {
        return (index + amount) % arrLen;
    }

    /**
     * Returns the previous index. Accounts for wrap-around.
     * The returned value is undefined for indices > arrLen.
     */
    size_type decrement(const size_type index) const
    {
        return (index + arrLen - 1) % arrLen;
    }
};

} // namespace AM
