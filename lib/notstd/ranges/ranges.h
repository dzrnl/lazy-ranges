#pragma once

#include "holders.h"
#include "viewers/viewer.h"
#include "viewers/transform_viewer.h"
#include "viewers/filter_viewer.h"
#include "viewers/take_viewer.h"
#include "viewers/drop_viewer.h"
#include "viewers/reverse_viewer.h"
#include "viewers/keys_viewer.h"
#include "viewers/values_viewer.h"

namespace notstd {

namespace ranges::views {

template<typename T>
function_holder<T, T, transform_type> transform(std::function<T(T)> function) {
    return function_holder<T, T, transform_type>(function);
}

template<typename Func>
auto transform(Func func) {
    return transform(std::function(func));
}

template<typename T>
function_holder<T, bool, filter_type> filter(std::function<bool(T)> function) {
    return function_holder<T, bool, filter_type>(function);
}

template<typename Func>
auto filter(Func func) {
    return filter(std::function(func));
}

value_holder<size_t, take_type> take(size_t value) {
    return value_holder<size_t, take_type>(value);
}

value_holder<size_t, drop_type> drop(size_t value) {
    return value_holder<size_t, drop_type>(value);
}

flag_holder<reverse_type> reverse() {
    return flag_holder<reverse_type>(true);
}

flag_holder<keys_type> keys() {
    return flag_holder<keys_type>(true);
}

flag_holder<values_type> values() {
    return flag_holder<values_type>(true);
}

template<typename Container, holder_type ViewerType, typename Input, typename Output, holder_type Type>
viewer<viewer<Container, ViewerType>, Type> operator|(viewer<Container, ViewerType> vwr,
                                                      function_holder<Input, Output, Type> holder) {
    return viewer<viewer<Container, ViewerType>, Type>(vwr, holder);
}

template<typename Container, typename Input, typename Output, holder_type Type>
viewer<viewer<Container, base_type>, Type> operator|(const Container& container,
                                                     function_holder<Input, Output, Type> holder) {
    viewer<Container, base_type> base(container);

    return viewer<viewer<Container, base_type>, Type>(base, holder);
}

template<typename Container, holder_type ViewerType, typename T, holder_type Type>
viewer<viewer<Container, ViewerType>, Type> operator|(viewer<Container, ViewerType> vwr,
                                                      value_holder<T, Type> holder) {
    return viewer<viewer<Container, ViewerType>, Type>(vwr, holder);
}

template<typename Container, typename T, holder_type Type>
viewer<viewer<Container, base_type>, Type> operator|(const Container& container,
                                                     value_holder<T, Type> holder) {
    viewer<Container, base_type> base(container);

    return viewer<viewer<Container, base_type>, Type>(base, holder);
}

} // ranges::views

namespace views = ranges::views;

} // notstd
