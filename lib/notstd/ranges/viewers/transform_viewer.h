#pragma once

#include "viewer.h"

namespace notstd::ranges::views {

template<typename Container>
class viewer<Container, transform_type> {
  public:
    using base_type = Container;
    using container_iterator = typename base_type::container_iterator;
    using value_type = typename base_type::value_type;
    using iterator = base_type;

  private:
    iterator pos_;

    std::function<value_type(value_type)> transform_function_;

  public:
    explicit viewer(base_type base, function_holder<value_type, value_type, transform_type> holder)
            : pos_(base), transform_function_(holder.function_) {}

    explicit viewer(base_type base, std::function<value_type(value_type)> function)
            : pos_(base), transform_function_(function) {}

    viewer begin() const {
        return viewer(pos_.begin(), transform_function_);
    }

    viewer end() const {
        return viewer(pos_.end(), transform_function_);
    }

    viewer rbegin() const {
        return viewer(pos_.rbegin(), transform_function_);
    }

    viewer rend() const {
        return viewer(pos_.rend(), transform_function_);
    }

    bool operator==(const viewer& other) const {
        return pos_ == other.pos_;
    }

    bool operator!=(const viewer& other) const {
        return !(*this == other);
    }

    viewer operator++() {
        ++pos_;

        return *this;
    }

    viewer operator--() {
        --pos_;

        return *this;
    }

    value_type operator*() const {
        return transform_function_(*pos_);
    }
};

} // notstd::ranges::views
