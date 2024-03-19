#pragma once
#include <vector>
#include <mutex>
#include "observer.hpp"

template<typename T>
class Distributor {

    std::vector<Observer<T>*> observers;
    mutable std::mutex mutex;

public:

    void add_observer(Observer<T>* observer) {
        std::lock_guard<std::mutex> lock(mutex);
        observers.push_back(observer);
    }

    void remove_observer(Observer<T>* observer) {
        std::lock_guard<std::mutex> lock(mutex);
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:

    void notify_observers(const T& data) const {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& observer : observers) {
            observer->update(data);
        }
    }

};

