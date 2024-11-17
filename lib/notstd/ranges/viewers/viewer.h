#pragma once

#include "../holders.h"

namespace notstd::ranges::views {

template<typename Container, holder_type Type = base_type>
class viewer {
  public:
    using base_type = Container;
    using container_iterator = typename Container::const_iterator;
    using value_type = typename base_type::value_type;
    using iterator = typename base_type::const_iterator;

  private:
    const base_type& base_;
    iterator pos_;

  public:
    explicit viewer(const base_type& base) : base_(base), pos_(base.cbegin()) {}

    explicit viewer(const base_type& base, iterator pos) : base_(base), pos_(pos) {}

    viewer begin() const {
        return viewer(base_, base_.cbegin());
    }

    viewer end() const {
        return viewer(base_, base_.cend());
    }

    viewer rbegin() const {
        return viewer(base_, --base_.cend());
    }

    viewer rend() const {
        return viewer(base_, --base_.cbegin());
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
