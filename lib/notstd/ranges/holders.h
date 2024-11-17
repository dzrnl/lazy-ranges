#pragma once

#include <functional>

namespace notstd::ranges::views {

enum holder_type {
    base_type,
    transform_type,
    filter_type,
    take_type,
    drop_type,
    reverse_type,
    keys_type,
    values_type
};

template<typename Input, typename Output, holder_type>
class function_holder {
  public:
    explicit function_holder(std::function<Output(Input)> function) : function_(function) {}

    template<typename Container, holder_type ViewerType>
    friend class viewer;

  private:
    std::function<Output(Input)> function_;
};

template<typename T, holder_type>
class value_holder {
  public:
    explicit value_holder(T value) : value_(value) {}

    template<typename Container, holder_type ViewerType>
    friend class viewer;

  private:
    T value_;
};

template<holder_type Type>
using flag_holder = value_holder<bool, Type>;

} // notstd::ranges::views
