#pragma once

#include "viewer.h"

namespace notstd::ranges::views {

template<typename Container>
class viewer<Container, filter_type> {
  public:
    using base_type = Container;
    using container_iterator = typename base_type::container_iterator;
    using value_type = typename base_type::value_type;
    using iterator = base_type;

  private:
    iterator pos_;

    std::function<bool(value_type)> filter_function_;

  public:
    explicit viewer(base_type base, function_holder<value_type, bool, filter_type> holder)
            : pos_(base), filter_function_(holder.function_) {}

    explicit viewer(base_type base, std::function<bool(value_type)> function)
            : pos_(base), filter_function_(function) {}

    viewer begin() const {
        iterator pos = pos_.begin();
        while (pos != pos.end() && !filter_function_(*pos)) {
            ++pos;
        }

        return viewer(pos, filter_function_);
    }

    viewer end() const {
        return viewer(pos_.end(), filter_function_);
    }

    viewer rbegin() const {
        iterator pos = pos_.rbegin();
        while (pos != pos_.rend() && !filter_function_(*pos)) {
            --pos;
        }
        return viewer(pos, filter_function_);
    }

    viewer rend() const {
        return viewer(pos_.rend(), filter_function_);
    }

    bool operator==(const viewer& other) const {
        return pos_ == other.pos_;
    }

    bool operator!=(const viewer& other) const {
        return !(*this == other);
    }

    viewer operator++() {
        ++pos_;
        while (pos_ != pos_.end() && !filter_function_(*pos_)) {
            ++pos_;
        }

        return *this;
    }

    viewer operator--() {
        --pos_;
        while (pos_ != pos_.rend() && !filter_function_(*pos_)) {
            --pos_;
        }

        return *this;
    }

    value_type operator*() const {
        return *pos_;
    }
};

} // notstd::ranges::views
