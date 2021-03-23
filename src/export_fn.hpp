#pragma once

#include <array>
#include <aument.h>

#include "value.hpp"

#define AU_EXPORT_FN(NAME, ARGS_ID, ARGS_LEN)                             \
    au::value NAME(std::array<au::value, ARGS_LEN> ARGS_ID);              \
    const int AU_EXPORTED_##NAME##_args = ARGS_LEN;                       \
    extern "C" au_value_t AU_EXPORTED_##NAME##_impl(                      \
        struct au_vm_thread_local *tl, const au_value_t *args) {          \
        (void)tl;                                                         \
        std::array<au::value, ARGS_LEN> my_args;                          \
        for (int i = 0; i < ARGS_LEN; i++) {                              \
            my_args[i] = args[i];                                         \
        }                                                                 \
        return NAME(std::move(my_args)).into_c_value();                   \
    }                                                                     \
    au::value NAME(std::array<au::value, ARGS_LEN> ARGS_ID)
