#include <vector>
#include <list>

template <typename V>
class FirstRingBuffer {
public:
    FirstRingBuffer(const size_t size) 
        : m_Data(size)
        , m_Size(size)
        , m_Head(0)
        , m_Tail(0) {
        if (size == 0) {
            throw std::out_of_range("Empty buffer initialization");
        }
    };

    void push(const V& value) {
        m_Data[m_Head] = value;
        if (m_IsFull) {
            m_Tail = (++m_Tail) % m_Size;
        }
        m_Head = (++m_Head) % m_Size;
        m_IsFull = (m_Head == m_Tail);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Buffer is empty");
        }

        m_Tail = (++m_Tail) % m_Size;
        m_IsFull = false;
    }

    const V& top() {
        return m_Data[m_Tail];
    }

    bool empty() {
        return !m_IsFull && (m_Head == m_Tail);
    }

private:
    std::size_t m_Tail;
    std::size_t m_Head;
    const std::size_t m_Size;

    bool m_IsFull;

    std::vector<V> m_Data;
};

template <typename V>
class SecondRingBuffer {
public:
    SecondRingBuffer(const size_t size)
        : m_Size(size) {
            if (size == 0) {
                throw std::out_of_range("Empty buffer initialization");
            }
        };

    void push(const V& value) {
        m_Data.emplace_back(value);
        if (m_Data.size() > m_Size) {
            m_Data.pop_front();
        }
    }

    void pop() {
        if (m_Data.empty()) {
            throw std::out_of_range("Buffer is empty");
        }

        m_Data.pop_front();
    }

    const V& top() {
        return m_Data.front();
    }

    bool empty() {
        return m_Data.empty();
    }

private:
    std::list<V> m_Data;
    const size_t m_Size;
};