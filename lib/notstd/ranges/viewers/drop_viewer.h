#pragma once

#include "viewer.h"

namespace notstd::ranges::views {

template<typename Container>
class viewer<Container, drop_type> {
  public:
    using base_type = Container;
    using container_iterator = typename base_type::container_iterator;
    using value_type = typename base_type::value_type;
    using iterator = base_type;

  private:
    iterator pos_;

    const size_t drop_count_;

  public:
    explicit viewer(base_type base, value_holder<size_t, drop_type> holder)
            : pos_(base), drop_count_(holder.value_) {}

    explicit viewer(base_type base, size_t value)
            : pos_(base), drop_count_(value) {}

    viewer begin() const {
        iterator pos = pos_.begin();
        for (size_t i = 0; pos != pos_.end() && i < drop_count_; ++i) {
            ++pos;
        }

        return viewer(pos, drop_count_);
    }

    viewer end() const {
        return viewer(pos_.end(), drop_count_);
    }

    viewer rbegin() const {
        return --end();
    }

    viewer rend() const {
        return --begin();
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
        return *pos_;
    }
};

} // notstd::ranges::views
