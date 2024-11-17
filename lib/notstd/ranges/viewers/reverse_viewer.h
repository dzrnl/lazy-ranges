#pragma once

#include "viewer.h"

namespace notstd::ranges::views {

template<typename Container>
class viewer<Container, reverse_type> {
  public:
    using base_type = Container;
    using container_iterator = typename base_type::container_iterator;
    using value_type = typename base_type::value_type;
    using iterator = base_type;

  private:
    static_assert(
            std::is_base_of_v<std::bidirectional_iterator_tag,
                    typename std::iterator_traits<container_iterator>::iterator_category> ||
            std::is_base_of_v<std::random_access_iterator_tag,
                    typename std::iterator_traits<container_iterator>::iterator_category>,
            "Container must have a bidirectional or random access iterator"
    );

    iterator pos_;

  public:
    explicit viewer(base_type base, flag_holder<reverse_type>)
            : pos_(base) {}

    explicit viewer(base_type base)
            : pos_(base) {}

    viewer begin() const {
        return viewer(pos_.rbegin());
    }

    viewer end() const {
        return viewer(pos_.rend());
    }

    viewer rbegin() const {
        return viewer(pos_.begin());
    }

    viewer rend() const {
        return viewer(pos_.end());
    }

    bool operator==(const viewer& other) const {
        return pos_ == other.pos_;
    }

    bool operator!=(const viewer& other) const {
        return !(*this == other);
    }

    viewer operator++() {
        --pos_;

        return *this;
    }

    viewer operator--() {
        ++pos_;

        return *this;
    }

    value_type operator*() const {
        return *pos_;
    }
};

} // notstd::ranges::views
