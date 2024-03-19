#pragma once

template<typename T>
class Observer {
    public:
        virtual void update(const T& data) = 0;
        virtual ~Observer() {}
};

