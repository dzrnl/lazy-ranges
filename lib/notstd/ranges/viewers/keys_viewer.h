#pragma once

#include "viewer.h"

namespace notstd::ranges::views {

template<typename Container>
class viewer<Container, keys_type> {
  public:
    using base_type = Container;
    using container_iterator = typename base_type::container_iterator;
    using value_type = std::remove_const_t<typename base_type::value_type::first_type>;
    using iterator = base_type;

  private:
    iterator pos_;

  public:
    explicit viewer(base_type base, flag_holder<keys_type>)
            : pos_(base) {}

    explicit viewer(base_type base)
            : pos_(base) {}

    viewer begin() const {
        return viewer(pos_.begin());
    }

    viewer end() const {
        return viewer(pos_.end());
    }

    viewer rbegin() const {
        return viewer(pos_.rbegin());
    }

    viewer rend() const {
        return viewer(pos_.rend());
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
        return (*pos_).first;
    }
};

} // notstd::ranges::views
